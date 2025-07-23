#pragma once
#include <random>
#include <type_traits>


void CreateActor(class Actor* _SpawnActor, ACTOR_TYPE _Type);
void ChangeLevel(LEVEL_TYPE _NextLevel);

Vec2 Rotate(Vec2 _Dir, float _Degree);

void DrawDebugRect(Vec2 _Pos, Vec2 _Scale, PEN_TYPE _Pen, float _Duration);
void DrawDebugCircle(Vec2 _Pos, float _Radius, PEN_TYPE _Pen, float _Duration);
void DrawDebugLine(Vec2 _Start, Vec2 _End, PEN_TYPE _Pen, float _Duration);

Vec2 GetRandomPos(Vec2 _center, float _radius);

void SaveWString(const wstring& _String, FILE* _File);
void LoadWString(wstring& _String, FILE* _File);

void SaveSpriteRef(class ASprite* _Sprite, FILE* _File);
ASprite* LoadSpriteRef(FILE* _File);

void SaveTextureeRef(class ASprite* _Sprite, FILE* _File);
ASprite* LoadTextureRef(FILE* _File);

void SaveFlipbookRef(class AFlipbook* _Flip, FILE* _File);
void LoadFlipbookRef(FILE* _File, AFlipbook* pFlip);

wstring GetFilenameFromPath(const wchar_t* _path);
wstring GetRelativePath(const wchar_t* _path);

float Clamp(float _val, float _min, float _max);

template <typename T>
T GetRandomNum(T _from, T _to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dis(_from, _to);
        return dis(gen);
    }
    else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dis(_from, _to);
        return dis(gen);
    }
    else {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    }
}