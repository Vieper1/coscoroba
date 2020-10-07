// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"
#include "Bofor/Sheild/Sheild.h"


#include "BaseCharacter.generated.h"




UCLASS(config = Game)
class BOFOR_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent * colliderComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent*   m_SplineComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent*    m_RootComponent;
	
	//Spline & Movement Speed
	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
		float               m_AmountToMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float               m_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float               m_DistanceAlongSpline;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		bool                m_LoopOnSpline;
private:
	FVector  m_VectorOnSpline;
	FRotator m_RotationOnSpline;
	
//Health & Damage 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float m_MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float m_AttackPower;
	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
		float m_CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sheild Type")
		TSubclassOf<class ASheild> ShieldComponentBP;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield ")
		ASheild *ShieldReference = nullptr;
	
	 
	//Functions
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void TakeDamage(float i_Damage);
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Healing(float i_Healing);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		void SpawnSheild(FVector ShieldSpawnLocation);

	
};
