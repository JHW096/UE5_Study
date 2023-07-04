// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PFCharacter.generated.h"

UCLASS()
class PORTFOLIO_TEST_API APFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APFCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	void CreateMove();
	void CreateView();
	void CreateSkelMesh();

public:
//Input Binding Keys
	void MappingAndBindingKey();

	
private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* m_SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* m_Camera;

	bool bClickLeftMouse = false;
	bool bclickRightMouse = false;
};
