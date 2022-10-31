#include "pch.h"
#include "CState.h"

#include "CEventMgr.h"

CState::CState()
	: m_pOwnerAI(nullptr)
{
}

CState::~CState()
{
}


void CState::ChangeState(const wchar_t* _pStateName)//문자열 주소를 받아온다
{
	tEvent evn = {};

	evn.eType = EVENT_TYPE::CHANGE_AI_STATE;
	evn.wParam = (DWORD_PTR)GetOwnerAI();//상태를 변경해야 할 AI의 주소
	evn.lParam = (DWORD_PTR)_pStateName;//바꿔야할 문자열 주소 정보

	CEventMgr::GetInst()->AddEvent(evn);
}
