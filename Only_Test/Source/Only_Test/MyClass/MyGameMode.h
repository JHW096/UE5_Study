// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ONLY_TEST_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void BeginPlay() override;
	
	void Tick(float _Delta) override;

public:
	
	FORCEINLINE FIntVector3 GetObjCount() const
	{
		return ObjCount;
	}

	FORCEINLINE FVector GetObjSize()
	{
		return ObjSize;
	}

	UFUNCTION(BlueprintCallable)
	void CreateWall(int _Y, int _Z, FVector _ObjSize);

	void CreateHead();

	void MapInfoClear();

	void SetPart(AActor* _Part);

	void CurBodyReset();

	bool IsPart(FVector _Pos, FName _Tag);

	AActor* GetPart(FVector _Pos, FName _Tag);

	FORCEINLINE AActor* GetHead()
	{
		return Head;
	}

	TArray<AActor*> Snake;

private:

	FVector ObjSize;
	FIntVector3 ObjCount;

private:
//Graphic info
	UPROPERTY(EditAnywhere, category = "GameModeValue")
	TSubclassOf<APawn> DefaultPawnType;

	UPROPERTY(EditAnywhere, category = "GameModeValue")
	TSubclassOf<AActor> HeadType;

	UPROPERTY(EditAnywhere, category = "GameModeValue")
	TSubclassOf<AActor> WallType;

	UPROPERTY(EditAnywhere, category = "GameModeValue")
	TSubclassOf<AActor> BodyType;

	UPROPERTY(EditAnywhere, category = "GameModeValue")
	int MyY;

	UPROPERTY(EditAnywhere, category = "GameModeValue")
	int MyZ;

private:
//Map info.

	AActor* Head;

	AActor* CurBody = nullptr;
	
	TArray<TArray<AActor*>> Mapinfo;

	FRandomStream RandomCreate = FRandomStream();


	

};
