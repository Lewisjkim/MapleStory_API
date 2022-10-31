#pragma once
#include "CLevel.h"
class CTexture;
enum class EDITOR_MODE
{
    TILE,
    ANIMATION,
    OBJECT,//오브젝트 배치

    NONE,
};

class CEditorLevel :
    public CLevel
{

private:
    HMENU           m_hMenu;//메뉴 핸들값
    EDITOR_MODE     m_eMode;
    CTexture*       m_pTex;
    HINSTANCE       hInst;
public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void update();
    void tile_update();
    void animation_update();
    void object_update();
    void CreateUI();


public:
    void SaveTile();
    void LoadTile();
    void CreateColliderBox(float posx, float posy, float sizex, float sizey);
    void LoadBackground();

public:
    CEditorLevel();
    ~CEditorLevel();
};

