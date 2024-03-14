//
// Created by janha on 09/03/2024.
//
#include "gtest/gtest.h"
#include "../src/properties/MessageBoard.h"

TEST(MessageBoardTestSuite, TestMessage){
    auto * msgs = new MessageBoard(R"(E:\DEV\C\MicroEngineProject\Assets\properties\messages_en.properties)");
    ASSERT_EQ(msgs->get("msg.test"), "Message board test");
}

TEST(MessageBoardTestSuite, MessageWithVariables){
    auto * msgs = new MessageBoard(R"(E:\DEV\C\MicroEngineProject\Assets\properties\messages_en.properties)");
    ASSERT_EQ(msgs->get("msg.empty", std::vector<std::string>{"Test01"}), "Test01");
}

TEST(MessageBoardTestSuite, MessageWithWithoutVariables){
    auto * msgs = new MessageBoard(R"(E:\DEV\C\MicroEngineProject\Assets\properties\messages_en.properties)");
    ASSERT_EQ(msgs->get("msg.empty", std::vector<std::string>{}), "{}");
}