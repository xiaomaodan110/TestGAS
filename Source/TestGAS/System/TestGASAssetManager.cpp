#include "TestGASAssetManager.h"

#include "AbilitySystemGlobals.h"

UTestGASAssetManager::UTestGASAssetManager()
{

}

void UTestGASAssetManager::StartInitialLoading() {
	Super::StartInitialLoading();

	// TODO
	UAbilitySystemGlobals::Get().InitGlobalData();
}
