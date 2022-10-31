#include "pch.h"
#include "CStage1.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CResMgr.h"

#include "CPlayer.h"
#include "CStage1BG.h"
#include "CWood.h"
#include "CPortal.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CCollider.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Enter()
{
	init();
}

void CStage1::Exit()
{
	DeleteAllObject();
}

void CStage1::init()
{
	//Stage1에서 사용 할 텍스쳐 불러오기
	CResMgr::GetInst()->LoadTexture(L"Stage1BG", L"texture\\BackGround\\FieldBG\\Acient_Perion_Field.bmp");
	CResMgr::GetInst()->LoadTexture(L"CWood", L"texture\\Monster\\Wood\\Stand\\stand_wood.bmp");
	CResMgr::GetInst()->LoadTexture(L"Portal", L"texture\\Portal\\portal.bmp");
	CResMgr::GetInst()->LoadTexture(L"DArrow", L"texture\\DefaultArrow.bmp");

	//배경 생성
	CStage1BG* Stage1BG = new CStage1BG;
	Stage1BG->SetPos(Vec2(0.f, 0.f));
	Stage1BG->SetScale(Vec2(1600.f, 900.f));
	AddObject(Stage1BG, LAYER::BACKGROUND);
	
	//Ground
	CPlatform* ground = new CPlatform;
	ground->SetPos(Vec2(800.f, 780.f));
	ground->GetCollider()->SetScale(Vec2(1600.f, 50.f));
	AddObject(ground, LAYER::PLATFORM);

	//플레이어 생성
	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2(100.f, 700.f));
	Player->SetScale(Vec2(180.f, 180.f));
	AddObject(Player, LAYER::PLAYER);

	//portal
	CPortal* portal = new CPortal;
	portal->SetPos(Vec2(100.f, 700.f));
	portal->SetScale(Vec2(80.f, 80.f));
	AddObject(portal, LAYER::PORTAL);
	
	//배경 string Collision 생성

	//플레이어 생성

	//몬스터 생성(Wood)
	CObj* monWood = new CWood;
	monWood->SetPos(Vec2(400.f, 400.f));
	monWood->SetScale(Vec2(100.f, 100.f));
	AddObject(monWood, LAYER::MONSTER);

	//UI생성

	//해상도를 엔진에서 받아와서 카메라가 중앙을 보고 있게 한다
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

}

void CStage1::tick()
{
	//본인이 소유하고 있는 모든 오브젝트들에게 tick을 주어야 되니 부모레벨의  tick을 가져온다
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		
	}
}




