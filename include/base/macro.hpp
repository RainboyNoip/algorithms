//一些常用的宏定义
#pragma once

#include <cstddef> // for std::size_t

#ifndef maxn
#define maxn 1000007
#endif

#ifndef maxe
#define maxe 2000007
#endif

#ifndef FOR
#define FOR(i, range) \
    for (auto i : range)
#else
    static_assert(0,"Macro FOR already defined!");
#endif

