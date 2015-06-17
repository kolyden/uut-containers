#pragma once
#include <memory>
#include <array>
#include <vector>
#include <map>
#include <list>
#include <windows.h>
#include <windowsx.h>
#include <stdint.h>

namespace uut
{
	template<class T, size_t N> using Array = std::array<T, N>;
	template<class T> using List = std::vector<T>;
	template<class Key, class Val> using Dictionary = std::map<Key, Val>;
}

#define UUT_API