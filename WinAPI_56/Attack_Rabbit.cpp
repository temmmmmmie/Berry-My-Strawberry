#include "pch.h"
#include "Attack_Rabbit.h"

#include "Rabbit.h"
#include "FlipbookPlayer.h"
#include "AssetMgr.h"

#include "Strawberrry.h"
#include "ASound.h"

void Attack_Rabbit::Enter()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(RABBIT_STATE::ATTACK);
	FlipbookPlayer* pflip = OwnerActor->GetComponent<FlipbookPlayer>();
	AssetMgr::GetInst()->FindSound(L"RabbitEat")->Play();
	pflip->Play((int)RABBIT_ANIM::ATTACK, 6.f, 0);
}

void Attack_Rabbit::FinalTick()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);
	if (OwnerActor->GetStrawberry()->GetState() < 1) {
		GetOwner()->ChangeState(L"Idle");
	}
}

void Attack_Rabbit::Exit()
{
}

Attack_Rabbit::Attack_Rabbit()
{
}

Attack_Rabbit::~Attack_Rabbit()
{
}
