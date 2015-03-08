#include "GameData.h"
#include "Utilities.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
 
namespace GameData
{
	namespace GameGlobalValues
	{
		float gravity = 0.1f;
		double frameDurationSeconds = 0.0166667;

		float Gravity()
		{
			return gravity;
		}

		void Gravity(float val)
		{
			gravity = val;
		}

		double FrameDuration()
		{
			return frameDurationSeconds;
		}

		void FrameDuration(double val)
		{
			frameDurationSeconds = val;
		}

	}
	namespace LevelGlobalValues
	{
		float groundPlaneY = 700.0f;
		 
		float GroundPlaneY()
		{
			return groundPlaneY;
		}

		void GroundPlaneY(float val)
		{
			  groundPlaneY = val;
		} 
	}

	void PopulateGameDataFromFile()
	{
		const char * readBuffer = Utilities::GetTextFileContents("data\\gamedata.json");
		Document doc;	
		doc.Parse(readBuffer);
		if(doc.HasParseError())
		{
			assert(0); //in release we should probably just use default hard coded values (possibly baked in from the json data at compile time)
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

	void DrawDebugGameData()
	{

	} 
}


 


