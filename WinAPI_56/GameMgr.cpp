#include "pch.h"

#include "Player.h"
#include "Level_Stage01.h"
#include "Level_Ending.h"
#include "TimeMgr.h"
#include "Tool.h"
#include "Text.h"
#include "Camera.h"
#include "GameMgr.h"
#include "LevelMgr.h"
#include "RenderMgr.h"

void GameMgr::init()
{
	Pause = false;
	Ended = false;
	m_Timelimit = TIMELIMIT;
	m_Rabbitinterval = m_Timelimit - RABBITINTERVAL;
	m_CurSec = m_Timelimit;
	m_StrawberryCount = 0;
}
void GoEndLevel() {
	GameMgr::GetInst()->SetScoreText(nullptr);
	GameMgr::GetInst()->SetTimerText(nullptr);
	ChangeLevel(LEVEL_TYPE::ENDING);
}

void GameMgr::tick()
{
	UpdateCor(DT);
	if (Ended || Pause) return;
	if (m_CurSec <= 0) {
		Camera::GetInst()->AddCamEffect(FADE_OUT, 1, GoEndLevel);
		Camera::GetInst()->AddCamEffect(FADE_IN, 0.7f);
		Ended = true;
		return;
	}
	m_CurSec -= DT;
	if (m_CurSec <= m_Rabbitinterval) {
		m_Rabbitinterval -= RABBITINTERVAL;
		m_StageLevel->SpawnRabbit(1);
	}
	int min = (int)m_CurSec / 60;
	int sec = (int)m_CurSec - min * 60;
	wstring time;
	if(sec < 10) time = to_wstring(min) + L" : 0" + to_wstring(sec);
	else time = to_wstring(min) + L" : " + to_wstring(sec);
	if(m_ScoreText)m_ScoreText->SetText(std::to_wstring(m_StrawberryCount));
	if(m_ScoreText && m_ScoreText->GetText() == L"10") m_ScoreText->SetPos(Vec2(56 + 15, 95 + 50));
	if(m_TimerText)m_TimerText->SetText(time);
}

void GameMgr::UpdateCor(float deltaTime)
{
	for (int i = 0; i < m_DelayedTasks.size(); )
	{
		m_DelayedTasks[i].Elapsed += deltaTime;
		if (m_DelayedTasks[i].Elapsed >= m_DelayedTasks[i].Delay)
		{
			m_DelayedTasks[i].Callback();
			m_DelayedTasks.erase(m_DelayedTasks.begin() + i);
		}
		else ++i;
	}
}

void GameMgr::Resetool(ITEMS _exclude)
{
	//disable collider
	vector<Actor*> interactables = m_StageLevel->GetActor(INTERACTABLE);
	for (auto i : interactables)
	{
		Tool* tool = dynamic_cast <Tool*>(i);
		if (tool) tool->GetCollider()->m_Enabled = false;
	}

	m_DelayedTasks.push_back({
		1,
		0.0f,
		[this, _exclude]() { this->Enabletool(_exclude); }
		});


}

void GameMgr::Enabletool(ITEMS _exclude)
{
	vector<Actor*> interactables = m_StageLevel->GetActor(INTERACTABLE);
	for (auto i : interactables)
	{
		Tool* tool = dynamic_cast <Tool*>(i);
		if (tool) {
			if ((UINT)tool->GetTooltype() == (UINT)_exclude - 1) {
				tool->Disable();
			}
			else
			{
				tool->Enable();
			}
		}
	}
}

GameMgr::GameMgr()
{
	Ended = true;
};
GameMgr::~GameMgr() {};
