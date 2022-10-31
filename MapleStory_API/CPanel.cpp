#include "pch.h"
#include "CPanel.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CPanel::CPanel()
{
}

CPanel::~CPanel()
{
}

void CPanel::tick()
{

	//drag and drop
	if (IsLbtnDown())//�������ִ� ���¶��
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;//���� ���콺 ��ġ - ���� ���콺 ��ġ ����

		Vec2 vPos = GetPos();
		vPos += vMove;
		SetPos(vPos);

		m_vPressPos = MOUSE_POS;//����
	}

	CUI::tick();
}

void CPanel::render(HDC _dc)
{
	if (nullptr == GetIdleTex())//�ڽ��� ������ �ִ� �ؽ��� ��ü�� ��ȯ
		return;

	Vec2 vPos = GetPos();//�ڽ��� ��ġ

	TransparentBlt(_dc, vPos.x, vPos.y
		, GetIdleTex()->Width()//�̹����� ����
		, GetIdleTex()->Height()//�̹����� ����
		, GetIdleTex()->GetDC()
		, 0, 0
		, GetIdleTex()->Width()
		, GetIdleTex()->Height()
		, RGB(255, 0, 255));


	render_childUI(_dc);//������ ���ϵ� ����
}

void CPanel::MouseLbtnDown()
{
	CUI::MouseLbtnDown();//�θ��� lbtndown����� �켱 ��������

	m_vPressPos = MOUSE_POS;//������ �� �ڽ��� ��ġ�� ����Ѵ�
}

void CPanel::MouseLbtnClicked()
{
	int a = 0;
}

