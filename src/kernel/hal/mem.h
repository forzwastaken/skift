#pragma once

#include <karm-base/align.h>
#include <karm-base/std.h>

namespace Hal {

inline constexpr size_t PAGE_SIZE = 0x1000;
inline constexpr size_t UPPER_HALF = 0xffff800000000000;

static inline size_t pageAlignDown(size_t addr) {
    return alignDown(addr, PAGE_SIZE);
}

static inline size_t pageAlignUp(size_t addr) {
    return alignUp(addr, PAGE_SIZE);
}

static inline bool isPageAlign(size_t addr) {
    return isAlign(addr, PAGE_SIZE);
}

struct IdentityMapper {
    size_t map(size_t addr) { return addr; }
};

struct UpperHalfMapper {
    size_t map(size_t addr) { return addr + UPPER_HALF; }
};

} // namespace Hal
