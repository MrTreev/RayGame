#!/bin/sh

while
    inotifywait \
        --recursive \
        --event modify,move,create,delete \
        raygame rules third_party games "${0}"
do
    clear
    bazel build //...
    bazel test //...
done
