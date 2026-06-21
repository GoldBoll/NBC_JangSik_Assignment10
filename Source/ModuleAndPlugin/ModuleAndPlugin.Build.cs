using UnrealBuildTool;

public class ModuleAndPlugin : ModuleRules
{
	public ModuleAndPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Public/Private 폴더 없이 모듈 루트에 헤더를 두므로 루트를 include 경로에 추가
		PublicIncludePaths.Add(ModuleDirectory);

		// "Test" = 직접 만든 새 모듈에 대한 의존. 주 모듈이 ATestActor를 스폰(헤더 참조)하므로
		// 헤더 단계에서 필요 → PublicDependency 로 등록한다. (Private면 .cpp에서만 가능)
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "Test"
		});
	}
}
