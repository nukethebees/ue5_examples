#include "DropdownMenuEditor.h"

#include "LevelEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FDropdownMenuEditorModule, DropdownMenuEditor);

void FDropdownMenuEditorModule::StartupModule() {
    CreateDropdownMenu();
}

void FDropdownMenuEditorModule::ShutdownModule() {}

void FDropdownMenuEditorModule::CreateDropdownMenu() {
    auto& level_editor_module{FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor")};
    auto const toolbar_menu_extender{MakeShared<FExtender>()};

    toolbar_menu_extender->AddMenuBarExtension(
        "Help",
        EExtensionHook::After,
        nullptr,
        FMenuBarExtensionDelegate::CreateRaw(
            this, &FDropdownMenuEditorModule::CreateDropdownMenuExtension));
    auto extensibility_manager{level_editor_module.GetMenuExtensibilityManager()};
    extensibility_manager->AddExtender(toolbar_menu_extender);
}
void FDropdownMenuEditorModule::CreateDropdownMenuExtension(FMenuBarBuilder& menu_bar_builder) {
    menu_bar_builder.AddPullDownMenu(
        FText::FromString("Example Menu"),
        FText::FromString("An example menu"),
        FNewMenuDelegate::CreateRaw(
            this, &FDropdownMenuEditorModule::CreateDropdownMenuExtensionButtons));
}
void FDropdownMenuEditorModule::CreateDropdownMenuExtensionButtons(FMenuBuilder& menu_builder) {
    menu_builder.AddMenuEntry(FText::FromName(TEXT("Example Button (lambda)")),
                              FText::FromName(TEXT("Example Button (lambda) Tooltip")),
                              FSlateIcon(),
                              FUIAction(FExecuteAction::CreateLambda(
                                  []() { UE_LOG(LogTemp, Log, TEXT("In a lambda function!")); })));

    menu_builder.AddSubMenu(FText::FromName(TEXT("Example Submenu")),
                            FText::FromName(TEXT("Example Submenu Tooltip")),
                            FNewMenuDelegate::CreateLambda([&](FMenuBuilder& submenu_builder) {
                                submenu_builder.AddMenuEntry(
                                    FText::FromName(TEXT("Example Button (static fn)")),
                                    FText::FromName(TEXT("Example Button (static fn) Tooltip")),
                                    FSlateIcon(),
                                    FUIAction(FExecuteAction::CreateStatic(
                                        &FDropdownMenuEditorModule::ExampleStaticFn)));
                                submenu_builder.AddMenuEntry(
                                    FText::FromName(TEXT("Example Button (member fn)")),
                                    FText::FromName(TEXT("Example Button (member fn) Tooltip")),
                                    FSlateIcon(),
                                    FUIAction(FExecuteAction::CreateRaw(
                                        this, &FDropdownMenuEditorModule::ExampleMemberFn)));
                            }));
    menu_builder.AddMenuEntry(FText::FromName(TEXT("Example Button (free fn)")),
                              FText::FromName(TEXT("Example Button (free fn)")),
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
