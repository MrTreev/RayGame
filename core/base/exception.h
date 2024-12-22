#pragma once
#include <stdexcept>

namespace core::exception {

class Exception: public std::runtime_error {
public:
    explicit Exception(const std::string& message);
    explicit Exception(const std::runtime_error&& error);
    virtual ~Exception() override;
};

class Condition: public Exception {
public:
    explicit Condition(const std::string& message);
    virtual ~Condition() override;
};

//! Pre-Check-Condition exception
/*!
 * 	A thrown PreCondition is guaranteed to not have caused any side-effects when
 * 	thrown.
 * 	The most common use of a PreCondition is to check for valid function arguments.
 */
class PreCondition: public Condition {
public:
    explicit PreCondition(const std::string& message);
    virtual ~PreCondition() override;
};

//! Check-Condition exception
/*!
 * 	A thrown CheckCondition does not have any guarantees, it is used anywhere in
 * 	a function as a runtime assertion.
 */
class CheckCondition: public Condition {
public:
    explicit CheckCondition(const std::string& message);
    virtual ~CheckCondition() override;
};

//! Post-Check-Condition exception
/*!
 * 	A thrown PostCondition is used to show that the operations within the
 * 	function were successful, but the function produced an invalid result.
 */
class PostCondition: public Condition {
public:
    explicit PostCondition(const std::string& message);
    virtual ~PostCondition() override;
};

} // namespace core::exception
