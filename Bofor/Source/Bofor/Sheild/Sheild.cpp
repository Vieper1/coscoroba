// Fill out your copyright notice in the Description page of Project Settings.


#include "Sheild.h"

// Sets default values
ASheild::ASheild()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASheild::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASheild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASheild::ShieldTakeDamage(float DamageAmount)
{
	
	if (ShieldHealth > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Taking damage %f"), ShieldHealth);
		ShieldHealth -= DamageAmount;
	}
	else
	{
		
		
		DestoryShield();
		
	}

}

void ASheild::RespawnShield()
{
	UE_LOG(LogTemp, Warning, TEXT("Shield Enabled"));
	ShieldHealth = 100;
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	IsShieldActive = true;
}

void ASheild::DestoryShield()
{
	UE_LOG(LogTemp, Warning, TEXT("Disabling Sheild"));
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	IsShieldActive = false;
	
	
}



