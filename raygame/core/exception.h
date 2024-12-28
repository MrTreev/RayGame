#pragma once
#include <stdexcept>

namespace core::exception {
// Honestly, just easier this way, macro is pretty obvious what it does
// macro-parentheses is because it's wrong to do that here
// NOLINTBEGIN(*-macro-usage,*-macro-parentheses)
#define RAYGAME_EXCEPTION_DECL(name)                                           \
    RAYGAME_EXCEPTION_DECL_BASE(name, Exception)
#define RAYGAME_EXCEPTION_DECL_BASE(name, base)                                \
    class name: public base {                                                  \
    public:                                                                    \
        explicit name(const std::string& message);                             \
        explicit name(const base&& error);                                     \
        name(name&&)                 = default;                                \
        name(const name&)            = default;                                \
        name& operator=(name&&)      = default;                                \
        name& operator=(const name&) = default;                                \
        ~name() override;                                                      \
    }

// NOLINTEND(*-macro-usage,*-macro-parentheses)

//! Exception parent class
/*!
 * 	This is the parent class for all RayGame exceptions
 */
RAYGAME_EXCEPTION_DECL_BASE(Exception, std::runtime_error);

//! Unimplemented exception
/*!
 * 	Thrown when a function is not yet implemented,
 * 	but is intended to be implemented at some future point.
 *
 *  Guarantees: No side-effects
 */
RAYGAME_EXCEPTION_DECL(Unimplemented);

//! UnknownCase
/*!
 * 	Thrown when a code case has not been covered.
 *
 *  Guarantees: None
 */
RAYGAME_EXCEPTION_DECL(UnknownCase);

//! Unreachable exception
/*!
 * 	Thrown when a line is hit that should not be reachable
 *
 *  Guarantees: None
 */
RAYGAME_EXCEPTION_DECL(Unreachable);

//! Condition parent class
/*!
 * 	This is the parent class for Pre, Post, and Check Condition exceptions
 *
 *  Guarantees: Specified in children
 *  @see PreCondition
 *  @see CheckCondition
 *  @see PostCondition
 */
RAYGAME_EXCEPTION_DECL(Condition);

//! Pre-Condition exception
/*!
 * 	A thrown PreCondition is guaranteed to not have caused any side-effects when thrown.
 * 	The most common use of a PreCondition is to check for valid function arguments.
 *
 *  Guarantees: No side-effects
 */
RAYGAME_EXCEPTION_DECL_BASE(PreCondition, Condition);

//! Check-Condition exception
/*!
 * 	A thrown CheckCondition does not have any guarantees,
 * 	it is used within a function as a runtime assertion.
 *
 * 	Guarantees: None
 */
RAYGAME_EXCEPTION_DECL_BASE(CheckCondition, Condition);

//! Post-Condition exception
/*!
 * 	Thrown when the operations within the function were successful,
 * 	but the function returned an invalid result.
 *
 *  Guarantees: State is still valid
 */
RAYGAME_EXCEPTION_DECL_BASE(PostCondition, Condition);

#undef RAYGAME_EXCEPTION_DECL
#undef RAYGAME_EXCEPTION_DECL_BASE
} // namespace core::exception
