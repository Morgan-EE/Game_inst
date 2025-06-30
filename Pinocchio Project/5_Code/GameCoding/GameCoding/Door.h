#pragma once
#include "Actor.h"
class Door : public Actor
{
	using Super = Actor;
public:
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;


	void SetRoomId(RoomNum roomId) { _roomId = roomId; }
	RoomNum GetRoomId() { return _roomId; }


	void OpenRoom() { _isOpen = true; }
	bool IsRoomOpen() { return _isOpen; }
private:
	RoomNum _roomId;
	bool _isOpen = false;
};

