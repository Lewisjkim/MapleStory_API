#pragma once
#include "CLevel.h"
class CStage2 :
    public CLevel
{
public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CStage2();
    ~CStage2();
};

