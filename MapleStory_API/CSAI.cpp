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

	m_pCurState->finaltick();//�����ϰ� �ִ� state �߿� ���� state�� final tick���ش�
}

void CSAI::AddState(const wstring& _strKey, CState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerAI = this;
}


void CSAI::ChangeState(const wstring& _strStateName)
{
	CState* pNextState = FindState(_strStateName);//���¸� ã�ƿͼ�
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}