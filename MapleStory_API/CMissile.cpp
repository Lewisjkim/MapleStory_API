#include "pch.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CMissile.h"



CMissile::CMissile()
	: m_fSpeed(200.f)
	, m_fDegree(80.f)
	, m_fTime(0.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	m_Tex = CResMgr::GetInst()->FindTexture(L"DArrow");
}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	Vec2 vPos = GetPos();

	// 60분법 -> 라디안
	float fRadian = (m_fDegree * PI) / 180.f;

	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y -= m_fSpeed * sinf(fRadian) * DT;

	SetPos(vPos);

	CObj::tick();
}

void CMissile::render(HDC _dc)
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

	//알파블랜드를 사용해서 이미지에 알파값이 흰색 처리 되어있지않으면 표시가 안됨
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * fRatio);//알파가 255인값만 출력

	AlphaBlend(_dc
		, (int)(vPos.x - m_Tex->Width() / 2.f)
		, (int)(vPos.y - m_Tex->Height() / 2.f)
		, m_Tex->Width()
		, m_Tex->Height()
		, m_Tex->GetDC()
		, 0, 0
		, m_Tex->Width()
		, m_Tex->Height()
		, tBlend);

	CObj::render(_dc);
}

void CMissile::BeginOverlap(CCollider* _pOther)
{
	//SetDead();
}
