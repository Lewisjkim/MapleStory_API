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
	DeleteAllObject();//CLevel�� ��� ������Ʈ ����
}

void CStartLevel::init()
{
	CCamera::GetInst()->FadeIn(3.f);
	//Start Level���� ��� �� �ؽ��� �ҷ�����
	CResMgr::GetInst()->LoadTexture(L"StartBackGround", L"texture\\BackGround\\StartBG\\StartLVImage.bmp");
	
	//��� �� obj ����
	CObj* pBG = new CBG;
	pBG->SetPos(Vec2(800.f, 450.f));
	pBG->SetScale(Vec2(1600.f, 900.f));
	AddObject(pBG, LAYER::BACKGROUND);


	//obj���� �浹 ����

	//�ػ󵵸� �������� �޾ƿͼ� ī�޶� �߾��� ���� �ְ� �Ѵ�
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

