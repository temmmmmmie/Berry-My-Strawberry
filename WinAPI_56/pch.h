#pragma once


// 미리 컴파일된 헤더
// 프로젝트 내에 존재하는 모든 .cpp 파일은 반드시 #include "pch.h" 를 상단에 작성해야한다.
// pch.h 에 작성한 내용은 프로젝트 모든 파일에 적용된다.
// pch.h 에 작성된 헤더에 대응하는 cpp 파일을 미리 컴파일 해둔다.
// 특별한 변경사항이 없다면 프로젝트를 컴파일하는 과정에서 중복 컴파일이되는 현상을 방지한다.
// 컴파일 속도 향상

// UnityBuild 가 더 효과가 좋다

#include <Windows.h>
#pragma comment(lib, "Msimg32.lib")


// 자료구조
#include <vector>
#include <list>
#include <map>

// 문자열
#include <string>
using namespace std;

// assert
#include <assert.h>

// PNG 로딩
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

// 사운드
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// 자체구현 헤더
#include "define.h"
#include "enum.h"
#include "struct.h"
#include "func.h"