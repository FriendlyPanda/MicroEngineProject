//
// Created by janha on 09/03/2024.
//
#include "gtest/gtest.h"
#include "../src/properties/MessageBoard.h"

TEST(MessageBoardTestSuite, TestMessage){
    MessageBoard * msgs = new MessageBoard("E:\\DEV\\C\\MicroEngineProject\\Assets\\properties\\messages_en.properties");
    ASSERT_EQ(msgs->get("msg.test"), "Message board test");
}