#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <numeric>

#pragma once

enum Result {Bad, Acceptable, Good, Great};

class City
{
private:
	/** Territory data **/
	int territory;
	int acrPrice;
	/** Population data **/
	int population;
	int numberOfDeaths = 0;
	int numberOfNewCitizens = 0;
	std::vector<int> historyData;
	bool deseaseHappened = false;
	int citizenProductivity = 10;
	/** Wheat data **/
	double wheat;
	int territoryForFields = 0;
	int harvest = 0;
	int harvestPerTerritory = 0;
	double wheatLost = 0;
	int wheatConsumption = 20;

	int feedPopulation(int wheatForConsume);
	void calculateNewCitizens();
	void deseaseModification();

	bool failedState = false;
	
public:
	City();
	City(int population, int wheat, int territory, int acrPrice);
	void handleRound(int wheatForConsume, int territoryForFields);
	Result calculateResult();
	bool ifDeseaseHappened() { return deseaseHappened; };
	void handleOrders(int territoryPurchase, int territoryForSale, int wheatForConnsume, int territoryForFields);
	/** Get data **/
	int getTerritory() { return territory; };
	int getAcrPrice() { return acrPrice; };
	int getPopulation() { return population; };
	int getNumberOfDeaths() { return numberOfDeaths; };
	int getNewCitizens() { return numberOfNewCitizens; };
	double getWheat() { return round(wheat*10) / 10; };
	int getHarvest() { return harvest; };
	int getHarvestPerAcr() { return harvestPerTerritory; };
	int getWheatLost() { return wheatLost; };
	bool isFailedState() { return failedState; };

	
};

