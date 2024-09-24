#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("order-by", "file");
    context.applyCommandLine(argc, argv);
    int res = context.run();
    return res;
}
