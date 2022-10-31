#include "pch.h"
#include "CSAI.h"

#include "CState.h"


CSAI::CSAI(CObj* _pOwner)
	: CComponent(_pOwner)
	, m_pCurState(nullptr)
{
}

CSAI::~CSAI()
{
	map<wstring, CState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);//***
	}
	m_mapState.clear();
}

void CSAI::final_tick()
{
	if (nullptr == m_pCurState)
		return;

	m_pCurState->finaltick();//보유하고 있는 state 중에 현재 state를 final tick해준다
}

void CSAI::AddState(const wstring& _strKey, CState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerAI = this;
}


void CSAI::ChangeState(const wstring& _strStateName)
{
	CState* pNextState = FindState(_strStateName);//상태를 찾아와서
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}