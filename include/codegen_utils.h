#pragma once

#include "utils/il2cpp-utils.hpp"
#include "utils/typedefs.h"

#include "System/Collections/Generic/List_1.hpp"
#include "System/Collections/Generic/IReadOnlyList_1.hpp"

template<typename ElementType>
std::vector<ElementType> to_vector(::Array<ElementType> *in) {
    auto itemsStart = in->values;
    auto itemsEnd = itemsStart + (sizeof(ElementType) * in->Length());
    return std::vector(itemsStart, itemsEnd);
}

template<typename ElementType>
std::vector<ElementType> to_vector(::System::Collections::Generic::List_1<ElementType> *in) {
    return to_vector(in->items);
}

template<typename ElementType>
std::vector<ElementType> to_vector(::System::Collections::Generic::IReadOnlyList_1<ElementType> *in) {
    return to_vector(reinterpret_cast<::System::Collections::Generic::List_1<ElementType> *>(in));
}

template<typename ResultType, typename ArgType = Il2CppObject *,
    std::enable_if_t<std::is_pointer_v<ResultType> && std::is_pointer_v<ArgType>, bool> = true>
ResultType cs_dynamic_cast(ArgType in) {
    if (!in) return nullptr;
    Il2CppClass *argClass = il2cpp_functions::object_get_class(in);
    Il2CppClass *resClass = classof(ResultType);
    if (il2cpp_functions::class_is_assignable_from(argClass, resClass))
        return reinterpret_cast<ResultType>(in);
    else return nullptr;
}
