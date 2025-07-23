#include "pch.h"


#include "RenderMgr.h"
#include "EventMgr.h"
#include "func.h"

void CreateActor(Actor* _SpawnActor, ACTOR_TYPE _Type)
{
	tEventInfo info = {};

	info.Type = EVENT::CREATE_ACTOR;
	info.Data0 = (DWORD_PTR)_SpawnActor;
	info.Data1 = (DWORD_PTR)_Type;

	EventMgr::GetInst()->AddEvent(info);
}
void ChangeLevel(LEVEL_TYPE _NextLevel)
{
	tEventInfo info = {};

	info.Type = EVENT::CHANGE_LEVEL;
	info.Data0 = (DWORD_PTR)_NextLevel;

	EventMgr::GetInst()->AddEvent(info);
}
Vec2 Rotate(Vec2 _Dir, float _Degree)
{
	float Radian = -_Degree * (PI / 180.f);

	// 삼각함수 합차공식
	// Cos(A + B) = cos(A) * cos(B) - sin(A) * sin(B)
	// Sin(A + B) = sin(A) * cos(B) + cos(A) + sin(B)

	Vec2 vRotatedDir = Vec2(cosf(Radian) * _Dir.x - sinf(Radian) * _Dir.y
		, sinf(Radian) * _Dir.x + cosf(Radian) * _Dir.y);



	return vRotatedDir;
}

void DrawDebugRect(Vec2 _Pos, Vec2 _Scale, PEN_TYPE _Pen, float _Duration)
{
	tDebugShapeInfo info = {};

	info.Center = _Pos;
	info.Scale = _Scale;
	info.Shape = DEBUG_SHAPE::RECT;
	info.PenType = _Pen;
	info.Duration = _Duration;
	info.CurTime = 0.f;

	RenderMgr::GetInst()->AddDebugShape(info);
}

void DrawDebugCircle(Vec2 _Pos, float _Radius, PEN_TYPE _Pen, float _Duration)
{
	tDebugShapeInfo info = {};

	info.Center = _Pos;
	info.Scale = Vec2(_Radius * 2.f, _Radius * 2.f);
	info.Shape = DEBUG_SHAPE::CIRCLE;
	info.PenType = _Pen;
	info.Duration = _Duration;
	info.CurTime = 0.f;

	RenderMgr::GetInst()->AddDebugShape(info);
}

void DrawDebugLine(Vec2 _Start, Vec2 _End, PEN_TYPE _Pen, float _Duration)
{
	tDebugShapeInfo info = {};

	info.Center = _Start;
	info.Scale = _End;
	info.Shape = DEBUG_SHAPE::LINE;
	info.PenType = _Pen;
	info.Duration = _Duration;
	info.CurTime = 0.f;

	RenderMgr::GetInst()->AddDebugShape(info);
}

Vec2 GetRandomPos(Vec2 _center, float _radius) {
	
	float x = GetRandomNum<float>(_center.x - _radius / 2, _center.x + _radius / 2);
	float y = GetRandomNum<float>(_center.y - _radius / 2, _center.y + _radius / 2);
	return Vec2(x, y);
}

void SaveWString(const wstring& _String, FILE* _File)
{
	UINT Len = (UINT)_String.length();
	fwrite(&Len, sizeof(UINT), 1, _File);
	fwrite(_String.c_str(), sizeof(wchar_t), Len, _File);
}

void LoadWString(wstring& _String, FILE* _File)
{
	UINT Len = 0;
	fread(&Len, sizeof(UINT), 1, _File);

	wchar_t buff[255] = {};
	fread(buff, sizeof(wchar_t), Len, _File);

	_String = buff;
}

#include "AssetMgr.h"
#include "ASprite.h"
void SaveSpriteRef(ASprite* _Sprite, FILE* _File)
{
	// 가리키고 있던 Sprite 가 있었는지 저장한다.
	bool Exist = _Sprite;
	fwrite(&Exist, sizeof(bool), 1, _File);

	if (Exist)
	{
		// 타일이 가리키고 있는 Sprite 의 Key 문자열을 파일에 저장한다.
		wstring Key = _Sprite->GetKey();
		wstring Path = _Sprite->GetRelativePath();
		SaveWString(Key, _File);
		SaveWString(Path, _File);
	}
}

ASprite* LoadSpriteRef(FILE* _File)
{
	// 가리키고 있던 Sprite 가 있었는지 불러온다.
	bool Exist = false;
	fread(&Exist, sizeof(bool), 1, _File);

	ASprite* pSprite = nullptr;

	if (Exist)
	{
		// 타일이 참조하던 Sprite 의 Key 문자열을 파일로부터 읽어온다.
		wstring Key, Path;
		LoadWString(Key, _File);
		LoadWString(Path, _File);

		// 읽어드린 Key 문자열로 AssetMgr 로부터 다시 해당 Sprite 를 찾아서 가리킨다.
		pSprite = AssetMgr::GetInst()->LoadSprite(Key, Path);
	}

	return pSprite;
}

#include "AFlipbook.h"

void SaveFlipbookRef(AFlipbook* _Flip, FILE* _File)
{
	// 가리키고 있던 Sprite 가 있었는지 저장한다.
	bool Exist = _Flip;
	fwrite(&Exist, sizeof(bool), 1, _File);

	if (Exist)
	{
		// 타일이 가리키고 있는 Sprite 의 Key 문자열을 파일에 저장한다.
		wstring Key = _Flip->GetKey();
		wstring Path = _Flip->GetRelativePath();
		SaveWString(Key, _File);
		SaveWString(Path, _File);
	}
}

void LoadFlipbookRef(FILE* _File, AFlipbook* pFlip)
{
	// 가리키고 있던 Sprite 가 있었는지 불러온다.
	bool Exist = false;
	fread(&Exist, sizeof(bool), 1, _File);

	if (Exist)
	{
		// 타일이 참조하던 Sprite 의 Key 문자열을 파일로부터 읽어온다.
		wstring Key, Path;
		LoadWString(Key, _File);
		LoadWString(Path, _File);

		pFlip->SetKey(Key);
		pFlip->SetRelativePath(Path);
	}
}

wstring GetFilenameFromPath(const wchar_t* _path)
{
	std::wstring full(_path);
	size_t lastSlash = full.find_last_of(L"\\/");

	std::wstring filename = (lastSlash != std::wstring::npos)
		? full.substr(lastSlash + 1)
		: full;

	return filename;
}

wstring GetRelativePath(const wchar_t* _path)
{
	std::wstring full(_path);
	size_t Content = full.find(L"Content");

	std::wstring filename = (Content != std::wstring::npos)
		? full.substr(Content + 8)
		: full;

	return filename;
}

float Clamp(float _val, float _min, float _max) {
	return max(_min, min(_val, _max));
}


