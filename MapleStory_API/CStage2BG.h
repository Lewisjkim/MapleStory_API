#pragma once
#include "CObj.h"
class CStage2BG :
    public CObj
{
private:
    CTexture* m_pTex;

private:
    virtual void tick()override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DEACTIVATE(CStage2BG);

public:
    CStage2BG();
    ~CStage2BG();
};

