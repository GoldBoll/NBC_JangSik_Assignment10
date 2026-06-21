#include "Temporary.h"

#define LOCTEXT_NAMESPACE "FTemporaryModule"

void FTemporaryModule::StartupModule()
{
	// LoadingPhase=Default 시점에 호출된다. 플러그인이 정상 로드됐음을 로그로 확인.
	UE_LOG(LogTemp, Warning, TEXT("[Temporary Plugin] StartupModule - 플러그인 모듈 로드됨"));
}

void FTemporaryModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("[Temporary Plugin] ShutdownModule - 플러그인 모듈 언로드됨"));
}

#undef LOCTEXT_NAMESPACE

// IMPLEMENT_MODULE: 일반 모듈 등록 매크로. 2번째 인자("Temporary")는 .uplugin의 모듈명 및
//   Build.cs 클래스명과 정확히 일치해야 StartupModule이 호출된다(불일치 시 로그 안 뜸).
IMPLEMENT_MODULE(FTemporaryModule, Temporary)
