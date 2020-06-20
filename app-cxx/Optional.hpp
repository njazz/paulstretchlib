//
//  Ranged_.hpp
//  ComboEngine
//
//  Created by Alex on 20/11/2019.
//

/// @file
/// @ingroup core_

#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

//#include <stdexcept>
#include "CoreExceptions.hpp"

#include <string>

namespace Core {

template <typename VAL>
struct Optional final {
protected:
    VAL value;
    bool null = true;

    // ---
public:
    bool IsNull() const { return null; }

    void SetNull() { null = true; }

    void Set(const VAL& d)
    {
        value = d;
        null = false;
    }

    VAL Get() const
    {
        if (!null)
            return value;
        else
            CE_THROW("Optional value error.");
    }
    
    VAL& GetRef() {
        if (!null)
            return value;
        else
            CE_THROW("Optional value error.");
    }

public:
    Optional() {}
    Optional(const VAL& v) { Set(v); }
};
}

// ---

#endif
