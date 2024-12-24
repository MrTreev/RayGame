#include <string>

namespace raygame::systems {
class Name {
    std::string      m_name;
    std::string_view m_first;
    std::string_view m_last;

public:
    Name(std::string name)
        : m_name(name) {
        if (m_name.contains(' ')) {
            const auto space = m_name.find(' ');

            m_first = std::string_view(m_name.data(), space);
            m_last  = std::string_view(
                m_name.cbegin()
                    + static_cast<std::string::difference_type>(space + 1),
                m_name.cend()
            );
        }
    }

    Name(std::string first, std::string last)
        : m_name(first + " " + last)
        , m_first(m_name.data(), first.size())
        , m_last(
              m_name.cbegin()
                  + static_cast<std::string::difference_type>(first.size() + 1),
              m_name.cend()
          ) {}

    operator std::string() {
        return m_name;
    }
};
} // namespace raygame::systems
