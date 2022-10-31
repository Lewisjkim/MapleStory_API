#include "pch.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTile::CTile() :
	m_pAtlas(nullptr)
{
}

CTile::~CTile()
{
}

void CTile::tick()
{

}

void CTile::render(HDC _dc)
{
	/*if (-1 == m_iImgIdx || m_pAtlas == nullptr)
		return;

	int iMaxCol = m_pAtlas->Width() / TILE_SIZE;

	int iCurRow = m_iImgIdx / iMaxCol;
	int iCurCol = m_iImgIdx % iMaxCol;*/

	
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, myBrush);

	Rectangle(_dc, vPos.x, vPos.y, vPos.x + TILE_SIZE, vPos.y + TILE_SIZE);

	SelectObject(_dc, oldBrush);
	DeleteObject(myBrush);
	//
	//static float fRatio = 0.f;
	//static float Dir = 1.f;
	//fRatio += DT * Dir * 8.f;

	//if (1.f < fRatio)
	//{
	//	fRatio = 1.f;
	//	Dir = -1.f;
	//}
	//else if (fRatio < 0.f)
	//{
	//	fRatio = 0.f;
	//	Dir = 1;
	//}

	////���ĺ��带 ����ؼ� �̹����� ���İ��� ��� ó�� �Ǿ����������� ǥ�ð� �ȵ�
	//BLENDFUNCTION tBlend = {};

	//tBlend.AlphaFormat = AC_SRC_ALPHA;
	//tBlend.BlendFlags = 0;
	//tBlend.BlendOp = AC_SRC_OVER;
	//tBlend.SourceConstantAlpha = (int)(255.f * fRatio);//���İ� 255�ΰ��� ���

	//AlphaBlend(_dc
	//	, (int)(vPos.x)
	//	, (int)(vPos.y)
	//	, vPos.x + TILE_SIZE
	//	, vPos.y + TILE_SIZE
	//	, m_pAtlas->GetDC()
	//	, 0, 0
	//	, vPos.x + TILE_SIZE
	//	, vPos.y + TILE_SIZE
	//	, tBlend);

	//*******************
	/*BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);*/

}

void CTile::SetImgIdx(int _imgidx)
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	assert(!(iImgMaxCount <= _imgidx));//�ε����� �ִ� ������ �Ѿ��

	m_iImgIdx = _imgidx;
}

void CTile::AddImgIdx()
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	++m_iImgIdx;

	// �ִ� �̹��� �ʰ��ϴ� ���, �ٽ� ó������...
	if (iImgMaxCount <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}
}


void CTile::Save(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// Ű�� ����,
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// ����� ����,
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	// �̹��� �ε���
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
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
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// �̹��� �ε���
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}