#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CWood.h"
#include "CRigidbody.h"


CPlatform::CPlatform()
{
	CreateCollider();
	
	/*GetCollider()->SetScale(Vec2(400.f, 50.f));*/
}

CPlatform::~CPlatform()
{
}

void CPlatform::BeginOverlap(CCollider* _pOther)
{
	
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;

	pPlayer->GetRigidbody()->SetGround(true);

	CWood* pWood = dynamic_cast<CWood*>(_pOther->GetOwner());
	if (nullptr == pWood)
		return;

	pWood->GetRigidbody()->SetGround(true);

}


void CPlatform::OnOverlap(CCollider* _pOther)
{

}

void CPlatform::EndOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;

	pPlayer->GetRigidbody()->SetGround(false);

	CWood* pWood = dynamic_cast<CWood*>(_pOther->GetOwner());
	if (nullptr == pWood)
		return;

	pWood->GetRigidbody()->SetGround(false);
}
