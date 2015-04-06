#include "CharacterStateFactory.h"
#include "Character.h" 
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Utilities.h"
#include "Collision.h"
#include "UFrameTimer.h"
#include "GameData.h"
#include "CharacterStates.h"


using namespace rapidjson;


namespace CharacterStateFactory
{
	CharacterStateAnimation ParseCharacterAnimation(const char * pathToAnimationDefinition,Character & character);
	
}

bool IsWalkingForward(const Character &  character, const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
			(character.Facing() == CharacterFacing::LEFT)) || 
			((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
			(character.Facing() == CharacterFacing::RIGHT)) ;
}

bool IsWalkingBackwards(const Character &  character,const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT)) || 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT)) ;
}

 
bool IsJumpingForward(const Character &  character,const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) 
		|| 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) ;
}

bool IsJumpingBackwards(const Character &  character, const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) 
		|| 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) ;
}



 

void State_Idle::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityX = 0;
	character.velocityY = 0;
	if (IsJumpingForward(character,inputInfo))
		character.state.ChangeState(JUMP_FORWARD); 
	else if (IsJumpingBackwards(character,inputInfo))
		character.state.ChangeState(JUMP_BACKWARD); 

	if (IsWalkingForward(character,inputInfo))
		character.state.ChangeState(WALKING_FORWARD); 
	else if (IsWalkingBackwards(character,inputInfo))
		character.state.ChangeState(WALKING_BACKWARD);  
	else if (inputInfo.inputMapping[InputValue::BTN1] == InputState::VIRTUAL_KEY_PRESSED) 
		character.state.ChangeState(STAND_ATTACK_1);  


	if (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)
	{ 
		character.state.ChangeState(JUMP_UP);
	}
	else if (inputInfo.inputMapping[InputValue::DOWN] == InputState::VIRTUAL_KEY_DOWN)
	{ 
		character.state.ChangeState(DUCK);
	} 
}

void State_Idle::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}



void State_Duck::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityX = 0;
	character.velocityY = 0;

	if (IsWalkingForward(character,inputInfo))
		character.state.ChangeState(WALKING_FORWARD); 
	else if (IsWalkingBackwards(character,inputInfo))
		character.state.ChangeState(WALKING_BACKWARD);  
	//this should be duck attack when added
	/*else if (inputInfo.inputMapping[InputValue::BTN1] == InputState::VIRTUAL_KEY_PRESSED) 
	character.state.ChangeState(STAND_ATTACK_1);  */


	if (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)
	{ 
		character.state.ChangeState(JUMP_UP);
	}
	else if (inputInfo.inputMapping[InputValue::DOWN] == InputState::VIRTUAL_KEY_UP)
	{ 
		character.state.ChangeState(STAND);
	} 
}

void State_Duck::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}




void State_StandAttack1::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	if (animation.Complete())
	{
		character.state.ChangeState(STAND);
	}
	else
	{
		character.velocityX = 0;
		character.velocityY = 0; 
	} 
}

void State_StandAttack1::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}

void State_WalkingForward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	if (IsJumpingForward(character,inputInfo))
		character.state.ChangeState(JUMP_FORWARD); 
	else if (IsJumpingBackwards(character,inputInfo))
		character.state.ChangeState(JUMP_BACKWARD); 

	if (IsWalkingForward(character,inputInfo))
	{
		if (character.Facing() == CharacterFacing::LEFT)
			character.velocityX = -0.1f; //TODO this needs to be data driven
		else
			character.velocityX = 0.1f; 
	} 
	else if (IsWalkingBackwards(character,inputInfo))
	{
		character.state.ChangeState(WALKING_BACKWARD);  
	} 
	else
	{
		character.state.ChangeState(STAND); 
	} 
}

void State_WalkingForward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  

void State_WalkingBackward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	if (IsJumpingForward(character,inputInfo))
		character.state.ChangeState(JUMP_FORWARD); 
	else if (IsJumpingBackwards(character,inputInfo))
		character.state.ChangeState(JUMP_BACKWARD); 

	if (IsWalkingBackwards(character,inputInfo))
	{
		if (character.Facing() == CharacterFacing::LEFT)
			character.velocityX = 0.1f;
		else
			character.velocityX = -0.1f; 
	} 
	else if (IsWalkingForward(character,inputInfo))
	{
		character.state.ChangeState(WALKING_FORWARD);  
	} 
	else
	{
		character.state.ChangeState(STAND); 
	}
}

void State_WalkingBackward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  

void State_HitStun::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	CharacterData_GeneralData * mData = character.characterData->MutableData();
	if (animation.Complete())
	{
		mData->knockBack = 0;
		character.state.PopState();
	}
	else
	{
		if (character.Facing() == CharacterFacing::LEFT)
		{
			character.velocityX = mData->knockBack;
		}
		else
		{
			character.velocityX = -mData->knockBack;
		}
	} 
}

void State_HitStun::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  

void State_Jump_Up::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityY += character.characterData->JumpData()->yDecay;
	if (character.y >= GameData::LevelGlobalValues::GroundPlaneY())
	{
		character.state.ChangeState(STAND); 
	}
}

void State_Jump_Up::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start(); 
	character.velocityY = -character.characterData->JumpData()->yStartVelocity;

}  

void State_Jump_Forward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo); 
	character.velocityY += character.characterData->JumpData()->yDecay;  
	if (character.y >= GameData::LevelGlobalValues::GroundPlaneY())
	{ 
		character.state.ChangeState(STAND); 
	}
}

void State_Jump_Forward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start(); 
	character.velocityY = -character.characterData->JumpData()->yStartVelocity;  
	if (character.Facing() == CharacterFacing::LEFT)
		character.velocityX = -character.characterData->JumpData()->xVelocity;
	else
		character.velocityX = character.characterData->JumpData()->xVelocity;
}  

void State_Jump_Backward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityY += character.characterData->JumpData()->yDecay;  
	if (character.y >= GameData::LevelGlobalValues::GroundPlaneY())
	{ 
		character.state.ChangeState(STAND); 
	}
}

void State_Jump_Backward::ResetState()
{
	CharacterState::ResetState();
	character.velocityY = -character.characterData->JumpData()->yStartVelocity;  
	if (character.Facing() == CharacterFacing::LEFT)
		character.velocityX = character.characterData->JumpData()->xVelocity;
	else
		character.velocityX = -character.characterData->JumpData()->xVelocity;
}  



CharacterState * CharacterStateFactory::GetCharacterState(CharacterStateType type,Character & character)
{
	switch (type)
	{
	case STAND:
		return(CharacterState *)( new State_Idle(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_idle.json",character),"Standing"));
	case WALKING_FORWARD:
		return(CharacterState *)( new State_WalkingForward(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_walkingforward.json",character),"Walking Forward"));
	case WALKING_BACKWARD:
		return(CharacterState *)( new State_WalkingBackward(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_walking_backward.json",character),"Walking Backward"));
	case JUMP_UP:
		return(CharacterState *)( new State_Jump_Up(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_jump_up.json",character),"Jumping Up"));
	case JUMP_FORWARD:
		return(CharacterState *)( new State_Jump_Forward(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_jump_up.json",character),"Jumping Forward")); //todo json
	case JUMP_BACKWARD:
		return(CharacterState *)( new State_Jump_Backward(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_jump_up.json",character),"Jumping Backward")); //todo json
	case DUCK:
		return(CharacterState *)( new State_Duck(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_duck.json",character),"Walking Backward"));
	case STAND_ATTACK_1:
		return(CharacterState *)( new State_StandAttack1(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_standattack1.json",character),"Stand Attack 1"));
	case STAND_ATTACK_2:
		break; 
	case HIT_STUN:
		return(CharacterState *)( new State_HitStun(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_hit_stun.json",character),"HitStun"));
	case FINAL_CHARACTER_STATE_TYPE_ENUM_VALUE:
		break;
	default:
		break;
	}
	return nullptr;
} 

CharacterStateAnimation CharacterStateFactory::ParseCharacterAnimation(const char * pathToAnimationDefinition,Character & character)
{
	bool looping = false;
	std::vector<CharacterStateSegment> segments;
	const char * fileContents = Utilities::GetTextFileContents(pathToAnimationDefinition);
	Document doc;	
	doc.Parse(fileContents);
	{
		const Value& vLooping = doc["looping"];
		assert(vLooping.IsBool());
		looping = vLooping.GetBool();
	} 
	const Value& vFrameDataCollection = doc["frame_data"];
	assert(vFrameDataCollection.IsArray());
	//build each animation segment and add to animation
	for (SizeType i = 0; i < vFrameDataCollection.Size(); i++) 
	{
		CharacterStateSegment segment;
		int lifeSpan = -1;
		Collision::Collider bodyHitbox;
		Collision::CollisionSet hitboxesAttack;
		const Value& vFrameData = vFrameDataCollection[i];
		assert(vFrameData.IsObject());  
		//lifespan 
		{
			const Value& vLifespan = vFrameData["lifespan"];
			assert(vLifespan.IsInt());
			lifeSpan = vLifespan.GetInt();
		} 
		//hitbox body
		{
			const Value& vHitboxBody = vFrameData["hitbox_body"];
			assert(vHitboxBody.IsObject()); 
			const Value& vHitboxBodyX = vHitboxBody["x"];
			const Value& vHitboxBodyY = vHitboxBody["y"];
			const Value& vHitboxBodyWidth = vHitboxBody["width"];
			const Value& vHitboxBodyHeight = vHitboxBody["height"];
			assert(vHitboxBodyX.IsInt() && vHitboxBodyY.IsInt() && vHitboxBodyWidth.IsInt() && vHitboxBodyHeight.IsInt()); 
			bodyHitbox.x = vHitboxBodyX.GetInt();
			bodyHitbox.y = vHitboxBodyY.GetInt();
			bodyHitbox.localX = bodyHitbox.x;
			bodyHitbox.localY = bodyHitbox.y;
			bodyHitbox.width = vHitboxBodyWidth.GetInt();
			bodyHitbox.height = vHitboxBodyHeight.GetInt();
			bodyHitbox.r = bodyHitbox.g = bodyHitbox.b = 1.0f;
		}

		//attack hitboxes 
		if (vFrameData.HasMember("hitbox_attack"))
		{ 
			const Value& vAttackHitboxes = vFrameData["hitbox_attack"];
			assert(vAttackHitboxes.IsArray());
			//build each animation segment and add to animation
			for (SizeType i = 0; i < vAttackHitboxes.Size(); i++) 
			{
				Collision::Collider attackHitbox;
				const Value& vAttackHitboxBody = vAttackHitboxes[i];
				assert(vAttackHitboxBody.IsObject());  
				const Value& vAttackHitboxBodyX = vAttackHitboxBody["x"];
				const Value& vAttackHitboxBodyY = vAttackHitboxBody["y"];
				const Value& vAttackHitboxBodyWidth = vAttackHitboxBody["width"];
				const Value& vAttackHitboxBodyHeight = vAttackHitboxBody["height"];
				const Value& vAttackHitboxDamage = vAttackHitboxBody["damage"];
				const Value& vAttackHitboxKnockback = vAttackHitboxBody["knockback"];
				assert(vAttackHitboxBodyX.IsInt() && vAttackHitboxBodyY.IsInt() && vAttackHitboxBodyWidth.IsInt() && vAttackHitboxBodyHeight.IsInt()); 
				attackHitbox.x = vAttackHitboxBodyX.GetInt();
				attackHitbox.y = vAttackHitboxBodyY.GetInt();
				attackHitbox.localX = attackHitbox.x;
				attackHitbox.localY = attackHitbox.y;
				attackHitbox.width = vAttackHitboxBodyWidth.GetInt();
				attackHitbox.height = vAttackHitboxBodyHeight.GetInt();
				attackHitbox.r = 1.0f;
				attackHitbox.g = attackHitbox.b = 0.0f;
				if (!vAttackHitboxDamage.IsNull() && vAttackHitboxDamage.IsInt())
					attackHitbox.damage = vAttackHitboxDamage.GetInt(); 
				else
					attackHitbox.damage = 0; 
				if (!vAttackHitboxKnockback.IsNull() && vAttackHitboxKnockback.IsDouble())
					attackHitbox.knockback = static_cast<float>(vAttackHitboxKnockback.GetDouble()); 
				else
					attackHitbox.knockback = 0; 

				hitboxesAttack.AddCollider(attackHitbox);
			} 
		}
		segment.HitboxBody(bodyHitbox);
		segment.HitboxesAttack(hitboxesAttack);
		segment.LifespanFrameCount(lifeSpan);
		segments.push_back(segment);
	}  
	CharacterStateAnimation charAnim(character,looping,segments); 
	delete fileContents;
	fileContents = nullptr;
	return charAnim;
}

 
CharacterData * CharacterStateFactory::ParseCharacterData(const char * pathToDataDefinition)
{
	const char * fileContents = Utilities::GetTextFileContents(pathToDataDefinition);
	CharacterData_JumpData_Constants * jumpData;
	CharacterData_GeneralData_Constants * generalData;
	Document doc;	
	doc.Parse(fileContents);

	//Parse and create general data
	{
		const Value& v_name = doc["name"];
		assert(v_name.IsString());  
		char * name = (char *)malloc(sizeof(char) * v_name.GetStringLength());
		int healthMax = -1; //TODO add this to data and parse
		strcpy(name, v_name.GetString());
		generalData = new CharacterData_GeneralData_Constants(name,healthMax);
	} 
	
	//Parse and create jump data
	{
		const Value& v_jump_data = doc["jump_data"];
		const Value& v_x_velocity = v_jump_data["x_velocity"];
		assert(v_x_velocity.IsNumber());
		const Value& v_y_start_velocity = v_jump_data["y_start_velocity"];
		assert(v_y_start_velocity.IsNumber());
		const Value& v_y_decay = v_jump_data["y_decay"];
		assert(v_y_decay.IsNumber());
		const Value& v_gravity_multiplier = v_jump_data["gravity_multiplier"];
		assert(v_gravity_multiplier.IsNumber()); 
		auto xVelocity = static_cast<float>(v_x_velocity.GetDouble());
		auto yStartVelocity = static_cast<float>(v_y_start_velocity.GetDouble());
		auto yDecay = static_cast<float>(v_y_decay.GetDouble());
		auto gravityMultiplier = static_cast<float>(v_gravity_multiplier.GetDouble());
		jumpData = new CharacterData_JumpData_Constants(xVelocity,yStartVelocity,yDecay,gravityMultiplier);
	} 
	CharacterData * characterData = new CharacterData(*generalData,*jumpData);

	delete fileContents;
	fileContents = nullptr;
	delete generalData;
	generalData = nullptr;
	delete jumpData;
	jumpData = nullptr;

	return characterData;
}

/*
void PopulateGameDataFromFile()
{
const char * readBuffer = Utilities::GetTextFileContents("data\\gamedata.json");
Document doc;	
doc.Parse(readBuffer);
if(doc.HasParseError())
{
assert(0); //in release use default hard coded values
return;
} 
{
Value& global_data = doc["global_data"];
Value& gravity = global_data["gravity"];
assert(gravity.IsNumber());
assert(gravity.IsDouble()); 
GameGlobalValues::Gravity(gravity.GetDouble());  
} 
{
Value& level_global_data = doc["level_global_data"];
Value& ground_plany_y = level_global_data["ground_plany_y"];
LevelGlobalValues::GroundPlaneY(ground_plany_y.GetDouble());
}
delete readBuffer;
readBuffer = nullptr;
}
*/
