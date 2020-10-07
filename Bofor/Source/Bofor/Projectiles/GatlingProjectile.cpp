#include "GatlingProjectile.h"
#include "BaseProjectile.h"
#include "ACosco/Cosco_Base_Character.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"


////////////////////////////////////////////////////////////////////// INIT
AGatlingProjectile::AGatlingProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AGatlingProjectile::OnBeginOverlap);
}
////////////////////////////////////////////////////////////////////// INIT












////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void AGatlingProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGatlingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
















////////////////////////////////////////////////////////////////////// Explode
void AGatlingProjectile::OnBeginOverlap(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Cast<ABaseProjectile>(OtherActor)) return;


	if (HitParticle)
	{
		FTransform spawnTransform = GetActorTransform();
		spawnTransform.SetScale3D(FVector::OneVector * HitParticleScale);
		UParticleSystemComponent* hitComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, spawnTransform, true, EPSCPoolMethod::AutoRelease);
	}

	ACoscoBaseCharacter * baseCharacter = Cast<ACoscoBaseCharacter>(OtherActor);
	if (baseCharacter)
	{
		baseCharacter->TakeDamage(Damage);
	}

	Destroy();
}
////////////////////////////////////////////////////////////////////// Explode