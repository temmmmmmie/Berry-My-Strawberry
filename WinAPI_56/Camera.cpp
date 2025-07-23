#include "pch.h"
#include "Camera.h"

#include "Engine.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

#include "AssetMgr.h"
#include "ATexture.h"

Camera::Camera()
	: m_CamSpeed(500.f)
{
	Vec2 Resol = Engine::GetInst()->GetResolution();
	m_Look = Vec2(Resol.x / 2.f, Resol.y / 2.f);

}

Camera::~Camera()
{

}



void Camera::init()
{
	glGenTextures(1, &m_Camtex);
	glBindTexture(GL_TEXTURE_2D, m_Camtex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void Camera::Tick()
{

	// 카메라 진동효과
	Oscillation();

	// 화면 중심과, 카메라가 바라보는 위치 차이값 계산(RenderPos 구할 때 사용하기 위해서)
	CalcDiff();

	// Camera Effect 후처리 계산
	CalcCamEffect();
}

void Camera::Render()
{
	if (m_CamEffectAlpha <= 0.05f)
		return;

	// Save current matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(1, 0, 0, 1, -1, 1); // NDC 맞춤

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set fade color
	glColor4f(0.0f, 0.0f, 0.0f, m_CamEffectAlpha);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Camtex);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2i(0, 0);
	glTexCoord2d(1, 0); glVertex2i(1, 0);
	glTexCoord2d(1, 1); glVertex2i(1, 1);
	glTexCoord2d(0, 1); glVertex2i(0, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW); // restore state
}

void Camera::Move()
{
	// 카메라 이동시키기
	if (KEY_PRESSED(KEY::LEFT))
		m_Look.x -= m_CamSpeed * DT;
	if (KEY_PRESSED(KEY::RIGHT))
		m_Look.x += m_CamSpeed * DT;
	if (KEY_PRESSED(KEY::UP))
		m_Look.y -= m_CamSpeed * DT;
	if (KEY_PRESSED(KEY::DOWN))
		m_Look.y += m_CamSpeed * DT;
}

void Camera::Oscillation()
{
	if (!m_bOscillation)
		return;

	// 이번 프레임에 카메라 오프셋의 변화량
	float fMove = (m_Amplitude * 4.f) * m_Frequency * m_fOscillationDir * DT;

	// 오프셋에 변화량 적용
	m_OffsetLook.y += fMove;

	// 진폭을 초과해서 넘어갔다면
	if (m_Amplitude < fabs(m_OffsetLook.y))
	{
		// 진행방향을 반전시킨다.
		m_fOscillationDir *= -1.f;

		// 초과한 분량을 반대방향에 적용시켜준다.
		float fExcess = fabs(m_OffsetLook.y) - m_Amplitude;
		m_OffsetLook.y += fExcess * m_fOscillationDir;
	}

	m_OscillationTime += DT;

	if (m_OscillationDuration < m_OscillationTime)
	{
		m_OffsetLook = Vec2(0.f, 0.f);
		m_bOscillation = false;
	}
}

void Camera::CalcDiff()
{
	// 해상도 중앙위치
	Vec2 Resol = Engine::GetInst()->GetResolution();
	Vec2 ResoluCenter = Vec2(Resol.x / 2.f, Resol.y / 2.f);


	
	// 해상도 중앙위치와 카메라가 보는 위치의 차이값을 계산
	m_Diff = (m_Look + m_OffsetLook) - ResoluCenter;

	DrawDebugRect(ResoluCenter, Vec2(50.f, 50.f), PEN_TYPE::MAGENTA, 0.f);
	DrawDebugLine(ResoluCenter - Vec2(0.f, 50.f), ResoluCenter + Vec2(0.f, 50.f), PEN_TYPE::MAGENTA, 0.f);
	DrawDebugLine(ResoluCenter - Vec2(50.f, 0.f), ResoluCenter + Vec2(50.f, 0.f), PEN_TYPE::MAGENTA, 0.f);
}

void Camera::CalcCamEffect()
{
	if (m_listEffect.empty())
		return;

	tCamEffect& effect = m_listEffect.front();

	// 효과 진행비율(0~1사이)
	float Ratio = effect.CurTime / effect.Duration;

	// 1 -> 0
	if (CAM_EFFECT::FADE_IN == effect.Effect)
	{
		m_CamEffectAlpha = 1.f - Ratio;
	}

	// 0 -> 1
	else if (CAM_EFFECT::FADE_OUT == effect.Effect)
	{
		m_CamEffectAlpha = Ratio;
	}

	if (1.f < m_CamEffectAlpha)
		m_CamEffectAlpha = 1.f;
	else if (m_CamEffectAlpha < 0.f)
		m_CamEffectAlpha = 0.f;


	effect.CurTime += DT;
	if (effect.Duration < effect.CurTime)
	{
		if (CAM_EFFECT::FADE_IN == effect.Effect)
			m_CamEffectAlpha = 0.f;
		else if (CAM_EFFECT::FADE_OUT)
			m_CamEffectAlpha = 1.f;
		if (effect.Callback)
			effect.Callback();
		m_listEffect.pop_front();
	}
}

Vec2 Camera::GetRenderPos(Vec2 _RealPos)
{
	return _RealPos - m_Diff;
}

Vec2 Camera::GetRealPos(Vec2 _RenderPos)
{
	return _RenderPos + m_Diff;
}