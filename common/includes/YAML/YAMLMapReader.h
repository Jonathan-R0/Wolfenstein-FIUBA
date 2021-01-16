#ifndef YAML_MAP_READER_H
#define YAML_MAP_READER_H

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <map>
#include <string>

#include "../Coordinate/Coordinate.h"

// compile with flag -lyaml-cpp

class YAMLMapReader {
 private:
  std::string fileName;
  YAML::Node data;
  YAML::Node getData();
  std::vector<Coordinate> getCoordinateVectorFromVectorOfVectorsOfSizeTwo(
      std::vector<std::vector<int>>& coordinatesData);

 public:
  std::map<int, std::vector<Coordinate>> getPartialItemCoordinateMap(
    int FROM_ID, int TO_ID);
  YAMLMapReader(std::string& fileName);
  std::vector<Coordinate> getTileCoordinatesWhereObjectIsIn(int objectId);
  std::vector<Coordinate> getRespawnLocations();
  std::map<int, std::vector<Coordinate>> getItemCoordinateMap();
  std::map<int, std::vector<Coordinate>> getWallTypeCoordinateMap();
  std::map<int, std::vector<Coordinate>> getItemTypeCoordinateMap();
  std::vector<int> getMapDimensions();
  std::vector<int> getWeaponsIdLimits();
  std::vector<int> getItemsIdLimits();
  std::vector<int> getDoorsIdLimits();
  std::vector<int> getWallsIdLimits();
};

#endif
