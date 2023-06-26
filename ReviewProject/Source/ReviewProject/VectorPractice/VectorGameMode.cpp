// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorGameMode.h"
#include "Kismet/GameplayStatics.h"


void AVectorGameMode::Reset()
{
	State = VectorState::Idle;
	OtherActor->SetActorLocation(OriPos);
}

void AVectorGameMode::BeginPlay()
{
	VectorSpeed = 200.0f;

#pragma region FindMain

	{
		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Main", AllActor);

		if (AllActor.Num() != 1)
		{
			UE_LOG(LogTemp, Error, TEXT("%s(%u) Main Actor is Nullptr"),
				__FUNCTION__, __LINE__
			);
		}

		MainActor = AllActor[0];
	}

#pragma endregion


#pragma region FindOther

	{
		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Other", AllActor);

		if (AllActor.Num() != 1)
		{
			UE_LOG(LogTemp, Error, TEXT("%s(%u) Other Actor is Nullptr"),
				__FUNCTION__, __LINE__
				);
		}

		OtherActor = AllActor[0];

		OriPos = OtherActor->GetActorLocation();
	}

#pragma endregion


}

void AVectorGameMode::Tick(float _Delta)
{
	switch (State)
	{
		case VectorState::Idle:

		break;
		case VectorState::Trace:
		{
			FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
			Dir.Normalize();

			OtherActor->AddActorLocalOffset(Dir * _Delta * VectorSpeed);
		}
		break;
		
		case VectorState::WorldTrace:
		{
			FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
			Dir.Normalize();

			OtherActor->AddActorWorldOffset(Dir * _Delta * VectorSpeed);
		}
		break;

		case VectorState::Jump:
		{
			FVector Gravity = { -500, 0, 0};

			UpVector += Gravity * _Delta;

			FVector LastVector = UpVector;			

			OtherActor->AddActorLocalOffset(LastVector * _Delta);
		}
		break;

		case VectorState::AccTrace:
		{
			FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
			Dir.Normalize();

			AccTraceDir += Dir * _Delta * 500.0f;

			if (AccTraceDir.Length() >= 350.0f)
			{
				AccTraceDir.Normalize();
				AccTraceDir *= 350.0f;
			}

			OtherActor->AddActorLocalOffset(AccTraceDir * _Delta);
		}
		break;

		case VectorState::Look:
		{
			FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
			
			FRotator Rot = Dir.Rotation();

			OtherActor->SetActorRotation(Rot);
		}
		break;

		case VectorState::AngleRot:
		{
			FRotator Rot = FRotator::MakeFromEuler( {0, 0, 360.0f * _Delta } );
			OtherActor->AddActorWorldRotation(Rot);
		}
		break;

		case VectorState::AngleLook:
		{
			FVector MainPos = MainActor->GetActorLocation();
			FVector OtherPos = OtherActor->GetActorLocation();

			MainPos.Z = 0.0f;
			OtherPos.Z = 0.0f;

			FVector Dir = MainPos - OtherPos;

			float Angle = Dir.HeadingAngle();
			Angle = FMath::RadiansToDegrees(Angle);

			UE_LOG(LogTemp, Log, TEXT("%s(%u) > Angle[%f] ")
				, __FUNCTION__, __LINE__, Angle );

			if (FMath::Abs(Angle) <= 5.0f)
			{
				break;
			}
			else
			{
				Angle = -1.0f;
			}

			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Angle * 360.0f * _Delta });
			OtherActor->AddActorWorldRotation(Rot);

		}
		break;
		default:
			break;
	}
}
