#include <string>

namespace raylib {

class Window {
    public:
        Window(int width, int height, const std::string title);
        ~Window();
        Window(const Window &)            = delete;
        Window &operator=(const Window &) = delete;
        Window(Window &&)                 = delete;
        Window &operator=(Window &&)      = delete;
        bool    should_close();

    private:
};

} // namespace raylib
