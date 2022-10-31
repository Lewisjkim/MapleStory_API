#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"

#include "CObj.h"
#include "CBG.h"
#include "CUI.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::Enter()
{
	init();
}

void CStartLevel::Exit()
{
	DeleteAllObject();//CLevel의 모든 오브젝트 삭제
}

void CStartLevel::init()
{
	CCamera::GetInst()->FadeIn(3.f);
	//Start Level에서 사용 할 텍스쳐 불러오기
	CResMgr::GetInst()->LoadTexture(L"StartBackGround", L"texture\\BackGround\\StartBG\\StartLVImage.bmp");
	
	//사용 할 obj 생성
	CObj* pBG = new CBG;
	pBG->SetPos(Vec2(800.f, 450.f));
	pBG->SetScale(Vec2(1600.f, 900.f));
	AddObject(pBG, LAYER::BACKGROUND);


	//obj간의 충돌 설정

	//해상도를 엔진에서 받아와서 카메라가 중앙을 보고 있게 한다
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::tick()
{
	CLevel::tick();
	
	if (IsTap(KEY::ENTER))
	{/*
		CCamera::GetInst()->FadeOut(3.f);*/
		CObj* pBG = new CBG;
		pBG->SetDead();
		
		ChangeLevel(LEVEL_TYPE::STAGE_01);
		
	}
}

