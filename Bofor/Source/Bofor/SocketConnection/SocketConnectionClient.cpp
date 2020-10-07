// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketConnectionClient.h"
#include "Engine.h"

// Sets default values
ASocketConnectionClient::ASocketConnectionClient()
{
	PrimaryActorTick.bCanEverTick = true;
	m_Data = new uint8[BufferSize];
}

void ASocketConnectionClient::BeginPlay()
{
	Super::BeginPlay();
	m_Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//FIPv4Address ip(155, 98, 167, 237);					// Pi
	FIPv4Address ip(ipv4_1, ipv4_2, ipv4_3, ipv4_4);
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(ipv4_port);

	bool connected = m_Socket->Connect(*addr);
}

void ASocketConnectionClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Socket
	uint8* T = new uint8[ipv4_bufferSize];
	
	int32 BRead = 0;
	uint32 pendingData;
	
	if (m_Socket->HasPendingData(pendingData))
	{
		if (m_Socket->Recv(T, ipv4_bufferSize, BRead, ESocketReceiveFlags::None))
		{
			if (BRead > 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Green, FString::Printf(TEXT("%d"), T[0]));
				for (size_t i = 0; i < BRead; i++)
				{
					UE_LOG(LogTemp, Warning, TEXT("%d"), T[i]);
				}
				UE_LOG(LogTemp, Warning, TEXT("////////////////////////////////////////////////////////////\n\n"));
			}
		}
	}
}

ASocketConnectionClient::~ASocketConnectionClient()
{
	if (m_Socket)
		m_Socket->Close();
}