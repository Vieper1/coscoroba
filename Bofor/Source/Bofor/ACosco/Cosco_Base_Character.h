#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Bofor/Sheild/Sheild.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Spline/SplineActor.h"
#include "Bofor/Sheild/Sheild.h"
#include "Engine/EngineTypes.h"
#include "Cosco_Base_Character.generated.h"


#pragma region Controller Settings

UENUM(BlueprintType)
enum class EGameBuildType : uint8
{
	AltCtrl     UMETA(DisplayName = "AltCtrl"),
	LocalMul    UMETA(DisplayName = "LocalMul")
};

#pragma endregion 

UCLASS(config = Game)
class BOFOR_API ACoscoBaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	ACoscoBaseCharacter();





	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;









	
#pragma region Mesh & Spline
	
public:
	// Base Mesh and Spline Reference
	UPROPERTY(Category = "Core", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent * CoreCollider;
	
	UPROPERTY(Category = "Core", VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent * MainMesh;

	UPROPERTY(Category = "Core", EditAnywhere, BlueprintReadWrite)
		ASplineActor * MySplineActor;
private:
	UPROPERTY(Category = "Core", VisibleAnywhere)
		bool hasSplineActorRef;
	UPROPERTY(Category = "Core", VisibleAnywhere)
		USplineComponent * SplineRef;

#pragma endregion














	
#pragma region Spline & Movement Speed
	//Spline & Movement Speed
public:
	FVector LastFakeVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector FakeVelocity;
	
	
	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
		float               m_AmountToMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float               m_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float               m_LerpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float               m_DistanceAlongSpline;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		float                m_LeanMultiplier;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		float                m_LeanLerpSpeed;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		float                m_LeanLimit;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		bool                m_LoopOnSpline;
	
	
private:
	FVector  m_VectorOnSpline;
	FRotator m_RotationOnSpline;
	FVector m_LastPosition;
	float m_CurrentLeanAngle;

#pragma endregion




#pragma region Shield
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield ")
		bool m_HasShield;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield")
		TSubclassOf<class ASheild> ShieldComponentBP;
	
	UPROPERTY(BlueprintReadWrite, Category = "Shield ")
		ASheild* ShieldReference = nullptr;
	

	UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		void SpawnSheild(FVector ShieldSpawnLocation, USceneComponent* RingRefrence);
	UFUNCTION(BlueprintCallable, Category = "Shield Settings")
		int CallRespawnSheild();

#pragma endregion









	
#pragma region Health & Damage
	
//Health & Damage 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float m_MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float m_AttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool m_Respawn;
	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
		float m_CurrentHealth;
	
	
	 
	//Functions
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void TakeDamage(float i_Damage);
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Healing(float i_Healing);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage();
#pragma endregion

#pragma region GameBuildType
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildType)
		EGameBuildType m_GameBuildType = EGameBuildType::LocalMul;
#pragma endregion
};

