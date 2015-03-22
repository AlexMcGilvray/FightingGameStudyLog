#pragma once 
#include "Input.h"

using namespace Input;
using namespace Input::VirtualInput; 
namespace Input
{
	namespace Keyboard
	{
		class KeyboardController : public IController
		{
		private: //local data definitions 
			//return values for various keyboard functions
			enum KeyState
			{
				KEY_NOT_FOUND = -2,
				KEY_NOT_MAPPED = -1, 
				KEY_DOWN = 1, //same as what glfw returns
				KEY_UP = 0 //same as what glfw returns
			};

			struct KeyboardInfo
			{
				KeyboardInfo(){}
				KeyboardInfo(KeyState state, Key key):
					state(state),
					key(key)
				{ } 
				Key key; //physical key
				KeyState state; //state of the physical key
			}; 

		public:
			virtual InputInfo Poll();
			void MapKeyToVirtualKey(Key key, InputValue vaule);
			KeyboardController();
			virtual	void DebugDraw();

		private:
			bool KeyDown(Key key);
			bool KeyPressed(Key key);
			bool KeyReleased(Key key);
			int GetVirtualKeyMappingToKey(Key key,bool previousInfo = true);
			std::string DrawInputStateField(KeyboardController::KeyState state);

			KeyboardInfo mappingInfo[FINAL_VIRTUAL_KEY_ENUM_VALUE];  
		}; 
	}
	
}
