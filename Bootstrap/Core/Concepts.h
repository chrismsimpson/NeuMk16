
#ifndef CONCEPTS_H
#define CONCEPTS_H

#include "Detail.h"

namespace Core::Concepts {
    
    template<typename T>
    concept Integral = IsIntegral<T>;
}

using Core::Concepts::Integral;

#endif