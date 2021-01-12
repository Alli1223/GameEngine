// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "MainGame.h"



int solution(std::string& S) 
{
	// write your code in C++14 (g++ 6.2.0)

	int pos = S.find("\n");
	std::string subStr = S;

	int TimeDiff = 0;
	int lastTime = 0;
	while (pos != -1)
	{
		std::string date = subStr.substr(0, subStr.find("\n"));
		std::string day = date.substr(0, date.find(" "));
		std::string startTime = date.substr(date.find(" "), date.find("-") - date.find(" "));
		int startHours = std::stoi(startTime.substr(0, startTime.find(":")));
		//int startMins = std::stoi(startTime.substr(startTime.find(":"), startTime.length() - startTime.find(":")));
		int sTime = std::stoi(startTime);
		std::string endTime = date.substr(date.find("-") + 1, date.length());
		int endHours = std::stoi(endTime.substr(0, endTime.find(":")));
		//int endMins = std::stoi(endTime.substr(endTime.find(":"), endTime.length() - endTime.find(":")));
		int eTime = std::stoi(endTime);




		if (lastTime > 0)
			if ((lastTime - sTime) % 24 > TimeDiff)
				TimeDiff = (lastTime - sTime) % 24;

		//int firstTime_secs = (sTime / 100) * 3600;

		
		std::cout << (sTime - lastTime) % 24 << std::endl;


		//int secondTime_secs = (eTime / 100) * 3600;

		lastTime = eTime;

		subStr.erase(0, pos + 1);
		pos = subStr.find("\n");
	}

	return TimeDiff;
	//copied to IDE
}


int main(int argc, char* args[])
{

	std::string dates = "Sun 10:00-20:00\nFri 05:00 - 10:00\nFri 16:30 - 23:50\nSat 10:00 - 24:00\nSun 01:00 - 04:00\nSat 02:00 - 06:00\nTue 03:30 - 18:15\nTue 19 : 00 - 20 : 00\nWed 04 : 25 - 15 : 14\nWed 15 : 14 - 22 : 40\nThu 00 : 00 - 23 : 59\nMon 05 : 00 - 13 : 00\nMon 15 : 00 - 21 : 00";


	solution(dates);




	float timeB4 = SDL_GetTicks();













	// Create new Game
	MainGame game;
	game.run();

	if(game.needsRestart)
	{
		MainGame game;
		game.run();
	}
	
	return 0;

}

