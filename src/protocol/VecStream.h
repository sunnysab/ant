//
// Created by sunnysab on 2021/6/29.
//

#pragma once

#include <vector>


// Append a string to the vector
void push_string(std::vector<uint8_t> &out_buf, std::string const &s);

// Get the string from the vector, with a 16-bit string length on the left of the string.
// And then move the iterator above the string
std::string get_string(std::vector<uint8_t>::iterator &it);

// Append an 8-bit integer
void push_u8(std::vector<uint8_t> &output_buffer, const uint8_t x);

// Get an u8 on the position of the iterator and move the iterator 1 place to the right
uint8_t get_u8(std::vector<uint8_t>::iterator &it);

// Append an 16-bit integer
void push_u16(std::vector<uint8_t> &output_buffer, const uint16_t x);

// Get an u16 on the position of the iterator and move the iterator 2 place to the right
uint16_t get_u16(std::vector<uint8_t>::iterator &it);

// Append an 32-bit integer
void push_u32(std::vector<uint8_t> &output_buffer, const uint32_t x);

// Get an u32 on the position of the iterator and move the iterator 4 place to the right
uint32_t get_u32(std::vector<uint8_t>::iterator &it);