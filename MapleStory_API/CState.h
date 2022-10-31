#pragma once
#include "CEntity.h"

#include "CSAI.h"
#include "CObj.h"

class CState :
    public CEntity
{
private:
    CSAI* m_pOwnerAI; // State �� �����ϰ� �ִ� AIComponent

public:
    virtual void finaltick() = 0;//���������Լ�(�߻�Ŭ����)�� ���ְ� ��ӹ޴� �Լ��� override������Ѵ�
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    CSAI* GetOwnerAI() { return m_pOwnerAI; }
    CObj* GetOwnerObj() { return m_pOwnerAI->GetOwner(); }

    void ChangeState(const wchar_t* _strStateName);


public:
    CState* Clone() = 0;

public:
    CState();
    ~CState();

    friend class CSAI;
};

