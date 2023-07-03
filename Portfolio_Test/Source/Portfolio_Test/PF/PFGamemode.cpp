// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGamemode.h"
#include "PFCharacter.h"
#include "PF_HUD.h"

APFGamemode::APFGamemode()
{

	DefaultPawnClass = APFGamemode::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter> BP_Character(
		TEXT("/Script/Engine.Blueprint'/Game/BP_PFCharacter.BP_PFCharacter_C'")
	);

	if (BP_Character.Succeeded())
	{
		DefaultPawnClass = BP_Character.Class;
	}

	PlayerControllerClass = APFGamemode::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerController> BP_PlayerController(
		TEXT("/Script/Engine.Blueprint'/Game/BP_PFPlayerController.BP_PFPlayerController_C'")
	);

	if (BP_PlayerController.Succeeded())
	{
		PlayerControllerClass = BP_PlayerController.Class;
	}


	HUDClass = APF_HUD::StaticClass();

	static ConstructorHelpers::FClassFinder<AHUD> BP_HUD(
		TEXT("/Script/Engine.Blueprint'/Game/WorldSetting/BP_PFHUD.BP_PFHUD_C'")
	);
 
	if (BP_HUD.Succeeded())
	{
		HUDClass = BP_HUD.Class;
	}

}