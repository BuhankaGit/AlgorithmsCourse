#pragma once
#include "City.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "CsvReader.h"
#include "City.h"

class GameController
{
private:
	int round = 1;
	std::string filepath = "save.csv";
	City city;

	void autoSave();
	void makeOrders();
	void showRoundInfo();
	void showStartInfo();
	void endGame(Result res);
public:
	GameController();
	void playGame();
};

