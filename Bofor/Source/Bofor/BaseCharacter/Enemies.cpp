// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AEnemies::AEnemies()
{
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
/*
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
*/

	WeaponRange = 5000.0f;
	WeaponDamage = 500000.0f;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AEnemies::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Actions

	// Axis
	

}

void AEnemies::Tick(float DeltaSeconds)
{

	// Movement
	
}

void AEnemies::TurnAtRate(float Rate)//A S for player keyboard
{
	AddYawInput(Rate);
}

void AEnemies::LookUpAtRate(float Rate)// W D 
{
	AddPitchInput(Rate);
}







void AEnemies::AddPitchInput(const float Input)
{
	//AI
}

void AEnemies::AddYawInput(const float Input)
{
	//AI
}
