#pragma once

#include "utils/il2cpp-utils.hpp"
#include "utils/typedefs.h"

#include "System/Collections/Generic/List_1.hpp"
#include "System/Collections/Generic/IReadOnlyList_1.hpp"

template <typename ElementType>
std::vector<ElementType> to_vector(::Array<ElementType> *in) {
    auto itemsStart = in->values;
    auto itemsEnd = itemsStart + (sizeof(ElementType) * in->Length());
    return std::vector(itemsStart, itemsEnd);
}

template <typename ElementType>
std::vector<ElementType> to_vector(::System::Collections::Generic::List_1<ElementType> *in) {
    return to_vector(in->items);
}

template <typename ElementType>
std::vector<ElementType> to_vector(::System::Collections::Generic::IReadOnlyList_1<ElementType> *in) {
    return to_vector(reinterpret_cast<::System::Collections::Generic::List_1<ElementType>*>(in));
}
