#pragma once
#include "CUI.h"
class CPanel :
    public CUI
{
private:
    Vec2    m_vLeftRightPadding;
    Vec2    m_vTopBottomPadding;
    Vec2    m_vInnerPadding;//���ϵ鰣 �е�


    Vec2    m_vPressPos;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;

public:
    CLONE(CPanel);

public:
    CPanel();
    ~CPanel();
};

