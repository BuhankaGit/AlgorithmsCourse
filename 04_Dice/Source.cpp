#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <cstdlib>


using namespace std;

class DiceRoll {
private:
	int rollNum;
	int edgeCount;
	int modificator;
public:
	DiceRoll(string data) {
		regex modRegex("\\+(.*)");
		smatch modData;
		regex_search(data, modData, modRegex);
		string procData = data;
		if (!modData[0].str().empty()) {
			modificator = stoi(modData[1].str());
			procData = regex_replace(data, modRegex, "");
		}
		else {
			modificator = 0;
		}
		regex rollDataRegex("(.*)d(.*)");
		smatch rollData;
		regex_search(data, rollData, rollDataRegex);
		rollNum = stoi(rollData[1].str());
		edgeCount = stoi(rollData[2].str());
 	}

	auto trueRandomGenerator() {
		int pseudoRandMod = rand() % edgeCount;
		auto now = chrono::time_point_cast<chrono::milliseconds>(chrono::high_resolution_clock::now());
		long entropy = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count() + pseudoRandMod;
		return entropy % edgeCount;
	}

	int sum() {
		int sum = 0;
		for (int i = 0; i < rollNum; i++) {
			int roll = trueRandomGenerator();
			sum += roll;
		}
		return sum + modificator;
	}
};

vector<string> split(string arg, string delimiter) {
	const auto r = regex(delimiter.data());
	return vector<string>{
		sregex_token_iterator(arg.begin(), arg.end(), r, -1),
		sregex_token_iterator()
	};
}

void showResults(vector<int> results) {
	for (int i = 0; i < results.size(); i++) {
		cout << results[i] << " ";
	}
}


int main() {
	vector<int> results {0, 0, 0, 0, 0, 0};
	string roll = "1d6";
	DiceRoll experiment(roll);
	int rollsCount = 1000000;
	for (int i = 0; i < rollsCount; i++) {
		int res = experiment.sum();
		results[res] += 1;
	}
	showResults(results);
	exit(0);
}