// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorObj.h"

// Sets default values
AVectorObj::AVectorObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVectorObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVectorObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVectorObj::MoveLeftAxis(float _Value)
{
	if (_Value == 0)
	{
		return;
	}

	AddActorLocalOffset(FVector::LeftVector * GetWorld()->DeltaTimeSeconds * MoveSpeed );
}

void AVectorObj::MoveRightAxis(float _Value)
{
	if (_Value == 0)
	{
		return;
	}

	AddActorLocalOffset(FVector::RightVector * GetWorld()->DeltaTimeSeconds * MoveSpeed);
}

void AVectorObj::MoveUpAxis(float _Value)
{
	if (_Value == 0)
	{
		return;
	}

	AddActorLocalOffset(FVector::ForwardVector * GetWorld()->DeltaTimeSeconds * MoveSpeed);
}

void AVectorObj::MoveDownAxis(float _Value)
{
	if (_Value == 0)
	{
		return;
	}

	AddActorLocalOffset(FVector::BackwardVector * GetWorld()->DeltaTimeSeconds * MoveSpeed);
}

