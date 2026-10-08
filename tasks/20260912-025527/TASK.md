# Make RayGame build for Mac and Windows

- STATUS: OPEN
- PRIORITY: 50
- TAGS: platform

Make RayGame build for Mac and Windows.
Doesn't have to run, just build.

Bazel rules and stuff work for MacOS, but there's no appropriate toolchain
(since libc++ is no longer supported), and the `static_assert`s still fail in
`raygame/core/config.hpp`
