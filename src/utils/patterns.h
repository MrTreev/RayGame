#pragma once

namespace utils::patterns {

class Singleton {
    public:
        static Singleton &getInstance() {
            static Singleton instance;
            return instance;
        }

    private:
        Singleton() {}

    public:
        Singleton(const Singleton &)      = delete;
        void operator=(const Singleton &) = delete;
};
} // namespace utils::patterns
