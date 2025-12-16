#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"


#include "AnimNotifyState_StopSpeed.generated.h"


UCLASS(meta = (DisplayName = "StopSpeed"))
class TESTGAS_API UAnimNotifyState_StopSpeed : public UAnimNotifyState {

	GENERATED_BODY()

protected:
	float MaxWalkSpeed = 0.f;
	float MinAnalogWalkSpeed = 0.f;
public:
	UAnimNotifyState_StopSpeed();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

};