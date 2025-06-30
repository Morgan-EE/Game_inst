#pragma once
#include "Button.h"
class TestButton : public Button
{
	using Super = Button;
public:
	TestButton();
	virtual ~TestButton() override;
private:

};

