#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <commdlg.h>//파일 열기 상자

#include <crtdbg.h>

#include <assert.h>

#include <vector>
#include <list>
#include <map>
#include <string>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;


#include "def.h"
#include "struct.h"
#include "func.h"

////gdiplus
//#include <gdiplus.h>
//#pragma	comment(lib, "Gdiplus.lib")
//using namespace Gdiplus;

#pragma comment (lib, "Msimg32.lib")//TransparentBlt을 사용하기 위해 필요한 라이브러리 msdn에서 requirement라고 표시됨