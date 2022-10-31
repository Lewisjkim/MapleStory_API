#pragma once
#include "CEntity.h"

class CTileMap;
class CObj;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrLayer[(UINT)LAYER::END];

    vector<CObj*>   m_vecTile;  // ȭ��ȿ� ������ Ÿ��

    UINT            m_iTileCountX;//Ÿ�� ���� ����
    UINT            m_iTileCountY;


public:
    UINT GetTileCountX() { return m_iTileCountX; }
    UINT GetTileCountY() { return m_iTileCountY; }

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();  //ĳ������ �����̳� ���걸���� ���°� �ƴ϶� ���۳�Ʈ���� ������ ���������� �ϱ����� �ѹ��� ȣ��Ǵ� �Լ�
    virtual void render(HDC _dc);

    virtual void Enter() = 0;   // ������ ������ �� ȣ�� ��
    virtual void Exit() = 0;    //������ ��� �� ȣ�� �Ǹ鼭 �ϴ� ��
public:
    void AddObject(CObj* _pObj, LAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }
    void DeleteAllObject();
    void DeleteObject(LAYER _eLayer);//Ư�� ���̾ �����
    void CreateTile(UINT _X, UINT _Y);

    void SetFocusedUI(CObj* _pUI);

private:
    void FindTileScreen();

public:
    CLONE_DEACTIVATE(CLevel);//nullptr�� ������ ���� Ŭ�������� ���� �ʿ䰡 ����

public:
    CLevel();
    virtual ~CLevel();
};

