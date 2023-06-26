// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MyPart.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	RandomCreate.GenerateNewSeed();

	ObjSize = { 100, 100, 100 };
	CreateHead();
	//CreateWall
	
	CreateWall(MyY, MyZ, ObjSize);
}

void AMyGameMode::Tick(float _Delta)
{
	Super::Tick(_Delta);

	TArray<AActor*> AllObjActor;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Part", AllObjActor);

	MapInfoClear();

	for (size_t i = 0; i < AllObjActor.Num(); i++)
	{
		SetPart(AllObjActor[i]);
	}

	if (BodyType == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BodyType)"), __FUNCTION__, __LINE__);
		return;
	}

	if (CurBody == nullptr && BodyType != nullptr)
	{
		TArray<FIntVector> EmptyPoint;

		for (int z = 0; z < Mapinfo.Num(); z++)
		{
			for (int y = 0; y < Mapinfo[z].Num(); y++)
			{
				if (Mapinfo[z][y] != nullptr)
				{
					continue;
				}

				EmptyPoint.Add({ 0, y, z });
			}
		}

		int RandomIndex = RandomCreate.RandRange(0, EmptyPoint.Num() - 1);

		FIntVector PointVector = EmptyPoint[RandomIndex];

		FTransform Trans;

		Trans.SetLocation({ 0.0f, PointVector.Y * ObjSize.Y, PointVector.Z * ObjSize.Z });


		CurBody = GetWorld()->SpawnActor<AActor>(BodyType, Trans);

	}

}

void AMyGameMode::CreateWall(int _Y, int _Z, FVector _ObjSize)
{
	UE_LOG(LogTemp, Log, TEXT("Create Walls"));

	//FIntVector for ArrayCount;
	ObjCount.Y = _Y;
	ObjCount.Z = _Z;

	//FVector for Setting Map
	ObjSize = _ObjSize;

#pragma region Map

//Init MapInfo.
	Mapinfo.SetNumZeroed(ObjCount.Z);
	for (size_t z = 0; z < Mapinfo.Num(); z++)
	{
		Mapinfo[z].SetNum(ObjCount.Y);
	}

//


#pragma endregion



#pragma region Draw
	//FIntVector for ArrayCount;
	ObjCount.Y = _Y;
	ObjCount.Z = _Z;

	//FVector for Setting Map
	ObjSize = _ObjSize;

	//Spawn Horizontal Wall Line
	for (size_t i = 0; i < ObjCount.Y; i++)
	{
		FTransform Trans;
		Trans.SetLocation({ 0, ObjSize.Y * static_cast<float>(i), 0.0f });
		AActor* SpawnActor0 = GetWorld()->SpawnActor<AActor>(WallType, Trans);

		Trans.SetLocation({ 0, ObjSize.Y * static_cast<float>(i), ObjSize.Z * static_cast<float>(ObjCount.Z - 1) });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(WallType, Trans);
	}

	//Spawn Vertical Wall Line
	for (size_t i = 0; i < ObjCount.Z; i++)
	{
		FTransform TmpTrans;

		//{ 0, 0, 100), (0, 0, 200) ...
		TmpTrans.SetLocation({ 0, 0, ObjSize.Z * i });
		AActor* SpawnActor0 = GetWorld()->SpawnActor<AActor>(WallType, TmpTrans);

		//(0, 400, 100) ..
		TmpTrans.SetLocation({ 0, ObjSize.Y * static_cast<float>(ObjCount.Y - 1), ObjSize.Z * i });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(WallType, TmpTrans);
	}
#pragma endregion

}

void AMyGameMode::CreateHead()
{
	UE_LOG(LogTemp, Log, TEXT("Create Head"));
	
	FIntVector3 CenterCount;
	CenterCount.Y = MyY / 2;
	CenterCount.Z = MyZ / 2;

	FTransform TempTrans;

	TempTrans.SetLocation({ 0.0f, ObjSize.Y * CenterCount.Y, ObjSize.Z * CenterCount.Z });
	

	Head = GetWorld()->SpawnActor<AActor>(HeadType, TempTrans);

	if (Head == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("HEAD IS NULLPTR"));

		return;
	}

	Snake.Add(Head);
	UE_LOG(LogTemp, Log, TEXT("Snake Size : %d"), Snake.Num());
	


}
void AMyGameMode::MapInfoClear()
{
	for (size_t z = 0; z < Mapinfo.Num(); z++)
	{
		for (size_t y = 0; y < Mapinfo[z].Num(); y++)
		{
			Mapinfo[z][y] = nullptr;
		}
	}
}

void AMyGameMode::SetPart(AActor* _Part)
{
	FVector Pos = _Part->GetActorLocation();

	int Y = Pos.Y / ObjSize.Y;
	int Z = Pos.Z / ObjSize.Z;

	if (Y < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return;
	}

	if (Z < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return;
	}

	if (Y >= ObjCount.Y)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (Y >= TileCount.Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return;
	}

	if (Z >= ObjCount.Z)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (Z >= TileCount.Z) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return;
	}
	Mapinfo[Z][Y] = _Part;
}

void AMyGameMode::CurBodyReset()
{
	CurBody = nullptr;
}

bool AMyGameMode::IsPart(FVector _Pos, FName _Tag)
{
	int Y = _Pos.Y / ObjSize.Y;
	int Z = _Pos.Z / ObjSize.Z;

	if (0 > Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return false;
	}

	if (0 > Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return false;
	}

	if (Y >= ObjCount.Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Y >= TileCount.Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return false;
	}

	if (Z >= ObjCount.Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Z >= TileCount.Z) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return false;
	}

	if (Mapinfo[Z][Y] == nullptr)
	{
		return false;
	}


	return Mapinfo[Z][Y]->ActorHasTag(_Tag);
}

AActor* AMyGameMode::GetPart(FVector _Pos, FName _Tag)
{
	int Y = _Pos.Y / ObjSize.Y;
	int Z = _Pos.Z / ObjSize.Z;

	if (0 > Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return nullptr;
	}

	if (0 > Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return nullptr;
	}

	if (Y >= ObjCount.Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Y >= TileCount.Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return nullptr;
	}

	if (Z >= ObjCount.Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Z >= TileCount.Z) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, Y, Z);
		return nullptr;
	}

	if (nullptr == Mapinfo[Z][Y])
	{
		return nullptr;
	}

	if (false == Mapinfo[Z][Y]->ActorHasTag(_Tag))
	{
		return nullptr;
	}

	return Mapinfo[Z][Y];
}

