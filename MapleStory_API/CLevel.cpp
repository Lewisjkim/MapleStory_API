#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

#include "CTile.h"

#include "CEngine.h"
#include "CCamera.h"


CLevel::CLevel()	:
	m_iTileCountX(0),
	m_iTileCountY(0)
{
}

CLevel::~CLevel()
{
	// 오브젝트 삭제
	DeleteAllObject();
}

void CLevel::tick()
{
	FindTileScreen();


	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); ++j)
			{
				m_vecTile[j]->tick();
			}
		}

		else
		{
			for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
			{
				m_arrLayer[i][j]->tick();
			}
		}
	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); ++j)
			{
				m_vecTile[j]->final_tick();
			}
		}
		else
		{
			for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
			{
				m_arrLayer[i][j]->final_tick();
			}
		}
	}
}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (i == (UINT)LAYER::TILE)
		{
			for (size_t j = 0; j < m_vecTile.size(); ++j)
			{
				m_vecTile[j]->render(_dc);
			}
		}
		else
		{
			vector<CObj*>::iterator iter = m_arrLayer[i].begin();

			for (; iter != m_arrLayer[i].end();)
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}



void CLevel::DeleteAllObject()
{
	// 오브젝트 삭제
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;
			DEL(m_arrLayer[i][j]);
		}
		//동적할당 해제시킨 주소값들을 백터내에서 비워내기(다시 해당 맵에 들어왔을 경우 해당 지워진 메모리값을 정리
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteObject(LAYER _eLayer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); ++i)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}

//class CObj* obj;//**

void CLevel::CreateTile(UINT _X, UINT _Y)
{
	// 기존에 깔아 둔 타일 제거
	DeleteObject(LAYER::TILE);

	m_iTileCountX = _X;
	m_iTileCountY = _Y;

	
	// 지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iTileCountY; ++iRow)
	{
		for (INT iCol = 0; iCol < m_iTileCountX; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(TILE_SIZE * iCol), (float)(TILE_SIZE * iRow)));
			AddObject(pTile, LAYER::TILE);
		}
	}
}

void CLevel::SetFocusedUI(CObj* _pUI)//창 튀어나오게 하기
{
	vector<CObj*>& vecUI = m_arrLayer[(UINT)LAYER::UI];

	if (vecUI.back() == _pUI)
		return;

	vector<CObj*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}

	// Focued 처리할 UI 가 레벨에 없었다?!?!?!?
	assert(nullptr);
}

void CLevel::FindTileScreen()
{
	m_vecTile.clear();


	Vec2 vLeftTop = CCamera::GetInst()->GetLook();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vLeftTop -= (vResolution / 2.f);

	int iLTCol = (int)vLeftTop.x / TILE_SIZE;
	int iLTRow = (int)vLeftTop.y / TILE_SIZE;

	if (vLeftTop.x < 0.f)
		iLTCol = 0;
	if (vLeftTop.y < 0.f)
		iLTRow = 0;

	int iMaxCol = ((int)vResolution.x / TILE_SIZE) + iLTCol + 1;
	int iMaxRow = ((int)vResolution.y / TILE_SIZE) + iLTRow + 1;

	if (m_iTileCountX < iMaxCol)
		iMaxCol = m_iTileCountX;
	if (m_iTileCountY < iMaxRow)
		iMaxRow = m_iTileCountY;

	for (int iRow = iLTRow; iRow < iMaxRow; ++iRow)
	{
		for (int iCol = iLTCol; iCol < iMaxCol; ++iCol)
		{
			int iTileIdx = iRow * m_iTileCountX + iCol;

			m_vecTile.push_back(m_arrLayer[(UINT)LAYER::TILE][iTileIdx]);
		}
	}
}
