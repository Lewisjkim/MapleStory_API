#include "pch.h"
#include "CUI.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTexture.h"


CUI::CUI() :
	m_pParentUI(nullptr),
	m_pIdleTex(nullptr),
	m_bLbtnDown(false),
	m_bMouseOn(false),
	m_bCmrAfctd(false)
{
}

CUI::CUI(const CUI& _other)
	: CObj(_other)
	, m_pParentUI(nullptr)
	, m_pIdleTex(_other.m_pIdleTex)
	, m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bCmrAfctd(_other.m_bCmrAfctd)
{
	for (size_t i = 0; i < _other.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::tick()
{
	//��ġ ���
	m_vFinalPos = GetPos();

	if (m_pParentUI)
	{
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	MouseOnCheck();//���콺 on üũ

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}
}

void CUI::render(HDC _dc)
{
	HPEN hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC �� ���� ��� �귯�ø� ���� ������ �͵�� ��ü�Ѵ�
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = GetPos();//���� ��ġ
	if (m_bCmrAfctd)//ī�޶� ���� �޾� ��ġ�� �޶����ٸ�
	{
		CCamera::GetInst()->GetRenderPos(vPos);
	}

	Vec2 vScale = GetScale();//���� ũ��

	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));//Left top�� ������ ũ�� ��ŭ

	// DC �� GDI ������Ʈ���� ������ ��� �귯�÷� �ǵ�����.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);


	render_childUI(_dc);
}

void CUI::render_childUI(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::SetIdleTex(CTexture* _pTex)
{
	m_pIdleTex = _pTex;

	if (nullptr != m_pIdleTex)//Texture��ü�� ������� �ʴٸ�
	{
		Vec2 vScale = Vec2((float)m_pIdleTex->Width(), (float)m_pIdleTex->Height());//��ü�� ���ο� , ���θ� vScale�� �����ϰ�
		SetScale(vScale);//ũ�⸦ �����ض�
	}
}

void CUI::MouseOnCheck()
{
	//���콺 ���� ��ġ Ȯ��
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;
	//ī�޶� ������ �޴´ٸ�
	if (m_bCmrAfctd)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);//������ǥ�� �ٲپ��ش�
	}

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}