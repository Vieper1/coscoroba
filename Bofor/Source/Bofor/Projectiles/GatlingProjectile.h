// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "GatlingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BOFOR_API AGatlingProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	AGatlingProjectile();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);


#pragma region Damage
	UPROPERTY(Category = "Damage", EditAnywhere, BlueprintReadWrite)
		float Damage;
#pragma endregion


#pragma region Hit
	UPROPERTY(Category = "Projectile", EditAnywhere, BlueprintReadWrite)
		float HitParticleScale;
	
	UFUNCTION(BlueprintCallable)
		void OnBeginOverlap(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
#pragma endregion
};