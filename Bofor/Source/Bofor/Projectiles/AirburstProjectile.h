// Created by Vishal Naidu (GitHub: Vieper1) | naiduvishal13@gmail.com | Vishal.Naidu@utah.edu

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







	////////////////////////////////////////////////////////////////////// CORE
#pragma region Airburst
	float time;
	UPROPERTY(Category = Airburst, VisibleAnywhere, BlueprintReadOnly)
		USphereComponent * BigCollider;
#pragma endregion
	////////////////////////////////////////////////////////////////////// CORE










	////////////////////////////////////////////////////////////////////// CONFIG

	// Use Remap value range to map the distance-based-damage-drop
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
	////////////////////////////////////////////////////////////////////// CONFIG





	

	
	

	////////////////////////////////////////////////////////////////////// DAMAGE
#pragma region Explosion

	// DELAYED EXPLOSION?

	// If the airburst always explodes upon the outer collider's overlap,
	// It'll EXPLODE PREMATURELY, leading to minimal damage
	
	// So I'm using explosion delay to set the airburst to explode N ms after
	// If you've got good aim, you'd naturally see the explosion real close to the target

	void Explode(const bool bForceExplode = false);
	UPROPERTY(Category = Projectile, EditAnywhere, Blueprintreadwrite)
		float ExplosionDelay;
	UPROPERTY(Category = Projectile, EditAnywhere, Blueprintreadwrite)
		float ExplosionScale;
#pragma endregion
	////////////////////////////////////////////////////////////////////// DAMAGE
};
