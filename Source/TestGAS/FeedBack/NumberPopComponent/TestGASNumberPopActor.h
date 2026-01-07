#pragma 

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TestGASNumberPopActor.generated.h"


class UWidgetComponent;


UCLASS()
class TESTGAS_API ATestGASDamageNumActor : public AActor {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DamageNumRootComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* DamageWidgetComponent;

public: 
	ATestGASDamageNumActor();

	void UpdateNum(const FText& InText);
	void UpdateNumColor(const FLinearColor& InColor);
};