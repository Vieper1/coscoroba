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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;













	////////////////////////////////////////////////////////////////////// Ring & Camera
public:
	UPROPERTY(Category = Ship, VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* ShipRing;
	UPROPERTY(Category = Ring, VisibleAnywhere, BlueprintReadOnly)
		float TargetRoll;
	UPROPERTY(Category = Ring, EditAnywhere, BlueprintReadWrite)
		float RollSpeed;

	UPROPERTY(Category = Ship, VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* MainCamera;

	UPROPERTY(Category = Level, EditAnywhere, BluePrintReadWrite)
		bool IsCloudLevel;

	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollTop();
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollRight();
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollBottom();
	UFUNCTION(BlueprintCallable, Category = "Ring Control")
		void Input_RingRollLeft();

protected:
	inline void Tick_RingMovement(const float DeltaSeconds) const;














	////////////////////////////////////////////////////////////////////// Camera Movement
protected:
	void Input_TurnAtRate(float Rate);
	void Input_LookUpAtRate(float Rate);
	void AddPitchInput(const float Input);
	void AddYawInput(const float Input);

	inline void Tick_CameraMovement(const float DeltaSeconds);
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Movement")
		FVector2D PitchRange;
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
	//charging rate
	float CurrentChargingTurn;
	float CurrentChargingUp;



	// Zoom
	UPROPERTY(Category = Zoom, BlueprintReadOnly)
		bool bZoomed = false;
	UPROPERTY(Category = Zoom, EditAnywhere, BlueprintReadWrite)
		float ZoomLerpSpeed;
	UPROPERTY(Category = Zoom, EditAnywhere, BlueprintReadWrite)
		FVector2D ZoomRange;
protected:
	inline void Tick_CameraZoom(const float DeltaSeconds) const;
	void Input_ZoomIn();
	void Input_ZoomOut();
public:
	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void TakeInputForLocalMulPlayer(ECameraControl CameraControlOption, float Input);
	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void UpdateCameraSettings();
};