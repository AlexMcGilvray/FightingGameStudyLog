#pragma once
//todo this should be replaced with only getters and be inited through some sort of config file.
namespace GameData
{
	void PopulateGameDataFromFile();
	void DrawDebugGameData(); 

	namespace GameGlobalValues
	{ 
		float Gravity();
		void Gravity(float val);
		double FrameDuration();
		void FrameDuration(double val);
	} 

	namespace LevelGlobalValues
	{
		float GroundPlaneY();
		void GroundPlaneY(float val); 
	} 
}