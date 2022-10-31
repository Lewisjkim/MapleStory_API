#include "pch.h"
#include "CStage2.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"

#include "CPlayer.h"
#include "CStage2BG.h"
#include "CWood.h"
#include "CCollider.h"
#include "CTile.h"
#include "CPlatform.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
}

void CStage2::Enter()
{
	init();
}

void CStage2::Exit()
{
	DeleteAllObject();
}

void CStage2::init()
{
	//Stage1���� ��� �� �ؽ��� �ҷ�����
	CResMgr::GetInst()->LoadTexture(L"Stage2BG", L"texture\\BackGround\\FieldBG\\Acient_Forest_Field.bmp");
	CResMgr::GetInst()->LoadTexture(L"CWood", L"texture\\Monster\\Wood\\Stand\\stand_wood.bmp");
	CResMgr::GetInst()->LoadTexture(L"DArrow", L"texture\\DefaultArrow.bmp");
	

	//��� ����
	CStage2BG* Stage2BG = new CStage2BG;
	Stage2BG->SetPos(Vec2(0.f, 0.f));
	Stage2BG->SetScale(Vec2(1600.f, 900.f));
	AddObject(Stage2BG, LAYER::BACKGROUND);

	//Collider
	CPlatform* ground = new CPlatform;
	ground->SetPos(Vec2(800.f,780.f));
	ground->GetCollider()->SetScale(Vec2(1600.f, 50.f));
	AddObject(ground, LAYER::PLATFORM);

	CPlatform* ground1 = new CPlatform;
	ground1->SetPos(Vec2(400.f, 430.f));
	ground1->GetCollider()->SetScale(Vec2(600.f, 50.f));
	AddObject(ground1, LAYER::PLATFORM);

	CPlatform* ground2 = new CPlatform;
	ground2->SetPos(Vec2(800.f, 780.f));
	ground2->GetCollider()->SetScale(Vec2(1600.f, 50.f));
	AddObject(ground2, LAYER::PLATFORM);

	//�÷��̾� ����
	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2(100.f, 710.f));
	Player->SetScale(Vec2(180.f, 180.f));
	AddObject(Player, LAYER::PLAYER);

	//���� ����(Wood)
	CWood* monWood1 = new CWood;
	monWood1->SetPos(Vec2(400.f, 380.f));
	monWood1->SetScale(Vec2(100.f, 100.f));
	AddObject(monWood1, LAYER::MONSTER);

	CWood* monWood2 = new CWood;
	monWood2->SetPos(Vec2(450.f, 380.f));
	monWood2->SetScale(Vec2(100.f, 100.f));
	AddObject(monWood2, LAYER::MONSTER);
	//UI����

	//Collision ����
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_ATTACK, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_ATTACK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::PLATFORM);

	

	//�ػ󵵸� �������� �޾ƿͼ� ī�޶� �߾��� ���� �ְ� �Ѵ�
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

}

void CStage2::tick()
{
	//������ �����ϰ� �ִ� ��� ������Ʈ�鿡�� tick�� �־�� �Ǵ� �θ𷹺���  tick�� �����´�
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{

	}
}




