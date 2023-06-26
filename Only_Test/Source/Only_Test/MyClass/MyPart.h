// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPart.generated.h"

UCLASS()
class ONLY_TEST_API AMyPart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	

	class AMyGameMode* GetMyGameMode();

public:

	FVector Prev;
	FVector Now;
	


};
