// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStaticPawn.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameMode.h"

// Sets default values
AMyStaticPawn::AMyStaticPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyStaticPawn::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	// 다운 캐스트를 해야합니다.
	if (nullptr == GameModePtr)
	{
		// 이 TEXT에 대해서도 설명하자면
		// 언리얼에서는 유니코드 멀티바이트를 구분하지 않는다.
		// 어떤 국가코드와 언리얼엔진이 알아서 찾아준다.
		// 문자열은 여러개의 인코딩이 있는에 그 인코딩을 알아서 자신들이 처리하겠다는 의미로
		// TEXT() 알아서 유니코드건 멀티바이트건 뭐건 알아서 잘 처리하겠다.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// 언리얼의 라이브러리는 이녀석이 단순히 nullptr이 아니라는 것 만으로는 안정성을 확인할수
	// 없다고 생각해서 무조건 UObject안에 맴버함수인
	// 내가 사용하려는 언리얼의 UOBject를 상속받은 포인터가 정상적인 포인터인지 확인하려면
	// 단순히 nullptr만으로 안되고 IsValidLowLevel 함수를 사용해서 언리얼이 제대로 관리해주고 있는
	// 포인터인지 알아낼수가 있다.
	if (false == GameModePtr->IsValidLowLevel())
	{
		// 언리얼의 검사상 이포인터는 위험할 가능성이 있다는것이다.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModePtr);

	if (nullptr == MyGameMode && false == MyGameMode->IsValidLowLevel())
	{
		return;
	}

	FIntVector3 Count = MyGameMode->GetObjCount();
	FVector Size = MyGameMode->GetObjSize();
	
	FVector Center = { -1000.0f, Size.Y * Count.Y * 0.5f, Size.Z * Count.Z * 0.5f };

	SetActorLocation(Center);

}

// Called every frame
void AMyStaticPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyStaticPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

