// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sheild/Sheild.h"
#include "PlayerShieldCPP.generated.h"

/**
 * 
 */
UCLASS()
class BOFOR_API APlayerShieldCPP : public ASheild
{


	GENERATED_BODY()

	public:

		

		/*UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		void PlayAnimation();
		UFUNCTION(BlueprintCallable, Category = "Shield Settings")
			void DestoryHeatSink();*/

private:
	float HeatSinkCount =3 ;
};
