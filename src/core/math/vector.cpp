#include "core/math/vector.h" // IWYU pragma: keep

template<typename T>
core::Vec2<T>::operator std::string() {
    return "Vec2(x: " + std::to_string(x) + ", y: " + std::to_string(y) + ")";
}

template<typename T>
core::Vec3<T>::operator std::string() {
    return "Vec3(x: " + std::to_string(x) + ", y: " + std::to_string(y)
           + ", z: " + std::to_string(z) + ")";
}

template<typename T>
core::Vec4<T>::operator std::string() {
    return "Vec4(x: " + std::to_string(x) + ", y: " + std::to_string(y)
           + ", z: " + std::to_string(z) + ", w: " + std::to_string(w) + ")";
}

// Vec2 Specialisations
template struct core::Vec2<uint8_t>;
template struct core::Vec2<uint16_t>;
template struct core::Vec2<uint32_t>;
template struct core::Vec2<uint64_t>;
template struct core::Vec2<int8_t>;
template struct core::Vec2<int16_t>;
template struct core::Vec2<int32_t>;
template struct core::Vec2<int64_t>;

// Vec3 Specialisations
template struct core::Vec3<uint8_t>;
template struct core::Vec3<uint16_t>;
template struct core::Vec3<uint32_t>;
template struct core::Vec3<uint64_t>;
template struct core::Vec3<int8_t>;
template struct core::Vec3<int16_t>;
template struct core::Vec3<int32_t>;
template struct core::Vec3<int64_t>;

// Vec4 Specialisations
template struct core::Vec4<uint8_t>;
template struct core::Vec4<uint16_t>;
template struct core::Vec4<uint32_t>;
template struct core::Vec4<uint64_t>;
template struct core::Vec4<int8_t>;
template struct core::Vec4<int16_t>;
template struct core::Vec4<int32_t>;
template struct core::Vec4<int64_t>;
