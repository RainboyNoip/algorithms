//一些常用的宏定义
#pragma once

#include <cstddef> // for std::size_t
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <string_view>
#include <functional>
#include <memory_resource>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

#ifdef __cpp_concepts
#include <concepts>
#endif

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

