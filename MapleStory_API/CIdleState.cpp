#include "pch.h"
#include "CIdleState.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CWood.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::finaltick()
{
	// ���� ���� ������Ʈ�� ���� ������ �ƴ� ���
	CWood* pMon = dynamic_cast<CWood*>(GetOwnerObj());
	assert(pMon);

	// Player �� �˾Ƴ���.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);

	// Player �� Monster �� �Ÿ����� ���
	float fDetectRange = pMon->GetMonInfo().m_fDetectRange;

	// Player �� Ž������ �̳��� ������ �������·� ��ȯ
	Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
	if (vDir.Length() < fDetectRange)
	{
		ChangeState(L"Trace");
	}
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}