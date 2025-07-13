#include "TestGASComponentBase.h"


UTestGASComponentBase::UTestGASComponentBase():Super()
{
	// close tick.
	PrimaryComponentTick.bCanEverTick = false;
}
