#pragma once

#include "CoreMinimal.h"
#include "Cosco_Weapons_Character.h"
#include "Cosco_Enemy_Character.generated.h"




UCLASS(config = Game)
class BOFOR_API ACoscoEnemyCharacter : public ACoscoWeaponsCharacter
{
	GENERATED_BODY()

public:
	ACoscoEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(Category = "Enemy", EditAnywhere, BlueprintReadWrite)
	float Range;
	UPROPERTY(Category = "Enemy", EditAnywhere, BlueprintReadWrite)
	bool Attack;
};
