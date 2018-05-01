#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "label_parser.hpp"

using std::ifstream;
using std::cout;
using std::endl;
using std::stringstream;

LabelParser::LabelParser(const string& label_file_path) {
  parseLabelFile(label_file_path);
}

void LabelParser::parseLabelFile(const string& label_file_path) {
  ifstream label_file(label_file_path);

  std::transform(std::istream_iterator<Item>(label_file), {},
                 std::inserter(detection_object, detection_object.end()),
                 [](const auto& item) {
                   return std::make_pair(item.class_id, item.class_name);
                 });
}

string LabelParser::getLabelById(int class_id) {
  return detection_object.find(class_id)->second;
}
