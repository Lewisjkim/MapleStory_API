#include "pch.h"
#include "CEditorLevel.h"

#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CUI.h"
#include "CButton.h"
#include "CPanel.h"
#include "CTile.h"
#include "CObj.h"
#include "CCollider.h"
#include "CPlatform.h"
#include "CLevel.h"

#include "resource.h"

#include "CStage2BG.h"
#include "CSelectBG.h"
#include "CWood.h"


CEditorLevel* level = nullptr;
CWood* wood = nullptr;

CEditorLevel::CEditorLevel() :
	hInst(nullptr),
	m_pTex(nullptr),
	m_hMenu(nullptr),
	m_eMode(EDITOR_MODE::NONE)
{
	level = this;
}

CEditorLevel::~CEditorLevel()
{
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);


}

void CEditorLevel::init()
{
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	//UI��ġ
	CreateUI();



	// Ÿ���� ����� ��Ʋ�� �̹��� �ε�
	CResMgr::GetInst()->LoadTexture(L"Stage2BG", L"texture\\BackGround\\FieldBG\\Acient_Forest_Field.bmp");

	CStage2BG* Stage2BG = new CStage2BG;
	Stage2BG->SetPos(Vec2(0.f, 0.f));
	Stage2BG->SetScale(Vec2(1600.f, 900.f));
	AddObject(Stage2BG, LAYER::BACKGROUND);
	

	CreateTile(0, 0);



	
}



void CEditorLevel::tick()
{
	CLevel::tick();
	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	if (IsTap(KEY::_1))
		m_eMode = EDITOR_MODE::ANIMATION;
	if (IsTap(KEY::_2))
		m_eMode = EDITOR_MODE::OBJECT;
	if (IsTap(KEY::_0))
		m_eMode = EDITOR_MODE::NONE;

	update();
}

void CEditorLevel::Enter()
{
	// �޴��� ����
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_MAPLESTORYAPI));//�޴��ٸ� �ҷ��´�(������ �ǰ� �������� �ʾ���)
	}

	// �޴��� �߰��� ���� �ػ� �� ����
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, m_hMenu);//�޴� ����

	//�޴��ٰ� �ٰ� ���� ������ ����� �ٽ� ���� ����� �޴��� ��ŭ �߰��ȴ�
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);


	// �ʱ� ������Ʈ ����
	init();
}

void CEditorLevel::Exit()
{
	// �޴��� ����
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	// ���� ������ ũ�� ������
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
}

void CEditorLevel::update()
{
	switch (m_eMode)
	{
	
	case EDITOR_MODE::ANIMATION:
		animation_update();
		break;
	case EDITOR_MODE::OBJECT:
		object_update();
		break;
	
	case EDITOR_MODE::NONE:
		return;
	}
}


void CEditorLevel::tile_update()
{
	if (IsTap(KEY::LBTN))
	{
		// ���콺 ��ġ�� �޾ƿͼ� ������ǥ�� ��ȯ	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		//tilecount�� Ÿ�� ������ ����ϰ��ֱ⿡ �����´�
		if (0.f <= vMousePos.x && iCol < GetTileCountX()
			&& 0.f <= vMousePos.y && iRow < GetTileCountY())
		{
			int iIdx = iRow * GetTileCountX() + iCol;
			const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}

	if (IsTap(KEY::_8))
	{
		SaveTile();
	}
	else if (IsTap(KEY::_9))
	{
		LoadTile();
	}
}


void CEditorLevel::animation_update()
{
}

void CEditorLevel::object_update()
{
}

void CEditorLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	//button�� ����� �ؽ���
	CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	//Panel
	CPanel* pPanel = new CPanel;
	pPanel->SetIdleTex(pPanelTex);
	pPanel->SetPos(Vec2(vResolution.x - (pPanelTex->Width() + 20.f), 10.f));

	//Tile Save button
	CButton* pSaveTileButton = new CButton;
	pSaveTileButton->SetScale(Vec2(100.f, 50.f));
	Vec2 vUIPos = Vec2(10.f, 20.f);
	pSaveTileButton->SetPos(vUIPos);
	pSaveTileButton->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	pSaveTileButton->SetIdleTex(pButtonTex);
	pSaveTileButton->SetPressedTex(pButtonPressedTex);


	//Tile Load button
	CButton* pLoadTileButton = pSaveTileButton->Clone();
	pLoadTileButton->SetPos(Vec2(150.f, 20.f));
	pLoadTileButton->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);

	//Save, Load ��ư�� panel�� �ڽ����� �߰�
	pPanel->AddChildUI(pSaveTileButton);
	pPanel->AddChildUI(pLoadTileButton);

	AddObject(pPanel, LAYER::UI);

	//�г� Ŭ�� �����
	CUI* pOtherPanelUI = pPanel->Clone();
	pOtherPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Width() * 2.f + 20.f), 10.f));
	AddObject(pOtherPanelUI, LAYER::UI);
}

void CEditorLevel::SaveTile()
{
	////opne a file name
	//OPENFILENAME ofn = {};

	//wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	//strTileFolderPath += L"tile\\";

	//wchar_t szFilePath[256] = {};//���������� �迭256�� ¥��

	//ZeroMemory(&ofn, sizeof(ofn));
	//ofn.lStructSize = sizeof(ofn);
	//ofn.hwndOwner = NULL;
	//ofn.lpstrFile = szFilePath;
	//ofn.lpstrFile[0] = '\0';
	//ofn.nMaxFile = 256;
	//ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";//������ �̸��� Tile �̰� Ȯ���ڴ� .tile or ALL
	//ofn.nFilterIndex = 1;//�⺻ ���͸� �� �Ұų�
	//ofn.lpstrFileTitle = NULL;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = strTileFolderPath.c_str();//�������
	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (false == GetSaveFileName(&ofn))//�����ִ� �Լ� (ofn = �� �ɼǰ��� �־ �Ѱ��ִ°�)
	//	return;

	////--------------------


	//FILE* pFile = nullptr;
	//_wfopen_s(&pFile, szFilePath, L"wb");

	//// Ÿ�� ���� ���� ���� ����
	//UINT iTileCountX = GetTileCountX();
	//UINT iTileCountY = GetTileCountY();

	//fwrite(&iTileCountX, sizeof(UINT), 1, pFile);
	//fwrite(&iTileCountY, sizeof(UINT), 1, pFile);



	//// ������ Ÿ�� ���� ����
	//const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	//for (size_t i = 0; i < vecTile.size(); ++i)
	//{
	//	((CTile*)vecTile[i])->Save(pFile);
	//}

	//fclose(pFile);
}

void CEditorLevel::LoadTile()
{
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};//���������� �迭256�� ¥��

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";//������ �̸��� Tile �̰� Ȯ���ڴ� .tile or ALL
	ofn.nFilterIndex = 1;//�⺻ ���͸� �� �Ұų�
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();//�������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))//�ҷ��ִ� �Լ� (ofn = �� �ɼǰ��� �־ �Ѱ��ִ°�)
		return;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"tile\\test.tile";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	// Ÿ�� ���� ���� ���� �б�
	UINT iTileCountX = 0, iTileCountY = 0;

	fread(&iTileCountX, sizeof(UINT), 1, pFile);
	fread(&iTileCountY, sizeof(UINT), 1, pFile);

	// ���� ������ �°� �ٽ� Ÿ�� ��ġ
	CreateTile(iTileCountX, iTileCountY);

	// ��ġ�� ������ Ÿ�ϵ��� ������ �е���
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}


void CEditorLevel::CreateColliderBox(float posx, float posy, float sizex, float sizey)
{
	CPlatform* ground2 = new CPlatform;
	ground2->SetPos(Vec2(posx, posy));
	ground2->GetCollider()->SetScale(Vec2(sizex, sizey));
	AddObject(ground2, LAYER::PLATFORM);
}

void CEditorLevel::LoadBackground()
{
	
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"texture\\";

	wchar_t szFilePath[256] = {};//���������� �迭256�� ¥��

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);//������ ����
	ofn.hwndOwner = NULL;//��ȭ ���ڸ� ������ â
	ofn.lpstrFile = szFilePath;//���� �̸� ���� ��Ʈ���� �ʱ�ȭ�ϴµ� ���Ǵ� ���� �̸�
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;//���� �̸��� ũ��
	ofn.lpstrFilter = L"bmp\0*.bmp\0ALL\0*.*";//ǥ�ù��ڿ�, bmp���ϰ� �������
	ofn.nFilterIndex = 1;//�⺻ ���͸� �� �Ұų�
	ofn.lpstrFileTitle = NULL;//������ ���� �̸� �� Ȯ����
	ofn.nMaxFileTitle = 0;//������ ����Ű�� ������ ũ��, ���� null�̸� ����
	ofn.lpstrInitialDir = strTileFolderPath.c_str();//�ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) != 0)//�ҷ��ִ� �Լ�
	{
		TCHAR	FileName[128] = {};
		//��θ� �޾ƿͼ�
		_wsplitpath_s(szFilePath, nullptr, 0, nullptr, 0, FileName, 128, nullptr, 0);

		char	TextureName[128] = {};

		//��θ� �ε��ϰ�

		//texture�� ã�´�

		//Size�� �޾ƿ´�

		//wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		//strFilePath += L"texture\\test.tex";
		////�̹��� �ҷ�����
		//FILE* pFile = nullptr;
		//_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

		//CSelectBG* selectbg = new CSelectBG;
		//selectbg->SetPos(Vec2(1.f, 1.f));
		//AddObject(selectbg, LAYER::BACKGROUND);

		//const vector<CObj*> vecTile = GetLayer(LAYER::BACKGROUND);
		//for (size_t i = 0; i < vecTile.size(); i++)
		//{
		//	((CSelectBG*)vecTile[i])->Load(pFile);
		//}


	}
	
}
//=========================================================================
//==============================Editor Tool================================
//=========================================================================
INT_PTR CALLBACK Editor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg, CollisionSizeX, 0, TRUE);
		SetDlgItemInt(hDlg, CollisionSizeY, 0, TRUE);
		SetDlgItemInt(hDlg, CollisionPosX, 0, TRUE);
		SetDlgItemInt(hDlg, CollisionPosY, 0, TRUE);
		SetDlgItemInt(hDlg, MonsterPosX, 0, TRUE);
		SetDlgItemInt(hDlg, MonsterPosY, 0, TRUE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//�Ϸ�
		case CreateTileButton:
		{
			float iCollisionSizeX = GetDlgItemInt(hDlg, CollisionSizeX, nullptr, true);//X��
			float iCollisionSizeY = GetDlgItemInt(hDlg, CollisionSizeY, nullptr, true);
			float iCollisionPosX = GetDlgItemInt(hDlg, CollisionPosX, nullptr, true);
			float iCollisionPosY = GetDlgItemInt(hDlg, CollisionPosY, nullptr, true);

			if (!(iCollisionSizeX && iCollisionSizeY ))
			{
				//��� �ؽ�Ʈ ������ִ� �Լ�
				MessageBox(nullptr, L"�浹ü ����� �����ϼ���", L"Ÿ�� ���� ����", MB_OK);
				return (INT_PTR)TRUE;
			}
			else if (!(iCollisionPosY && iCollisionPosY))
			{
				//��� �ؽ�Ʈ ������ִ� �Լ�
				MessageBox(nullptr, L"�浹ü ���� ��ġ�� �����ϼ���", L"Ÿ�� ���� ����", MB_OK);
				return (INT_PTR)TRUE;
			}

			level->CreateColliderBox(iCollisionPosY, iCollisionPosY,
				iCollisionSizeX, iCollisionSizeY);
		}
			break;

			//1.������
		case LoadBackgroundButton:
		{
			level->LoadBackground();
		}
			break;

			//�Ϸ�
		case CreateMonsterButton:
		{
			//CheckBox�� true�� box���� �޾ƿ���
			if (IsDlgButtonChecked(hDlg, WoodCheckBox))//���� üũ�ڽ� ���� �޾ƿ���
			{
				CResMgr::GetInst()->LoadTexture(L"CWood", L"texture\\Monster\\Wood\\Stand\\stand_wood.bmp");
				
				float MonPosX = GetDlgItemInt(hDlg, MonsterPosX, nullptr, true);
				float MonPosY = GetDlgItemInt(hDlg, MonsterPosY, nullptr, true);
				//Monster�� ���� �Ѵ�
				wood = new CWood;
				wood->SetPos(Vec2(MonPosX, MonPosY));
				level->AddObject(wood, LAYER::MONSTER);

			}
			
		}
			break;
		
			//3.������
		case SaveTileMapButton:
			break;

			//4.������
		case LoadTileMapButton:
			break;
		case IDOK:
			DestroyWindow(hDlg);
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}