// Created by Vishal Naidu (GitHub: Vieper1) naiduvishal13@gmail.com | Vishal.Naidu@utah.edu
// And Chilagani Rajesh | chilaganirajesh95@gmail.com 

#include "Cosco_Base_Character.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"






////////////////////////////////////////////////////////////////////// INIT
ACoscoBaseCharacter::ACoscoBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CoreCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CoreCollider"));
	RootComponent = CoreCollider;

	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoreSkeletalMesh"));
	MainMesh->SetupAttachment(RootComponent);



	// Config
	m_Speed = 1.0f;
	m_AmountToMove = 0.0f;
	m_DistanceAlongSpline = 0.0f;
	m_MaxHealth = 100.0f;

	m_LeanMultiplier = 180.0f;
	m_LeanLerpSpeed = 0.8f;
	m_LeanLimit = 60.f;
	m_LerpSpeed = 0.5f;
}

void ACoscoBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
////////////////////////////////////////////////////////////////////// INIT













////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void ACoscoBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//init current health
	m_CurrentHealth = m_MaxHealth;
	m_LastPosition = GetActorLocation();
}



// Spline Riding Logic here
void ACoscoBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Since our character is a Spline Rider (Teleporter) he doesn't have a PhysicsVelocity
	// Use last and current position to get a FakeVelocity
	
	// Do a LateUpdate on the FakeVelocity so you can tell if there's been a change in direction
	// Use the delta to make the ship lean like a bike

	const FVector CurrentPosition = GetActorLocation();
	LastFakeVelocity = FakeVelocity;
	FakeVelocity = (CurrentPosition - m_LastPosition) / DeltaTime;


	// Formula to make the ship LEAN like a BIKE
	// TargetLeanAngle 		=> Immediately set by the change in direction
	// CurrentLeanAngle 	=> Lerp the current angle to the target to get a SMOOTH TRANSITION

	const float targetLeanAngle = UKismetMathLibrary::NormalizedDeltaRotator(FakeVelocity.Rotation(), LastFakeVelocity.Rotation()).Yaw * m_LeanMultiplier;
	m_CurrentLeanAngle = FMath::FInterpTo(m_CurrentLeanAngle, targetLeanAngle, DeltaTime, m_LeanLerpSpeed);
	m_LastPosition = CurrentPosition;


	m_AmountToMove = m_Speed * DeltaTime;
	m_DistanceAlongSpline += m_AmountToMove;
	if (m_CurrentHealth > 0)
	{
		m_Respawn = false;
	}
	else
	{
		m_Respawn = true;
	}
	if (hasSplineActorRef && MySplineActor)
	{
		m_VectorOnSpline = SplineRef->GetLocationAtDistanceAlongSpline(m_DistanceAlongSpline, ESplineCoordinateSpace::World);
		m_RotationOnSpline = SplineRef->GetRotationAtDistanceAlongSpline(m_DistanceAlongSpline, ESplineCoordinateSpace::Local);


		// Use LERPING with current spline position and target spline position
		// To make the ship do smooth turns instead of relying on (Lot of) spline points
		// And to MITIGATE any HEAVY SNAPPING because of spline tangents not being smooth curves

		SetActorLocation(FMath::VInterpTo(GetActorLocation(), m_VectorOnSpline, DeltaTime, m_LerpSpeed));
		const FRotator CurrentRotation = GetActorRotation();
		SetActorRotation(FMath::RInterpTo(CurrentRotation, FRotator(m_RotationOnSpline.Pitch, m_RotationOnSpline.Yaw, m_CurrentLeanAngle < m_LeanLimit ? m_CurrentLeanAngle : CurrentRotation.Roll), DeltaTime, m_LerpSpeed));

		if (m_LoopOnSpline)
			if (SplineRef->GetSplineLength() - m_DistanceAlongSpline < 1.0f)
				m_DistanceAlongSpline = 0.0f;
	}
	else
	{
		if (MySplineActor)
		{
			hasSplineActorRef = true;
			SplineRef = MySplineActor->Spline;
		}
	}
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK

























void ACoscoBaseCharacter::SpawnSheild(FVector ShieldSpawnLocation, USceneComponent * RingRefrence)
{
	FRotator Rotation(0, 0, 0);
	ShieldReference = GetWorld()->SpawnActor<ASheild>(ShieldComponentBP, ShieldSpawnLocation, Rotation);
	ShieldReference->IsShieldActive = true;
	//ShieldReference->AttachToActor(RingRefrence, FAttachmentTransformRules::KeepWorldTransform);
	ShieldReference->AttachToComponent(RingRefrence, FAttachmentTransformRules::KeepWorldTransform);
}

int ACoscoBaseCharacter::CallRespawnSheild()
{
	if (m_CurrentHealth < 85)

		if (m_CurrentHealth < 65)
		{
			if (m_CurrentHealth < 40)
			{
				if (m_CurrentHealth == 0)
				{
					return 4;
				}
				else
				{
					return 3;
				}
			}
			else
			{
				return 2;
			}

		}
		else
		{
			return 1;
		}
	return 0;
}

void ACoscoBaseCharacter::TakeDamage(float i_Damage) {
	if (m_HasShield)
	{
		if (ShieldReference)
		{

			if (ShieldReference->IsShieldActive)
			{
				UE_LOG(LogTemp, Warning, TEXT("Shield taking Damage"));
			}
			else
			{
				if (m_CurrentHealth - i_Damage > 0) {
					m_CurrentHealth -= i_Damage;
					CallRespawnSheild();
				}
				else {
					//dead 
					m_CurrentHealth = 0;
				}
			}
			this->OnTakeDamage();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("You forgot to add shield"));
		}
	}
	else
	{
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

void ACoscoBaseCharacter::Healing(float i_Healing) {
	if (m_CurrentHealth + i_Healing < m_MaxHealth) {
		m_CurrentHealth += i_Healing;
	}
	else {
		m_CurrentHealth = m_MaxHealth;
	}
}




