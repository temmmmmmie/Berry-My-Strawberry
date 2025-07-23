#include "pch.h"
#include "Idle_Rabbit.h"

#include "Rabbit.h"
#include "FlipbookPlayer.h"
#include "LevelMgr.h"

#include "Level_Stage01.h"
#include "Strawberrry.h"

void Idle_Rabbit::Enter()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(RABBIT_STATE::IDLE);

	Level_Stage01* Stage1 = dynamic_cast<Level_Stage01*> (LevelMgr::GetInst()->GetCurrentLevel());
	if (!Stage1) return;
	vector< Actor*> Strawberries = Stage1->GetActor(ACTOR_TYPE::STRAWBERRY);
	for (auto i : Strawberries)
		m_Strawberries.push_back(dynamic_cast<Strawberrry*> (i));
}

void Idle_Rabbit::FinalTick()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);
	if (OwnerActor->GetArrived()) OwnerActor->Settarget();
	OwnerActor->Move(OwnerActor->Gettarget());

	DIR Curdir = OwnerActor->GetDir();
	if (Curdir != m_Prevdir) ChangeAnim(Curdir);
	m_Prevdir = Curdir;

	for (auto i: m_Strawberries)
	{
		if (i->GetState() > 1 && i->GetState() < 7) {
			OwnerActor->Settarget(i->GetPos());
			OwnerActor->Settarget(i);
			GetOwner()->ChangeState(L"Trace");
			break;
		}
	}

}

void Idle_Rabbit::Exit()
{
}

void Idle_Rabbit::ChangeAnim(DIR _dir)
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);
	FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
	switch (_dir)
	{
	case DIR::LEFT:
		pFlipbookPlayer->Play((int)RABBIT_ANIM::MOVE_LEFT, 6.f, 0);
		break;
	case DIR::RIGHT:
		pFlipbookPlayer->Play((int)RABBIT_ANIM::MOVE_RIGHT, 6.f, 0);
		break;
	}
}

Idle_Rabbit::Idle_Rabbit()
{
}

Idle_Rabbit::~Idle_Rabbit()
{
}
