#include "City.h"

City::City()
{
	population = 100;
	wheat = 2800.;
	territory = 1000;
	acrPrice = std::rand() % 10 + 17;
}

/** Create city from file **/
City::City(int population, int wheat, int territory, int acrPrice)
{
	this->population = population;
	this->wheat = wheat;
	this->territory = territory;
	this->acrPrice = acrPrice;
}

void City::handleRound(int wheatForConsume, int territoryForFields)
{
	harvestPerTerritory = std::rand() % 6 + 1;
	feedPopulation(wheatForConsume);
	int percentOfDeaths = round((numberOfDeaths / population) * 100);
	historyData.push_back(percentOfDeaths);
	wheatLost = (std::rand() % 8 / 100.) * wheat;
	wheat = wheat - wheatLost;
	calculateNewCitizens();
	deseaseModification();
	acrPrice = std::rand() % 10 + 17;
	harvest = territoryForFields * harvestPerTerritory;
	wheat += harvest;
	if (percentOfDeaths > 45) {
		failedState = true;
	}
}

/** Return the number of deaths **/
int City::feedPopulation(int wheatForConsume)
{
	int feedCapacity = wheatForConsume / wheatConsumption;
	if (population <= feedCapacity) {
		return 0;
	}
	else 
	{
		numberOfDeaths = population - feedCapacity;
		population -= numberOfDeaths;
	}
	
}

void City::calculateNewCitizens() {
	int calculation = (numberOfDeaths / 2) + (5 - harvestPerTerritory) * wheat / 600 + 1;
	if (calculation <= 0) {
		numberOfNewCitizens = 0;
	}
	else {
		if (calculation >= 50) {
			numberOfNewCitizens = 50;
		}
		else {
			numberOfNewCitizens = calculation;
		}
	}
	population += numberOfNewCitizens;
}

void City::deseaseModification() {
	int deseaseHappenedCalc = std::rand() % 100;
	if (deseaseHappenedCalc < 15) {
		deseaseHappened = true;
		population = floor(population / 2);
	}
	else {
		deseaseHappened = false;
	}
}

Result City::calculateResult() {
	int P = round(territory / population);
	double L = std::accumulate(historyData.begin(), historyData.end(), 0) / historyData.size();
	if (P > 33 || L < 7) {
		return Result::Bad;
	}
	else if (P > 10 || L < 9) {
		return Result::Acceptable;
	}
	else if (P > 3 || L < 10) {
		return Result::Good;
	}
	else {
		return Result::Great;
	}
}

void City::handleOrders(int territoryPurchase, int territoryForSale, int wheatForConsume, int territoryForFields)
{
	territory = territory + territoryPurchase - territoryForSale;
	wheat = wheat + (territoryForSale * acrPrice) - (territoryPurchase * acrPrice) - (territoryForFields * 0.5) - wheatForConsume;
	handleRound(wheatForConsume, territoryForFields);
}