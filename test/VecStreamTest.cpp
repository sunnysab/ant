//
// Created by sunnysab on 2021/6/29.
//

#include <string>
#include <vector>
#include "protocol/VecStream.h"
#include "gtest/gtest.h"


TEST(TestVecStream, push_u8) {
    std::vector<uint8_t> buffer = {};
    std::vector<uint8_t> expected = {0x05};

    push_u8(buffer, 0x05);
    ASSERT_EQ(buffer, expected);
}

TEST(TestVecStream, get_u8) {
    std::vector<uint8_t> buffer = {0x05};
    uint8_t expected = 0x05;
    auto it = buffer.begin();
    auto result = get_u8(it);

    ASSERT_EQ(result, expected);
}

TEST(TestVecStream, push_u16) {
    std::vector<uint8_t> buffer = {};
    std::vector<uint8_t> expected = {0x05, 0x03};

    push_u16(buffer, 0x0503);
    ASSERT_EQ(buffer, expected);
}

TEST(TestVecStream, get_u16) {
    std::vector<uint8_t> buffer = {0x05, 0x03};
    uint16_t expected = 0x0503;
    auto it = buffer.begin();
    auto result = get_u16(it);

    ASSERT_EQ(result, expected);
}

TEST(TestVecStream, push_u32) {
    std::vector<uint8_t> buffer = {};
    std::vector<uint8_t> expected = {0x12, 0x34, 0x56, 0x78};

    push_u32(buffer, 0x12345678);
    ASSERT_EQ(buffer, expected);
}

TEST(TestVecStream, get_u32) {
    std::vector<uint8_t> buffer = {0x12, 0x34, 0x56, 0x78};
    uint32_t expected = 0x12345678;
    auto it = buffer.begin();
    auto result = get_u32(it);

    ASSERT_EQ(result, expected);
}


TEST(TestVecStream, push_string) {
    std::vector<uint8_t> buffer;
    std::vector<uint8_t> expected;
    std::string s;

    s = "Hello, World!";
    buffer = {};
    expected = {0x00, 0x0D, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    push_string(buffer, s);
    ASSERT_EQ(buffer, expected);

    s = "";
    buffer = {};
    expected = {0x00, 0x00};
    push_string(buffer, s);
    ASSERT_EQ(buffer, expected);
}


TEST(TestVecStream, get_string) {
    std::vector<uint8_t> buffer;
    std::string expected;
    std::string result;

    buffer = {0x00, 0x0D, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    expected = "Hello, World!";
    auto it = buffer.begin();
    result = get_string(it);
    ASSERT_EQ(result, expected);

    buffer = {0x00, 0x00};
    expected = "";
    it = buffer.begin();
    result = get_string(it);
    ASSERT_EQ(result, expected);
}
