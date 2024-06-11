#pragma once
#include <stdexcept>

namespace core::exception {

namespace detail {
class Condition: public std::logic_error {
public:
    explicit Condition(const std::string& message)
        : ::std::logic_error(message){};
    explicit Condition(const std::logic_error&& error)
        : ::std::logic_error(error){};
};
} // namespace detail

//! Pre-Check-Condition exception
/*!
 * 	A thrown PreCondition is guaranteed to not have caused any side-effects when
 * 	thrown.
 * 	The most common use of a PreCondition is to check for valid function arguments.
 */
class PreCondition: public detail::Condition {
public:
    explicit PreCondition(const std::string& message)
        : detail::Condition(message){};
};

//! Check-Condition exception
/*!
 * 	A thrown CheckCondition does not have any guarantees, it is used anywhere in
 * 	a function as a runtime assertion.
 */
class CheckCondition: public detail::Condition {
public:
    explicit CheckCondition(const std::string& message)
        : detail::Condition(message){};
};

//! Post-Check-Condition exception
/*!
 * 	A thrown PostCondition is used to show that the operations within the
 * 	function were successful, but the function produced an invalid result.
 */
class PostCondition: public detail::Condition {
public:
    explicit PostCondition(const std::string& message)
        : detail::Condition(message){};
};
} // namespace core::exception
