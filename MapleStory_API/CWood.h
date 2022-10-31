#pragma once
#include "CObj.h"

class CPlayer;
class CTexture;

class CWood :
    public CObj
{
private:
    float m_fSpeed;
    UINT            m_iHP;
    CObj* m_pTarget;
    CTexture* m_pTex;

    tMonsterInfo    m_tInfo;


private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;


public:
    void SetTarget(CObj* _pPlayer) { m_pTarget = _pPlayer; }
    tMonsterInfo& GetMonInfo() { return m_tInfo; }

public:
    CLONE(CWood);

public:
    CWood();
    ~CWood();
};

