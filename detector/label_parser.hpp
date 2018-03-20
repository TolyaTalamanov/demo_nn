#ifndef DETECTOR_LABEL_PARSER_HPP_
#define DETECTOR_LABEL_PARSER_HPP_

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class LabelParser {
 public:
  explicit LabelParser(const string& label_file_path);
  string getLabelById(int class_id);

 private:
  void parseLabelFile(const string& label_file_path);
  unordered_map<int, string> detection_object;
};

struct Item {
  int class_id;
  string class_name;

  friend std::istream& operator>>(std::istream& fin, Item& item) {
    string line;

    if (!getline(fin, line)) {
      fin.setstate(std::ios::failbit);
      return fin;
    }
    getline(fin, line);
    getline(fin, line);

    item.class_id = stoi(line.substr(line.find_last_of(" ") + 1));
    getline(fin, line);

    auto start = line.find_first_of("\"");
    auto end   = line.find_last_of("\"");

    item.class_name = line.substr(start + 1, end - start - 1);
    getline(fin, line);

    return fin;
  }
};

#endif  // DETECTOR_LABEL_PARSER_HPP_
