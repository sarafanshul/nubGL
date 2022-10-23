//
// Created by Anshul Saraf on 23/10/22.
//

#ifndef OPENGLBASICS_UTILS_H
#define OPENGLBASICS_UTILS_H

#include "memory"


template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args){
    return std::make_unique<T>(std::forward<Args>(args)...);
}

#endif //OPENGLBASICS_UTILS_H
