#include "pch.h"
#include "CVillage.h"
#include "CResMgr.h"
#include "CTexture.h"

CVillage::CVillage() :
	m_pTex(nullptr)
{
	//�ؽ��� �ҷ��� �����ϱ�
	m_pTex = CResMgr::GetInst()->FindTexture(L"VillageBG");
}

CVillage::~CVillage()
{
}


void CVillage::tick()
{
	CObj::tick();
}

void CVillage::render(HDC _dc)
{
	//�ش� BG�� �׸� ��ġ�� ������
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	BitBlt(_dc,								//hdc Dest
		(int)vPos.x,	//��µ� X ������ġ
		(int)vPos.y,	//��µ� Y ������ġ
		m_pTex->Width(),					//�̹����� ���α���
		m_pTex->Height(),					//�̹����� ���α���
		m_pTex->GetDC(),					//hdc Src
		0,									//��µ� X ������ġ �������� X����
		0,									//��µ� Y ������ġ �������� Y����
		SRCCOPY);


}

