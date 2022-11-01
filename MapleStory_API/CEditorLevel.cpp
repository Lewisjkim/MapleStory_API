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
	// 카메라 시점
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	//UI배치
	CreateUI();



	// 타일이 사용할 아틀라스 이미지 로딩
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
	// 메뉴바 생성
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_MAPLESTORYAPI));//메뉴바를 불러온다(생성만 되고 부착되지 않았음)
	}

	// 메뉴바 추가로 인한 해상도 재 설정
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, m_hMenu);//메뉴 부착

	//메뉴바가 붙고 나서 윈도우 사이즈를 다시 변경 해줘야 메뉴바 만큼 추가된다
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);


	// 초기 오브젝트 설정
	init();
}

void CEditorLevel::Exit()
{
	// 메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	// 메인 윈도우 크기 재조정
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
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		//tilecount가 타일 개수를 기록하고있기에 가져온다
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

	//button이 사용할 텍스쳐
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

	//Save, Load 버튼을 panel의 자식으로 추가
	pPanel->AddChildUI(pSaveTileButton);
	pPanel->AddChildUI(pLoadTileButton);

	AddObject(pPanel, LAYER::UI);

	//패널 클론 만들기
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

	//wchar_t szFilePath[256] = {};//지역변수로 배열256개 짜리

	//ZeroMemory(&ofn, sizeof(ofn));
	//ofn.lStructSize = sizeof(ofn);
	//ofn.hwndOwner = NULL;
	//ofn.lpstrFile = szFilePath;
	//ofn.lpstrFile[0] = '\0';
	//ofn.nMaxFile = 256;
	//ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";//필터의 이름은 Tile 이고 확장자는 .tile or ALL
	//ofn.nFilterIndex = 1;//기본 필터를 뭘 할거냐
	//ofn.lpstrFileTitle = NULL;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = strTileFolderPath.c_str();//최종경로
	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (false == GetSaveFileName(&ofn))//열어주는 함수 (ofn = 에 옵션값을 넣어서 넘겨주는것)
	//	return;

	////--------------------


	//FILE* pFile = nullptr;
	//_wfopen_s(&pFile, szFilePath, L"wb");

	//// 타일 개로 세로 개수 저장
	//UINT iTileCountX = GetTileCountX();
	//UINT iTileCountY = GetTileCountY();

	//fwrite(&iTileCountX, sizeof(UINT), 1, pFile);
	//fwrite(&iTileCountY, sizeof(UINT), 1, pFile);



	//// 각각의 타일 정보 저장
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

	wchar_t szFilePath[256] = {};//지역변수로 배열256개 짜리

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";//필터의 이름은 Tile 이고 확장자는 .tile or ALL
	ofn.nFilterIndex = 1;//기본 필터를 뭘 할거냐
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();//최종경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))//불러주는 함수 (ofn = 에 옵션값을 넣어서 넘겨주는것)
		return;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"tile\\test.tile";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	// 타일 개로 세로 개수 읽기
	UINT iTileCountX = 0, iTileCountY = 0;

	fread(&iTileCountX, sizeof(UINT), 1, pFile);
	fread(&iTileCountY, sizeof(UINT), 1, pFile);

	// 읽은 개수에 맞게 다시 타일 배치
	CreateTile(iTileCountX, iTileCountY);

	// 배치한 각각의 타일들을 데이터 읽도록
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

	wchar_t szFilePath[256] = {};//지역변수로 배열256개 짜리

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);//구조의 길이
	ofn.hwndOwner = NULL;//대화 상자를 소유한 창
	ofn.lpstrFile = szFilePath;//파일 이름 편집 컨트롤을 초기화하는데 사용되는 파일 이름
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;//파일 이름의 크기
	ofn.lpstrFilter = L"bmp\0*.bmp\0ALL\0*.*";//표시문자열, bmp파일과 모든파일
	ofn.nFilterIndex = 1;//기본 필터를 뭘 할거냐
	ofn.lpstrFileTitle = NULL;//선택한 파일 이름 및 확장자
	ofn.nMaxFileTitle = 0;//위에서 가리키는 문자의 크기, 위가 null이면 무시
	ofn.lpstrInitialDir = strTileFolderPath.c_str();//초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) != 0)//불러주는 함수
	{
		TCHAR	FileName[128] = {};
		//경로를 받아와서
		_wsplitpath_s(szFilePath, nullptr, 0, nullptr, 0, FileName, 128, nullptr, 0);

		char	TextureName[128] = {};

		//경로를 로드하고

		//texture를 찾는다

		//Size를 받아온다

		//wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		//strFilePath += L"texture\\test.tex";
		////이미지 불러오기
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
			//완료
		case CreateTileButton:
		{
			float iCollisionSizeX = GetDlgItemInt(hDlg, CollisionSizeX, nullptr, true);//X축
			float iCollisionSizeY = GetDlgItemInt(hDlg, CollisionSizeY, nullptr, true);
			float iCollisionPosX = GetDlgItemInt(hDlg, CollisionPosX, nullptr, true);
			float iCollisionPosY = GetDlgItemInt(hDlg, CollisionPosY, nullptr, true);

			if (!(iCollisionSizeX && iCollisionSizeY ))
			{
				//띄울 텍스트 만들어주는 함수
				MessageBox(nullptr, L"충돌체 사이즈를 지정하세요", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			else if (!(iCollisionPosY && iCollisionPosY))
			{
				//띄울 텍스트 만들어주는 함수
				MessageBox(nullptr, L"충돌체 생성 위치를 지정하세요", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			level->CreateColliderBox(iCollisionPosY, iCollisionPosY,
				iCollisionSizeX, iCollisionSizeY);
		}
			break;

			//1.진행중
		case LoadBackgroundButton:
		{
			level->LoadBackground();
		}
			break;

			//완료
		case CreateMonsterButton:
		{
			//CheckBox중 true인 box값을 받아오고
			if (IsDlgButtonChecked(hDlg, WoodCheckBox))//몬스터 체크박스 유무 받아오고
			{
				CResMgr::GetInst()->LoadTexture(L"CWood", L"texture\\Monster\\Wood\\Stand\\stand_wood.bmp");
				
				float MonPosX = GetDlgItemInt(hDlg, MonsterPosX, nullptr, true);
				float MonPosY = GetDlgItemInt(hDlg, MonsterPosY, nullptr, true);
				//Monster를 생성 한다
				wood = new CWood;
				wood->SetPos(Vec2(MonPosX, MonPosY));
				level->AddObject(wood, LAYER::MONSTER);

			}
			
		}
			break;
		
			//3.진행중
		case SaveTileMapButton:
			break;

			//4.진행중
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