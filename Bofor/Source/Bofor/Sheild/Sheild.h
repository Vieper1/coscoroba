// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Sheild.generated.h"


UCLASS()
class BOFOR_API ASheild : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASheild();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//UProperties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Settings")
		float ShieldHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Shield Setttings")
		bool IsShieldActive;

	
		

	//UFunctions
	UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		void ShieldTakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		void RespawnShield();

	UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		void DestoryShield();
	
};
