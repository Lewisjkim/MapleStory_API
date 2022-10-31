#pragma once
#include "CObj.h"

class CTexture;

class CPortal :
    public CObj
{
private:
    CTexture* m_pTex;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;


public:
    CLONE_DEACTIVATE(CPortal);

public:
    CPortal();
    ~CPortal();
};

