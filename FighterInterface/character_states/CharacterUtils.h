#pragma once 
#include "../Input.h"
#include "../Character.h"

bool IsWalkingForward(const Character &  character, const InputInfo &  inputInfo); 
bool IsWalkingBackwards(const Character &  character,const InputInfo &  inputInfo); 
bool IsJumpingForward(const Character &  character,const InputInfo &  inputInfo); 
bool IsJumpingBackwards(const Character &  character, const InputInfo &  inputInfo);
