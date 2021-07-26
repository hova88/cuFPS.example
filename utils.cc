// headers in STL
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int LoadCloud( float* &points_array , float* &temp ,std::string file_name , int num_feature = 4)
{
  std::ifstream InFile;
  InFile.open(file_name.data());
//   assert(InFile.is_open());

  std::vector<float> temp_points;
  std::string c;

  while (!InFile.eof())
  {
      InFile >> c;

      temp_points.push_back(atof(c.c_str()));
  }
  points_array = new float[temp_points.size()/ num_feature * 3 ];
  temp = new float[temp_points.size()];
  for (int i = 0 ; i < temp_points.size() / num_feature; ++i) {
    points_array[i * 3 + 0] = temp_points[i * num_feature + 0];
    points_array[i * 3 + 1] = temp_points[i * num_feature + 1];
    points_array[i * 3 + 2] = temp_points[i * num_feature + 2];
    temp[i] = 1e10;
  }

  InFile.close();  
  return temp_points.size() / num_feature;
};