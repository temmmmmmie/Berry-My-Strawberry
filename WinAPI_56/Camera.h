#pragma once
#include <gl/GL.h>

typedef void (*CAM_EFFECT_CALLBACK)();

// PostProcess (후처리)
// 안개, 왜곡, 안티앨리어싱(계단현상 완화)
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
	Vec2		m_Diff; // 해상도 중심위치과, 카메라 Look 위치의 차이값
	float		m_CamSpeed;

	// 카메라 진동
	bool		m_bOscillation;			// 진동효과 On / Off
	float		m_Frequency;			// 초당 진동수
	float		m_Amplitude;			// 진폭
	float		m_OscillationDuration;	// 진동효과 유지시간
	float		m_OscillationTime;		// 진동 진행시간
	float		m_fOscillationDir;		// 진행방향

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

