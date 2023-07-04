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
	
	UFUNCTION(BlueprintCallable)
	void SetAnimState(float& _Speed)
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

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float m_AnimSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	ANIMSTATE Anim_State = ANIMSTATE::Idle;
};
