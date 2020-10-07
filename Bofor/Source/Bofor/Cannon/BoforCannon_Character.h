// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter/BaseCharacter.h"
#include "SocketConnection/SocketConnectionClient.h"
#include "Components/BoxComponent.h"
#include "BoforCannon_Character.generated.h"


class UCameraComponent;


UCLASS(config = Game)
class ABoforCannon_Character : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABoforCannon_Character();
	~ABoforCannon_Character();

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent *MyCollider;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *MyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponDamage;

protected:
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Movement
	void AddPitchInput(const float Input);
	void AddYawInput(const float Input);


public:

	// Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Movement")
		float CurrentLookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Movement")
		float CurrentTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float BaseTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float BaseLookUpRate;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float InputLerpSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float InputMultiplier;

















	////////////////////////////////////////////////////////////////////// Socket Programming
public:
	
	FSocket* m_Socket;
	uint8* m_Data;
	int32 BufferSize = 4;
	int32 BytesRead;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		bool m_ConnectToServer=false;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_bufferSize;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_1;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_2;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_3;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_4;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_port;

	UPROPERTY(Category = Output, EditAnywhere, BlueprintReadWrite)
		FString output;
};

