#pragma once
#include "CUI.h"
//
//class CEditorLevel;//���漱��(Delegate����)
class CTexture;//���漱���ؾߵǴ� ������ CTexture�� ������ ���������� ���������� �ؾ��ؼ� ��ȿ�����̶��� �Ѵ�.

typedef void(CEntity::* DELEGATE)(void);

typedef void(*TestFuncType)(void);


class CButton :
    public CUI
{
private:
    CTexture* m_pPressedTex;
    CTexture* m_pHighlightTex;//�������� �ؽ���

    //Call back������ ���
    TestFuncType    m_pFunc;

    //Delegate������ ���
    CEntity* m_pInst;//Entity ������ ��ü �ּ�(Entity�� �ϸ� �� ���� �Լ� �� ��)
    DELEGATE        m_pDelegateFunc;//Entity ������ ����Լ���



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

