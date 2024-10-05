#include "core/types.h" // IWYU pragma: keep

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Vec2<T> c) {
    os << "Vec2(x: " << c.x << ", y: " << c.y << ")";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Vec3<T> c) {
    os << "Vec3(x: " << c.x << ", y: " << c.y << ", z: " << c.z << ")";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Vec4<T> c) {
    os << "Vec4(x: " << c.x << ", y: " << c.y << ", z: " << c.z
       << ", w: " << c.w << ")";
}

template<typename Pos_t, typename Dis_t>
std::ostream& operator<<(std::ostream& os, core::Rect<Pos_t, Dis_t> c) {
    os << "Rect(x: " << c.x << ", y: " << c.y << ", width: " << c.width
       << ", height: " << c.height << ")";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Quad<T> c) {
    os << "Quad(tl: " << c.tl << ", bl: " << c.bl << ", br: " << c.br
       << ", tr: " << c.tr << ")";
}
