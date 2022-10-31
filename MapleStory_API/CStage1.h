#pragma once
#include "CLevel.h"
class CStage1 :
    public CLevel
{
public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CStage1();
    ~CStage1();
};

