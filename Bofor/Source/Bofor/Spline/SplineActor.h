// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "SplineActor.generated.h"

UCLASS()
class BOFOR_API ASplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplineActor();

	UPROPERTY(Category = Core, EditAnywhere, BlueprintReadWrite)
		USphereComponent * SceneRoot;
	
	UPROPERTY(Category = Core, EditAnywhere, BlueprintReadWrite)
		USplineComponent * Spline;
};
