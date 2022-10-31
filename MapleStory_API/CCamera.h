#pragma once

class CTexture;


struct tCamEffect
{
	CAMERA_EFFECT	m_eCurEffect;//Fade in, Fade out
	float			m_fAccTime;
	float			m_fMaxTime;
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2				m_vLook;//�����ִ� ����
	Vec2				m_vDiff;//���� ī�޶� �����ִ� �߽� ��ġ�� �ػ��� �߽ɰ��� ���� ��
	CTexture* m_pBlindTex;

	list<tCamEffect>	m_CamEffectList;
	float				m_fRatio;

	Vec2				m_vOffset;
	float				m_fAccTime;		// Camera Shake ���� �ð�
	float				m_fMaxTime;		// Cemar Shake �ִ� �ð�
	float				m_fRange;		// ��鸲 ����
	float				m_fShakeSpeed;	// ��鸮�� �ӵ�
	float				m_fShakeDir;	// ���� ����
	bool				m_bCamShake;

public:
	void tick();
	void render(HDC _dc);

public:
	void SetLook(Vec2 _vLook) { m_vLook = _vLook; }
	Vec2 GetLook() { return m_vLook; }
	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);
	void CameraShake(float _fRange, float _fSpeed, float _fTerm);

public:
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }//������ �� ��ǥ
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

private:
	void CameraEffect();
	void CameraShake();
};

