#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Temporary 플러그인의 런타임 모듈.
 * 플러그인의 진입/종료 지점을 직접 다루기 위해 IModuleInterface를 구현한다.
 * (일반 Test 모듈이 FDefaultModuleImpl로 충분했던 것과 대비되는 지점)
 */
class FTemporaryModule : public IModuleInterface
{
public:
	/** 모듈이 메모리에 로드된 직후 호출 — 플러그인 초기화 자리 */
	virtual void StartupModule() override;

	/** 모듈이 언로드되기 직전 호출 — StartupModule에서 잡은 자원 정리 자리 */
	virtual void ShutdownModule() override;
};
