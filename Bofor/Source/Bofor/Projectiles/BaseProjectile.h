// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class ACoscoBaseCharacter;
class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class BOFOR_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



////////////////////////////////////////////////////////////////////// CORE
#pragma region Projectile
public:
	// Sphere for collision check
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		USphereComponent * SphereCollision;

	// Bullet trail
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * TrailParticle;

	// Projectile movement to simulate bullet
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent * ProjectileMovementComponent;

	// If you know WHO SPAWNED the projectile
	// You can prevent it from exploding in their face
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		ACoscoBaseCharacter * InstigatorActor;

	// Owner's skeleton that spawned it
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent * InstigatorMesh;
	
	// The socket on which we spawned the projectile
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		FName InstigatorSocket;
#pragma endregion
////////////////////////////////////////////////////////////////////// CORE




	
////////////////////////////////////////////////////////////////////// HIT
#pragma region Hit
	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadWrite)
		UParticleSystem * HitParticle;
#pragma endregion
////////////////////////////////////////////////////////////////////// HIT




	
	
////////////////////////////////////////////////////////////////////// MUZZLE
#pragma region Muzzle Flash
	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadWrite)
		UParticleSystem * MuzzleFlashParticle;

	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadWrite)
		float MuzzleFlashScale;
};
#pragma endregion
////////////////////////////////////////////////////////////////////// MUZZLE