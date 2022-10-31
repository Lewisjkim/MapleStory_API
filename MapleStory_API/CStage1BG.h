#pragma once
#include "CObj.h"
class CStage1BG :
    public CObj
{
private:
    CTexture* m_pTex;

private:
    virtual void tick()override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DEACTIVATE(CStage1BG);

public:
    CStage1BG();
    ~CStage1BG();
};

