

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "SocketConnectionClient.generated.h"

UCLASS()
class BOFOR_API ASocketConnectionClient : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASocketConnectionClient();
	~ASocketConnectionClient();
	void SendData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FSocket* m_Socket;
	uint8* m_Data;
	int32 BufferSize = 4;
	int32 BytesRead;

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

	UPROPERTY(Category = Output, EditAnywhere, BlueprintReadWrite)
		FString output;
};
