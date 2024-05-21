#include <stdexcept>

namespace core::exception {
class PreCondition: public std::logic_error {
public:
    explicit PreCondition(const std::string& message)
        : ::std::logic_error(message){};
};

class CheckCondition: public std::logic_error {
public:
    explicit CheckCondition(const std::string& message)
        : ::std::logic_error(message){};
};

class PostCondition: public std::logic_error {
public:
    explicit PostCondition(const std::string& message)
        : ::std::logic_error(message){};
};
} // namespace core::exception

namespace core::conditions {

void pre_condition(bool check, const std::string& message);
void check_condition(bool check, const std::string& message);
void post_condition(bool check, const std::string& message);

} // namespace core::conditions
