// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "PFCharacter.h"


APFPlayerController::APFPlayerController()
{
	bShowMouseCursor = true;

	if (m_Player == nullptr)
	{
		m_Player = Cast<APFCharacter>(GetPawn());
	}
}


void APFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	static bool bBindingAdded = false;

	if (!bBindingAdded)
	{
		bBindingAdded = true;

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("ActionQ"), EKeys::Q));
		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ActionW", EKeys::W, 1.0f));
		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ActionE", EKeys::E, 1.0f));
		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ActionR", EKeys::R, 1.0f));
		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ActionZ", EKeys::Z, 1.0f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("ActionC"), EKeys::C));
	}

	//Character Move
	InputComponent->BindAction("RightClick", IE_Pressed, this, &APFPlayerController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &APFPlayerController::InputLeftMouseButtonPressed);

	InputComponent->BindAction("ActionC", EInputEvent::IE_Pressed, this, &APFPlayerController::InputCKeyPressed);


	InputComponent->BindAction("ActionQ", EInputEvent::IE_Pressed, this, &APFPlayerController::InputQKeyPressed);
	



	


}

void APFPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickRightMouse)
	{
		MoveToMouseCursor();
	}
	m_Speed = GetPawn()->GetVelocity().Size();
	SetAnimState(m_Speed);
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

	GetHitResultUnderCursor(ECC_Visibility, false, m_Hit);

	if (m_Hit.bBlockingHit)
	{
		SetNewDestination(m_Hit.ImpactPoint);
	}
}

void APFPlayerController::InputQKeyPressed()
{

	UE_LOG(LogTemp, Warning, TEXT("Input Q Key Pressed"));
}

void APFPlayerController::InputCKeyPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Input C Key Pressed"));
	m_AnimState = AnimState::NORMALATTACK;
}