#include "pch.h"
#include "CButton.h"

#include "CEditorLevel.h"
#include "CLevelMgr.h"

#include "CTexture.h"

CButton::CButton() :
	m_pFunc(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
{
}

CButton::~CButton()
{
}

void CButton::render(HDC _dc)
{
	CTexture* pTargetTex = GetIdleTex();//�ؽ��� ��ü

	if (IsLbtnDown())
	{
		if (m_pPressedTex)
			pTargetTex = m_pPressedTex;//�������� �ؽ��Ķ�� pTargetTex�� �־���� 
	}
	else if (IsMouseOn())//���콺�� �÷���������
	{
		if (m_pHighlightTex)
			pTargetTex = m_pHighlightTex;
	}

	if (!pTargetTex)
	{
		CUI::render(_dc);
		return;
	}

	Vec2 vPos = GetFinalPos();
	BitBlt(_dc, vPos.x, vPos
		.y, pTargetTex->Width(), pTargetTex->Height(), pTargetTex->GetDC(), 0, 0, SRCCOPY);



	render_childUI(_dc);
}

void CButton::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc();
	}
	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}
}