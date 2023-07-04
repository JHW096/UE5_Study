// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Capsulecomponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PFPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "GameFramework/PlayerController.h"

// Sets default values
APFCharacter::APFCharacter()
{
 	//Set this character to call Tick() every frame. 
	// : 캐릭터가 Tick함수에서 매 프레임마다 호출되는 것을 세팅하는 함수
	//You can turn this off to improve performance if you don't need it.
	// 이 기능이 필요 없다면, 향상된 퍼포먼스를 얻을 수 있다.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CreateMove();
	CreateView();
	CreateSkelMesh();

}

// Called when the game starts or when spawned
void APFCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bClickLeftMouse)
	{
		
	}

}

// Called to bind functionality to input
void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	MappingAndBindingKey();
	//Equals Project Input Setting
}

void APFCharacter::CreateMove()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void APFCharacter::CreateView()
{
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	m_SpringArm->SetupAttachment(this->GetCapsuleComponent());
	m_SpringArm->SetUsingAbsoluteRotation(true);
	m_SpringArm->TargetArmLength = 1250.0f;
	m_SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	m_SpringArm->bDoCollisionTest = false;



	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MAINCAMERA"));
	m_Camera->SetupAttachment(this->m_SpringArm);
	m_Camera->bUsePawnControlRotation = false;
}

void APFCharacter::CreateSkelMesh()
{
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Player(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/CharacterMesh/RPG-Character.RPG-Character'")
	);

	if (SM_Player.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Player.Object);
	}

	
}

void APFCharacter::MappingAndBindingKey()
{
	static bool bBindingAdded = false;

	//Mapping equals Project input settings.
	if (!bBindingAdded)
	{
		bBindingAdded = true;

		//Mapping Click Move
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("LeftClick", EKeys::LeftMouseButton, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("RightClick", EKeys::RightMouseButton, 1.0f));

		//Mapping Player Control
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Button_Space", EKeys::SpaceBar, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Button_C", EKeys::C, 1.0f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Button_Q", EKeys::Q, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Button_W", EKeys::W, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Button_E", EKeys::E, 1.0f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Button_R", EKeys::R, 1.0f));

		//Mapping Use Item
		
	}

	//Binding InputKey and Playe
}
