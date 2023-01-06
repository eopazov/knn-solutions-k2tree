#include <iostream>

#include "libs/knnir.hpp"
#include "libs/kTree.h"

using namespace std;

int main(int argc, char * argv[]){

	if(argc < 5){
		printf("%s <PATH> <X_1> <Y_1> <K>\n", argv[0]);
		return -1;
	}

	MREP *rep = loadRepresentation(argv[1]);
	int x = atoi(argv[2]);
	int y = atoi(argv[3]);
	int k = atoi(argv[4]);

	knnir knn;
	vector<pair<int,int>> points = knn.knn(rep, x, y, k, 1);

	for(pair<int,int> point : points){
		cout << "(" << point.first << "," << point.second << ")\n";
	}


	return 0;
}
