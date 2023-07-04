// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PFAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ANIMSTATE : uint8
{
	None,
	Idle,
	FwdMove
};

UCLASS()
class PORTFOLIO_TEST_API UPFAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public: 
	
	FORCEINLINE
	ANIMSTATE GetAnimState()
	{
		return Anim_State;
	}

	UFUNCTION(BlueprintCallable)
	void SetAnimState(const float& _Speed)
	{
		
		if (_Speed > 1.0f)
		{
			Anim_State = ANIMSTATE::FwdMove;
		}
		else
		{
			Anim_State = ANIMSTATE::Idle;
		}
	}

	FORCEINLINE
	float GetAnimSpeed()
	{
		return m_AnimSpeed;
	}

	FORCEINLINE
	void SetAnimSpeed(float& _Speed)
	{
		m_AnimSpeed = _Speed;
	}

	

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float m_AnimSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	ANIMSTATE Anim_State = ANIMSTATE::Idle;

	
	
};
