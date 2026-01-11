#include "ExampleClass.h"

#include <type_traits>

UExampleClass::UExampleClass() {
    static_assert(std::is_same_v<UExampleClass, ThisClass>);
}
