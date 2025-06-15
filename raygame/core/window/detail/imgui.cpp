#include "raygame/core/window/detail/imgui.h"
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/arithmetic/safe_add.h"
#include "raygame/core/math/numeric_cast.h"
#include "raygame/core/window/detail/imgui/imgui_include.h"

namespace core::window::detail {
namespace {
using core::condition::unreachable;

[[maybe_unused]]
void glfw_error_callback(int error, const char* description) {
    log::warning("GLFW Error {}: {}", error, description);
}

} // namespace

ImguiWindowImpl::ImguiWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style)
    : WindowImpl(size, std::move(title), style) {
    if constexpr (config::EnabledBackends::imgui()) {
        log::debug("constructing ImGUI window");
        glfwSetErrorCallback(glfw_error_callback);
        if (glfwInit() == 0) {
            condition::pre_condition(false, "Could not initialise GLFW");
        }
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        m_window = glfwCreateWindow(
            math::numeric_cast<int>(size.x),
            math::numeric_cast<int>(size.y),
            title.c_str(),
            nullptr,
            nullptr
        );
        condition::check_ptr(m_window, "Could not initialise window");

        glfwMakeContextCurrent(m_window);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_io = &ImGui::GetIO();

        // NOLINTBEGIN(*-signed-bitwise)
        m_io->ConfigFlags  = ImGuiConfigFlags_None;
        m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        m_window_flags |= ImGuiWindowFlags_NoDecoration;
        m_window_flags |= ImGuiWindowFlags_NoInputs;
        m_window_flags |= ImGuiWindowFlags_NoMove;
        m_window_flags |= ImGuiWindowFlags_NoNav;
        m_window_flags |= ImGuiWindowFlags_NoResize;
        m_window_flags |= ImGuiWindowFlags_NoTitleBar;

        // NOLINTEND(*-signed-bitwise)

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init();
        pre_frame();
    } else {
        unreachable();
    }
}

ImguiWindowImpl::~ImguiWindowImpl() {
    post_frame();
    ImGui::End();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    glfwTerminate();
}

void ImguiWindowImpl::draw(const drawing::ImageView& image) {
    GLuint image_texture{};
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(
        GL_TEXTURE_2D,
        0, // Level
        GL_RGBA,
        math::numeric_cast<int>(image.width()),
        math::numeric_cast<int>(image.height()),
        0, // Border
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image.data()
    );
    using math::safe_add;
    ImGui::GetWindowDrawList()->AddImage(
        image_texture,
        ImVec2(static_cast<float>(image.pos_x()), static_cast<float>(image.pos_y())),
        ImVec2(
            static_cast<float>(safe_add<size_t>(image.pos_x(), image.width())),
            static_cast<float>(safe_add<size_t>(image.pos_y(), image.height()))
        )
    );
    glBindTexture(GL_TEXTURE_2D, image_texture);
}

void ImguiWindowImpl::restyle(WindowStyle style) {
    std::ignore = style;
}

void ImguiWindowImpl::render_frame() {
    glfwPollEvents();
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
#ifdef IMGUI_HAS_VIEWPORT
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetWindowPos(viewport->WorkPos);
    ImGui::SetWindowSize(viewport->WorkSize);
    core::log::debug("Pos: ({}, {})", viewport->Pos.x, viewport->Pos.y);
    core::log::debug("Size: ({}, {})", viewport->Size.x, viewport->Size.y);
#else
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
#endif
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    const bool begin = ImGui::Begin(get_title().c_str(), nullptr, m_window_flags);
    condition::check_condition(begin, "Could not begin window");
    // FRAME HERE
    ImGui::End();
    ImGui::PopStyleVar(1);
    post_frame();
    pre_frame();
}

bool ImguiWindowImpl::next_frame() {
    if (!should_close()) {
        render_frame();
    }
    return !should_close();
}

bool ImguiWindowImpl::should_close() const {
    return (glfwWindowShouldClose(m_window) != 0);
}

void ImguiWindowImpl::post_frame() {
    int display_w = 0;
    int display_h = 0;
    ImGui::Render();

    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window);
}

void ImguiWindowImpl::pre_frame() {
    if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0) {
        constexpr auto SLEEP_AMOUNT = 10;
        ImGui_ImplGlfw_Sleep(SLEEP_AMOUNT);
        return;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

} // namespace core::window::detail
