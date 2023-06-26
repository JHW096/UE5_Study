// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHead.h"
#include "MyGameMode.h"

// Sets default values
AMyHead::AMyHead()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyHead::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyHead::PressLeftAction()
{
	FVector MovePos = FVector::LeftVector * 100.0f;
	if (GetMyGameMode()->IsPart(GetActorLocation() + MovePos, "Wall") == true)
	{
		return;
	}

	for (int i = 0; i < GetMyGameMode()->Snake.Num(); i++)
	{
		Cast<AMyPart>(GetMyGameMode()->Snake[i])->Prev = GetMyGameMode()->Snake[i]->GetActorLocation();
	}

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetActorLocation() + MovePos ==
			GetMyGameMode()->Snake[i]->GetActorLocation())
		{
			return;
		}
	} 

	AddActorLocalOffset(FVector::LeftVector * 100.0f);

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetMyGameMode()->Snake[i] != nullptr)
		{
			GetMyGameMode()->Snake[i]->SetActorLocation(
				Cast<AMyPart>(GetMyGameMode()->Snake[i - 1])->Prev
			);
		}
	}


	if (GetMyGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetMyGameMode()->GetPart(GetActorLocation(), "Body");
		
		Body->SetActorLocation(
			GetMyGameMode()->Snake[GetMyGameMode()->Snake.Num() - 1]->GetActorLocation() + FVector::RightVector * 100
		);

		GetMyGameMode()->Snake.Add(Body);

		if (GetMyGameMode()->Snake.Num() != 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Snake Size : %d"), GetMyGameMode()->Snake.Num());
		}
		
		GetMyGameMode()->CurBodyReset();
	}

	

}

void AMyHead::PressRightAction()
{
	FVector MovePos = FVector::RightVector * 100.0f;
	if (GetMyGameMode()->IsPart(GetActorLocation() + MovePos, "Wall") == true)
	{
		return;
	}

	for (int i = 0; i < GetMyGameMode()->Snake.Num(); i++)
	{
		Cast<AMyPart>(GetMyGameMode()->Snake[i])->Prev = GetMyGameMode()->Snake[i]->GetActorLocation();
	}

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetActorLocation() + MovePos ==
			GetMyGameMode()->Snake[i]->GetActorLocation())
		{
			return;
		}
	}

	AddActorLocalOffset(FVector::RightVector * 100.0f);

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetMyGameMode()->Snake[i] != nullptr)
		{
			GetMyGameMode()->Snake[i]->SetActorLocation(
				Cast<AMyPart>(GetMyGameMode()->Snake[i - 1])->Prev
			);
		}
	} 

	if (GetMyGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetMyGameMode()->GetPart(GetActorLocation(), "Body");
		
		Body->SetActorLocation(
			GetMyGameMode()->Snake[GetMyGameMode()->Snake.Num() - 1]->GetActorLocation() + FVector::LeftVector * 100
		);

		GetMyGameMode()->Snake.Add(Body);

		if (GetMyGameMode()->Snake.Num() != 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Snake Size : %d"), GetMyGameMode()->Snake.Num());
		}
		
		GetMyGameMode()->CurBodyReset();
	}
}

void AMyHead::PressUpAction()
{
	FVector MovePos = FVector::UpVector * 100.0f;
	if (GetMyGameMode()->IsPart(GetActorLocation() + MovePos, "Wall") == true)
	{
		return;
	}

	for (int i = 0; i < GetMyGameMode()->Snake.Num(); i++)
	{
		Cast<AMyPart>(GetMyGameMode()->Snake[i])->Prev = GetMyGameMode()->Snake[i]->GetActorLocation();
	}

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetActorLocation() + MovePos ==
			GetMyGameMode()->Snake[i]->GetActorLocation())
		{
			return;
		}
	}

	AddActorLocalOffset(FVector::UpVector * 100.0f);

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetMyGameMode()->Snake[i] != nullptr)
		{
			GetMyGameMode()->Snake[i]->SetActorLocation(
				Cast<AMyPart>(GetMyGameMode()->Snake[i - 1])->Prev
			);
		}
	}
	if (GetMyGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetMyGameMode()->GetPart(GetActorLocation(), "Body");
		
		Body->SetActorLocation(
			GetMyGameMode()->Snake[GetMyGameMode()->Snake.Num() - 1]->GetActorLocation() + FVector::DownVector * 100
		);

		GetMyGameMode()->Snake.Add(Body);

		if (GetMyGameMode()->Snake.Num() != 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Snake Size : %d"), GetMyGameMode()->Snake.Num());
		}
		
		GetMyGameMode()->CurBodyReset();
	}
}

void AMyHead::PressDownAction()
{
	FVector MovePos = FVector::DownVector * 100.0f;
	if (GetMyGameMode()->IsPart(GetActorLocation() + MovePos, "Wall") == true)
	{
		return;
	}


	for (int i = 0; i < GetMyGameMode()->Snake.Num(); i++)
	{
		Cast<AMyPart>(GetMyGameMode()->Snake[i])->Prev = GetMyGameMode()->Snake[i]->GetActorLocation();
	}

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetActorLocation() + MovePos ==
			GetMyGameMode()->Snake[i]->GetActorLocation())
		{
			return;
		}
	}

	AddActorLocalOffset(FVector::DownVector * 100.0f);

	for (size_t i = 1; i < GetMyGameMode()->Snake.Num(); i++)
	{
		if (GetMyGameMode()->Snake[i] != nullptr)
		{
			GetMyGameMode()->Snake[i]->SetActorLocation(
				Cast<AMyPart>(GetMyGameMode()->Snake[i - 1])->Prev
			);
		}
	}
	if (GetMyGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetMyGameMode()->GetPart(GetActorLocation(), "Body");
		
		Body->SetActorLocation(
			GetMyGameMode()->Snake[GetMyGameMode()->Snake.Num() - 1]->GetActorLocation() + FVector::UpVector * 100
		);

		GetMyGameMode()->Snake.Add(Body);

		if (GetMyGameMode()->Snake.Num() != 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Snake Size : %d"), GetMyGameMode()->Snake.Num());
		}
		
		GetMyGameMode()->CurBodyReset();
	}
}

