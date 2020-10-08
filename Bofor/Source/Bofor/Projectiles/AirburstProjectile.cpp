// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu

#include "AirburstProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Bofor/Cannon/BoforCannon_Character.h"
#include "ACosco/Cosco_Base_Character.h"


////////////////////////////////////////////////////////////////////// INIT
AAirburstProjectile::AAirburstProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Attach the big collider which'll tell us if the airburst is in exploding range
	BigCollider = CreateDefaultSubobject<USphereComponent>(FName("BigCollider"));
	BigCollider->SetCollisionProfileName(FName("OverlapAllDynamic"));
	BigCollider->SetupAttachment(RootComponent);
}
////////////////////////////////////////////////////////////////////// INIT












////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void AAirburstProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Set the countdown time to the Explosion Delay
	time = ExplosionDelay;

	// Ignore collisions with self
	SphereCollision->IgnoreComponentWhenMoving(BigCollider, true);
	BigCollider->IgnoreComponentWhenMoving(SphereCollision, true);
}

void AAirburstProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time -= DeltaTime;

	BigCollider->GetOverlappingActors(overlappingActors, TSubclassOf<ACoscoBaseCharacter>());
	TArray<AActor*> innerSphereOverlappingActors;

	// Figured the OnBeginOverlap is costlier
	// So checking the overlap for a specific class till impact feels lighter

	SphereCollision->GetOverlappingActors(innerSphereOverlappingActors);
	if (innerSphereOverlappingActors.Num() > 0)
		Explode(true);
	

	// Explode automatically upon lifetime completion
	if (time < 0 || overlappingActors.Num() > 0)
		Explode();
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
















////////////////////////////////////////////////////////////////////// Explode
float AAirburstProjectile::CalcRadialDamage(const float distance) const
{
	// Use RemapRange to map your DistanceRange to DamageRange
	const FVector2D distanceRange = FVector2D(MinDistance, MaxDistance);
	const FVector2D damageRange = FVector2D(MinDamage, MaxDamage);
	return FMath::GetMappedRangeValueClamped(distanceRange, damageRange, distance);
}

void AAirburstProjectile::Explode(const bool bForceExplode)
{
	bool confirmExplosion = false;
	
	for (AActor * actor : overlappingActors)
	{
		// Don't explode if it's just close to another projectile
		if (Cast<ABaseProjectile>(actor) || actor == InstigatorActor)
			continue;
		
		const FVector targetActorLocation = actor->GetActorLocation();
		const FVector myLocation = GetActorLocation();
		float hitDistance = FVector::Distance(targetActorLocation, myLocation);

		FHitResult hitResult;
		GetWorld()->LineTraceSingleByChannel(
			hitResult,
			GetActorLocation(),
			targetActorLocation,
			ECollisionChannel::ECC_Visibility);
		if (hitResult.bBlockingHit)
		{
			hitDistance = FVector::Distance(hitResult.Location, GetActorLocation());
		}

		// Deal damage if it's a subclass of BaseCharacter
		ACoscoBaseCharacter * baseCharacter = Cast<ACoscoBaseCharacter>(actor);
		if (!baseCharacter) continue;
		baseCharacter->TakeDamage(CalcRadialDamage(hitDistance));

		confirmExplosion = true;
	}

	// If explosion's confirmed, destroy projectile spawning the explosion particle
	if (confirmExplosion || bForceExplode)
	{
		if (HitParticle)
		{
			FTransform spawnTransform = GetActorTransform();
			spawnTransform.SetScale3D(FVector::OneVector * ExplosionScale);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, spawnTransform, true, EPSCPoolMethod::None);
		}

		Destroy();
	}
}
////////////////////////////////////////////////////////////////////// Explode