// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

APFPlayerController::APFPlayerController()
{
	bShowMouseCursor = true;
}

void APFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("RightClick", IE_Pressed, this, &APFPlayerController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &APFPlayerController::InputLeftMouseButtonPressed);

}

void APFPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickRightMouse)
	{
		MoveToMouseCursor();
	}
}

void APFPlayerController::InputLeftMouseButtonPressed()
{
	bClickRightMouse = false;
}

void APFPlayerController::InputRightMouseButtonPressed()
{
	bClickRightMouse = true;
}

void APFPlayerController::SetNewDestination(const FVector _Destination)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		float const Distance = FVector::Dist(_Destination, MyPawn->GetActorLocation());
		if (Distance > 120.0f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, _Destination);
		}
	}
}

void APFPlayerController::MoveToMouseCursor()
{
	FHitResult Hit;

	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewDestination(Hit.ImpactPoint);
	}
}


