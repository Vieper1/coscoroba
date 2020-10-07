#pragma once

#include "CoreMinimal.h"
#include "Cosco_Base_Character.h"
#include "Projectiles/BaseProjectile.h"
#include "Camera/CameraShake.h"
#include "Cosco_Weapons_Character.generated.h"



class UCameraComponent;



#pragma region Weapon Modes
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EWeaponMode : uint8
{
    WS_Airburst		UMETA(DisplayName="Airburst"),
    WS_Gatling	 	UMETA(DisplayName="Gatling"),
	WS_BFG			UMETA(DisplayName="BFG")
};
#pragma endregion










#pragma region Turret Struct
USTRUCT(BlueprintType)
struct FTurret
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ABaseProjectile> ProjectileType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float ProjectileConeAngle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FName SocketName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool IsActive;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<UCameraShake> CameraShakeType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float CameraShakeScale;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float AngleLimit;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FName OriginalTurretSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent * SocketMeshRef;
};
#pragma endregion






#pragma region Controller Settings

UENUM(BlueprintType)
enum class ECameraControl : uint8
{
	TurnRight UMETA(DisplayName = "TurnRight"),
	LookUp    UMETA(DisplayName = "LookUp")
};

UENUM(BlueprintType)
enum class EFireControl : uint8
{
	Airburst   UMETA(DisplayName = "Airburst"),
	Gatling    UMETA(DisplayName = "Gatling")
};

USTRUCT(BlueprintType)
struct FControllerSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muiltiplayer")
		ECameraControl CameraControlSettings = ECameraControl::TurnRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muiltiplayer")
		EFireControl FireSettings = EFireControl::Airburst;
};

#pragma endregion










UCLASS(config = Game)
class BOFOR_API ACoscoWeaponsCharacter : public ACoscoBaseCharacter
{
	GENERATED_BODY()

public:
	ACoscoWeaponsCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




#pragma region Base
public:
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		UCameraComponent * CameraRef;
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		bool bIsFiring;
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		bool bIsFiring2;
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		EWeaponMode CurrentWeaponMode;
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		float RandomRotationOffset;
protected:
	inline void Input_FirePressed();
	inline void Input_FireReleased();
#pragma endregion











	





#pragma region Utility
protected:
	UFUNCTION(Category = Utility, BlueprintPure)
		FQuat GetRandomForwardRotation(const FRotator MuzzleRotation, const float ConeAngle) const;
	void GetSocketMeshReferences();
#pragma endregion




	
#pragma region SpawnProjectile
public:
	UPROPERTY(Category = "Weapon System", EditAnyWhere, BlueprintReadWrite)
		TArray<FTurret> Projectiles;
	UFUNCTION(Category = "Weapon System", BlueprintCallable)
		void Fire();
	UFUNCTION(Category = "Weapon System", BlueprintCallable)
		void FireManual(TSubclassOf<ABaseProjectile> ProjectileClass, const FVector SpawnLocation, const FRotator SpawnRotation);
	UFUNCTION(Category = "Weapon System", BlueprintCallable)
		void FireManualWithTurret(const int ProjectileID);
#pragma endregion

#pragma region BDG
public:
	UPROPERTY(Category = "BDG", EditAnyWhere, BlueprintReadWrite)
		bool IsBDGCharging;
	UPROPERTY(Category = "BDG", EditAnyWhere, BlueprintReadWrite)
		float ChargingFrame;
	UPROPERTY(Category = "BDG", EditAnyWhere, BlueprintReadWrite)
		float CurrentCharging;
	UPROPERTY(Category = "BDG", EditAnyWhere, BlueprintReadWrite)
		bool CanFire;
	UPROPERTY(Category = "BDG", EditAnyWhere, BlueprintReadWrite)
		bool bPressFiring;
	UPROPERTY(Category = "BDG", EditAnyWhere, BlueprintReadWrite)
		bool bPressFiring2;
	bool FormerCharging;
#pragma endregion

#pragma region MultiPlayer Setings
public:
	UPROPERTY(Category = "Muiltiplayer", EditAnywhere, BlueprintReadWrite)
		bool IsOnline = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muiltiplayer")
		FControllerSettings ControllerSettings;
#pragma endregion
};