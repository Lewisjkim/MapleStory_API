#include "pch.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CUIMgr.h"
#include "CEventMgr.h"
#include "CSound.h"

CEngine::CEngine()	:
	m_hMainWnd(nullptr),
	m_hDC(nullptr),
	m_ptResolution{},
	m_arrPen{},
	m_pMemTex(nullptr)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);
	for (UINT i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CEngine::init(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;
	m_hDC = GetDC(m_hMainWnd);

	// 윈도우 크기 설정
	ChangeWindowSize(_iWidth, _iHeight);

	//Pen 생성
	CreatePenBrush();

	//Manager들 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CLevelMgr::GetInst()->init(); 

	
	CSound* pSound = CResMgr::GetInst()->LoadSound(L"BGM", L"sound\\BGM\\Title.wav");
	pSound->SetPosition(0);
	pSound->PlayToBGM();
}

void CEngine::progress()
{
	tick();
	render();
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CCamera::GetInst()->tick();
	CLevelMgr::GetInst()->tick();
	CCollisionMgr::GetInst()->tick();
	/*CUIMgr::GetInst()->tick();*/
}

void CEngine::render()
{
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);//왜 texture dc로 지우는가?***
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
	/*CTimeMgr::GetInst()->render();*/
	
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CEngine::ChangeWindowSize(UINT _iWidth, UINT _iHeight)
{
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;


	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	HMENU hMenu = GetMenu(m_hMainWnd);

	if (nullptr != hMenu)
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	else
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);


	// 백버퍼가 없으면 생성
	if (nullptr == m_pMemTex)
	{
		// 백버퍼 용 비트맵 제작
		m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}

	// 백버퍼가 있으면, 변경된 해상도에 맞추어 크기 재조정
	else
	{
		m_pMemTex->Resize(m_ptResolution.x, m_ptResolution.y);
	}
}
