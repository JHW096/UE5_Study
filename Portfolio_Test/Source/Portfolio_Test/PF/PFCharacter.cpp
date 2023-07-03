// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Capsulecomponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APFCharacter::APFCharacter()
{
 	//Set this character to call Tick() every frame. 
	// : ĳ���Ͱ� Tick�Լ����� �� �����Ӹ��� ȣ��Ǵ� ���� �����ϴ� �Լ�
	//You can turn this off to improve performance if you don't need it.
	// �� ����� �ʿ� ���ٸ�, ���� �����ս��� ���� �� �ִ�.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CreateMove();
	CreateView();
	CreateCharacterSkelMesh();

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

}

// Called to bind functionality to input
void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Equals Project Input Setting

	static bool bBindingsAdded = false;

	//Add Input Mapping
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;


		//Key Mappping
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveBackward", EKeys::S, -1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveLeft", EKeys::A, -1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.0f));

		//Mouse Mapping
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.0f));

		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("LeftClick", ))
	}
	
	//Bind Key and Function
	


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

void APFCharacter::CreateCharacterSkelMesh()
{
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Player(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/CharacterMesh/RPG-Character.RPG-Character'")
	);

	if (SM_Player.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Player.Object);
	}

	
}
