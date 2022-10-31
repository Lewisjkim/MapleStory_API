#include "pch.h"
#include "CWood.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CSAI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidbody.h"

CWood::CWood()
	: m_iHP(3)
	, m_pTarget(nullptr)
	, m_pTex(nullptr)
	, m_tInfo{}
	, m_fSpeed(10.f)
{
	
	SetScale(Vec2(100.f, 100.f));


	// 충돌체 설정
	CreateCollider();
	GetCollider()->SetScale(Vec2(62.f, 51.f));
	m_pTex = CResMgr::GetInst()->FindTexture(L"CWood");

	m_tInfo.m_fSpeed = 100.f;
	m_tInfo.m_fDetectRange = 300.f;

	// AI 설정
	CreateAI();
	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->ChangeState(L"Trace");

	CreateRigidbody();
	//GetRigidbody()->SetFriction(100.f);//마찰력
	GetRigidbody()->SetGravity(true);//중력 켜기
	GetRigidbody()->SetGravityAccel(100);//중력 가속도 설정
	GetRigidbody()->SetGravityVelocityLimit(1000.f);//중력제한속도
	
}

CWood::~CWood()
{
}

void CWood::tick()
{
	/*if (IsValid(m_pTarget))
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		m_pTarget->SetName(L"Player");
		Vec2 vPos = GetPos();

		Vec2 vDir = vTargetPos - vPos;
		vDir.Normalize();

		vPos.x += vDir.x * 100.f * DT;
		vPos.y += vDir.y * 100.f * DT;

		SetPos(vPos);
	}*/

	CObj::tick();
}

void CWood::render(HDC _dc)
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

void CWood::BeginOverlap(CCollider* _pOther)
{
	int a = 0;
	/*SetDead();*/
}
