//
// Created by Anshul Saraf on 28/12/22.
//

#ifndef OPENGLBASICS_SINGLETON_H
#define OPENGLBASICS_SINGLETON_H

#include "Common.h"

template <typename TYPE>
class Singleton : NonCopyable
{
public:
    // This function should be inlined as much as possible. The first access should
    // provide a mutex protected creation of the instance
    static TYPE& getInstance() ALWAYS_INLINE
    {
        if (CC_LIKELY(spInstance))
            return *spInstance;
        return getInstanceInternal();
    }

private:
    // This function does not want to be inlined. This saves 23 instructions of assembly per getInstance call.
    static TYPE& getInstanceInternal() NEVER_INLINE
    {
        static TYPE sInstance;
        spInstance = &sInstance;
        return sInstance;
    }

    static TYPE *spInstance;
};

template<typename TYPE> TYPE* Singleton< TYPE >::spInstance;

#endif //OPENGLBASICS_SINGLETON_H
