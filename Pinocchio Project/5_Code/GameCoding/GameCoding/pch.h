#pragma once

#define _HAS_STD_BYTE 0

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Values.h"

#include <windows.h>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <functional>
//#include <memory>

using namespace std;

// C++20
#include <format>
#include <filesystem>
namespace fs = std::filesystem;


#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


#ifdef _DEBUG
#define new1 new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma comment(lib, "msimg32.lib")

// »ç¿îµå
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


//https://luckygg.tistory.com/226