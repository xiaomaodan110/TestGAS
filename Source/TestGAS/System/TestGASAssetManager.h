#pragma once

#include "Engine/AssetManager.h"

#include "Templates/SubclassOf.h"
#include "TestGASAssetManager.generated.h"

UCLASS(Config = Game)
class TESTGAS_API UTestGASAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	UTestGASAssetManager();

protected:
	virtual void StartInitialLoading() override;
};

