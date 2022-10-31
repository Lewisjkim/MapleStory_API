#pragma once
#include "CEntity.h"

#include "CSAI.h"
#include "CObj.h"

class CState :
    public CEntity
{
private:
    CSAI* m_pOwnerAI; // State 를 소유하고 있는 AIComponent

public:
    virtual void finaltick() = 0;//순수가상함수(추상클래스)로 해주고 상속받는 함수에 override해줘야한다
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

