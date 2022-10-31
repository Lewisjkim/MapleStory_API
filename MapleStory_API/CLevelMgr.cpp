#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CStartLevel.h"
#include "CStage1.h"
#include "CStage2.h"
#include "CBossLevel.h"
#include "CVillageLevel.h"
#include "CEditorLevel.h" 



CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::init()
{
	//Level 만들기
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage1;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_02] = new CStage2;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_BOSS] = new CBossLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::VILLAGE] = new CVillageLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;

	//시작할 현재 화면 설정
	ChangeLevel(LEVEL_TYPE::EDITOR);

	
	/*//// Level 생성
	//m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	//m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage01Level;
	//m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;
	////m_pCurLevel = m_arrLevel[(UINT)LEVEL_TYPE::EDITOR];
	//ChangeLevel(LEVEL_TYPE::START);//시작 Level*/
}

void CLevelMgr::tick()
{
	m_pCurLevel->tick();
	m_pCurLevel->final_tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	// 현재 레벨과 변경하려는 레벨이 동일 한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// 현재 레벨을 벗어남
	if (nullptr != m_pCurLevel)
		m_pCurLevel->Exit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];//원하는 레벨을 현재 레벨로 바꾸어주고

	m_pCurLevel->Enter();//바꾼 현재 레벨로 입장(초기화)
}
