#include "TestActor.h"
#include "Engine/Engine.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	// Test 모듈이 살아 동작함을 로그 + 화면 메시지로 확인 (모듈 간 참조 성공의 증거)
	UE_LOG(LogTemp, Warning, TEXT("[Test Module] ATestActor::BeginPlay 호출됨"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Test 모듈 정상 동작!"));
	}
}
