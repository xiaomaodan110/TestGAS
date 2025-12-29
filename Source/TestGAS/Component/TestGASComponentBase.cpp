#include "TestGASComponentBase.h"


UTestGASComponentBase::UTestGASComponentBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// close tick.
	PrimaryComponentTick.bCanEverTick = false;
}
