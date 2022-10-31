#include "pch.h"
#include "CSelectBG.h"
#include "CResMgr.h"
#include "CTexture.h"

CSelectBG::CSelectBG() :
	m_pTex(nullptr)
{
	//텍스쳐 불러와 설정하기
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
	//해당 BG를 그릴 위치와 사이즈
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	BitBlt(_dc,								//hdc Dest
		(int)vPos.x,	//출력될 X 시작위치
		(int)vPos.y,	//출력될 Y 시작위치
		m_pTex->Width(),					//이미지의 가로길이
		m_pTex->Height(),					//이미지의 세로길이
		m_pTex->GetDC(),					//hdc Src
		0,									//출력될 X 시작위치 기준으로 X지점
		0,									//출력될 Y 시작위치 기준으로 Y지점
		SRCCOPY);


}
void CSelectBG::Save(FILE* _pFile)
{
	// 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// 아틀라스 이미지 정보
	bool bAtlas = m_pTex;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// 키값 저장,
		wstring strKey = m_pTex->GetKey();
		SaveWString(strKey, _pFile);

		// 상대경로 저장,
		wstring strRelativePath = m_pTex->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}
}
void CSelectBG::Load(FILE* _pFile)
{
	// 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// 아틀라스 이미지 정보
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_pTex = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	//// 이미지 인덱스
	//fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

