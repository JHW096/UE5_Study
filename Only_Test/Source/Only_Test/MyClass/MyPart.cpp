// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPart.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameMode.h"

// Sets default values
AMyPart::AMyPart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Part");

}

// Called when the game starts or when spawned
void AMyPart::BeginPlay()
{
	Super::BeginPlay();
	
	AGameModeBase* GameModePtr = UGameplayStatics::UGameplayStatics::GetGameMode(GetWorld());

	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}
	
	AddTickPrerequisiteActor(GameModePtr);

}

// Called every frame
void AMyPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

AMyGameMode* AMyPart::GetMyGameMode()
{
	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	if (false == GameModePtr->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModePtr);

	if (MyGameMode == nullptr && MyGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}


	return MyGameMode;
}

