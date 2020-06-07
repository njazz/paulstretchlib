//
//  CoreExceptions.hpp
//  ComboEngine
//
//  Created by Alex on 24/02/2020.
//

#ifndef CoreExceptions_h
#define CoreExceptions_h

// @todo: better handling with no exceptions

#ifndef CE_NO_EXCEPTIONS
    #define CE_THROW(x) throw x
    #define CE_TRY try
    #define CE_CATCH(x) catch(x)
    #define CE_INTERNAL_CATCH(x) catch(x)

    #define CE_ERR_RUNTIME(x) std::runtime_error(x)
    #define CE_ERR(x) std::runtime_error(x)

    constexpr bool CoreCap_NoExceptions() { return false; }
#else
    #include <cstdlib>
    #define CE_THROW(exception) std::abort()
    #define CE_TRY if(true)
    #define CE_CATCH(exception) if(false)
    #define CE_INTERNAL_CATCH(exception) if(false)

    #define CE_ERR_RUNTIME(x) __CE_ERR(x)
    #define CE_ERR(x) __CE_ERR(x)

    constexpr bool CoreCap_NoExceptions() { return true; }
#endif

#endif /* CoreExceptions_h */
