#pragma once
#include "IUpdatable.h" 
#include "Input.h"
#include "Collision.h"
#include <map>
#include "UStack.h"
 
class Character; 

using namespace Input::VirtualInput;


enum CharacterStateType
{
	STAND,
	WALKING_FORWARD,
	WALKING_BACKWARD,
	JUMP_UP,
	JUMP_FORWARD,
	JUMP_BACKWARD,
	DUCK,
	STAND_ATTACK_1,
	STAND_ATTACK_2,
	HIT_STUN,
	KNOCKED_OUT,
	FINAL_CHARACTER_STATE_TYPE_ENUM_VALUE //always should be the last value

};

//was going to be names CharacterStateFrame but it seemed confusing considering 
//that a segmentt can last several frames.
class CharacterStateSegment
{
public: 
	int LifespanFrameCount() const { return lifespanFrameCount; }
	void LifespanFrameCount(int val) { lifespanFrameCount = val; }
	Collision::Collider HitboxBody() const { return hitboxBody; }
	void HitboxBody(Collision::Collider val) { hitboxBody = val; } 
	Collision::CollisionSet HitboxesAttack() const { return hitboxesAttack; }
	void HitboxesAttack(Collision::CollisionSet val) { hitboxesAttack = val; }
private:
	//duration of this frame counted in game frames
	int lifespanFrameCount; 
	//players body hitbox for this frame
	Collision::Collider hitboxBody; 
	Collision::CollisionSet hitboxesAttack;

};

class CharacterStateAnimation : public IUpdatable
{
public: 
	CharacterStateAnimation(Character & character, bool looping,std::vector<CharacterStateSegment> segments);
	~CharacterStateAnimation(void);
	void Reset();
	void Start();
	void Stop();
	bool Complete() const { return complete; } 
	//void Complete(bool val) { complete = val; }
	virtual void Update();


private:
	std::vector<CharacterStateSegment> segments;
	CharacterStateSegment * currentSegment;
	int currentFrame;
	bool started;
	bool looping;
	int currentFrameTime;
	bool complete;
	//maybe have this so that a hit on the same hitbox wont occur multiple times
	//bool hasAppliedHitboxes; 

	Character & character;
};

class CharacterState 
{
public:
	CharacterState(Character & character,CharacterStateAnimation anim, const char * name = "unnamed");
	~CharacterState(void);

	virtual void UpdateState(InputInfo & inputInfo) ;  
	virtual void ResetState();
	bool HasEmittedDamage() const { return hasEmittedDamage; }
	void HasEmittedDamage(bool val) { hasEmittedDamage = val; }
	const char * Name() const {return name;}
	bool AffectedByGravity() const {return affectedByGravity;}
protected : 
	 Character & character; 
	 CharacterStateAnimation animation;
	 bool hasEmittedDamage;
	 void AffectedByGravity(bool val) {affectedByGravity = val;}
private:
	const char * name;
	bool affectedByGravity;
};


//TODO make a stack class so states can be pushed and popped off the machine
class CharacterStateMachine 
{
public:
	CharacterStateMachine();
	void ChangeState(CharacterStateType type); 
	void PopState();
	void PushState(CharacterStateType type);
	void AddState(CharacterStateType type, CharacterState * state);
	void UpdateState(InputInfo & inputInfo) ; 
	CharacterState * CurrentState() const {return stateStack.Peek();}
private:

	std::map<CharacterStateType,CharacterState *> states;
	UStack<CharacterState *> stateStack; 
};

