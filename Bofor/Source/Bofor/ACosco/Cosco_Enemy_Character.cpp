#include "Cosco_Enemy_Character.h"
#include "Engine/Engine.h"






////////////////////////////////////////////////////////////////////// INIT
ACoscoEnemyCharacter::ACoscoEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoscoEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
////////////////////////////////////////////////////////////////////// INIT











////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void ACoscoEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACoscoEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK