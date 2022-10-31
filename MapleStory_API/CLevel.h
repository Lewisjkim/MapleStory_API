#pragma once
#include "CEntity.h"

class CTileMap;
class CObj;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrLayer[(UINT)LAYER::END];

    vector<CObj*>   m_vecTile;  // 화면안에 들어오는 타일

    UINT            m_iTileCountX;//타일 가로 개수
    UINT            m_iTileCountY;


public:
    UINT GetTileCountX() { return m_iTileCountX; }
    UINT GetTileCountY() { return m_iTileCountY; }

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();  //캐릭터의 로직이나 연산구조에 쓰는게 아니라 컴퍼넌트들이 마지막 최종연산을 하기위한 한번더 호출되는 함수
    virtual void render(HDC _dc);

    virtual void Enter() = 0;   // 레벨에 진입할 때 호출 됨
    virtual void Exit() = 0;    //레벨을 벗어날 때 호출 되면서 하는 일
public:
    void AddObject(CObj* _pObj, LAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }
    void DeleteAllObject();
    void DeleteObject(LAYER _eLayer);//특정 레이어만 지울것
    void CreateTile(UINT _X, UINT _Y);

    void SetFocusedUI(CObj* _pUI);

private:
    void FindTileScreen();

public:
    CLONE_DEACTIVATE(CLevel);//nullptr로 함으로 하위 클래스들은 만들 필요가 없다

public:
    CLevel();
    virtual ~CLevel();
};

