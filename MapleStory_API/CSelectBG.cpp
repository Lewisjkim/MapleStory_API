#include "pch.h"
#include "CSelectBG.h"
#include "CResMgr.h"
#include "CTexture.h"

CSelectBG::CSelectBG() :
	m_pTex(nullptr)
{
	//�ؽ��� �ҷ��� �����ϱ�
}

CSelectBG::~CSelectBG()
{
}


void CSelectBG::tick()
{
	CObj::tick();
}

void CSelectBG::render(HDC _dc)
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
void CSelectBG::Save(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = m_pTex;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// Ű�� ����,
		wstring strKey = m_pTex->GetKey();
		SaveWString(strKey, _pFile);

		// ����� ����,
		wstring strRelativePath = m_pTex->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}
}
void CSelectBG::Load(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_pTex = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	//// �̹��� �ε���
	//fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

