#include "pch.h"
#include "Die_Rabbit.h"

#include "AssetMgr.h"
#include "LevelMgr.h"
#include "Level.h"
#include "Level_Stage01.h"
#include "Rabbit.h"
#include "FlipbookPlayer.h"
#include "ASound.h"
void Die_Rabbit::Enter()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(RABBIT_STATE::DIE);
	FlipbookPlayer* pflip = OwnerActor->GetComponent<FlipbookPlayer>();
	DIR dir = OwnerActor->GetDir();
	pflip->SetSpriteIdx(0);
	pflip->SetCallback(bind(&Die_Rabbit::DestroyRabbit, this));

	AssetMgr::GetInst()->FindSound(L"RabbitDie")->Play();
	if(dir == DIR::LEFT)
		pflip->Play((int)RABBIT_ANIM::DIE_LEFT, 6.f, 1);
	else
		pflip->Play((int)RABBIT_ANIM::DIE_RIGHT, 6.f, 1);

}

void Die_Rabbit::FinalTick()
{
}

void Die_Rabbit::Exit()
{
}

void Die_Rabbit::DestroyRabbit()
{
	Rabbit* OwnerActor = dynamic_cast<Rabbit*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->Destroy();

	FlipbookPlayer* pflip = OwnerActor->GetComponent<FlipbookPlayer>();
	pflip->DeleteCallback();
}

Die_Rabbit::Die_Rabbit()
{
}

Die_Rabbit::~Die_Rabbit()
{
}
