#pragma once

enum class SceneType
{
	None,
	DevScene,
	GameScene,
	TitleScene,
	CutScene,
	DeadScene,
	EndingScene,
};

enum class SoundType
{
	BGM,
	SFX
};

enum class RoomNum
{
	restRoom,
	wareHouse,
	kitchen,
	bedRoom,
	workRoom,


	hall1,
	hall2,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND = 0,
	LAYER_OBJECT,
	LAYER_UI,

	LAYER_MAXCOUNT,
};

enum class ColliderType
{
	Box,
	Sphere,
};

enum COLLISION_LAYER_TYPE
{
	CLT_OBJECT,
	CLT_GROUND,
	CLT_WALL,

	CLT_TRIGGER, // 범위 체크 용. 
	CLT_TRIGGER2,
	CLT_TRIGGER3,
	CLT_TRIGGER4,

	CLT_PLAYER,
	CLT_OBSTACLES,	// 
	CLT_ITEM,
	CLT_DOOR,
	CLT_CLOSET,
	CLT_TRAP,
	CLT_INTERACTIONABLE,


	CLT_PINO,	// 피노키오
	CLT_MANNEQUIN, // 마네킹
};

enum class RegionType
{
	Sphere,
};

enum class ItemType
{
	None,
	Key_red,
	Key_brown,
	Key_yellow,
	Key_green,
	Key_blue,
	Key_purple,
	Key_white,
	Usable,
	Cheese,
	Piece,
};

enum class KeyID
{
	Room1,
	Room2,
	Room3,
	Room4,

	count,
};

enum class InteractionType
{
	None,
	LittlePino,
	Deadbody,
	Pino_interaction,
	Doll,
	Switch,
	Safe,
	Zepeto,

	Ending,
};

enum class StageID
{
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
};

enum UISpriteState
{
	US_None,
	US_Item,
	US_Key,
	US_Cheese,
	US_PIECE1,
	US_PIECE2,
	US_PIECE3,
	US_PIECE4,
	US_PIECE5,
	US_Panel,
	US_Key_red,
	US_Key_brown,
	US_Key_yellow,
	US_Key_green,
	US_Key_blue,
	US_Key_purple,
	US_Key_white,

	US_MaxCount,
};