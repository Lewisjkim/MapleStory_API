#include "pch.h"
#include "CBG.h"
#include "CResMgr.h"
#include "CTexture.h"

CBG::CBG()	:
	m_pTex(nullptr)
{
	//�ؽ��� �ҷ��� �����ϱ�
	m_pTex = CResMgr::GetInst()->FindTexture(L"StartBackGround");
}

CBG::~CBG()
{
}


void CBG::tick()
{
	CObj::tick();
}

void CBG::render(HDC _dc)
{
	//�ش� BG�� �׸� ��ġ�� ������
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	BitBlt(	_dc,								//hdc Dest
			(int)vPos.x - m_pTex->Width()/2,	//��µ� X ������ġ
			(int)vPos.y - m_pTex->Height()/2,	//��µ� Y ������ġ
			m_pTex->Width(),					//�̹����� ���α���
			m_pTex->Height(),					//�̹����� ���α���
			m_pTex->GetDC(),					//hdc Src
			0,									//��µ� X ������ġ �������� X����
			0,									//��µ� Y ������ġ �������� Y����
			SRCCOPY);

	
}

