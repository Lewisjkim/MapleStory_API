#pragma once
#include "CUI.h"
//
//class CEditorLevel;//전방선언(Delegate사용시)
class CTexture;//전방선언해야되는 이유는 CTexture가 변경이 있을때마다 재컴파일을 해야해서 비효율적이라고들 한다.

typedef void(CEntity::* DELEGATE)(void);

typedef void(*TestFuncType)(void);


class CButton :
    public CUI
{
private:
    CTexture* m_pPressedTex;
    CTexture* m_pHighlightTex;//눌린상태 텍스쳐

    //Call back형식일 경우
    TestFuncType    m_pFunc;

    //Delegate형식일 경우
    CEntity* m_pInst;//Entity 레벨의 객체 주소(Entity로 하면 그 하위 함수 다 됨)
    DELEGATE        m_pDelegateFunc;//Entity 레벨의 멤버함수만



public:
    void SetCallBack(TestFuncType _pCallBack) { m_pFunc = _pCallBack; }
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }
    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex; }
    void SetPressedTex(CTexture* _pTex) { m_pPressedTex = _pTex; }

    virtual void render(HDC _dc);

private:
    virtual void MouseLbtnClicked();

public:
    CLONE(CButton)

public:
    CButton();
    ~CButton();
};

