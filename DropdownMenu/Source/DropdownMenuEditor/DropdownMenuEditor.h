#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FMenuBarBuilder;
class FMenuBuilder;

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
};

void ExampleFreeFn();
