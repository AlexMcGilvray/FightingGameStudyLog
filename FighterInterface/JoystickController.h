#pragma once
#include "Input.h"

using namespace Input;
using namespace Input::VirtualInput; 


class JoystickController : public IController
{
public:
	virtual InputInfo Poll(); 
	virtual void DebugDraw();
private:

};  