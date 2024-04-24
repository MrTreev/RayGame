#include "raylib/types.h"
#include <string>

namespace raylib {
using flag_t = unsigned int;

class Window {
    public:
        Window(int width, int height, const std::string title);
        ~Window();
        Window(const Window &)            = delete;
        Window &operator=(const Window &) = delete;
        Window(Window &&)                 = delete;
        Window &operator=(Window &&)      = delete;

        bool should_close();
        bool is_ready();
        bool is_fullscreen();
        bool is_hidden();
        bool is_maximised();
        bool is_minimised();
        bool is_focused();
        bool is_resized();

        void set_state(flag_t flags);
        void check_state(flag_t flag);
        void clear_state(flag_t flags);

        void toggle_fullscreen();
        void toggle_borderless();

        void maximise();
        void minimise();
        void restore();

        void set_icon(raylib::Image image);

    private:
};

} // namespace raylib
