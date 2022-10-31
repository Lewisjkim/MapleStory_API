#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
private:
    vector<CUI*>    m_vecChildUI;//자식 UI들을 가질 수 있는 구조 , 레이어에는 최상위 부모 레이어만 넣는다
    CUI* m_pParentUI;
    Vec2            m_vFinalPos;

    CTexture* m_pIdleTex;

    bool            m_bLbtnDown;
    bool            m_bMouseOn;
    bool            m_bCmrAfctd;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    void render_childUI(HDC _dc);

public:
    void SetIdleTex(CTexture* _pTex);
    void SetCameraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    CUI* GetParentUI() { return m_pParentUI; }
    const vector<CUI*>GetChildUI() { return m_vecChildUI; }

    CTexture* GetIdleTex() { return m_pIdleTex; }

    void AddChildUI(CUI* _pChildUI)
    {
        _pChildUI->m_pParentUI = this;
        m_vecChildUI.push_back(_pChildUI);
    }

    //UI이벤트 함수
public:
    virtual void MouseLbtnDown() { m_bLbtnDown = true; };//오버라이딩 할 경우 부모함수(CUI) 호출 해야 됨
    virtual void MouseLbtnClicked() {};
    virtual void MouseOn() {};

private:
    void MouseOnCheck();

public:
    CLONE(CUI);

public:
    CUI();
    CUI(const CUI& _other);
    ~CUI();

    friend class CUIMgr;
};

