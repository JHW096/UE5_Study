// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "PFCharacter.h"


APFPlayerController::APFPlayerController()
{
	bShowMouseCursor = true;
}

void APFPlayerController::QKeyPress()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Q Key Pressed"));
	
}

void APFPlayerController::WKeyPress()
{
	UE_LOG(LogTemp, Warning, TEXT("W Key Pressed"));
}

void APFPlayerController::EKeyPress()
{
	UE_LOG(LogTemp, Warning, TEXT("E Key Pressed"));
}

void APFPlayerController::RKeyPress()
{
	UE_LOG(LogTemp, Warning, TEXT("R Key Pressed"));
}

void APFPlayerController::ZKeyPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Z Key Pressed"));
}

void APFPlayerController::SpaceKeyPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Space Key Pressed"));
}

void APFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	static bool bBindingAdded = false;

	if (!bBindingAdded)
	{
		bBindingAdded = true;

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Dash", EKeys::SpaceBar, 1.0f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("NormalAttack", EKeys::C, 1.0f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Q_Skill", EKeys::Q, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("W_Skill", EKeys::W, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("E_SKill", EKeys::E, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("R_Skill", EKeys::R, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Ult_Skill", EKeys::Z, 1.0f));
		
	}

	//Character Move
	InputComponent->BindAction("RightClick", IE_Pressed, this, &APFPlayerController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &APFPlayerController::InputLeftMouseButtonPressed);

	//Dash
	InputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &APFPlayerController::SpaceKeyPress);

	//Skill
	InputComponent->BindAction("W_Skill", EInputEvent::IE_Pressed, this, &APFPlayerController::QKeyPress);
	InputComponent->BindAction("W_Skill", EInputEvent::IE_Pressed, this, &APFPlayerController::WKeyPress);
	InputComponent->BindAction("E_Skill", EInputEvent::IE_Pressed, this, &APFPlayerController::EKeyPress);
	InputComponent->BindAction("R_Skill", EInputEvent::IE_Pressed, this, &APFPlayerController::RKeyPress);
	InputComponent->BindAction("Ult_Skill", EInputEvent::IE_Pressed, this, &APFPlayerController::EKeyPress);


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


