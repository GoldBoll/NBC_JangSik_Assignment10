#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

/**
 * Test 모듈이 제공하는 액터.
 * 주 게임 모듈이 이 클래스를 참조·스폰하여 "모듈 간 상호작용"을 보여준다.
 * TEST_API: 다른 모듈에서 이 클래스를 사용할 수 있도록 내보내는(export) 매크로.
 */
UCLASS()
class TEST_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	ATestActor();

protected:
	virtual void BeginPlay() override;
};
