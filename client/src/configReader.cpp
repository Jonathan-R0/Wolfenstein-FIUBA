#include "../includes/configReader.h"

bool ConfigReader::fullScreen() {
  return true;
}

ConfigReader::ConfigReader(std::string fileName){
    this->fileName = fileName;
    this->data = this->getData();
}

YAML::Node ConfigReader::getData() {
  return YAML::LoadFile(this->fileName);
}

int ConfigReader::getHeight(){
    return data["HEIGHT"].as<int>();
}

int ConfigReader::getWidth(){
    return data["WIDTH"].as<int>();
}
