//
// Created by sunnysab on 2021/6/29.
//

#include <vector>
#include <string>
#include "VecStream.h"


void push_string(std::vector<uint8_t> &out_buf, std::string const &s) {
    auto string_size = static_cast<uint16_t>(s.size());
    auto buf_size = static_cast<uint16_t>(out_buf.size());

    // We push the size of string before the string characters.
    push_u16(out_buf, string_size);
    // Resize output buffer to ensure that the buffer could contain all characters.
    // buf_size + 2 is the postion of the first character
    out_buf.resize((buf_size + 2) + string_size);
    // If string_size is zero, accessing s[0] is an undefined behavior.
    if (string_size != 0)
        // Use memcpy fucntion to copy faster.
        memcpy(&out_buf[buf_size + 2], &s[0], string_size);
}

std::string get_string(std::vector<uint8_t>::iterator &it) {
    auto size = get_u16(it);
    auto end = it + size;
    std::string result(size, '\0');

    for (auto dst = result.begin(); it != end; ++it, ++dst) {
        *dst = static_cast<char>(*it);
    }
    return std::move(result);
}

void push_u8(std::vector<uint8_t> &output_buffer, const uint8_t x) {
    output_buffer.push_back(x);
}

uint8_t get_u8(std::vector<uint8_t>::iterator &it) {
    uint8_t result = *(it++);
    return result;
}

void push_u16(std::vector<uint8_t> &output_buffer, const uint16_t x) {
    push_u8(output_buffer, x >> 8);
    push_u8(output_buffer, x & 127);
}

uint16_t get_u16(std::vector<uint8_t>::iterator &it) {
    uint16_t result = get_u8(it) << 8;
    return result | get_u8(it);
}

void push_u32(std::vector<uint8_t> &output_buffer, const uint32_t x) {
    push_u16(output_buffer, x >> 16);
    push_u16(output_buffer, x & 65535);
}

uint32_t get_u32(std::vector<uint8_t>::iterator &it) {
    uint32_t result = get_u16(it) << 16;
    return result | get_u16(it);
}
