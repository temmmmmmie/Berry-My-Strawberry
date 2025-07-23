#pragma once
class Level_Stage01;
class Text;

#define TIMELIMIT 120;
#define STRAWBERRYGOAL 10;
#define RABBITINTERVAL 10;
class GameMgr
{
	SINGLE(GameMgr);
private:
	vector<DelayedTask> m_DelayedTasks;

	Text* m_ScoreText;
	Text* m_TimerText;
	float m_Timelimit = TIMELIMIT;
	float m_CurSec;

	int m_Rabbitinterval = RABBITINTERVAL;
	
	UINT m_StrawberryGoal = STRAWBERRYGOAL;
	UINT m_StrawberryCount;

	Level_Stage01* m_StageLevel;

	bool Ended;
	bool Pause;
public:
	UINT GetStrawberry() { return m_StrawberryCount; }
	void AddStrawberry() { ++m_StrawberryCount; }
	UINT GetStrawberryGoal() { return m_StrawberryGoal; }
	void AddDelay(DelayedTask _tesk) { m_DelayedTasks.push_back(_tesk); }

	void SetLevel(Level_Stage01* _level) { m_StageLevel = _level; }
	Level_Stage01* GetStageLevel(){ if(m_StageLevel)return m_StageLevel; }
	void SetScoreText(Text* _txt) { m_ScoreText = _txt; }
	void SetTimerText(Text* _txt) { m_TimerText = _txt; }
	void init();
	void tick();
	void Setpause(bool _switch) { Pause = _switch; }
	bool Getpause() { return Pause; }
	void UpdateCor(float deltaTime);

	void Resetool(ITEMS _exclude = ITEMS::NONE);
	void Enabletool(ITEMS _exclude);
};

