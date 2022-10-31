#include "pch.h"
#include "CTraceState.h"

#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CWood.h"

CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}


void CTraceState::finaltick()
{
	// ���� ���� ������Ʈ�� ���� ������ �ƴ� ���
	CWood* pMon = dynamic_cast<CWood*>(GetOwnerObj());
	assert(pMon);

	// Player �� �˾Ƴ���.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);

	Vec2 vMonPos = pMon->GetPos();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonToPlayer = vPlayerPos - vMonPos;
	vMonToPlayer.Normalize();

	float fSpeed = pMon->GetMonInfo().m_fSpeed;

	vMonPos += vMonToPlayer * DT * fSpeed;

	pMon->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
