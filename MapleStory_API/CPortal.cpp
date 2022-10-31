#include "pch.h"
#include "CPortal.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"

#include "CCollider.h"


#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"



CPortal::CPortal()	:
	m_pTex(nullptr)
	
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(80.f, 100.f));
	m_pTex = CResMgr::GetInst()->FindTexture(L"Portal");
	
}

CPortal::~CPortal()
{

}

void CPortal::tick()
{
	
	



	// 부모 오브젝트의 Tick 도 실행시킨다(Component Tick 호출)
	CObj::tick();
}

void CPortal::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();


	static float fRatio = 0.f;
	static float Dir = 1.f;
	fRatio += DT * Dir * 8.f;

	if (1.f < fRatio)
	{
		fRatio = 1.f;
		Dir = -1.f;
	}
	else if (fRatio < 0.f)
	{
		fRatio = 0.f;
		Dir = 1;
	}

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * fRatio);

	AlphaBlend(_dc
		, (int)(vPos.x - m_pTex->Width() / 2.f)
		, (int)(vPos.y - m_pTex->Height() / 2.f)
		, m_pTex->Width()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0, 0
		, m_pTex->Width()
		, m_pTex->Height()
		, tBlend);

	CObj::render(_dc);
}


void CPortal::BeginOverlap(CCollider* _pOther)
{
	int a = 0;
}

void CPortal::OnOverlap(CCollider* _pOther)
{
	int a = 0;
}

void CPortal::EndOverlap(CCollider* _pOther)
{
	int a = 0;
}
