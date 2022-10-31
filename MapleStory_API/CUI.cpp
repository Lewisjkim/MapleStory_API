#include "pch.h"
#include "CUI.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTexture.h"


CUI::CUI() :
	m_pParentUI(nullptr),
	m_pIdleTex(nullptr),
	m_bLbtnDown(false),
	m_bMouseOn(false),
	m_bCmrAfctd(false)
{
}

CUI::CUI(const CUI& _other)
	: CObj(_other)
	, m_pParentUI(nullptr)
	, m_pIdleTex(_other.m_pIdleTex)
	, m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bCmrAfctd(_other.m_bCmrAfctd)
{
	for (size_t i = 0; i < _other.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::tick()
{
	//위치 계산
	m_vFinalPos = GetPos();

	if (m_pParentUI)
	{
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	MouseOnCheck();//마우스 on 체크

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}
}

void CUI::render(HDC _dc)
{
	HPEN hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC 의 기존 펜과 브러시를 새로 가져온 것들로 대체한다
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = GetPos();//본인 위치
	if (m_bCmrAfctd)//카메라에 영향 받아 위치가 달라진다면
	{
		CCamera::GetInst()->GetRenderPos(vPos);
	}

	Vec2 vScale = GetScale();//본인 크기

	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));//Left top과 본인의 크기 만큼

	// DC 의 GDI 오브젝트들을 기존의 펜과 브러시로 되돌린다.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);


	render_childUI(_dc);
}

void CUI::render_childUI(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::SetIdleTex(CTexture* _pTex)
{
	m_pIdleTex = _pTex;

	if (nullptr != m_pIdleTex)//Texture객체가 비어있지 않다면
	{
		Vec2 vScale = Vec2((float)m_pIdleTex->Width(), (float)m_pIdleTex->Height());//객체의 가로와 , 세로를 vScale에 설정하고
		SetScale(vScale);//크기를 설정해라
	}
}

void CUI::MouseOnCheck()
{
	//마우스 최종 위치 확인
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;
	//카메라 영향을 받는다면
	if (m_bCmrAfctd)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);//실제좌표로 바꾸어준다
	}

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}