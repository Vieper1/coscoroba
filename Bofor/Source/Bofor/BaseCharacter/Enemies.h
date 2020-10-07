// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemies.generated.h"

/**
 * 
 */

class UCameraComponent;


UCLASS(config = Game)
class AEnemies : public ABaseCharacter
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

public:
	AEnemies();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bIsAlive = true;


protected:
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	//FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;

	void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Movement
	void AddPitchInput(const float Input);
	void AddYawInput(const float Input);

	


public:
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	// Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float CurrentLookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float CurrentTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float BaseTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float BaseLookUpRate;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float InputLerpSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float InputMultiplier;
	
};
