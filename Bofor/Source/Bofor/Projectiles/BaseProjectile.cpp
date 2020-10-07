// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"


////////////////////////////////////////////////////////////////////// INIT
ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollision"));
	SphereCollision->SetCollisionProfileName(FName("OverlapAll"));
	RootComponent = SphereCollision;

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("TrailParticle"));
	TrailParticle->SetupAttachment(SphereCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile"));
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
		 ProjectileMovementComponent->Velocity = FVector(1, 0, 0);
	}

	InitialLifeSpan = 5.0f;
}
////////////////////////////////////////////////////////////////////// INIT














////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (MuzzleFlashParticle)
	{
		if (InstigatorMesh)
		{
			UGameplayStatics::SpawnEmitterAttached(
				MuzzleFlashParticle,
				InstigatorMesh,
				InstigatorSocket,
				GetActorLocation(),
				InstigatorMesh->GetForwardVector().Rotation(),
				FVector::OneVector * MuzzleFlashScale,
				EAttachLocation::KeepWorldPosition,
				true,
				EPSCPoolMethod::AutoRelease
			);
		}
		else
		{
			FTransform spawnTransform = GetActorTransform();
			spawnTransform.SetScale3D(FVector::OneVector * MuzzleFlashScale);
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				MuzzleFlashParticle,
				spawnTransform,
				true,
				EPSCPoolMethod::None);
		}
	}
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK