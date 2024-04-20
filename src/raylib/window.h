#include <raylib.h>
#include <string>

namespace raylib {

class Window {
    public:
        Window(int width, int height, const std::string title);
        ~Window();
        // Moving is allowed
        Window(const Window &)            = default;
        Window &operator=(const Window &) = default;
        // No copying
        Window(Window &&)                 = delete;
        Window &operator=(Window &&)      = delete;

    private:
};

} // namespace raylib
