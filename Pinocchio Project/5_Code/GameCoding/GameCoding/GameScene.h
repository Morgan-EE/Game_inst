#pragma once
#include "Scene.h"

class Player;
class Actor;
class UI;
class Room;
class Hall;
class Stage;
class Light;
class Collider;
class Key;
class Item;
class DollCheck;
class Cheese;

class GameScene : public Scene
{
	using Super = Scene;
public:
	GameScene();
	virtual ~GameScene() override;

	virtual void Init() override;
	virtual void Update() override;
	void EnterRoom(RoomNum roomNum);
	void EnterHall(RoomNum roomNum);
	virtual void Render(HDC hdc) override;

	void SetText(string key);

	Hall* _currentHall;
	Room* _currentRoom;
	Player* _player;
	// Test

public:
	vector<Hall*> _hallVector;
	vector<Room*> _roomVector;

	Hall* _hall;
	Light* _light;
	Actor* ground;

public:
	vector<Collider*> _hallColliders;
	vector<Collider*> _hall2Colliders;
	vector<Collider*> _restRoomColliders;
	vector<Collider*> _wareHouseColliders;
	vector<Collider*> _kitchenColliders;

	vector<Collider*> _workRoomColliders;

	vector<Collider*> _bedRoomColliders;
	
	// RestRoom
public:
	//vector<Actor*> _
	bool isUseSwitch = false;
	bool _isRestRoomClear = false;

	Key* _restRoomKey;
	Key* _wareHouseKey;
	Key* _kitchenKey;
	Key* _workRoomKey;

	bool _isGetRestRoomKey = false;
	bool _isGetPiece1 = false;
	bool _isGetWareHouseKey = false;
	bool _isLittleTakingEnd = false;

	Item* _piece1;
	Item* _piece2;
	Item* _piece3;
	Item* _piece4;
	Item* _piece5;

	Cheese* _cheese;

	// workRoom
public:

private:
	std::unordered_map<string, wstring> _playerText;
	bool isOnTextThisFrame = false;
	DollCheck* dollcheck = nullptr;
};
