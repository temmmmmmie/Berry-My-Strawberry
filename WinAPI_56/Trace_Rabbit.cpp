#include "pch.h"
#include "Trace_Rabbit.h"

#include "Rabbit.h"
#include "Strawberrry.h"
#include "FlipbookPlayer.h"

void Trace_Rabbit::Enter()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(RABBIT_STATE::TRACE);
}

void Trace_Rabbit::FinalTick()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);

	DIR Curdir = OwnerActor->GetDir();
	if (Curdir != m_Prevdir) ChangeAnim(Curdir);
	m_Prevdir = Curdir;

	if (OwnerActor->GetStrawberry()->GetState() == 7)
		GetOwner()->ChangeState(L"Idle");
	else OwnerActor->Move(OwnerActor->Gettarget());

	if (OwnerActor->GetArrived()) GetOwner()->ChangeState(L"Attack");

}

void Trace_Rabbit::ChangeAnim(DIR _dir)
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

void Trace_Rabbit::Exit()
{
}

Trace_Rabbit::Trace_Rabbit()
{
}

Trace_Rabbit::~Trace_Rabbit()
{
}
