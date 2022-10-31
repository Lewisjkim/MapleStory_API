#pragma once
#include "CObj.h"
class CVillage :
    public CObj
{
private:
    CTexture* m_pTex;

private:
    virtual void tick()override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DEACTIVATE(CVillage);

public:
    CVillage();
    ~CVillage();
};

