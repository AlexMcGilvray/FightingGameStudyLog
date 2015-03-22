#pragma once
#include "Input.h"
 
using namespace Input::VirtualInput; 

namespace Input
{
	namespace Joystick
	{ 
		typedef unsigned char JoystickButton;

		class JoystickController : public IController
		{
		public:
			virtual InputInfo Poll();
			virtual void DebugDraw();
			int HardwareID();
			void HardwareID(int val);
		private:
			int hardwareID;

			enum JoystickButtonState
			{
				BUTTON_NOT_FOUND = -2,
				BUTTON_NOT_MAPPED = -1, 
				BUTTON_DOWN = 1, //same as what glfw returns
				BUTTON_UP = 0 //same as what glfw returns
			};

			struct JoystickButtonInfo
			{
				JoystickButtonInfo(){}
				JoystickButtonInfo(JoystickButtonState state, JoystickButton button):
					state(state),
					button(button)
				{ } 
				JoystickButton button; //physical button
				JoystickButtonState state; //state of the button
			}; 
		};  

		
	} 
}
