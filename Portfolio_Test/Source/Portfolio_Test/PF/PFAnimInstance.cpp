// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAnimInstance.h"
#include "PFCharacter.h"

void UPFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		m_AnimSpeed = pawn->GetVelocity().Size();
	}
}


