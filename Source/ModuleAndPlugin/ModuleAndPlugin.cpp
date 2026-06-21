#include "ModuleAndPlugin.h"
#include "Modules/ModuleManager.h"

// IMPLEMENT_PRIMARY_GAME_MODULE: 프로젝트의 "주 게임 모듈"을 등록한다(프로젝트당 정확히 1개).
//   1번째 인자 = 모듈 구현체(기본 게임 모듈 구현),
//   2번째 = 모듈명, 3번째 = 게임 이름. 일반 모듈의 IMPLEMENT_MODULE 와 구분된다.
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, ModuleAndPlugin, "ModuleAndPlugin");
