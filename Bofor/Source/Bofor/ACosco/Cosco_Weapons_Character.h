// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu
#pragma once

#include "CoreMinimal.h"
#include "Cosco_Base_Character.h"
#include "Projectiles/BaseProjectile.h"
#include "Camera/CameraShake.h"
#include "Cosco_Weapons_Character.generated.h"



class UCameraComponent;



// Enum useful before we switched to using one gun per player
#pragma region Weapon Modes
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EWeaponMode : uint8
{
    WS_Airburst		UMETA(DisplayName="Airburst"),
    WS_Gatling	 	UMETA(DisplayName="Gatling"),
	WS_BFG			UMETA(DisplayName="BFG")
};
#pragma endregion









/*
* Vieper1
* This is an innovative way of selectively FIRING projectiles
* from a set of bones (With muzzle sockets) we're assuming to be weapons
* E.g. 10 ships on one gun, and you can cleanly control which ones to fire from, using this logic
*
* I came up with this logic when I thought we could write a BONE CONTROl LOGIC for those weapon bones
* on the ENEMY SHIPS to automatically look at the player (While locking up when going out of angle)
* 
* This would allow you to selectively fire from the ones are actually facing the player ship
*
* [Configs allow changing per-gun-properties without having to edit a blueprint]
*/
#pragma region Turret Struct
USTRUCT(BlueprintType)
struct FTurret
{
	GENERATED_BODY()

	// Subclass of the projectile class
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ABaseProjectile> ProjectileType;

	// Fire error cone angle
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float ProjectileConeAngle;

	// Socket to fire projectile from
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FName SocketName;

	// Is weapon usable?
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool IsActive;

	// Which Camera Shake to apply for which gun (Only to be used with the Player Ship)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<UCameraShake> CameraShakeType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float CameraShakeScale;

	// Angle lock for the weapon (E.g. A surface gun can't turn more than 90 Degs since it'll hit itself after)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float AngleLimit;

	// If you have a dummy bone to just angle lock with, instead of some PerTick angle calculation
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FName OriginalTurretSocketName;

	// Which Mesh/ChildMesh has the socket to the gun we need
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




	////////////////////////////////////////////////////////////////////// EVENTS
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	////////////////////////////////////////////////////////////////////// EVENTS









	////////////////////////////////////////////////////////////////////// CORE
#pragma region Base
public:
	// Camera's Ref to calculate spawn transform from
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		UCameraComponent * CameraRef;

	// Toggles for individual guns (After separating gun controls)
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		bool bIsFiring;
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		bool bIsFiring2;

	// Gun Mode (Before separating gun controls)
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		EWeaponMode CurrentWeaponMode;

	// Dirty variable to hold random cone angles
	UPROPERTY(Category = "Weapon System", EditAnywhere, BlueprintReadWrite)
		float RandomRotationOffset;

	// Inputs (Before separation | Fire primary)
protected:
	inline void Input_FirePressed();
	inline void Input_FireReleased();
#pragma endregion
	////////////////////////////////////////////////////////////////////// CORE










	




	////////////////////////////////////////////////////////////////////// UTILITY
#pragma region Utility
protected:
	// Get random rotation to simulate firing error/recoil
	UFUNCTION(Category = Utility, BlueprintPure)
		FQuat GetRandomForwardRotation(const FRotator MuzzleRotation, const float ConeAngle) const;
	
	// Find and store all sockets we need to fire projectiles from
	void GetSocketMeshReferences();
#pragma endregion
	////////////////////////////////////////////////////////////////////// UTILITY










	////////////////////////////////////////////////////////////////////// SPAWN PROJECTILE
#pragma region SpawnProjectile
public:
	// Array of structs storing gun properties
	UPROPERTY(Category = "Weapon System", EditAnyWhere, BlueprintReadWrite)
		TArray<FTurret> Projectiles;

	// Fire every active weapon from the turret list
	UFUNCTION(Category = "Weapon System", BlueprintCallable)
		void Fire();

	// Fire using reference to turret
	UFUNCTION(Category = "Weapon System", BlueprintCallable)
		void FireManualWithTurret(const int ProjectileID);

	// Fire individual turret in full manual (Specify spawn transform to fire)
	UFUNCTION(Category = "Weapon System", BlueprintCallable)
		void FireManual(TSubclassOf<ABaseProjectile> ProjectileClass, const FVector SpawnLocation, const FRotator SpawnRotation);
#pragma endregion
	////////////////////////////////////////////////////////////////////// SPAWN PROJECTILE
















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