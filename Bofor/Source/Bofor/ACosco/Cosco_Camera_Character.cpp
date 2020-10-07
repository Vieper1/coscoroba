#include "Cosco_Camera_Character.h"
#include "Components/StaticMeshComponent.h"
#include <Components/InputComponent.h>
#include "Engine/Engine.h"




static UInputComponent* s_PlayerInputComponent = nullptr;

////////////////////////////////////////////////////////////////////// INIT
ACoscoCameraCharacter::ACoscoCameraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	ShipRing = CreateDefaultSubobject<UStaticMeshComponent>(FName("ShipRing"));
	ShipRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShipRing->SetupAttachment(MainMesh);

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(ShipRing);


	// Config
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FormerCharging = false;
	CanFire = false;
	CurrentCharging = 0.0f;

	//Controller Default Setings
	ControllerSettings.CameraControlSettings = ECameraControl::LookUp;
	ControllerSettings.FireSettings = EFireControl::Airburst;
}

void ACoscoCameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	s_PlayerInputComponent = PlayerInputComponent;

	// Action
	
	// Axis
	switch (m_GameBuildType)
	{
	case EGameBuildType::AltCtrl:
		PlayerInputComponent->BindAxis("TurnRate", this, &ACoscoCameraCharacter::Input_TurnAtRate);
		PlayerInputComponent->BindAxis("LookUpRate", this, &ACoscoCameraCharacter::Input_LookUpAtRate);
		PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ACoscoCameraCharacter::Input_ZoomIn);
		PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ACoscoCameraCharacter::Input_ZoomOut);
		PlayerInputComponent->BindAction("RingRollTop", IE_Pressed, this, &ACoscoCameraCharacter::Input_RingRollTop);
		PlayerInputComponent->BindAction("RingRollRight", IE_Pressed, this, &ACoscoCameraCharacter::Input_RingRollRight);
		PlayerInputComponent->BindAction("RingRollBottom", IE_Pressed, this, &ACoscoCameraCharacter::Input_RingRollBottom);
		PlayerInputComponent->BindAction("RingRollLeft", IE_Pressed, this, &ACoscoCameraCharacter::Input_RingRollLeft);
		break;
	case EGameBuildType::LocalMul:
		/*switch (ControllerSettings.CameraControlSettings)
		{
		case ECameraControl::TurnRight:
			PlayerInputComponent->BindAxis("TurnRate", this, &ACoscoCameraCharacter::Input_TurnAtRate);
			break;
		case ECameraControl::LookUp:
			PlayerInputComponent->BindAxis("LookUpRate", this, &ACoscoCameraCharacter::Input_LookUpAtRate);
			break;
		default:
			break;
		}*/
		break;

	default:
		break;
	}
}
////////////////////////////////////////////////////////////////////// INIT













////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void ACoscoCameraCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UpdateCameraSettings();
}

void ACoscoCameraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Tick_CameraMovement(DeltaTime);
	Tick_CameraZoom(DeltaTime);
	Tick_RingMovement(DeltaTime);
}
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
















////////////////////////////////////////////////////////////////////// TICK HELPERS
// Movement
void ACoscoCameraCharacter::Tick_CameraMovement(const float DeltaSeconds)
{
	if (!IsBDGCharging) {

		FRotator newRotation = MainCamera->RelativeRotation + FRotator(CurrentLookUpRate, CurrentTurnRate, 0);

		if (newRotation.Pitch > PitchRange.Y)
			newRotation.Pitch = PitchRange.Y - 1.0f;

		if (newRotation.Pitch < PitchRange.X)
			newRotation.Pitch = PitchRange.X + 1.0f;

		MainCamera->SetRelativeRotation(newRotation);

		CurrentTurnRate = FMath::FInterpTo(CurrentTurnRate, 0, DeltaSeconds, InputLerpSpeed);
		CurrentLookUpRate = FMath::FInterpTo(CurrentLookUpRate, 0, DeltaSeconds, InputLerpSpeed);
	}
	else if (IsBDGCharging && !CanFire) {
		CurrentCharging = 0.0f;
		CurrentCharging = FMath::Abs(CurrentChargingTurn) + FMath::Abs(CurrentChargingUp);
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("%f"), CurrentCharging));
		if (CurrentCharging > ChargingFrame)
		{
			//charged
			CanFire = true;
			CurrentChargingTurn = 0.0f;
			CurrentChargingUp = 0.0f;
		}
		else
		{
			//charging
			CanFire = false;
		}
	}
}

// Ring
void ACoscoCameraCharacter::Tick_RingMovement(const float DeltaSeconds) const
{
	FRotator targetRotation = ShipRing->RelativeRotation;
	targetRotation.Roll = TargetRoll;
	ShipRing->SetRelativeRotation(FMath::RInterpConstantTo(ShipRing->RelativeRotation, targetRotation, DeltaSeconds, RollSpeed));
}

// Zoom
void ACoscoCameraCharacter::Tick_CameraZoom(const float DeltaSeconds) const
{
	const float fov = MainCamera->FieldOfView;
	if (bZoomed)
		MainCamera->FieldOfView = FMath::FInterpTo(fov, ZoomRange.Y, DeltaSeconds, ZoomLerpSpeed);
	else
		MainCamera->FieldOfView = FMath::FInterpTo(fov, ZoomRange.X, DeltaSeconds, ZoomLerpSpeed);
}
////////////////////////////////////////////////////////////////////// TICK HELPERS




















////////////////////////////////////////////////////////////////////// INPUT
//Camera Movement
void ACoscoCameraCharacter::Input_TurnAtRate(float Rate) { AddYawInput(Rate); }
void ACoscoCameraCharacter::Input_LookUpAtRate(float Rate) { AddPitchInput(Rate); }
void ACoscoCameraCharacter::AddYawInput(const float Input)
{
	if (!IsBDGCharging) {
		const float newTurnRate = (GetWorld()->GetDeltaSeconds() * Input * InputMultiplier) + CurrentTurnRate;
		if (FMath::Abs(newTurnRate) < FMath::Abs(BaseTurnRate))
			CurrentTurnRate = newTurnRate;
	}
	else {
		const float newTurnRate = (GetWorld()->GetDeltaSeconds() * Input * InputMultiplier) + CurrentChargingTurn;
		CurrentChargingTurn = newTurnRate;
	}
}
void ACoscoCameraCharacter::AddPitchInput(const float Input)
{
	if (!IsBDGCharging) {
		const float newLookUpRate = (GetWorld()->GetDeltaSeconds() * Input * InputMultiplier) + CurrentLookUpRate;
		if (FMath::Abs(newLookUpRate) < FMath::Abs(BaseLookUpRate))
			CurrentLookUpRate = newLookUpRate;
	}
	else {
		const float newLookUpRate = (GetWorld()->GetDeltaSeconds() * Input * InputMultiplier) + CurrentChargingUp;
		CurrentChargingUp = newLookUpRate;
	}

}
void ACoscoCameraCharacter::TakeInputForLocalMulPlayer(ECameraControl CameraControlOption, float Input)
{

	switch (CameraControlOption)
	{
	case ECameraControl::TurnRight:
		Input_TurnAtRate(Input);
		break;
	case ECameraControl::LookUp:
		Input_LookUpAtRate(Input);
		break;
	default:
		break;
	}
}

void ACoscoCameraCharacter::UpdateCameraSettings()
{
	switch (ControllerSettings.CameraControlSettings)
	{
	case ECameraControl::TurnRight:
		s_PlayerInputComponent->BindAxis("TurnRate", this, &ACoscoCameraCharacter::Input_TurnAtRate);
		break;
	case ECameraControl::LookUp:
		s_PlayerInputComponent->BindAxis("LookUpRate", this, &ACoscoCameraCharacter::Input_LookUpAtRate);
		break;
	default:
		break;
	}
}
// Ring
void ACoscoCameraCharacter::Input_RingRollTop()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Top"));
	TargetRoll = 0;
}
void ACoscoCameraCharacter::Input_RingRollRight()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Right"));
	TargetRoll = 90;
}
void ACoscoCameraCharacter::Input_RingRollBottom()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Bottom"));
	TargetRoll = 180;
}
void ACoscoCameraCharacter::Input_RingRollLeft()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Left"));
	TargetRoll = 270;
}

// Camera Zoom
void ACoscoCameraCharacter::Input_ZoomIn()
{
	bZoomed = true;
}
void ACoscoCameraCharacter::Input_ZoomOut()
{
	bZoomed = false;
}
////////////////////////////////////////////////////////////////////// INPUT