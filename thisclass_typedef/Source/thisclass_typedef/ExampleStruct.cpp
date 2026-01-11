#include "ExampleStruct.h"

#include <type_traits>

FExampleStruct::FExampleStruct() {
    //static_assert(std::is_same_v<FExampleStruct, This>);
}
