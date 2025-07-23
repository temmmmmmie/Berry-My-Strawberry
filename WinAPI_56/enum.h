#pragma once

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	WHITE,
	MAGENTA,
	END,
};


enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	MAGENTA,
	HOLLOW,
	END,
};

enum class Fonttype
{
	HeirofLightBold,
	HeirofLightRegular,

	END,
};
extern wstring CustomFontName[];

enum COMPONENT_TYPE
{
	COLLIDER,
	RIGIDBODY,
	FLIPBOOKPLAYER,
	STATEMACHINE,
	TILERENDER,
	SPRITERENDER,
	ANIMATOR
};


enum class DIR
{
	DOWN,
	LEFT,
	UP,
	RIGHT,

	DIR_END,
};

enum class LEVEL_TYPE
{
	EDITOR,
	FLIPBOOKEDIT,
	TUTORIAL,
	START,
	STAGE_01,
	ENDING,

	END,
};

enum ACTOR_TYPE
{
	DEFAULT,
	BACKGROUND,
	TILE,
	FLIPBOOK,
	PLATFORM,
	STRAWBERRY,
	ENERMY,
	PLAYER,
	PLAYER_PROJECTILE,
	ENERMY_PROJECTILE,
	FONT,
	OBJECT,
	INTERACTABLE,



	UI = 31,
	ACTOR_END = 32,
};




enum class DEBUG_SHAPE
{
	RECT, 
	CIRCLE,
	LINE,
};


enum class EVENT
{
	CREATE_ACTOR,
	DESTROY_ACTOR,
	CHANGE_LEVEL,

};

enum class Animationtype
{
	MOVE_LEFT,
	MOVE_RIGHT
};

enum class ITEMS
{
	NONE,
	SWORD,
	WATER,
	POTION,
	SEED,
	STRAWBERRY,
};

enum class tooltype
{
	SWORD,
	WATER,
	POTION,
	SEED
};

