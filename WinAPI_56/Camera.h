#pragma once
#include <gl/GL.h>

typedef void (*CAM_EFFECT_CALLBACK)();

// PostProcess (��ó��)
// �Ȱ�, �ְ�, ��Ƽ�ٸ����(������� ��ȭ)
enum CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
};

struct tCamEffect
{
	CAM_EFFECT	Effect;
	float		Duration;
	float		CurTime;
	CAM_EFFECT_CALLBACK Callback;

};

class ATexture;

class Camera
{
	SINGLE(Camera);
private:
	Vec2		m_Look;
	Vec2		m_OffsetLook;
	Vec2		m_Diff; // �ػ� �߽���ġ��, ī�޶� Look ��ġ�� ���̰�
	float		m_CamSpeed;

	// ī�޶� ����
	bool		m_bOscillation;			// ����ȿ�� On / Off
	float		m_Frequency;			// �ʴ� ������
	float		m_Amplitude;			// ����
	float		m_OscillationDuration;	// ����ȿ�� �����ð�
	float		m_OscillationTime;		// ���� ����ð�
	float		m_fOscillationDir;		// �������

	list<tCamEffect>	m_listEffect;
	float				m_CamEffectAlpha;

	GLuint m_Camtex;

public:
	GET_SET(Vec2, Look);
	void SetCamOscillation(float _Frequency, float _Amplitude, float _Duration)
	{
		m_bOscillation = true;
		m_Frequency = _Frequency;
		m_Amplitude = _Amplitude;
		m_OscillationDuration = _Duration;
		m_fOscillationDir = -1.f;
		m_OscillationTime = 0.f;
	}
	void AddCamEffect(CAM_EFFECT _Effect, float _Duration)
	{
		tCamEffect effect = {};

		effect.Effect = _Effect;
		effect.CurTime = 0.f;
		effect.Duration = _Duration;
		effect.Callback = nullptr;

		m_listEffect.push_back(effect);
	}
	void AddCamEffect(CAM_EFFECT _Effect, float _Duration, CAM_EFFECT_CALLBACK onComplete)
	{
		tCamEffect effect = {};

		effect.Effect = _Effect;
		effect.CurTime = 0.f;
		effect.Duration = _Duration;
		effect.Callback = onComplete;

		m_listEffect.push_back(effect);
	}


public:
	Vec2 GetRenderPos(Vec2 _RealPos);
	Vec2 GetRealPos(Vec2 _RenderPos);

public:
	void init();
	void Tick();
	void Render();

private:
	void Move();
	void Oscillation();
	void CalcDiff();
	void CalcCamEffect();
};

