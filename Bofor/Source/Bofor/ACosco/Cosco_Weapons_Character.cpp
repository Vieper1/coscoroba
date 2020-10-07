#include "Cosco_Weapons_Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


////////////////////////////////////////////////////////////////////// INIT
ACoscoWeaponsCharacter::ACoscoWeaponsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoscoWeaponsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACoscoWeaponsCharacter::Input_FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACoscoWeaponsCharacter::Input_FireReleased);
}
////////////////////////////////////////////////////////////////////// INIT











////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void ACoscoWeaponsCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetSocketMeshReferences();
}

void ACoscoWeaponsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK














////////////////////////////////////////////////////////////////////// UTILITY
FQuat ACoscoWeaponsCharacter::GetRandomForwardRotation(const FRotator MuzzleRotation, const float ConeAngle) const
{
	const FRotator randRotation = UKismetMathLibrary::RandomRotator();
	const FRotator randForwardRotation = UKismetMathLibrary::Multiply_RotatorFloat(randRotation, ConeAngle / 360.0f);
	const FRotator muzzleRotationWithoutZ = FRotator(MuzzleRotation.Pitch, MuzzleRotation.Yaw, 0);

	return UKismetMathLibrary::ComposeRotators(randForwardRotation, muzzleRotationWithoutZ).Quaternion();
}

void ACoscoWeaponsCharacter::GetSocketMeshReferences()	// To be called in BeginPlay()
{
	for (FTurret & turret : Projectiles)
	{
		TArray<USceneComponent*> components;
		RootComponent->GetChildrenComponents(true, components);
		for (USceneComponent * component : components)
		{
			USkeletalMeshComponent * meshComponent = Cast<USkeletalMeshComponent>(component);
			if (meshComponent && meshComponent->DoesSocketExist(turret.SocketName))
			{
				turret.SocketMeshRef = meshComponent;
				break;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////// UTILITY











////////////////////////////////////////////////////////////////////// INPUT
void ACoscoWeaponsCharacter::Input_FirePressed()
{
	//bIsFiring = true;
}

void ACoscoWeaponsCharacter::Input_FireReleased()
{
	//bIsFiring = false;
}

////////////////////////////////////////////////////////////////////// INPUT










/////////////////////////////////////////////////////////////////////// Fire
void ACoscoWeaponsCharacter::Fire()			// We need to figure out a better way to do this
{
	for (FTurret projectile : Projectiles)
	{
		if (!projectile.IsActive) continue;
		if (!projectile.SocketMeshRef)
		{
			UE_LOG(LogTemp, Warning, TEXT("No USkeletalMeshComponent with socket given found!"));
			continue;
		}

		
		FTransform spawnTransform = projectile.SocketMeshRef->GetSocketTransform(projectile.SocketName, ERelativeTransformSpace::RTS_World);
		spawnTransform.SetRotation(GetRandomForwardRotation(spawnTransform.Rotator(), projectile.ProjectileConeAngle));
		spawnTransform.SetScale3D(FVector::OneVector);
		ABaseProjectile * spawnedObject = GetWorld()->SpawnActorDeferred<ABaseProjectile>(projectile.ProjectileType, spawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		if (spawnedObject)
		{
			spawnedObject->InstigatorActor = this;
			spawnedObject->InstigatorMesh = projectile.SocketMeshRef;
			spawnedObject->InstigatorSocket = projectile.SocketName;
			UGameplayStatics::FinishSpawningActor(spawnedObject, spawnTransform);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Projectile failed to spawn! %hs @ %d"), __FILE__, __LINE__);
			return;
		}

		
		if (projectile.CameraShakeType)
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(projectile.CameraShakeType, projectile.CameraShakeScale, ECameraAnimPlaySpace::CameraLocal);
	}
}

void ACoscoWeaponsCharacter::FireManual(TSubclassOf<ABaseProjectile> ProjectileClass, const FVector SpawnLocation, const FRotator SpawnRotation)
{
	const FTransform spawnTransform = FTransform(SpawnRotation, SpawnLocation, FVector::OneVector);
	ABaseProjectile * spawnedObject = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, spawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (spawnedObject)
	{
		spawnedObject->InstigatorActor = this;
		UGameplayStatics::FinishSpawningActor(spawnedObject, spawnTransform);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile failed to spawn! %hs @ %d"), __FILE__, __LINE__);
		return;
	}
}

void ACoscoWeaponsCharacter::FireManualWithTurret(const int projectileID)
{
	if (projectileID < 0 || projectileID > Projectiles.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ProjectileID!"));
		return;
	}

	const int i = projectileID;

	FTransform spawnTransform = Projectiles[i].SocketMeshRef->GetSocketTransform(Projectiles[i].SocketName, ERelativeTransformSpace::RTS_World);
	spawnTransform.SetRotation(GetRandomForwardRotation(spawnTransform.Rotator(), Projectiles[i].ProjectileConeAngle));
	spawnTransform.SetScale3D(FVector::OneVector);
	ABaseProjectile * spawnedObject = GetWorld()->SpawnActorDeferred<ABaseProjectile>(Projectiles[i].ProjectileType, spawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (spawnedObject)
	{
		spawnedObject->InstigatorActor = this;
		spawnedObject->InstigatorMesh = Projectiles[i].SocketMeshRef;
		spawnedObject->InstigatorSocket = Projectiles[i].SocketName;
		UGameplayStatics::FinishSpawningActor(spawnedObject, spawnTransform);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile failed to spawn! %hs @ %d"), __FILE__, __LINE__);
		return;
	}


	if (Projectiles[i].CameraShakeType)
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(Projectiles[i].CameraShakeType, Projectiles[i].CameraShakeScale, ECameraAnimPlaySpace::CameraLocal);
}
/////////////////////////////////////////////////////////////////////// Fire