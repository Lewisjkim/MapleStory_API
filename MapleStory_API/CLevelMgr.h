#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr);
private:
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_pCurLevel;

public:
	void init();
	void tick();
	void render(HDC _dc);

private:
	void ChangeLevel(LEVEL_TYPE _eNext);//event mgr에서만 부를 수 있게 private

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }

	friend class CEventMgr;
};

