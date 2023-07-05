#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class AnimState : uint8
{
	NONE,
	IDLE,
	FWDMOVE,
	NORMALATTACK,
	DASH
};
