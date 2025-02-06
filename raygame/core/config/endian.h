#pragma once

//! @ingroup macros_machine
//! @defgroup macros_machine_endian Endianness
//! @{
#if defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_LITTLE_ENDIAN
#    define RAYGAME_BIG_ENDIAN
#endif
//! @}

#if defined(__BYTE_ORDER__)
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#        define RAYGAME_LITTLE_ENDIAN
#    elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#        define RAYGAME_BIG_ENDIAN
#    endif
#endif
