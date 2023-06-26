// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VectorObj.generated.h"

UCLASS()
class REVIEWPROJECT_API AVectorObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVectorObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


	UFUNCTION(BlueprintCallable)
	void MoveLeftAxis(float _Value);

	UFUNCTION(BlueprintCallable)
	void MoveRightAxis(float _Value);

	UFUNCTION(BlueprintCallable)
	void MoveUpAxis(float _Value);

	UFUNCTION(BlueprintCallable)
	void MoveDownAxis(float _Value);

private:

	float MoveSpeed = 500.0f;
};
