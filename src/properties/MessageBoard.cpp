//
// Created by User on 28/12/2023.
//
#include "MessageBoard.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <utility>

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

bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    else return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

MessageBoard::MessageBoard(const string &filename) {

	pathToMessages = filename;

    std::ifstream file(filename);
    string line;
    while(getline(file, line)){
        if(line.rfind('#', 0) == 0){
            // if a line is a comment skip
            continue;
        }

        if(line.rfind('!', 0) == 0){
            // if a line is a readable comment read it out then skip
            std::cout << line << std::endl;
            continue;
        }
        if(const size_t pos = line.find('='); pos != string::npos){
            // if the line has both the name and value then add it to the messages
            const string key = line.substr(0, pos);

            // remove the \n from the end of the line
            string value = line.substr(pos + 1);

            // check for the \r at the end of the windows files lines (used for linux)
            if(ends_with(value, "\r")){
                value = value.substr(0, value.size() - 1);
            }
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

void MessageBoard::update(const std::string& key, std::string newValue) {
    messages[key] = std::move(newValue);
}

void MessageBoard::save() {
    std::ifstream file(pathToMessages);
    string stringToSave;
    string line;
    bool updatedFile = false;
    bool endR = false;
    while(getline(file, line)){
        if(const size_t pos = line.find('='); pos != string::npos){
            // if the line has both the name and value then add it to the messages
            const string key = line.substr(0, pos);

            // remove the \n from the end of the line
            string value = line.substr(pos + 1);

            // check for the \r at the end of the windows files lines (used for linux)
            if(ends_with(value, "\r")){
                endR = true;
                value = value.substr(0, value.size() - 1);
            }
            if(messages.find(key) != messages.end()){
                // check if key exists
                if(messages[key] != value){
                    // if the value is different then add a new line
                    if(!endR){
                        // linux made text file
                        stringToSave.append(key + "=" + messages[key] + "\n");
                    }
                    updatedFile = true;
                }else{
                    // if the value is the same then do nothing
                    stringToSave.append(line + "\n");
                }
            }else{
                // if it doesn't exist then just add to the string to save
                stringToSave.append(line + "\n");
            }
        }else{
            stringToSave.append(line + "\n");
        }
    }
    file.close();
    if(updatedFile){
        //if variables have been updated then save the file
        std::ofstream outputFile(pathToMessages);
        outputFile << stringToSave;
        outputFile.close();
    }else{
        std::cout << "nothing to do" << std::endl;
    }

}
