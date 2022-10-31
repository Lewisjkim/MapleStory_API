#pragma once
#include "CObj.h"
class CSelectBG :
    public CObj
{
private:
    CTexture* m_pTex;
private:
    virtual void tick()override;
    virtual void render(HDC _dc) override;
public:
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);
public:
    CLONE_DEACTIVATE(CSelectBG);

public:
    CSelectBG();
    ~CSelectBG();

};

