#include "pch.h"
#include "CBossStage.h"
#include "CResMgr.h"
#include "CTexture.h"

CBossStage::CBossStage() :
	m_pTex(nullptr)
{
	//텍스쳐 불러와 설정하기
	m_pTex = CResMgr::GetInst()->FindTexture(L"BossBG");
}

CBossStage::~CBossStage()
{
}


void CBossStage::tick()
{
	CObj::tick();
}

void CBossStage::render(HDC _dc)
{
	//해당 BG를 그릴 위치와 사이즈
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	BitBlt(_dc,								//hdc Dest
		(int)vPos.x,	//출력될 X 시작위치
		(int)vPos.y,	//출력될 Y 시작위치
		m_pTex->Width(),					//이미지의 가로길이
		m_pTex->Height(),					//이미지의 세로길이
		m_pTex->GetDC(),					//hdc Src
		0,									//출력될 X 시작위치 기준으로 X지점
		0,									//출력될 Y 시작위치 기준으로 Y지점
		SRCCOPY);


}

