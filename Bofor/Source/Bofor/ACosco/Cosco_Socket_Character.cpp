#include "Cosco_Socket_Character.h"
#include "SocketConnection/SocketConnectionClient.h"
#include "Engine/Engine.h"
#include <Components/InputComponent.h>


////////////////////////////////////////////////////////////////////// INIT
ACoscoSocketCharacter::ACoscoSocketCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

ACoscoSocketCharacter::~ACoscoSocketCharacter()
{
	if (m_Socket)
		m_Socket->Close();
}


void ACoscoSocketCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
////////////////////////////////////////////////////////////////////// INIT











////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK
void ACoscoSocketCharacter::BeginPlay()
{
	Super::BeginPlay();

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

void ACoscoSocketCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
						switch (T[i])
						{
						case 49:
							Input_LookUpAtRate(1.f);
							break;
						case 50:
							Input_LookUpAtRate(-1.f);
							break;
						case 51:
							Input_TurnAtRate(1.f);
							break;
						case 52:
							Input_TurnAtRate(-1.f);
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
////////////////////////////////////////////////////////////////////// BEGINPLAY & TICK