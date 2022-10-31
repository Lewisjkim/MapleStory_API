#pragma once
#include "CLevel.h"
class CVillageLevel :
    public CLevel
{
public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CVillageLevel();
    ~CVillageLevel();
};

