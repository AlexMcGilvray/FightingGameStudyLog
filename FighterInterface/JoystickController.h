#pragma once
#include "Input.h"
 
using namespace Input::VirtualInput; 

namespace Input
{
	namespace  Joystick
	{
		class JoystickController : public IController
		{
		public:
			virtual InputInfo Poll();
			virtual void DebugDraw();
			int HardwareID();
			void HardwareID(int val);
		private:
			int hardwareID;
		};  
	} 
}
