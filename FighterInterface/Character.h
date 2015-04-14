#pragma once
 
#include "Collision.h"
#include "IUpdatable.h"
#include "IRenderable.h" 
#include "CharacterState.h"
#include "CharacterData.h"


class GameState;
namespace Input
{
	class IController;
}
 
enum CharacterFacing
{ 
	LEFT,
	RIGHT
};

class Character : public IUpdatable, public IRenderable
{
public:
	Character(GameState * gameState);
	~Character(void);
	 
	virtual void Update() override;
	virtual void Render() override;

	CharacterFacing Facing() const {return facing;}
	void Facing(CharacterFacing dir) {this->facing = dir;}

	Input::IController * controller; 

	void ZeroVelocity() {velocityX = 0; velocityY = 0;}

	int playerNumber;
	float x,y; //center bottom of the character. 
	bool visible;

	float velocityX,velocityY;
	CharacterData * characterData;

	Collision::Collider hitboxBody;
	Collision::CollisionSet hitboxesAttack;

	CharacterStateMachine state;
	GameState * gameState;

	const char * FacingToString()
	{ 
		if (facing == CharacterFacing::LEFT)
			return "Left";
		else if (facing == CharacterFacing::RIGHT)
			return "Right";
		else
			return "Error";
	}

private: 
	CharacterFacing facing;
};

