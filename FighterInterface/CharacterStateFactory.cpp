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
#include "character_states/CharacterUtils.h"

using namespace rapidjson; 

namespace CharacterStateFactory
{
	CharacterStateAnimation ParseCharacterAnimation(const char * pathToAnimationDefinition,Character & character); 
}  

CharacterState * CharacterStateFactory::GetCharacterState(CharacterStateType type,Character & character)
{
	switch (type)
	{
	case STAND:
		return(CharacterState *)( new State_Idle(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_idle.json",character),"Standing"));
	case WALKING_FORWARD:
		return(CharacterState *)( new State_WalkingForward(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_walking_forward.json",character),"Walking Forward"));
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
		return(CharacterState *)( new State_StandAttack1(character,ParseCharacterAnimation("data\\boxyboxerson\\boxy_stand_attack_1.json",character),"Stand Attack 1"));
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
	//cleanup
	{
		delete fileContents;
		fileContents = nullptr;
	} 
	return charAnim;
}


CharacterData * CharacterStateFactory::ParseCharacterData(const char * pathToDataDefinition)
{
	const char * fileContents = Utilities::GetTextFileContents(pathToDataDefinition);
	CharacterData_JumpData_Constants * jumpData;
	CharacterData_GeneralData_Constants * generalData;
	CharacterData_Movement_Constants * movementDataConstants;
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

	//Movement constants
	{
		//TODO make this data driven
		movementDataConstants = new CharacterData_Movement_Constants(5.0f);
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
	CharacterData * characterData = new CharacterData(*generalData,*jumpData,*movementDataConstants);
	//cleanup
	{ 
		delete fileContents;
		fileContents = nullptr;
		delete generalData;
		generalData = nullptr;
		delete jumpData;
		jumpData = nullptr;
		delete movementDataConstants;
		movementDataConstants = nullptr;
	}

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
