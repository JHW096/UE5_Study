// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSEnum.h"
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

	

	void InputLeftMouseButtonPressed();

	void InputRightMouseButtonPressed();

	void SetNewDestination(const FVector _Destination);

	void MoveToMouseCursor();

	void SetupInputComponent() override;

	void PlayerTick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AnimState m_AnimState = AnimState::IDLE;

	float m_Speed = 0.0f;

	bool bClickRightMouse = false;

	float _Destination = 0.0f;
	
	APawn* m_Player = nullptr;

	FHitResult m_Hit;

public:

	void SetAnimState(const float& _Speed)
	{

		if (_Speed > 1.0f)
		{
			if (m_AnimState == AnimState::NORMALATTACK)
			{
				return;
			}
			m_AnimState = AnimState::FWDMOVE;
		}
		else
		{
			if (m_AnimState == AnimState::NORMALATTACK)
			{
				return;
			}
			m_AnimState = AnimState::IDLE;
		}
	}

public:

	void InputQKeyPressed();

	void InputCKeyPressed();
	
	
};
