#include "CharacterState.h"
#include "GameData.h"
#include "Character.h"
#include "Debug.h"

CharacterState::CharacterState(Character & character,CharacterStateAnimation anim, const char * name) :
	character(character),
	animation(anim),
	name(name),
	hasEmittedDamage(false),
	affectedByGravity(true)
{ 
}


CharacterState::~CharacterState(void)
{
}

void CharacterState::UpdateState(InputInfo & inputInfo)
{
	animation.Update();
}

void CharacterState::ResetState()
{
	hasEmittedDamage = false;
}

void CharacterStateMachine::ChangeState(CharacterStateType type)
{
	if (states.find(type) != states.end())
	{
		stateStack.Clear();
		stateStack.Push(states[type]); 
		states[type]->ResetState();
		Debug::Logger::Log("Changed State to ");
		Debug::Logger::LogAppend(states[type]->Name()); 
	}
	else
	{
		Debug::Logger::Log("Could not find the state you want to change to.");
	}
}

void CharacterStateMachine::AddState(CharacterStateType type, CharacterState * state)
{
	states[type] = state;  
}

void CharacterStateMachine::UpdateState(InputInfo & inputInfo)
{
	CharacterState * currentState = stateStack.Peek();
	if (currentState != nullptr)
	{
		currentState->UpdateState(inputInfo);
	}
	else
	{
		Debug::Logger::Log("No states on stack, skipping character state update");
	}
}

CharacterStateMachine::CharacterStateMachine() 
{

}

void CharacterStateMachine::PopState()
{
	stateStack.Pop();
	Debug::Logger::Log("Popped state "); 
}

void CharacterStateMachine::PushState(CharacterStateType type)
{
	if (states.find(type) != states.end())
	{ 
		stateStack.Push(states[type]); 
		states[type]->ResetState();
		Debug::Logger::Log("Pushed State to ");
		Debug::Logger::LogAppend(states[type]->Name()); 
	}
	else
	{
		Debug::Logger::Log("Could not find the state you want to push.");
	}
}

void CharacterStateAnimation::Update()
{ 
	if (!started)
	{
		return;
	}
	currentFrameTime--; //subtract one frame, we measure everything in frames
	if (currentFrameTime <= 0)
	{
		if (currentFrame >= segments.size() - 1)
		{
			if (looping)
			{
				currentFrame = 0;
			}
			else
			{
				currentFrame = segments.size() - 1;
				complete = true;
			}
		}
		else
		{
			currentFrame++; 
		}
		currentSegment = &(segments[currentFrame]); 
		currentFrameTime = segments[currentFrame].LifespanFrameCount();
	}
	character.hitboxBody = currentSegment->HitboxBody();
 	character.hitboxesAttack = currentSegment->HitboxesAttack(); 
}

void CharacterStateAnimation::Reset()
{
	currentFrame = 0;
	started = true;
	complete = false;
	//setup the segment to the first frame so that there aren't any lingering hitboxes for one frame
	currentSegment = &(segments[0]); 
	character.hitboxBody = currentSegment->HitboxBody();
	character.hitboxesAttack = currentSegment->HitboxesAttack(); 
}

CharacterStateAnimation::CharacterStateAnimation(Character & character, bool looping,std::vector<CharacterStateSegment> segments) :
	character(character),
	looping(looping),
	segments(segments),
	currentFrameTime(0)
{

}

CharacterStateAnimation::~CharacterStateAnimation(void)
{

}

void CharacterStateAnimation::Stop()
{
	started = false;
}

void CharacterStateAnimation::Start()
{
	started = true;
}
 