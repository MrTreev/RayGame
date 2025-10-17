# Coding Standard

The final decisions of whether code is good enough is up to [MrTreev](https://github.com/MrTreev).

## Never use `using namespace`

## Limit the use of `using` directives to minimal scopes

Using directives should be kept only in the smallest scope required.
Using directives should not be used in header files unless it is specifically to export a symbol in a new namespace.

## Use modern C++ library includes

Use `#include <cstdio>` in place of `<stdio.h>` for example.

## No nested ternaries

Nested ternaries make code more difficult to read and lead to more bugs.

## Use ISO standard C++ extensions only used when absolutely required

Prefer ISO standard methods over extensions where possible.

## Failures

Use exceptions to signal a failure to perform a required task
Use std::optional to signal a failure to perform an optional task
