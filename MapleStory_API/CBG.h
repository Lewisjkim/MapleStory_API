#pragma once
#include "CObj.h"
class CBG :
    public CObj
{
private:
    CTexture* m_pTex;

private:
    virtual void tick()override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DEACTIVATE(CBG);

public:
    CBG();
    ~CBG();
};

