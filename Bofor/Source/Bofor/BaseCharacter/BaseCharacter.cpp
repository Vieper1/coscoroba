// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	RootComponent = m_RootComponent;
	m_SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	
	m_Speed = 1.0f;
	m_AmountToMove = 0.0f;
	m_DistanceAlongSpline = 0.0f;
	m_MaxHealth = 100.0f;
	
	

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	//init current health
	m_CurrentHealth = m_MaxHealth;

	TArray<USceneComponent *> compArray;
	m_RootComponent->GetChildrenComponents(false, compArray);
	for (USceneComponent * comp : compArray)
	{
		if (comp->GetName().Equals("BoxCollider"))
		{
			colliderComp = comp;
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_AmountToMove = m_Speed * DeltaTime;
	m_DistanceAlongSpline += m_AmountToMove;
	m_VectorOnSpline = m_SplineComponent->GetLocationAtDistanceAlongSpline(m_DistanceAlongSpline, ESplineCoordinateSpace::World);
	m_RotationOnSpline = m_SplineComponent->GetRotationAtDistanceAlongSpline(m_DistanceAlongSpline, ESplineCoordinateSpace::Local);
	m_RootComponent->GetChildComponent(1)->SetWorldLocation(m_VectorOnSpline);
	m_RootComponent->GetChildComponent(1)->SetRelativeRotation(m_RotationOnSpline);
	
	//colliderComp->SetWorldLocation(m_VectorOnSpline);
	//colliderComp->SetRelativeRotation(m_RotationOnSpline);
	if (m_LoopOnSpline)
	{
		if (m_SplineComponent->GetSplineLength()-m_DistanceAlongSpline  < 1.0f)
		{
			m_DistanceAlongSpline = 0.0f;
		}
	}

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void ABaseCharacter::TakeDamage(float i_Damage) {

	if (ShieldReference)
	{
		if (ShieldReference->IsShieldActive)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sheild ACtive"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sheild ACtive??"));
			if (m_CurrentHealth - i_Damage > 0) {
				m_CurrentHealth -= i_Damage;
			}
			else {
				//dead 
				m_CurrentHealth = 0;
			}
			this->OnTakeDamage();
		}
	}
	
}

void ABaseCharacter::Healing(float i_Healing) {
	
	if (m_CurrentHealth + i_Healing < m_MaxHealth) {
		m_CurrentHealth += i_Healing;
	}
	else {
		m_CurrentHealth = m_MaxHealth;
	}
}

void ABaseCharacter::SpawnSheild(FVector ShieldSpawnLocation )
{
	FRotator Rotation(0, 0, 0);
	ShieldReference = GetWorld()->SpawnActor<ASheild>(ShieldComponentBP, ShieldSpawnLocation, Rotation);
	ShieldReference->IsShieldActive = true;
}

