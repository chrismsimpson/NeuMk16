
#ifndef WEAKABLE_H
#define WEAKABLE_H

#include "RefCounted.h"

namespace Core {

    class WeakLink: public RefCounted<WeakLink> {
        
    };
}

#endif