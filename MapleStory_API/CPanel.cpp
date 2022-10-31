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
	if (IsLbtnDown())//눌려져있는 상태라면
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;//현재 마우스 위치 - 기존 마우스 위치 차이

		Vec2 vPos = GetPos();
		vPos += vMove;
		SetPos(vPos);

		m_vPressPos = MOUSE_POS;//갱신
	}

	CUI::tick();
}

void CPanel::render(HDC _dc)
{
	if (nullptr == GetIdleTex())//자신이 가지고 있는 텍스쳐 객체를 반환
		return;

	Vec2 vPos = GetPos();//자신의 위치

	TransparentBlt(_dc, vPos.x, vPos.y
		, GetIdleTex()->Width()//이미지의 가로
		, GetIdleTex()->Height()//이미지의 세로
		, GetIdleTex()->GetDC()
		, 0, 0
		, GetIdleTex()->Width()
		, GetIdleTex()->Height()
		, RGB(255, 0, 255));


	render_childUI(_dc);//소유한 차일들 렌더
}

void CPanel::MouseLbtnDown()
{
	CUI::MouseLbtnDown();//부모의 lbtndown기능을 우선 가져오고

	m_vPressPos = MOUSE_POS;//눌렀을 때 자신의 위치를 기억한다
}

void CPanel::MouseLbtnClicked()
{
	int a = 0;
}

