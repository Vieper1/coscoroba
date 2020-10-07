// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "AirburstProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BOFOR_API AAirburstProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
		AAirburstProjectile();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);








#pragma region Airburst
	float time;
	UPROPERTY(Category = Airburst, VisibleAnywhere, BlueprintReadOnly)
		USphereComponent * BigCollider;
#pragma endregion







#pragma region Radial Damage
	UPROPERTY(Category = "Radial Damage", EditAnywhere, BlueprintReadWrite)
		float MaxDistance;
	UPROPERTY(Category = "Radial Damage", EditAnywhere, BlueprintReadWrite)
		float MinDistance;
	UPROPERTY(Category = "Radial Damage", EditAnywhere, BlueprintReadWrite)
		float MaxDamage;
	UPROPERTY(Category = "Radial Damage", EditAnywhere, BlueprintReadWrite)
		float MinDamage;
	inline float CalcRadialDamage(const float distance) const;
	TArray<AActor*> overlappingActors;
#pragma endregion






	

	
	


#pragma region Explosion
	void Explode(const bool bForceExplode = false);
	UPROPERTY(Category = Projectile, EditAnywhere, Blueprintreadwrite)
		float ExplosionDelay;
	UPROPERTY(Category = Projectile, EditAnywhere, Blueprintreadwrite)
		float ExplosionScale;
#pragma endregion
};
