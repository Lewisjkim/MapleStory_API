#pragma once
#include "CComponent.h"
//몬스터들이 가지는 많은 상태들을 owner에 추가해주거나 변경해 준다
class CState;

class CSAI :
    public CComponent
{
private:

    map<wstring, CState*>   m_mapState;     //ai가 가지는 여러가지 상태를 넣어주는 map
    CState* m_pCurState;    //몬스터한테 다양한 상태를 넣어주면 된다

public:
    virtual void tick() override {}
    virtual void final_tick() override;
    virtual void render(HDC _dc) override {}

public:
    void AddState(const wstring& _strKey, CState* _pState);

    CState* FindState(const wstring& _strKey)
    {
        map<wstring, CState*>::iterator iter = m_mapState.find(_strKey);
        if (iter != m_mapState.end())
            return iter->second;
        return nullptr;
    }

    void ChangeState(const wstring& _strStateName);



    CLONE(CSAI);

public:
    CSAI(CObj* _pObj);
    ~CSAI();
};

