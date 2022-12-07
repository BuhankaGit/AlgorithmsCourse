#include <iostream>
#include <ctime>
#include <string>
#include "GameController.h"
#include "CsvReader.h"

int main() {
	std::srand(std::time(nullptr));
	GameController gc;
	gc.playGame();
	exit(0);
}