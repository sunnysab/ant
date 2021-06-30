//
// Created by sunnysab on 2021/6/29.
//

#include <string>
#include <vector>
#include "protocol/RequestPayload.h"
#include "protocol/DataPayload.h"
#include "gtest/gtest.h"



TEST(TestRequestPayload, serialize) {
    RequestPayload payload;

    payload.client_name = "client";
    payload.file_name = "something.dat";
    payload.file_id = 0x12345678;
    payload.file_size = 0x55AA;
    payload.block_size = 1024;

    std::vector<uint8_t> buffer = payload.serialize();
    std::vector<uint8_t> expected = {0x00, 0x06, 0x63, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x00, 0x0d, 0x73, 0x6f, 0x6d, 0x65,
                                     0x74, 0x68, 0x69, 0x6e, 0x67, 0x2e, 0x64, 0x61, 0x74, 0x12, 0x34, 0x56, 0x78, 0x00,
                                     0x00, 0x55, 0xaa, 0x04, 0x00};
    ASSERT_EQ(buffer, expected);

    buffer = {};
    payload.serialize_append(buffer);
    ASSERT_EQ(buffer, expected);
}

TEST(TestRequestPayload, deserialize) {
    RequestPayload expected;

    expected.client_name = "client";
    expected.file_name = "something.dat";
    expected.file_id = 0x12345678;
    expected.file_size = 0x55AA;
    expected.block_size = 1024;

    std::vector<uint8_t> buffer = {0x00, 0x06, 0x63, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x00, 0x0d, 0x73, 0x6f, 0x6d, 0x65,
                                   0x74, 0x68, 0x69, 0x6e, 0x67, 0x2e, 0x64, 0x61, 0x74, 0x12, 0x34, 0x56, 0x78, 0x00,
                                   0x00, 0x55, 0xaa, 0x04, 0x00};
    RequestPayload *result = nullptr;

    RequestPayload::deserialize(buffer, &result);
    ASSERT_EQ(*result, expected);

    delete result;
}

TEST(TestDataPayload, serialize) {
    DataPayload payload;

    std::string test_content = "helloworld!";
    std::vector<uint8_t> test(test_content.begin(), test_content.end());

    payload.content = test;

    std::vector<uint8_t> buffer = payload.serialize();
    std::vector<uint8_t> expected = {0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x21};
    ASSERT_EQ(buffer, expected);

    buffer = {};
    payload.serialize_append(buffer);
    ASSERT_EQ(buffer, expected);
}

TEST(TestDataPayload, deserialize) {
    DataPayload expected;
    std::string test_content = "helloworld!";
    std::vector<uint8_t> test(test_content.begin(), test_content.end());

    expected.content = test;

    std::vector<uint8_t> buffer = {0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x21};
    DataPayload *result = nullptr;

    DataPayload::deserialize(buffer, &result);
    ASSERT_EQ(*result, expected);

    delete result;
}
