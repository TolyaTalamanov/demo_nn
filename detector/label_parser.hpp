#ifndef DETECTOR_LABEL_PARSER_H_ 
#define DETECTOR_LABEL_PARSER_H_ 

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
		unordered_map<int, string> labelmap_;
};

#endif  // DETECTOR_LABEL_PARSER_H_ 
