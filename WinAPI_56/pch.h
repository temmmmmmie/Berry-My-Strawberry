#pragma once


// �̸� �����ϵ� ���
// ������Ʈ ���� �����ϴ� ��� .cpp ������ �ݵ�� #include "pch.h" �� ��ܿ� �ۼ��ؾ��Ѵ�.
// pch.h �� �ۼ��� ������ ������Ʈ ��� ���Ͽ� ����ȴ�.
// pch.h �� �ۼ��� ����� �����ϴ� cpp ������ �̸� ������ �صд�.
// Ư���� ��������� ���ٸ� ������Ʈ�� �������ϴ� �������� �ߺ� �������̵Ǵ� ������ �����Ѵ�.
// ������ �ӵ� ���

// UnityBuild �� �� ȿ���� ����

#include <Windows.h>
#pragma comment(lib, "Msimg32.lib")


// �ڷᱸ��
#include <vector>
#include <list>
#include <map>

// ���ڿ�
#include <string>
using namespace std;

// assert
#include <assert.h>

// PNG �ε�
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

// ����
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// ��ü���� ���
#include "define.h"
#include "enum.h"
#include "struct.h"
#include "func.h"