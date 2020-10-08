// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu

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

	// Attach Sphere collider here but override the overlap events in the children
	// Not assigning it here since not all projectiles are going to use it

	// E.g. Gatling projectile will fire the event on Hit/Overlap
	// 		But the airburst will explode from a distance using a bigger outer collider

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollision"));
	SphereCollision->SetCollisionProfileName(FName("OverlapAll"));
	RootComponent = SphereCollision;

	// Trails
	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("TrailParticle"));
	TrailParticle->SetupAttachment(SphereCollision);

	// Spawn & set projectile movement settings
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