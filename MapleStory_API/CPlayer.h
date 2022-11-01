#pragma once
#include "CObj.h"

class CTexture;

class CPlayer :
    public CObj
{
private:
    float       m_fSpeed;   // 속력 ( scalar )
    float       m_Damage;   // 데미지
    float       m_HP;       // HP
    float       m_MaxHP;   
    float       m_MP;      
    float       m_MaxMP;   
    float       m_EXP;     
    float       m_MaxEXP;     

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    void SetSpeed(float _f)
    {
        m_fSpeed = _f;
    }

public:
    CLONE_DEACTIVATE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
};

