//=============================================================================
// Development Utility Macros
//=============================================================================

// ColumnLimit for this file is longer (140 currently) for readability
// clang-format off
// NOLINTBEGIN(*-macro-usage)
#define RAYGAME_PP_MACRO_STRINGIFY(x) RAYGAME_PP_STRINGIFY(x)
#define RAYGAME_PP_STRINGIFY(x) #x

#define RAYGAME_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define RAYGAME_VA_NUM_ARGS(...) RAYGAME_VA_NUM_ARGS_HELPER(__VA_ARGS__ __VA_OPT_(, ) 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define RAYGAME_XPASTE(a, b)     a##b
#define RAYGAME_PASTE(a, b)      RAYGAME_XPASTE(a, b)
#define RAYGAME_XCALL(FUNC, ...) FUNC(__VA_ARGS__)
#define RAYGAME_CALL(func, ...)  RAYGAME_XCALL(func, __VA_ARGS__)
#define RAYGAME_PROC(X)          X

#define RAYGAME_TEMPLATE_INTS(name)                                                                                                        \
    template class name<uint8_t>;                                                                                                          \
    template class name<uint16_t>;                                                                                                         \
    template class name<uint32_t>;                                                                                                         \
    template class name<uint64_t>;                                                                                                         \
    template class name<int8_t>;                                                                                                           \
    template class name<int16_t>;                                                                                                          \
    template class name<int32_t>;                                                                                                          \
    template class name<int64_t>

#define RAYGAME_EXTERN_TEMPLATE_INTS(name)                                                                                                 \
    extern template class name<uint8_t>;                                                                                                   \
    extern template class name<uint16_t>;                                                                                                  \
    extern template class name<uint32_t>;                                                                                                  \
    extern template class name<uint64_t>;                                                                                                  \
    extern template class name<int8_t>;                                                                                                    \
    extern template class name<int16_t>;                                                                                                   \
    extern template class name<int32_t>;                                                                                                   \
    extern template class name<int64_t>

#define RAYGAME_ADD_STRUCTURED_BINDINGS_2(A, B)                                                                                            \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_3(A, B, C)                                                                                         \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_4(A, B, C, D)                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
        if constexpr (Size == 3) return std::move(D);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_5(A, B, C, D, E)                                                                                   \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
        if constexpr (Size == 3) return std::move(D);                                                                                      \
        if constexpr (Size == 4) return std::move(E);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_6(A, B, C, D, E, F)                                                                                \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
        if constexpr (Size == 3) return std::move(D);                                                                                      \
        if constexpr (Size == 4) return std::move(E);                                                                                      \
        if constexpr (Size == 5) return std::move(F);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_7(A, B, C, D, E, F, G)                                                                             \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
        if constexpr (Size == 6) return G;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
        if constexpr (Size == 6) return G;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
        if constexpr (Size == 3) return std::move(D);                                                                                      \
        if constexpr (Size == 4) return std::move(E);                                                                                      \
        if constexpr (Size == 5) return std::move(F);                                                                                      \
        if constexpr (Size == 6) return std::move(G);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_8(A, B, C, D, E, F, G, H)                                                                          \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
        if constexpr (Size == 6) return G;                                                                                                 \
        if constexpr (Size == 7) return H;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
        if constexpr (Size == 6) return G;                                                                                                 \
        if constexpr (Size == 7) return H;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
        if constexpr (Size == 3) return std::move(D);                                                                                      \
        if constexpr (Size == 4) return std::move(E);                                                                                      \
        if constexpr (Size == 5) return std::move(F);                                                                                      \
        if constexpr (Size == 6) return std::move(G);                                                                                      \
        if constexpr (Size == 7) return std::move(H);                                                                                      \
    }

#define RAYGAME_ADD_STRUCTURED_BINDINGS_9(A, B, C, D, E, F, G, H, I)                                                                       \
    template<size_t Size>                                                                                                                  \
    auto& get() & {                                                                                                                        \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
        if constexpr (Size == 6) return G;                                                                                                 \
        if constexpr (Size == 7) return H;                                                                                                 \
        if constexpr (Size == 8) return I;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    const auto& get() const& {                                                                                                             \
        if constexpr (Size == 0) return A;                                                                                                 \
        if constexpr (Size == 1) return B;                                                                                                 \
        if constexpr (Size == 2) return C;                                                                                                 \
        if constexpr (Size == 3) return D;                                                                                                 \
        if constexpr (Size == 4) return E;                                                                                                 \
        if constexpr (Size == 5) return F;                                                                                                 \
        if constexpr (Size == 6) return G;                                                                                                 \
        if constexpr (Size == 7) return H;                                                                                                 \
        if constexpr (Size == 8) return I;                                                                                                 \
    }                                                                                                                                      \
    template<size_t Size>                                                                                                                  \
    auto&& get() && {                                                                                                                      \
        if constexpr (Size == 0) return std::move(A);                                                                                      \
        if constexpr (Size == 1) return std::move(B);                                                                                      \
        if constexpr (Size == 2) return std::move(C);                                                                                      \
        if constexpr (Size == 3) return std::move(D);                                                                                      \
        if constexpr (Size == 4) return std::move(E);                                                                                      \
        if constexpr (Size == 5) return std::move(F);                                                                                      \
        if constexpr (Size == 6) return std::move(G);                                                                                      \
        if constexpr (Size == 7) return std::move(H);                                                                                      \
        if constexpr (Size == 8) return std::move(I);                                                                                      \
    }

#define RAYGAME_ADD_TUPLE_SIZE(TemplatedClass, Size)                                                                                       \
    template<typename... T>                                                                                                                \
    struct ::std::tuple_size<TemplatedClass<T...>>: ::std::integral_constant<size_t, Size> {}

#define RAYGAME_ADD_TUPLE_ELEMENT_2(TemplatedClass)                                                                                        \
    template<typename A, typename B>                                                                                                       \
    struct ::std::tuple_element<0, TemplatedClass<A, B>> {                                                                                 \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B>                                                                                                       \
    struct ::std::tuple_element<1, TemplatedClass<A, B>> {                                                                                 \
        using type = B;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_3(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C>                                                                                           \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C>> {                                                                              \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C>                                                                                           \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C>> {                                                                              \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C>                                                                                           \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C>> {                                                                              \
        using type = C;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_4(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C, typename D>                                                                               \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C, D>> {                                                                           \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D>                                                                               \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C, D>> {                                                                           \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D>                                                                               \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C, D>> {                                                                           \
        using type = C;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D>                                                                               \
    struct ::std::tuple_element<3, TemplatedClass<A, B, C, D>> {                                                                           \
        using type = D;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_5(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C, typename D, typename E>                                                                   \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C, D, E>> {                                                                        \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E>                                                                   \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C, D, E>> {                                                                        \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E>                                                                   \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C, D, E>> {                                                                        \
        using type = C;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E>                                                                   \
    struct ::std::tuple_element<3, TemplatedClass<A, B, C, D, E>> {                                                                        \
        using type = D;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E>                                                                   \
    struct ::std::tuple_element<4, TemplatedClass<A, B, C, D, E>> {                                                                        \
        using type = E;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_6(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C, typename D, typename E, typename F>                                                       \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C, D, E, F>> {                                                                     \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F>                                                       \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C, D, E, F>> {                                                                     \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F>                                                       \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C, D, E, F>> {                                                                     \
        using type = C;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F>                                                       \
    struct ::std::tuple_element<3, TemplatedClass<A, B, C, D, E, F>> {                                                                     \
        using type = D;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F>                                                       \
    struct ::std::tuple_element<4, TemplatedClass<A, B, C, D, E, F>> {                                                                     \
        using type = E;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F>                                                       \
    struct ::std::tuple_element<5, TemplatedClass<A, B, C, D, E, F>> {                                                                     \
        using type = F;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_7(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = C;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<3, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = D;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<4, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = E;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<5, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = F;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>                                           \
    struct ::std::tuple_element<6, TemplatedClass<A, B, C, D, E, F, G>> {                                                                  \
        using type = G;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_8(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = C;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<3, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = D;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<4, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = E;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<5, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = F;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<6, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = G;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>                               \
    struct ::std::tuple_element<7, TemplatedClass<A, B, C, D, E, F, G, H>> {                                                               \
        using type = H;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_ELEMENT_9(TemplatedClass)                                                                                        \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<0, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = A;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<1, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = B;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<2, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = C;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<3, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = D;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<4, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = E;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<5, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = F;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<6, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = G;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<7, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = H;                                                                                                                    \
    };                                                                                                                                     \
    template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>                   \
    struct ::std::tuple_element<8, TemplatedClass<A, B, C, D, E, F, G, H, I>> {                                                            \
        using type = I;                                                                                                                    \
    }

#define RAYGAME_ADD_TUPLE_INTERFACE(TemplatedClass, N)                         \
    RAYGAME_ADD_TUPLE_SIZE(TemplatedClass, N);                                 \
    RAYGAME_CALL(                                                              \
        RAYGAME_PROC(RAYGAME_XPASTE(RAYGAME_ADD_TUPLE_ELEMENT_, N)),           \
        TemplatedClass                                                         \
    )

// NOLINTEND(*-macro-usage)
// clang-format on
