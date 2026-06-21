#include "ModuleAndPluginGameMode.h"
#include "TestActor.h"      // ★ Test 모듈의 공개 헤더 참조 — 모듈 간 의존을 실제로 사용하는 지점
#include "CharacterData.h"  // ★ Test 모듈의 데이터 클래스 참조 (도전 과제)
#include "Engine/World.h"
#include "Engine/Engine.h"

void AModuleAndPluginGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 주 모듈(ModuleAndPlugin)에서 Test 모듈의 액터를 스폰한다.
	// 이 한 줄이 성립하려면 Build.cs PublicDependency 에 "Test" 가 있어야 하고,
	// Test 모듈이 주 모듈보다 먼저 로드되어야(.uproject LoadingPhase=PreDefault) 안전하다.
	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<ATestActor>(ATestActor::StaticClass(), FTransform::Identity);
		UE_LOG(LogTemp, Warning, TEXT("[ModuleAndPlugin] GameMode::BeginPlay -> TestActor 스폰 요청"));
	}

	// 도전 과제: Test 모듈의 UCharacterData를 생성해 캐릭터 데이터처럼 사용하고 화면에 출력한다.
	// NewObject의 Outer를 this(GameMode)로 두어 GameMode 수명에 맞춰 GC가 관리하게 한다.
	UCharacterData* Data = NewObject<UCharacterData>(this);
	UE_LOG(LogTemp, Warning, TEXT("[ModuleAndPlugin] CharacterData: %s / HP %d / Speed %.0f"),
		*Data->CharacterName, Data->Health, Data->MoveSpeed);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
			FString::Printf(TEXT("Name: %s  HP: %d  Speed: %.0f"),
				*Data->CharacterName, Data->Health, Data->MoveSpeed));
	}
}
