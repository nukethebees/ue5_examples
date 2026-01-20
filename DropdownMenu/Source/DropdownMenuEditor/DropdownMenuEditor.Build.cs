using UnrealBuildTool;

public class DropdownMenuEditor : ModuleRules
{
    public DropdownMenuEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Slate", "SlateCore" });
    }
}