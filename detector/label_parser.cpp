#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
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
	string line;
	string object_name;
	string str_class_id;
	int class_id;

	while (getline(label_file, line)) {
		stringstream iss(line);
		getline(iss, str_class_id, ':');
		getline(iss, object_name, ':');

		//class_id = std::stoi(str_class_id);

		cout << "class_id = " << str_class_id << endl;
		cout << "object_name = " << object_name << endl;
	}
}
