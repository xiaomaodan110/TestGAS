#pragma once

#include "CoreMinimal.h"
#include "TestGASComponentBase.h"
#include "TestGASComboComponent.generated.h"


// no sync component.
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTGAS_API UTestGASComboComponent : public UTestGASComponentBase
{
	GENERATED_BODY()

public:
	UTestGASComboComponent();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	int32 GetComboIndex();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	UAnimMontage* GetNextComboAnimMontage();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	UAnimMontage* GetLastComboAnimMontage();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	void UpdateComboIndex();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	void ResetComboIndex();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	void SetPressed();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	void ResetPressed();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Fight|Combo")
	bool IsStillPressed();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "TestGAS|Fight|Combo")
	TArray<UAnimMontage*> ComboMontages; 

	UPROPERTY();
	UAnimMontage* LastPlayMontage = nullptr;

	int32 ComboIndex = 0;

	int32 ComboMaxIndex = 0;

	bool bShortPress = false;
};