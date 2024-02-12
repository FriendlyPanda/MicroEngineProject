//
// Created by JFH on 08/03/2023.
//

#ifndef MEP_MESSAGEBOARD_H
#define MEP_MESSAGEBOARD_H


#include <string>
#include <unordered_map>
#include <memory_resource>
#include <vector>

class MessageBoard {
public:
    /**
     * simple constructor, takes in the filepath to the .properties file containing the messages
     * @param filename file path to the messages
     */
    explicit MessageBoard(const std::string& filename);

    /**
     * retrieves the message without any parameters being passed, if placeholders exist, they will not be removed
     * @param key the message key to the map
     * @return the string containing the message
     */
    [[nodiscard]] std::string get(const std::string& key) const;

    /**
     * retrieve the message with parameters to replace existing placeholders
     * @param key the message map to the map
     * @param params the parameters to replace the placeholders with
     * @return the string containing the message
     */
    [[nodiscard]] std::string get(const std::string& key, const std::vector<std::string>& params) const;

    /**
     * basic destructor
     */
    virtual ~MessageBoard() {
        messages.clear();
    }

private:
 /** all of the messages are paired with a key and saved as a map */
 std::pmr::unordered_map<std::string, std::string> messages;

 /**
  * replace the placeholders in the message with the following parameters
  * @param message the message to replace the placeholders from
  * @param params the vector of strings to replace the placeholders with
  */
 static void replacePlaceholders(std::string& message, const std::vector<std::string>& params);
};


#endif //MEP_MESSAGEBOARD_H
