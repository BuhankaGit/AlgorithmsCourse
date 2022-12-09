#include "GameController.h"

GameController::GameController()
{
	std::ifstream file;
	file.open(filepath);
	if (!file) {
		file.close();
		round = 1;
		city = City();
	}
	else {
		file.close();
		char answer = 0;
		do {
			std::cout << "Do you want to start a game from previous save? (y/n) ";
			std::cin >> answer;
		} while (answer != 'y' && answer != 'n');
		switch (answer) {
		case 'y': {
			CsvReader reader;
			reader.read(filepath);
			round = stoi(reader.getParams()[0].getValue());
			std::vector<int> data;
			std::vector<std::string> temp = reader.split(reader.getParams()[5].getValue(), ",");
			for (int i = 0; i < temp.size(); i++) {
				data.push_back(stoi(temp[i]));
			}
			city = City(stoi(reader.getParams()[1].getValue()), 
				stoi(reader.getParams()[2].getValue()), 
				stod(reader.getParams()[3].getValue()),
				stoi(reader.getParams()[4].getValue()),
				data
			);
			break;
		}
		case 'n': {
			round = 1;
			city = City();
			break;
		}
		}
	}
}

void GameController::autoSave() {
	std::ofstream file;
	file.open(filepath, std::ios::trunc);
	if (file.is_open()) {
		file << "round:" + std::to_string(round) + '\n';
		file << "population:" + std::to_string(city.getPopulation()) + '\n';
		file << "wheat:" + std::to_string(city.getWheat()) + '\n';
		file << "territory:" + std::to_string(city.getTerritory()) + '\n';
		file << "acrPrice:" + std::to_string(city.getAcrPrice()) + '\n';
		file << "historyData:";
		for (int i = 0; i < city.getHistoryData().size(); i++) {
			file << city.getHistoryData()[i] << ",";
		}
	}
	file.close();
}

void GameController::playGame() {
	bool start = true;
	for (; round <= 10;) {
		autoSave();
		start ? showStartInfo() : showRoundInfo();
		start = false;
		makeOrders();
		if (city.isFailedState()) {
			std::cout << "More than 45% of the population starved to death. You are a bad ruler..." << std::endl;
			std::cout << "===============GAME OVER===============" << std::endl;
			return;
		}
		round++;
	}
	endGame(city.calculateResult());
}

void GameController::makeOrders()
{
	int territoryPurchase, territoryForSale, territoryForField;
	double wheatForConsume;

	std::cout << "Input amount of territory for purchase: ";
	std::cin >> territoryPurchase;
	while (city.getWheat() / city.getAcrPrice() < territoryPurchase || territoryPurchase < 0) {
		std::cout << "Invalid value" << std::endl;
		std::cout << "Input amount of territory for purchase: ";
		std::cin >> territoryPurchase;
	}

	std::cout << "Input amount of territory for sale: ";
	std::cin >> territoryForSale;
	while (city.getTerritory() < territoryForSale || territoryForSale < 0) {
		std::cout << "Invalid value" << std::endl;
		std::cout << "Input amount of territory for sale: ";
		std::cin >> territoryForSale;
	}

	double wheatUpdValue = city.getWheat() - (city.getAcrPrice() * territoryPurchase) + (city.getAcrPrice() * territoryForSale);

	std::cout << "Input amount of wheat for consumption: ";
	std::cin >> wheatForConsume;
	while (wheatUpdValue < wheatForConsume || wheatForConsume < 0) {
		std::cout << "Invalid value" << std::endl;
		std::cout << "Input amount of wheat for consumption: ";
		std::cin >> wheatForConsume;
	}

	int territoryUpdValue = city.getTerritory() - territoryForSale + territoryPurchase;
	double seedsPerAcr = 0.5;
	wheatUpdValue -= wheatForConsume;

	std::cout << "Input amount of territory for fields: ";
	std::cin >> territoryForField;
	while (territoryUpdValue < territoryForField || territoryForField < 0 || territoryForField*seedsPerAcr > wheatUpdValue) {
		std::cout << "Invalid value" << std::endl;
		std::cout << "Input amount of territory for fields: ";
		std::cin >> territoryForField;
	}

	city.handleOrders(territoryPurchase, territoryForSale, wheatForConsume, territoryForField);
}

void GameController::showRoundInfo()
{
	std::cout << "===============NEW ROUND===============" << std::endl;
	std::cout << "My lord, let me tell you" << std::endl;
	printf("It is the year %i now;\n", round);
	printf("%i people were starved to death, also we have %i new citizens;\n", city.getNumberOfDeaths(), city.getNewCitizens());
	if (city.ifDeseaseHappened()) {
		std::cout << "The plague wiped out half of the population;" << std::endl;
	}
	printf("Now there are %i people living in the city\n", city.getPopulation());
	printf("We harvested %i bushels of wheat, %i bushels per acre;\n", city.getHarvest(), city.getHarvestPerAcr());
	printf("Rats destroyed %i bushels of wheat, leaving %.1f bushels in barns;\n", city.getWheatLost(), city.getWheat());
	printf("The city now occupies %i acres;\n", city.getTerritory());
	printf("1 acre of land is now worth %i bushels\n", city.getAcrPrice());
}

void GameController::showStartInfo()
{
	std::cout << "My Lord, allow me to congratulate you on your accession to the throne!" << std::endl;
	printf("It is the year %i now\n", round);
	printf("You possess: %i acres of land, %.1f bushels of wheat and %i people\n", city.getTerritory(), city.getWheat(), city.getPopulation());
	printf("Current acr price: %i bushels\n", city.getAcrPrice());
}

void GameController::endGame(Result res)
{
	std::cout << "===============RESULTS===============" << std::endl;
	switch (res) {
	case Bad:
		std::cout << "Because of your incompetence in management, the people staged a riot, and expelled you from their city." << std::endl;
		break;
	case Acceptable:
		std::cout << "The people have breathed a sigh of relief, and no one wants to see you as a ruler anymore." << std::endl;
		break;
	case Good:
		std::cout << "You did quite well, of course, you have detractors, but many would like to see you at the head of the city again." << std::endl;
		break;
	case Great:
		std::cout << "Fantastic! Charlemagne, Disraeli and Jefferson couldn't have done better together." << std::endl;
		break;
	}
}
