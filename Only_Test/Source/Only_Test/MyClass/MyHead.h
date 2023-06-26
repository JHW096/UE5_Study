// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPart.h"
#include "MyHead.generated.h"

UCLASS()
class ONLY_TEST_API AMyHead : public AMyPart
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyHead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	
	UFUNCTION(BlueprintCallable)
	void PressLeftAction();

	UFUNCTION(BlueprintCallable)
	void PressRightAction();

	UFUNCTION(BlueprintCallable)
	void PressUpAction();

	UFUNCTION(BlueprintCallable)
	void PressDownAction();


};
