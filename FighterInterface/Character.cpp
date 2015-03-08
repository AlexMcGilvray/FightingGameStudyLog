#include "Character.h"
#include "GameData.h"
#include "CharacterStateFactory.h"

using namespace Input::VirtualInput;

Character::Character(GameState * gameState):
	hitboxBody(330,330,100,300),
	x(300),
	y(300),
	velocityX(0),
	velocityY(0), 
	gameState(gameState),
	visible(true)
{

	characterData = CharacterStateFactory::ParseCharacterData("data\\boxyboxerson\\boxy_character_data.json");

	state.AddState(CharacterStateType::STAND,CharacterStateFactory::GetCharacterState(STAND,*this));
	state.AddState(CharacterStateType::DUCK,CharacterStateFactory::GetCharacterState(DUCK,*this));
	state.AddState(CharacterStateType::WALKING_FORWARD,CharacterStateFactory::GetCharacterState(WALKING_FORWARD,*this));
	state.AddState(CharacterStateType::WALKING_BACKWARD,CharacterStateFactory::GetCharacterState(WALKING_BACKWARD,*this));
	state.AddState(CharacterStateType::STAND_ATTACK_1,CharacterStateFactory::GetCharacterState(STAND_ATTACK_1,*this));
	state.AddState(CharacterStateType::HIT_STUN,CharacterStateFactory::GetCharacterState(HIT_STUN,*this));
	state.AddState(CharacterStateType::JUMP_UP,CharacterStateFactory::GetCharacterState(JUMP_UP,*this));
	state.AddState(CharacterStateType::JUMP_FORWARD,CharacterStateFactory::GetCharacterState(JUMP_FORWARD,*this));
	state.AddState(CharacterStateType::JUMP_BACKWARD,CharacterStateFactory::GetCharacterState(JUMP_BACKWARD,*this));
	
	state.ChangeState(CharacterStateType::STAND);
}


Character::~Character(void) 
{
}

void Character::Update()
{
	InputInfo inputInfo;
	if (controller)
	{
		inputInfo = controller->Poll();
		state.UpdateState(inputInfo);
	} 
	if (state.CurrentState()->AffectedByGravity())
	{
		this->velocityY += GameData::GameGlobalValues::Gravity() * characterData->JumpData()->gravityMultiplier;
	}
	

	this->x += velocityX;
	this->y += velocityY; 
	//hitbox is always centered so it doesn't need to be recalculated according to which direction a character is facing
	hitboxBody.x = this->x - hitboxBody.width / 2;
	hitboxBody.y = this->y - this->hitboxBody.height; 
	if (this->Facing() == CharacterFacing::LEFT)
	{   
		for (int i = 0 ;i < hitboxesAttack.colliders.size();++i)
		{ 
			float colliderFinalX = this->x - hitboxesAttack.colliders[i].localX  - hitboxesAttack.colliders[i].width;
			hitboxesAttack.colliders[i].x = colliderFinalX;
			hitboxesAttack.colliders[i].y = this->y - this->hitboxBody.height;
		}
	}
	else 
	{   
		for (int i = 0 ;i < hitboxesAttack.colliders.size();++i)
		{
			float colliderFinalX = this->x + hitboxesAttack.colliders[i].localX ;
			hitboxesAttack.colliders[i].x = colliderFinalX;
			hitboxesAttack.colliders[i].y = this->y - this->hitboxBody.height;
		}
	} 
}

void Character::Render()
{
	if (visible)
	{
		hitboxBody.Render();
	} 
	for (int i = 0 ;i < hitboxesAttack.colliders.size();++i)
	{
		hitboxesAttack.colliders[i].Render(); 
	}
}