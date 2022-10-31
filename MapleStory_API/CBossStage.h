#pragma once
#include "CObj.h"
class CBossStage :
    public CObj
{
private:
    CTexture* m_pTex;

private:
    virtual void tick()override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DEACTIVATE(CBossStage);

public:
    CBossStage();
    ~CBossStage();
};

