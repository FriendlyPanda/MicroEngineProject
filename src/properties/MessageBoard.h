//
// Created by JFH on 08/03/2023.
//

#ifndef MEP_MESSAGEBOARD_H
#define MEP_MESSAGEBOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

class MessageBoard {
private:
    /** all of the messages are paired with a key and saved as a map */
    map<string, string> messages;

    /**
     * replace the placeholders in the message with the following parameters
     * @param message the message to replace the placeholders from
     * @param params the strings to replace the placeholders with
     */
    static void replacePlaceholders(string& message, const vector<string>& params) {
        stringstream ss;
        size_t pos = 0;
        for(const auto & param : params){
            pos = message.find("{}", pos);
            if(pos != string::npos){
                message.replace(pos, 2, param);
                pos += param.size();
            }else{
                break;
            }
        }
    }
public:
    /**
     * simple constructor, takes in the filepath to the .properties file containing the messages
     * @param filename file path to the messages
     */
    explicit MessageBoard(const string& filename){

        ifstream file(filename);
        string line;
        while(getline(file, line)){
            if(line.rfind('#', 0) == 0){
                continue;
            }else{
                size_t pos = line.find('=');
                if(pos != string::npos){
                    string key = line.substr(0, pos);
                    string value = line.substr(pos + 1);
                    messages[key] = value;
                }
            }

        }
        file.close();
    }

    /**
     * retrieves the message without any parameters being passed, if placeholders exist, they will not be removed
     * @param key the message key to the map
     * @return the string containing the message
     */
    [[nodiscard]] string get(const string& key) const {
        return get(key, vector<string>());
    }

    /**
     * retrieve the message with parameters to replace existing placeholders
     * @param key the message map to the map
     * @param params the parameters to replace the placeholders with
     * @return the string containing the message
     */
    [[nodiscard]] string get(const string& key, const vector<string>& params) const {
        auto it = messages.find(key);
        if(it != messages.end()){
            string message = it->second;
            replacePlaceholders(message, params);
            return message;
        }else{
            return "ERROR: message (" + key + ") not found";
        }
    }

    /**
     * basic destructor
     */
    virtual ~MessageBoard() {
        messages.clear();
    }
};


#endif //MEP_MESSAGEBOARD_H
