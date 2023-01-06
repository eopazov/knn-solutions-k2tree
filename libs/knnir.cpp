#include "knnir.hpp"
#include<unistd.h>
#include <iostream>
#include <unistd.h>

using namespace std;

vector<pair<int, int>> knnir::knn(MREP *rep, int x, int y, uint k, uint radius)
{

  vector<pair<int, int>> points;

  int min_radius = 0;
  int max_radius = radius;
  int stepCount = 0;
  bool growUp = true;

  int x_min, y_min, x_max, y_max; // Created to rangue query
  int lastStepRadius;

  int max_border = rep->numberOfNodes;

  Count countFunction;


  while (min_radius <= max_radius)
  { 
    x_min = x - (int)radius;
    y_min = y - (int)radius;
    x_max = x + (int)radius;
    y_max = y + (int)radius;

    stepCount = countFunction.compactCount(rep, x_min, x_max, y_min, y_max);

    if (stepCount == k || (radius > max_border*2))
    {
      points = getPointsinRadius(rep, x_min, y_min, x_max, y_max, k);
      return points;
    }

    if (growUp)
    {

      if (stepCount < k)
      {
        lastStepRadius = radius;
        radius = radius * 2;
      }
      else if (stepCount > k)
      {
        min_radius = lastStepRadius;
        max_radius = radius;
        radius = (max_radius + min_radius) / 2;
        
        growUp = false;
      }
    }
    else
    {
      // si k de mayor = k de menor return lo que haya

      if((max_radius - min_radius) == 1){
        return getPointsinRadius(rep, x - (int)max_radius, y - (int)max_radius, x + (int)max_radius, y + (int)max_radius, k);
      }

      if(stepCount > k){
        max_radius = radius;
        radius = (min_radius + radius) / 2;
        
      }
      else if(stepCount < k){
        min_radius = radius;
        radius = (max_radius + radius) /2;
      }

      
      // Busqueda binaria.
    }
  }
  points = getPointsinRadius(rep, x_min, y_min, x_max, y_max, k);
  return points;
};

vector<pair<int, int>> knnir::getPointsinRadius(MREP *rep, int x1, int y1, int x2, int y2, int k)
{
  vector<pair<int, int>> points;

  x1 = x1 < 0 ? 0 : x1;
  y1 = y1 < 0 ? 0 : y1;
  
  uint ** point_matrix = compactRangeQuery(rep, y1, y2, x1, x2); 
  int maximun = k > point_matrix[0][0] ? point_matrix[0][0] : k;

  for(int i=0; i < maximun; i++){
    points.push_back(make_pair(point_matrix[1][i+1], point_matrix[0][i+1]));
  }

  return points;
};


