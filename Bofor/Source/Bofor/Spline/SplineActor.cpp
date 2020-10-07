#include "SplineActor.h"

ASplineActor::ASplineActor()
{
	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));
	SceneRoot->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SceneRoot->SetHiddenInGame(true);
	RootComponent = SceneRoot;
	
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Core Spline"));
	Spline->SetupAttachment(SceneRoot);
}