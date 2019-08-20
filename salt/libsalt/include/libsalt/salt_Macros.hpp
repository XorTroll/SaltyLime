
#pragma once
#include <utility>
#include <vector>

#define SALT_LINKNN(...) \
extern "C" \
{ \
    extern __VA_ARGS__ __attribute__((weak)); \
}

#define SALT_DEFINE(name, externc) const auto &name = externc;