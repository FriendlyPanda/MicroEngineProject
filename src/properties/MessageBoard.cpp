//
// Created by User on 28/12/2023.
//
#include "MessageBoard.h"
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

void MessageBoard::replacePlaceholders(string &message, const vector<string> &params) {
    std::stringstream ss;
    size_t pos = 0;
    for (const auto &param: params) {
        pos = message.find("{}", pos);
        if (pos != string::npos) {
            message.replace(pos, 2, param);
            pos += param.size();
        } else {
            break;
        }
    }
}

MessageBoard::MessageBoard(const string &filename) {

	pathToMessages = filename;

    std::ifstream file(filename);
    string line;
    while(getline(file, line)){
        if(line.rfind('#', 0) == 0){
            continue;
        }
        if(const size_t pos = line.find('='); pos != string::npos){
            const string key = line.substr(0, pos);
            const string value = line.substr(pos + 1);
            messages[key] = value;
        }
    }
    file.close();
}

string MessageBoard::get(const string &key) const {
    return get(key, vector<string>());
}

string MessageBoard::get(const string &key, const vector<string> &params) const {
    if(const auto it = messages.find(key); it != messages.end()){
        string message = it->second;
        replacePlaceholders(message, params);
        return message;
    }

    return "ERROR: message (" + key + ") not found";
}

MessageBoard::MessageBoard() {

}