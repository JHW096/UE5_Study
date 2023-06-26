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
	// �ٿ� ĳ��Ʈ�� �ؾ��մϴ�.
	if (nullptr == GameModePtr)
	{
		// �� TEXT�� ���ؼ��� �������ڸ�
		// �𸮾󿡼��� �����ڵ� ��Ƽ����Ʈ�� �������� �ʴ´�.
		// � �����ڵ�� �𸮾����� �˾Ƽ� ã���ش�.
		// ���ڿ��� �������� ���ڵ��� �ִ¿� �� ���ڵ��� �˾Ƽ� �ڽŵ��� ó���ϰڴٴ� �ǹ̷�
		// TEXT() �˾Ƽ� �����ڵ�� ��Ƽ����Ʈ�� ���� �˾Ƽ� �� ó���ϰڴ�.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// �𸮾��� ���̺귯���� �̳༮�� �ܼ��� nullptr�� �ƴ϶�� �� �����δ� �������� Ȯ���Ҽ�
	// ���ٰ� �����ؼ� ������ UObject�ȿ� �ɹ��Լ���
	// ���� ����Ϸ��� �𸮾��� UOBject�� ��ӹ��� �����Ͱ� �������� ���������� Ȯ���Ϸ���
	// �ܼ��� nullptr������ �ȵǰ� IsValidLowLevel �Լ��� ����ؼ� �𸮾��� ����� �������ְ� �ִ�
	// ���������� �˾Ƴ����� �ִ�.
	if (false == GameModePtr->IsValidLowLevel())
	{
		// �𸮾��� �˻�� �������ʹ� ������ ���ɼ��� �ִٴ°��̴�.
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

