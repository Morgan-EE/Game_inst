#pragma once

enum class KeyType
{
	LeftMouse	= VK_LBUTTON,
	RightMouse	= VK_RBUTTON,

	Up			= VK_UP,
	Down		= VK_DOWN,
	Left		= VK_LEFT,
	Right		= VK_RIGHT,
	SpaceBar	= VK_SPACE,
	Tab			= VK_TAB,
	ESC			= VK_ESCAPE,

	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E',
	F = 'F',
	G = 'G',
	H = 'H',
	I = 'I',
	J = 'J',
	K = 'K',
	L = 'L',
	N = 'N',
	M = 'M',
	O = 'O',
	P = 'P',
	Q = 'Q',
	R = 'R',
	S = 'S',
	T = 'T',
	U = 'U',
	V = 'V',
	W = 'W',
	X = 'X',
	Y = 'Y',
	Z = 'Z',
};

enum class KeyState
{
	None,
	Press,
	Down,
	Up,

	End
};

enum
{
	KEY_TYPE_COUNT	= static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End),
};

class InputManager
{
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }
private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint64>(key)]; }
private:
	HWND				_hwnd = {};
	vector<KeyState>	_states;
	POINT				_mousePos = {};
};

