#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

#include "CMissile.h"
#include "CCollider.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidbody.h"



CPlayer::CPlayer()	: 
	m_fSpeed(200.f),
	m_Damage(10.f),
	m_HP(100.f),
	m_MaxHP(100.f),
	m_MP(100),
	m_MaxMP(100),
	m_EXP(0.f),
	m_MaxEXP(100.f)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidbody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(80.f, 80.f));

	//��� �� �ִϸ��̼� �ؽ��� �ҷ�����
	CTexture* pRightWalk = CResMgr::GetInst()->LoadTexture(L"PlayerRWalk", L"texture\\Player\\Right\\awalk.bmp");
	CTexture* pLeftWalk = CResMgr::GetInst()->LoadTexture(L"PlayerLWalk", L"texture\\Player\\Left\\awalk_left.bmp");
	CTexture* pRightStand = CResMgr::GetInst()->LoadTexture(L"PlayerRStand", L"texture\\Player\\Right\\astand.bmp");
	CTexture* pLeftStand = CResMgr::GetInst()->LoadTexture(L"PlayerLStand", L"texture\\Player\\Left\\astand_left.bmp");
	CTexture* pRightAttack = CResMgr::GetInst()->LoadTexture(L"PlayerRightAttack", L"texture\\Player\\Right\\ashoot1.bmp");
	CTexture* pLeftAttack = CResMgr::GetInst()->LoadTexture(L"PlayerLeftAttack", L"texture\\Player\\Left\\ashoot1_left.bmp");
	CTexture* pRope = CResMgr::GetInst()->LoadTexture(L"PlayerRightLying", L"texture\\Player\\Right\\lope.bmp");
	CTexture* pRightLying = CResMgr::GetInst()->LoadTexture(L"PlayerRightLying", L"texture\\Player\\Right\\prone.bmp");
	CTexture* pLeftLying = CResMgr::GetInst()->LoadTexture(L"PlayerLeftLying", L"texture\\Player\\Left\\prone_left.bmp");


	//�̸� ¢��, ������ġ, �����Ӵ� ������, ������ ����, �����Ӻ� ����ð�

	//Create*Save
	/*GetAnimator()->CreateAnimation(L"PLAYER_WALK_RIGHT", pRightWalk, Vec2(0.f, 0.f), Vec2(85.f, 75.f), 4, 0.2f);
	GetAnimator()->CreateAnimation(L"PLAYER_WALK_LEFT", pLeftWalk, Vec2(0.f, 0.f), Vec2(85.f, 75.f), 4, 0.2f);
	GetAnimator()->CreateAnimation(L"PLAYER_STAND_RIGHT", pRightStand, Vec2(0.f, 0.f), Vec2(82.f, 73.f), 6, 0.2f);
	GetAnimator()->CreateAnimation(L"PLAYER_STAND_LEFT", pLeftStand, Vec2(0.f, 0.f), Vec2(82.f, 73.f), 6, 0.2f);
	GetAnimator()->CreateAnimation(L"PLAYER_ATTACK_RIGHT", pRightAttack, Vec2(0.f, 0.f), Vec2(160.f, 177.f), 3, 0.2f);
	GetAnimator()->CreateAnimation(L"PLAYER_ATTACK_LEFT", pLeftAttack, Vec2(0.f, 0.f), Vec2(70.f, 81.f), 3, 0.2f);
	GetAnimator()->CreateAnimation(L"PLAYER_ROPE", pRope, Vec2(0.f, 0.f), Vec2(59.f, 72.f), 2, 0.2f);

	GetAnimator()->FindAnimation(L"PLAYER_WALK_RIGHT")->Save(L"animation\\PLAYER_WALK_RIGHT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_WALK_LEFT")->Save(L"animation\\PLAYER_WALK_LEFT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_STAND_RIGHT")->Save(L"animation\\PLAYER_STAND_RIGHT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_STAND_LEFT")->Save(L"animation\\PLAYER_STAND_LEFT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_ATTACK_RIGHT")->Save(L"animation\\PLAYER_ATTACK_RIGHT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_ATTACK_LEFT")->Save(L"animation\\PLAYER_ATTACK_LEFT.anim");
	GetAnimator()->FindAnimation(L"PLAYER_ROPE")->Save(L"animation\\PLAYER_ROPE.anim");*/

	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_STAND_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_STAND_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_ATTACK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_ROPE.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_PRONE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_PRONE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_PRONE_STAB_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\PLAYER_PRONE_STAB_LEFT.anim");

	GetAnimator()->Play(L"PLAYER_STAND_RIGHT", true);
	// Rigidbody ����

	GetRigidbody()->SetFriction(100.f);//������
	GetRigidbody()->SetGravity(true);//�߷� �ѱ�
	GetRigidbody()->SetGravityAccel(900);//�߷� ���ӵ� ����

	//GetRigidbody()->SetVelocityLimit(200.f);//�¿����Ѽӵ�
	GetRigidbody()->SetGravityVelocityLimit(1000.f);//�߷����Ѽӵ�
}

CPlayer::~CPlayer()
{

}

void CPlayer::tick()
{
	Vec2 vPos = GetPos();
	if (IsPressed(KEY::LEFT))
	{
		/*GetRigidbody()->AddForce(Vec2(-300.f, 0.f));*/
		vPos.x -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::RIGHT))
	{
		/*GetRigidbody()->AddForce(Vec2(300.f, 0.f));*/
		vPos.x += m_fSpeed * DT;
	}

	if (IsPressed(KEY::UP))
	{
		vPos.y -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::DOWN))
	{
		vPos.y += m_fSpeed * DT;

	}

	//Animation
	if (IsTap(KEY::UP))
		GetAnimator()->Play(L"PLAYER_ROPE", true);
	if (IsTap(KEY::DOWN))
		GetAnimator()->Play(L"PLAYER_ROPE", true);
	if (IsTap(KEY::LEFT))
		GetAnimator()->Play(L"PLAYER_WALK_LEFT", true);
	if (IsTap(KEY::RIGHT))
		GetAnimator()->Play(L"PLAYER_WALK_RIGHT", true);
	if (IsRelease(KEY::LEFT))
		GetAnimator()->Play(L"PLAYER_STAND_LEFT", true);
	if (IsRelease(KEY::RIGHT))
		GetAnimator()->Play(L"PLAYER_STAND_RIGHT", true);


	if (IsTap(KEY::SPACE))
	{
		// �̻��� ���� 
		CMissile* pMissile = new CMissile;
		pMissile->SetScale(Vec2(20.f, 20.f));
		pMissile->SetSpeed(400.f);
		pMissile->SetDir(1);
		Instantiate(pMissile, GetPos(), LAYER::PLAYER_ATTACK);
		/*for (int i = 0; i < 3; ++i)
		{
			CMissile* pMissile = new CMissile;
			pMissile->SetScale(Vec2(20.f, 20.f));
			pMissile->SetSpeed(400.f);
			pMissile->SetDir(75.f + 15.f * (float)i);

			Instantiate(pMissile, GetPos(), LAYER::PLAYER_PROJECTILE);
		}*/
		GetAnimator()->Play(L"PLAYER_ATTACK_RIGHT", false);
	}
	if (IsRelease(KEY::SPACE))
	{
		GetAnimator()->Play(L"PLAYER_STAND_RIGHT", true);
	}

	if (IsTap(KEY::LCTRL))
	{
		Vec2 V = GetRigidbody()->GetVelocity();//�߷� ���ӵ�

		if (0.f < V.y)
		{
			GetRigidbody()->AddVelocity(Vec2(0.f, -(V.y + 300.f)));
		}
		else
		{
			GetRigidbody()->AddVelocity(Vec2(0.f, -300.f));
		}


	}
	if (IsTap(KEY::LCTRL) && IsPressed(KEY::DOWN))
	{

	}

	SetPos(vPos);

	// �θ� ������Ʈ�� Tick �� �����Ų��(Component Tick ȣ��)
	CObj::tick();
}

void CPlayer::render(HDC _dc)
{
	CObj::render(_dc);
}


void CPlayer::BeginOverlap(CCollider* _pOther)
{
	int a = 0;
}

void CPlayer::OnOverlap(CCollider* _pOther)
{
	int a = 0;
}

void CPlayer::EndOverlap(CCollider* _pOther)
{
	int a = 0;
}
