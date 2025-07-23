#pragma once
#include <functional>

struct Vec2
{
	float x;
	float y;

public:
	// 내적
	float Dot(Vec2 _Other)
	{
		// this Length * _Other Length * Cos(theta)
		return x * _Other.x + y * _Other.y;
	}

	float Cross(Vec2 _Other)
	{
		return x * _Other.y - y * _Other.x;
	}


	// 피타고라스 정리로, 벡터성분의 길이를 구한다.
	float Length() { return sqrt(x * x + y * y); }

	float Distance(Vec2 _Other) { return sqrt((x - _Other.x) * (x - _Other.x) + (y - _Other.y) * (y - _Other.y)); }

	// 방향은 유지한채로, 길이를 1로 만든다.
	void Normalize() { float Len = Length(); x /= Len; y /= Len; }


public:
	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}

	void operator += (Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	Vec2 operator+ (Vec2 _Other)
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}
	
	Vec2 operator - (Vec2 _Other)
	{
		return Vec2(x - _Other.x, y - _Other.y);
	}

	Vec2 operator * (float _Data)
	{
		return Vec2(x * _Data, y * _Data);		
	}

	void operator *=(float _Data)
	{
		x *= _Data;
		y *= _Data;
	}
	Vec2 operator / (float _Data)
	{
		assert(_Data);
		return Vec2(x / _Data, y / _Data);
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	~Vec2(){}
};


// 디버그용 그림 정보
struct tDebugShapeInfo
{
	Vec2		Center;
	Vec2		Scale;
	PEN_TYPE	PenType;	
	DEBUG_SHAPE Shape;
	float		Duration;
	float		CurTime;
};

struct tImGUIDebugInfo
{
	const char* Text;
	string Value;
};


struct tEventInfo
{
	EVENT		Type;
	DWORD_PTR	Data0;
	DWORD_PTR	Data1;
};

struct DelayedTask
{
	float Delay;
	float Elapsed;
	std::function<void()> Callback;
};

struct AnimationStruct
{
	Animationtype Animationtype;
	float Speed;
	bool Repeated;
	float Duration = 1;
	float Curtime = 0;
};
