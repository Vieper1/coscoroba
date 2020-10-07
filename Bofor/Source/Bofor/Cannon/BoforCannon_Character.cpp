// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BoforCannon_Character.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);





//////////////////////////////////////////////////////////////////////////////////////////////////// INIT
ABoforCannon_Character::ABoforCannon_Character()
{
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("box_collider"));
	MyCollider->SetupAttachment(RootComponent);

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("primary_mesh"));
	MyMesh->SetupAttachment(MyCollider);
	

	/*FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetupAttachment(FirstPersonCameraComponent);*/
	
	WeaponRange = 5000.0f;
	WeaponDamage = 500000.0f;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}
ABoforCannon_Character::~ABoforCannon_Character()
{
	if (m_Socket)
		m_Socket->Close();
}


void ABoforCannon_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Actions

	// Axis
	PlayerInputComponent->BindAxis("TurnRate", this, &ABoforCannon_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABoforCannon_Character::LookUpAtRate);
}
//////////////////////////////////////////////////////////////////////////////////////////////////// INIT











//////////////////////////////////////////////////////////////////////////////////////////////////// TICK & BEGINPLAY
void ABoforCannon_Character::BeginPlay()
{
	Super::BeginPlay();

	// Socket
	if (m_ConnectToServer)
	{
		m_Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
		//FIPv4Address ip(155, 98, 167, 237);					// Pi
		FIPv4Address ip(ipv4_1, ipv4_2, ipv4_3, ipv4_4);
		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);
		addr->SetPort(ipv4_port);

		bool connected = m_Socket->Connect(*addr);
	}
	else
	{
		m_Socket = nullptr;
	}
	
}


void ABoforCannon_Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);



	// Movement
	//AddControllerYawInput(CurrentTurnRate);
	CurrentTurnRate = FMath::FInterpTo(CurrentTurnRate, 0, DeltaSeconds, InputLerpSpeed);

	//AddControllerPitchInput(CurrentLookUpRate);
	CurrentLookUpRate = FMath::FInterpTo(CurrentLookUpRate, 0, DeltaSeconds, InputLerpSpeed);





	// Socket
	if (m_ConnectToServer && m_Socket)
	{
		uint8* T = new uint8[ipv4_bufferSize];
		int32 BRead = 0;
		uint32 pendingData;

		if (m_Socket->HasPendingData(pendingData))
		{
			if (m_Socket->Recv(T, ipv4_bufferSize, BRead, ESocketReceiveFlags::None))
			{
				if (BRead > 0)
				{
					FString str = "";
					for (size_t i = 0; i < BRead; i++)
					{
						//if (T[i] == 82)			// R
						//{
						//	const uint8 t = T[i + 1];
						//	if (t == 49)		// 1
						//	{
						//		TurnAtRate(1.f);
						//	}
						//	else if (t == 50)	// 2
						//	{
						//		TurnAtRate(-1.f);
						//	}
						//}
						//else if (T[i] == 76)	// L
						//{
						//	const uint8 t = T[i + 1];
						//	if (t == 49)		// 1
						//	{
						//		LookUpAtRate(1.f);
						//	}
						//	else if (t == 50)	// 2
						//	{
						//		LookUpAtRate(-1.f);
						//	}
						//}

						switch (T[i]) {
						case 49:
							LookUpAtRate(1.f);
							break;
						case 50:
							LookUpAtRate(-1.f);
							break;
						case 51:
							TurnAtRate(1.f);
							break;
						case 52:
							TurnAtRate(-1.f);
							break;
						}

						str.Append(FString::Printf(TEXT("%c "), static_cast<char>(T[i])));
						GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, str);
						//UE_LOG(LogTemp, Warning, TEXT("%d"), T[i]);
					}
					//UE_LOG(LogTemp, Warning, TEXT("////////////////////////////////////////////////////////////\n\n"));
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////// TICK & BEGINPLAY












//////////////////////////////////////////////////////////////////////////////////////////////////// INPUT
void ABoforCannon_Character::TurnAtRate(float Rate)
{
	AddYawInput(Rate);
}

void ABoforCannon_Character::LookUpAtRate(float Rate)
{
	AddPitchInput(Rate);
}








void ABoforCannon_Character::AddYawInput(const float Input)
{
	const float newTurnRate = (GetWorld()->GetDeltaSeconds() * Input * InputMultiplier) + CurrentTurnRate;
	if (FMath::Abs(newTurnRate) < FMath::Abs(BaseTurnRate))
		CurrentTurnRate = newTurnRate;
}

void ABoforCannon_Character::AddPitchInput(const float Input)
{
	const float newLookUpRate = (GetWorld()->GetDeltaSeconds() * Input * InputMultiplier) + CurrentLookUpRate;
	if (FMath::Abs(newLookUpRate) < FMath::Abs(BaseLookUpRate))
		CurrentLookUpRate = newLookUpRate;
}
//////////////////////////////////////////////////////////////////////////////////////////////////// INPUT