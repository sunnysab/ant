//
// Created by sunnysab on 2021/6/30.
//

#include <vector>
#include <fstream>
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "gtest/gtest.h"


TEST(TestReadBuffer, read_file) {
    std::ifstream in;
    in.open("./test/test-case/pure-text.txt", std::ifstream::binary | std::ifstream::in);
    ReadBuffer buffer(&in);
    std::vector<uint8_t> expected = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    auto s = buffer.read();
    in.close();

    ASSERT_EQ(buffer.eof(), true);
    ASSERT_EQ(s, expected);
}

TEST(TestWriteBuffer, save_file) {
    std::ofstream out;
    out.open("./test/test-case/pure-text.txt", std::ofstream::binary | std::ofstream::out);
    WriteBuffer out_buffer(&out);

    std::vector<uint8_t> content_to_write = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    out_buffer.write(content_to_write);
    out.close();

    std::ifstream in;
    in.open("./test/test-case/pure-text.txt", std::ifstream::binary | std::ifstream::in);
    ReadBuffer in_buffer(&in);
    auto s = in_buffer.read();
    in.close();

    ASSERT_EQ(in_buffer.eof(), true);
    ASSERT_EQ(s, content_to_write);
}
