// Fill out your copyright notice in the Description page of Project Settings.

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




#pragma region Projectile
public:
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		USphereComponent * SphereCollision;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * TrailParticle;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		ACoscoBaseCharacter * InstigatorActor;

	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent * InstigatorMesh;
	
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly)
		FName InstigatorSocket;
#pragma endregion





	
#pragma region Hit
	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadWrite)
		UParticleSystem * HitParticle;
#pragma endregion




	
	

#pragma region Muzzle Flash
	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadWrite)
		UParticleSystem * MuzzleFlashParticle;

	UPROPERTY(Category = Projectile, EditAnywhere, BlueprintReadWrite)
		float MuzzleFlashScale;
#pragma endregion
};
