#pragma once
#include "Input.h"
 
using namespace Input::VirtualInput; 



namespace Input
{
	namespace Joystick
	{ 

		typedef unsigned char JoystickButton;
		const unsigned char JOYSTICK_BUTTON_UNINITIALIZED = 100;

		class JoystickController : public IController
		{ 
		private: //nested private data definitions 
			enum JoystickButtonState //possible joystick button states
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
		public:
			virtual InputInfo Poll();
			virtual void DebugDraw();
			int HardwareID();
			void HardwareID(int val);
		private:
			int hardwareID;
			bool ButtonDown(JoystickButton button);
			bool ButtonPressed(JoystickButton button);
			bool ButtonReleased(JoystickButton button);
			JoystickButtonInfo mappingInfo[FINAL_VIRTUAL_KEY_ENUM_VALUE]; 

			
		};  

		//Todo add a joystick mapping system so people can write joystick data files to make custom JoystickButtonInfos
	} 
}
