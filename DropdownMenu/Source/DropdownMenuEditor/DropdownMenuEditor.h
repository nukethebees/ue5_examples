#pragma once

#include "Templates/SharedPointer.h"

#include "Modules/ModuleInterface.h"

class FMenuBarBuilder;
class FMenuBuilder;
class FExtender;

class FDropdownMenuEditorModule : public IModuleInterface {
  public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

  private:
    void CreateDropdownMenu();
    void CreateDropdownMenuExtension(FMenuBarBuilder& menu_bar_builder);
    void CreateDropdownMenuExtensionButtons(FMenuBuilder& menu_builder);

    static void ExampleStaticFn();
    void ExampleMemberFn();

    TSharedPtr<FExtender> toolbar_menu_extender;
};

void ExampleFreeFn();
