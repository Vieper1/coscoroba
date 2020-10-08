// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu

#pragma once

#include "CoreMinimal.h"
#include "Cosco_Weapons_Character.h"
#include <Camera/CameraComponent.h>
#include "Cosco_Camera_Character.generated.h"



UCLASS(config = Game)
class BOFOR_API ACoscoCameraCharacter : public ACoscoWeaponsCharacter
{
	GENERATED_BODY()

public:
	ACoscoCameraCharacter();

	////////////////////////////////////////////////////////////////////// EVENTS
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	////////////////////////////////////////////////////////////////////// EVENTS













	////////////////////////////////////////////////////////////////////// Ring & Camera
public:
	// A container to hold the Camera and the Weapons
	// Can also roll around the ship to help shoot enemies both above and below the ship
	UPROPERTY(Category = Ship, VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* ShipRing;

	// Config for the ShipRing roll motion
	UPROPERTY(Category = Ring, VisibleAnywhere, BlueprintReadOnly)
		float TargetRoll;
	UPROPERTY(Category = Ring, EditAnywhere, BlueprintReadWrite)
		float RollSpeed;

	// Main Player Camera
	UPROPERTY(Category = Ship, VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* MainCamera;


	
	// Functions to be called in the level event scripts
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollTop();
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollRight();
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollBottom();
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollLeft();


	// Operations to be performed in Tick()
protected:
	inline void Tick_RingMovement(const float DeltaSeconds) const;







	









	////////////////////////////////////////////////////////////////////// CAMERA
	////////////////////////////////////////////////// Zoom
protected:
	// Using the stock camera control functions
	void Input_TurnAtRate(float Rate);
	void Input_LookUpAtRate(float Rate);
	void AddPitchInput(const float Input);
	void AddYawInput(const float Input);


	// Operations to be performed in Tick()
	inline void Tick_CameraMovement(const float DeltaSeconds);
	
public:
	// Farthest LookUp and LookDown angle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Movement")
		FVector2D PitchRange;


	// Using a 2 layer input system for SUPER SMOOTH camera control
	// CurrentTurn/LookUp Rates climb LINEARLY when the user applies input
	// BaseTurn/LookUp Rates are the speed LIMITS for the Current Rates
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Movement")
		float CurrentLookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Movement")
		float CurrentTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float BaseTurnRate;
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float BaseLookUpRate;

	// This controls the DAMPING that needs to apply over the Camera Turns
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float InputLerpSpeed;

	// This controls the CLIMB SPEED for the Current Rates
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
		float InputMultiplier;
	////////////////////////////////////////////////// Rotation




	////////////////////////////////////////////////// Zoom
	// Simple LERPING used for zoom controls
	UPROPERTY(Category = Zoom, BlueprintReadOnly)
		bool bZoomed = false;
	UPROPERTY(Category = Zoom, EditAnywhere, BlueprintReadWrite)
		float ZoomLerpSpeed;
	UPROPERTY(Category = Zoom, EditAnywhere, BlueprintReadWrite)
		FVector2D ZoomRange;	// FOV (Low, High)
protected:
	inline void Tick_CameraZoom(const float DeltaSeconds) const;
	void Input_ZoomIn();
	void Input_ZoomOut();
	////////////////////////////////////////////////// Zoom
	////////////////////////////////////////////////////////////////////// CAMERA





	













	UPROPERTY(Category = Level, EditAnywhere, BluePrintReadWrite)
		bool IsCloudLevel;

	float CurrentChargingTurn;
	float CurrentChargingUp;

public:
	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void TakeInputForLocalMulPlayer(ECameraControl CameraControlOption, float Input);
	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void UpdateCameraSettings();
};