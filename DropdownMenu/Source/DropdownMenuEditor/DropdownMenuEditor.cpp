#include "DropdownMenuEditor.h"

#include "LevelEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDropdownMenuEditorModule, DropdownMenuEditor);

#define LOCTEXT_NAMESPACE "DropdownMenuEditor"

void FDropdownMenuEditorModule::StartupModule() {
    CreateDropdownMenu();
}

void FDropdownMenuEditorModule::ShutdownModule() {}

void FDropdownMenuEditorModule::CreateDropdownMenu() {
    auto const toolbar_menu_extender{MakeShared<FExtender>()};
    toolbar_menu_extender->AddMenuBarExtension(
        "Help",
        EExtensionHook::After,
        nullptr,
        FMenuBarExtensionDelegate::CreateRaw(
            this, &FDropdownMenuEditorModule::CreateDropdownMenuExtension));

    auto& level_editor_module{FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor")};
    auto extensibility_manager{level_editor_module.GetMenuExtensibilityManager()};
    extensibility_manager->AddExtender(toolbar_menu_extender);
}
void FDropdownMenuEditorModule::CreateDropdownMenuExtension(FMenuBarBuilder& menu_bar_builder) {
    menu_bar_builder.AddPullDownMenu(
        LOCTEXT("ExampleMenu_Label", "Example Menu"),
        LOCTEXT("ExampleMenu_Tooltip", "An example menu"),
        FNewMenuDelegate::CreateRaw(
            this, &FDropdownMenuEditorModule::CreateDropdownMenuExtensionButtons));
}
void FDropdownMenuEditorModule::CreateDropdownMenuExtensionButtons(FMenuBuilder& menu_builder) {
    menu_builder.AddMenuEntry(LOCTEXT("ExampleMenuLambda_Label", "Example Button (lambda)"),
                              LOCTEXT("ExampleMenuLambda_Label", "Example Button (lambda) Tooltip"),
                              FSlateIcon(),
                              FUIAction(FExecuteAction::CreateLambda(
                                  []() { UE_LOG(LogTemp, Log, TEXT("In a lambda function!")); })));

    menu_builder.AddSubMenu(LOCTEXT("ExampleMenuSubmenu_Label", "Example Submenu"),
                            LOCTEXT("ExampleMenuSubmenu_Tooltip", "Example Submenu Tooltip"),
                            FNewMenuDelegate::CreateLambda([&](FMenuBuilder& submenu_builder) {
                                submenu_builder.AddMenuEntry(
                                    LOCTEXT("ExampleMenuStatic_Label",
                                            "Example Button (static fn)"),
                                    LOCTEXT("ExampleMenuStatic_Tooltip",
                                            "Example Button (static fn) Tooltip"),
                                    FSlateIcon(),
                                    FUIAction(FExecuteAction::CreateStatic(
                                        &FDropdownMenuEditorModule::ExampleStaticFn)));
                                submenu_builder.AddMenuEntry(
                                    LOCTEXT("ExampleMenuMemberFn_Label",
                                            "Example Button (member fn)"),
                                    LOCTEXT("ExampleMenuMemberFn_Tooltip",
                                            "Example Button (member fn) Tooltip"),
                                    FSlateIcon(),
                                    FUIAction(FExecuteAction::CreateRaw(
                                        this, &FDropdownMenuEditorModule::ExampleMemberFn)));
                            }));
    menu_builder.AddMenuEntry(LOCTEXT("ExampleMenuFreeFn_Label", "Example Button (free fn)"),
                              LOCTEXT("ExampleMenuFreeFn_Tooltip", "Example Button (free fn)"),
                              FSlateIcon(),
                              FUIAction(FExecuteAction::CreateStatic(&ExampleFreeFn)));
}

void FDropdownMenuEditorModule::ExampleStaticFn() {
    UE_LOG(LogTemp, Log, TEXT("In a static member function!"));
}
void FDropdownMenuEditorModule::ExampleMemberFn() {
    UE_LOG(LogTemp, Log, TEXT("In a member function!"));
}

void ExampleFreeFn() {
    UE_LOG(LogTemp, Log, TEXT("In a free function!"));
}

#undef LOCTEXT_NAMESPACE