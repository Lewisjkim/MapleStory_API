#include "pch.h"
#include "CStage2BG.h"
#include "CResMgr.h"
#include "CTexture.h"

CStage2BG::CStage2BG() :
	m_pTex(nullptr)
{
	//�ؽ��� �ҷ��� �����ϱ�
	m_pTex = CResMgr::GetInst()->FindTexture(L"Stage2BG");
}

CStage2BG::~CStage2BG()
{
}


void CStage2BG::tick()
{
	CObj::tick();
}

void CStage2BG::render(HDC _dc)
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

