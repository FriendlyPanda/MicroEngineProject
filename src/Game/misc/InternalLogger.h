//
// Created by jan on 5/25/23.
//

#ifndef MEP_INTERNALLOGGER_H
#define MEP_INTERNALLOGGER_H

#include "../../properties/MessageBoard.h"
#include "spdlog/spdlog.h"

class InternalLogger {

public:
    /**
     * @class InternalLogger
     * @brief A class representing an internal logger.
     *
     * This class provides functionality for logging messages for internal use.
     * It takes a logger name as input and creates a logger object for that name.
     */
    explicit InternalLogger(std::string logger_name);
    /**
     * @brief Set the Message Board object.
     *
     * This function is used to set the message board object for the InternalLogger. The message board object is used
     * to retrieve messages from a message map.
     *
     * @param newMSG A pointer to the MessageBoard object.
     */
    void setMessageBoard(MessageBoard * newMSG);
    /**
     * @brief Sets up the message board for the internal logger.
     *
     * This function initializes the message board for the internal logger by creating a new MessageBoard object based on the provided file path.
     * The file path should point to a .properties file containing the messages.
     *
     * @param filepath The file path to the .properties file.
     */
    void setupMessageBoard(const std::string& filepath);
    /**
      * @brief Returns the pointer to the MessageBoard object.
      * @return Pointer to the MessageBoard object.
      */
    MessageBoard * getMessageBoard();

#ifdef NDEBUG
    // release version
#else
    //debug version
    /**
     * @brief Logs a debug message.
     *
     * This function logs the specified debug message using the logger.
     *
     * @param message The debug message to be logged.
     */
    void debug(const std::string& message);

    /**
     * @brief Display a debug message based on the given message key.
     *
     * This function retrieves the debug message based on the given message key from the message board and logs it using the internal logger.
     *
     * @param msgKey The key used to retrieve the debug message from the message board.
     */
    void debugMsg(const std::string& msgKey);
    /**
     * @brief Logs a debug message with optional parameters.
     *
     * This function retrieves the debug message associated with the given message key from the message board,
     * and logs it using the internal logger. Optional parameters can be provided to replace placeholders in the message.
     *
     * @param msgKey The message key used to retrieve the debug message.
     * @param params Optional parameters used to replace placeholders in the debug message.
     */
    void debugMsg(const std::string& msgKey, const std::vector<std::string> &params);
#endif


    /**
     * @brief Logs an error message.
     *
     * This function logs the specified error message using the logger.
     *
     * @param message The error message to be logged.
     */
    void error(const std::string& message);
    /**
     * @brief Display an error message based on the given message key.
     *
     * This function retrieves the error message based on the given message key from the message board and logs it using the internal logger.
     *
     * @param msgKey The key used to retrieve the error message from the message board.
     */
    void errorMsg(const std::string& msgKey);
    /**
     * @brief Logs an error message with optional parameters.
     *
     * This function retrieves the error message associated with the given message key from the message board,
     * and logs it using the internal logger. Optional parameters can be provided to replace placeholders in the message.
     *
     * @param msgKey The message key used to retrieve the error message.
     * @param params Optional parameters used to replace placeholders in the error message.
     */
    void errorMsg(const std::string& msgKey, const std::vector<std::string> &params);

    /**
     * @brief Logs a warning message.
     *
     * This function logs the specified warning message using the logger.
     *
     * @param message The warning message to be logged.
     */
    void warning(const std::string& message);
    /**
     * @brief Display an warning message based on the given message key.
     *
     * This function retrieves the warning message based on the given message key from the message board and logs it using the internal logger.
     *
     * @param msgKey The key used to retrieve the warning message from the message board.
     */
    void warningMsg(const std::string& msgKey);
    /**
     * @brief Logs a warning message with optional parameters.
     *
     * This function retrieves the warning message associated with the given message key from the message board,
     * and logs it using the internal logger. Optional parameters can be provided to replace placeholders in the message.
     *
     * @param msgKey The message key used to retrieve the warning message.
     * @param params Optional parameters used to replace placeholders in the warning message.
     */
    void warningMsg(const std::string& msgKey, const std::vector<std::string> &params);

    /**
     * @brief Logs an info message.
     *
     * This function logs the specified info message using the logger.
     *
     * @param message The info message to be logged.
     */
    void info(const std::string& message);
    /**
     * @brief Display an info message based on the given message key.
     *
     * This function retrieves the info message based on the given message key from the message board and logs it using the internal logger.
     *
     * @param msgKey The key used to retrieve the info message from the message board.
     */
    void infoMsg(const std::string& msgKey);
    /**
     * @brief Logs an info message with optional parameters.
     *
     * This function retrieves the info message associated with the given message key from the message board,
     * and logs it using the internal logger. Optional parameters can be provided to replace placeholders in the message.
     *
     * @param msgKey The message key used to retrieve the info message.
     * @param params Optional parameters used to replace placeholders in the info message.
     */
    void infoMsg(const std::string& msgKey, const std::vector<std::string> &params);

    /**
     * @fn void clear()
     * @brief Clears the internal logger.
     *
     * This function clears the internal logger by freeing the msg pointer and setting it to nullptr.
     */
    void clear();

private:
    MessageBoard * msg = nullptr;
    spdlog::logger logger = spdlog::logger("");

};


#endif //MEP_INTERNALLOGGER_H
