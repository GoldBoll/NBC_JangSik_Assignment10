#include "Test.h"
#include "Modules/ModuleManager.h"

// 일반(비-게임) 모듈 등록. 별도 StartupModule 로직이 없으면 기본 구현체 FDefaultModuleImpl 로 충분하다.
//   2번째 인자("Test")는 모듈명과 정확히 일치해야 한다.
IMPLEMENT_MODULE(FDefaultModuleImpl, Test);
