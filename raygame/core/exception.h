#pragma once
#include "raygame/core/concepts.h"
#include <stdexcept>

namespace core::exception {
// Honestly, just easier this way, macro is pretty obvious what it does
// macro-parentheses is because it's wrong to do that here
// NOLINTBEGIN(*-macro-usage,*-macro-parentheses)
#define RAYGAME_EXCEPTION_DECL_BASE(name, base)                                                    \
    class name: public base {                                                                      \
    public:                                                                                        \
        explicit name(const std::string& message);                                                 \
        explicit name(const base&& error);                                                         \
        name(name&&)                 = default;                                                    \
        name(const name&)            = default;                                                    \
        name& operator=(name&&)      = default;                                                    \
        name& operator=(const name&) = default;                                                    \
        ~name() override;                                                                          \
        std::string type() override;                                                               \
    }

// NOLINTEND(*-macro-usage,*-macro-parentheses)

//! Exception parent class
/*!
 * 	This is the parent class for all RayGame exceptions
 */
class Exception: public std::runtime_error {
public:
    explicit Exception(const std::string& message);
    explicit Exception(const std::runtime_error&& error);
    Exception(Exception&&)                 = default;
    Exception(const Exception&)            = default;
    Exception& operator=(Exception&&)      = default;
    Exception& operator=(const Exception&) = default;
    ~Exception() override;
    virtual std::string type();
};

//! Unimplemented exception
/*!
 * 	Thrown when a function is not yet implemented,
 * 	but is intended to be implemented at some future point.
 *
 *  Guarantees: No side-effects
 */
RAYGAME_EXCEPTION_DECL_BASE(Unimplemented, Exception);

//! UnknownCase
/*!
 * 	Thrown when a code case has not been covered.
 *
 *  Guarantees: None
 */
RAYGAME_EXCEPTION_DECL_BASE(UnknownCase, Exception);

//! Unreachable exception
/*!
 * 	Thrown when a line is hit that should not be reachable
 *
 *  Guarantees: None
 */
RAYGAME_EXCEPTION_DECL_BASE(Unreachable, Exception);

//! Condition parent class
/*!
 * 	This is the parent class for Pre, Post, and Check Condition exceptions
 *
 *  Guarantees: Specified in children
 *  @see PreCondition
 *  @see CheckCondition
 *  @see PostCondition
 */
RAYGAME_EXCEPTION_DECL_BASE(Condition, Exception);

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

#undef RAYGAME_EXCEPTION_DECL_BASE

template<concepts::Exception T>
void raygame_throw() {}

} // namespace core::exception
