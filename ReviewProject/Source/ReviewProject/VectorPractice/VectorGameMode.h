// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VectorGameMode.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class VectorState : uint8
{
	Idle,
	Trace,
	Jump,
	AccTrace,
	Look, // Just Teleport Rotataion
};

UCLASS()
class REVIEWPROJECT_API AVectorGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetVectorState(VectorState _State)
	{
		State = _State;
	}

	

	UFUNCTION(BlueprintCallable)
	void Reset();

protected:

	void BeginPlay() override;
	void Tick(float _Delta) override;


private:

	UPROPERTY(Category = "VectorGameModeValue", EditAnywhere, DisplayName = "Actor State");
	VectorState State = VectorState::Idle;

	

	AActor* MainActor = nullptr;
	AActor* OtherActor = nullptr;


	FVector OriPos = FVector::ZeroVector;
	FVector UpVector = { 1000, 0, 0 };
	FVector AccTraceDir = FVector::ZeroVector;

	bool IsLook = false;

	float VectorSpeed;
};
