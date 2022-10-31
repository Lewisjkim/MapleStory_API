#include "pch.h"
#include "CEventMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CSAI.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::tick()
{
	// �������� ������Ʈ ����
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();


	// �̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EVENT_TYPE::CREATE_OBJECT: // wParam : Object Adress, lParam : Layer
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CObj* pNewObj = (CObj*)m_vecEvent[i].wParam;
			LAYER eLayer = (LAYER)m_vecEvent[i].lParam;

			pCurLevel->AddObject(pNewObj, eLayer);
		}
		break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			// �������� ������Ʈ�� Dead ���·� �ΰ� Garbage �� �ִ´�.
			CObj* pObj = (CObj*)m_vecEvent[i].wParam;

			// ���� Ȯ���� ���� tick ���� ���ÿ� ���� ������Ʈ�� ������û �� ��츦 ���
			if (false == pObj->m_bDead)
			{
				m_vecGarbage.push_back(pObj);
				pObj->m_bDead = true;
			}
		}
		break;


		case EVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Next Level Type
			LEVEL_TYPE eNextLevel = (LEVEL_TYPE)m_vecEvent[i].wParam;//level type���� �ٲپ��ְ�
			CLevelMgr::GetInst()->ChangeLevel(eNextLevel);//LVMG���� change level�� ���� �������ش� 
		}
		break;
		case EVENT_TYPE::CHANGE_AI_STATE:
		{
			// wParam : AI Component Adress, lParam : Next State Name
			CSAI* pAI = (CSAI*)m_vecEvent[i].wParam;//�ּҰ� ������
			const wchar_t* pName = (const wchar_t*)m_vecEvent[i].lParam;
			pAI->ChangeState(pName);
		}
		default:
			break;
		}
	}

	m_vecEvent.clear();
}
