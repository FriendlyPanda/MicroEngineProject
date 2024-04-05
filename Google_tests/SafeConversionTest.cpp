//
// Created by janha on 14/03/2024.
//
#include "gtest/gtest.h"
#include "../src/properties/SafeConversion.cpp"

TEST(SafeConversionInt, CorrectStringToIntegerTest){
    std::string str = "2002";
    ASSERT_EQ(stringToIntSafe(const_cast<char *>(str.c_str()), 0), 2002);
}

TEST(SafeConversionInt, IncorrectStringToIntegerTest){
    std::string str = "r196";
    ASSERT_EQ(stringToIntSafe(const_cast<char *>(str.c_str()), 0), 0);
}

TEST(SafeConversionInt, TooLargeStringToIntegerTest){
    std::string str = "9999999999999999999999999999999";
    ASSERT_EQ(stringToIntSafe(const_cast<char *>(str.c_str()), 0), 2147483647);
}