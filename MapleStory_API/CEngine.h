#pragma once

class CTexture;

class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;
	HWND		m_hMainWnd;
	HDC			m_hDC;
	POINT		m_ptResolution;
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];

	CTexture* m_pMemTex;
public:
	HINSTANCE GetMainInstance() { return m_hInst; }
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }

	void ChangeWindowSize(UINT _iWidth, UINT _iHeight);
public:
	void init(HWND _hwnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();	// °»½Å
	void render();	// ·»´õ¸µ
	void CreatePenBrush();
};