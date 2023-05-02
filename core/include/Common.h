//
// Created by Anshul Saraf on 23/10/22.
//

#ifndef OPENGLBASICS_COMMON_H
#define OPENGLBASICS_COMMON_H

#include "memory"

#define ALWAYS_INLINE   __attribute__ ((always_inline))
#define NEVER_INLINE    __attribute__ ((noinline))

#ifdef __cplusplus
#   define CC_LIKELY( exp )    (__builtin_expect( !!(exp), true ))
#   define CC_UNLIKELY( exp )  (__builtin_expect( !!(exp), false ))
#else
#   define CC_LIKELY( exp )    (__builtin_expect( !!(exp), 1 ))
#   define CC_UNLIKELY( exp )  (__builtin_expect( !!(exp), 0 ))
#endif

/**
 */
class NonCopyable{
protected:
    NonCopyable() = default;
private:
    NonCopyable(NonCopyable const&) = delete;
    void operator=(NonCopyable const&) = delete;
};

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args){
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args){
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#endif //OPENGLBASICS_COMMON_H
