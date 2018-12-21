//Leif Eriksson 

#include <vector>
#include <tuple>
#include <algorithm>

template<typename T = int, typename C = int, typename CC = C>
void knapsack(C c, const std::vector<std::pair<C, std::pair<C, C>>> & valueAweight, std::vector<T>& result) {
	//Having valueAweight sorted in order of increasing weight seems to yield best result
	//Contains current value and index vector
	std::vector<std::pair<CC, std::vector<T>>> dynamicVector(c + 1);

	dynamicVector[0].first = 1; //Only to diff from 0

	T i, j, newIndex;
	CC newValue;

	T maxValIndex{ c };
	CC maxVal{ 0 };

	//For all objects
	for (i = 0; i < valueAweight.size(); ++i) {
		//For the whole container (backwards to not add same twice)
		for (j = c - valueAweight[i].second.second; j > -1; --j) {
			//Need to already exists
			if (dynamicVector[j].first != 0) {
				newValue = dynamicVector[j].first + valueAweight[i].second.first;
				newIndex = j + valueAweight[i].second.second;
				//If better
				if (dynamicVector[newIndex].first < newValue) {
					dynamicVector[newIndex] = newValue;
					dynamicVector[newIndex] = dynamicVector[j].second;
					dynamicVector[newIndex].second.push_back(valueAweight[i].first);
					if (newValue > maxVal) {
						maxValIndex = newIndex;
						maxVal = newValue;
					}
				}
			}
		}
	}

	result.resize(dynamicVector[maxValIndex].second.size());
	copy(dynamicVector[maxValIndex].second.begin(), dynamicVector[maxValIndex].second.end(), result.begin());
}