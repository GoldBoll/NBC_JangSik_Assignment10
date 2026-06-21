#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ModuleAndPluginGameMode.generated.h"

/**
 * 주 게임 모듈의 기본 GameMode.
 * BeginPlay에서 Test 모듈의 ATestActor를 스폰해 "모듈 간 참조"를 실증한다.
 * (DefaultEngine.ini의 GlobalDefaultGameMode로 지정되어 어떤 레벨에서 Play 해도 동작)
 */
UCLASS()
class MODULEANDPLUGIN_API AModuleAndPluginGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
