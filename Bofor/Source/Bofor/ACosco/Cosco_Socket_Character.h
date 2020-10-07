#pragma once

#include "CoreMinimal.h"
#include "Cosco_Camera_Character.h"
#include "Cosco_Socket_Character.generated.h"


class FSocket;
UCLASS(config = Game)
class BOFOR_API ACoscoSocketCharacter : public ACoscoCameraCharacter
{
	GENERATED_BODY()

public:
	ACoscoSocketCharacter();
	~ACoscoSocketCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;





	
public:
	FSocket * m_Socket;
	uint8 * m_Data;
	int32 BufferSize = 4;
	int32 BytesRead;
	
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		bool m_ConnectToServer = false;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_bufferSize;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_1;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_2;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_3;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_4;
	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadWrite)
		int ipv4_port;

	UPROPERTY(Category = Connection, EditAnywhere, BlueprintReadOnly)
		FString output;
};
