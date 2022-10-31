#pragma once
#include "CEntity.h"

#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidbody;
class CSAI;

class CObj :
    public CEntity
{
private:
    Vec2        m_vPos;
    Vec2        m_vScale;
    
    CCollider* m_pCollider;
    CAnimator* m_pAnimator;
    CRigidbody* m_pRigidbody;
    CSAI* m_pAI;

    bool        m_bDead;


public:
    void SetPos(Vec2 _v) { m_vPos = _v; }
    Vec2 GetPos() { return m_vPos; }

    void SetScale(Vec2 _v) { m_vScale = _v; }
    Vec2 GetScale() { return m_vScale; }

    void CreateCollider();
    void CreateAnimator();
    void CreateRigidbody();
    void CreateAI();

    CCollider* GetCollider() { return m_pCollider; }
    CAnimator* GetAnimator() { return m_pAnimator; }
    CRigidbody* GetRigidbody() { return m_pRigidbody; }
    CSAI* GetAI() { return m_pAI; }

public:
    virtual void tick();
    virtual void final_tick() final;
    virtual void render(HDC _dc);

    virtual void BeginOverlap(CCollider* _pOther) {}
    virtual void OnOverlap(CCollider* _pOther) {}
    virtual void EndOverlap(CCollider* _pOther) {}

public:
    bool IsDead() { return m_bDead; }//죽었는지 물어보기
    void SetDead();//죽은 상태로 만들기

public:
    virtual CObj* Clone() = 0;

public:
    CObj();
    CObj(const CObj& _other);
    virtual ~CObj();

    friend class CEventMgr;
};

