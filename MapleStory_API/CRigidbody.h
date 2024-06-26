#pragma once
#include "CComponent.h"

class CRigidbody :
    public CComponent
{
private:
    Vec2    m_vForce;           // 힘
    Vec2    m_vVelocity;        // 속도 ( vector )
    float   m_fMass;            // 질량

    float   m_fFriction;        // 마찰력
    float   m_fFrictionScale;   // 마찰계수

    float   m_fVelocityLimit;   // 제한 속도
    float   m_fGravityVLimit;   // 중력에 의한 제한 속도


    float   m_fGravityAccel;    // 중력 가속도 설정
    bool    m_bGravityUse;      // 중력 사용여부
    bool    m_bGround;          // 땅 체크


public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }

    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vec2 _vAddV) { m_vVelocity += _vAddV; }//원래 속도 + 추가 속도

    void SetFriction(float _f) { m_fFriction = _f; }
    void SetFrictionScale(float _f) { m_fFrictionScale = _f; }
    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }
    void SetGround(bool _bGround);

public:
    CLONE(CRigidbody);

public:
    CRigidbody(CObj* _pOwner);
    CRigidbody(const CRigidbody& _other);
    virtual ~CRigidbody();
};

