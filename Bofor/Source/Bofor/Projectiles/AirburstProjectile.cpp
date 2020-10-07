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
	
	BigCollider = CreateDefaultSubobject<USphereComponent>(FName("BigCollider"));
	BigCollider->SetCollisionProfileName(FName("OverlapAllDynamic"));
	BigCollider->SetupAttachment(RootComponent);
}
////////////////////////////////////////////////////////////////////// INIT












////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void AAirburstProjectile::BeginPlay()
{
	Super::BeginPlay();
	time = ExplosionDelay;
	SphereCollision->IgnoreComponentWhenMoving(BigCollider, true);
	BigCollider->IgnoreComponentWhenMoving(SphereCollision, true);
}

void AAirburstProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time -= DeltaTime;

	BigCollider->GetOverlappingActors(overlappingActors, TSubclassOf<ACoscoBaseCharacter>());
	TArray<AActor*> innerSphereOverlappingActors;
	SphereCollision->GetOverlappingActors(innerSphereOverlappingActors);
	if (innerSphereOverlappingActors.Num() > 0)
	{
		Explode(true);
	}
	
	if (time < 0 || overlappingActors.Num() > 0)
	{
		Explode();
	}
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
















////////////////////////////////////////////////////////////////////// Explode
float AAirburstProjectile::CalcRadialDamage(const float distance) const
{
	const FVector2D distanceRange = FVector2D(MinDistance, MaxDistance);
	const FVector2D damageRange = FVector2D(MinDamage, MaxDamage);
	return FMath::GetMappedRangeValueClamped(distanceRange, damageRange, distance);
}

void AAirburstProjectile::Explode(const bool bForceExplode)
{
	bool confirmExplosion = false;
	
	for (AActor * actor : overlappingActors)
	{
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

		ACoscoBaseCharacter * baseCharacter = Cast<ACoscoBaseCharacter>(actor);
		if (!baseCharacter) continue;
		baseCharacter->TakeDamage(CalcRadialDamage(hitDistance));

		// Temp
		/*ABoforCannon_Character * bofor = Cast<ABoforCannon_Character>(actor);
		if (bofor)
			bofor->TakeDamage(CalcRadialDamage(hitDistance));*/
		// Temp

		confirmExplosion = true;
	}

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