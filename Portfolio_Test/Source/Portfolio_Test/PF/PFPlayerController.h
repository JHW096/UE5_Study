// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PFPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_TEST_API APFPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APFPlayerController();
	
protected:

	void QKeyPress();
	void WKeyPress();
	void EKeyPress();
	void RKeyPress();
	void ZKeyPress();
	void SpaceKeyPress();

	bool bClickRightMouse;

	void InputLeftMouseButtonPressed();

	void InputRightMouseButtonPressed();

	void SetNewDestination(const FVector _Destination);

	void MoveToMouseCursor();

	void SetupInputComponent() override;

	void PlayerTick(float DeltaTime) override;

};
