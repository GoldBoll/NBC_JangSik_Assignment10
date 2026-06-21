using UnrealBuildTool;

public class Temporary : ModuleRules
{
	public Temporary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 플러그인 모듈도 일반 모듈과 같은 ModuleRules 규칙을 따른다.
		// Public: 헤더(.h)에서 쓰는 의존, Private: 소스(.cpp)에서만 쓰는 의존
		PublicDependencyModuleNames.AddRange(new[] { "Core" });
		PrivateDependencyModuleNames.AddRange(new[] { "CoreUObject", "Engine" });
	}
}
