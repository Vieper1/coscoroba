// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu

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
	

	// Use standard BeginOverlap against the inner collider
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