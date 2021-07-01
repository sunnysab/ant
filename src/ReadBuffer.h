//
// Created by sunnysab on 2021/6/30.
//

#pragma once

#include <fstream>
#include <queue>

class ReadBuffer {
protected:
    // Ifstream object
    std::ifstream *in_stream_ = nullptr;
    // Buffer queue
    std::queue<uint8_t> buffer_;

    // File reading end flag
    bool end_flag_ = false;

public:
    // Default buffer size
    constexpr static size_t DefaultBufferSize = 1 * 1024 * 1024;

protected:
    void read_from_file();

public:
    ReadBuffer() = default;

    // Construct with a file stream
    explicit ReadBuffer(std::ifstream *stream);

    // Open a file stream for reading
    void open(std::ifstream *stream);

    // Read file from buffer
    std::vector<uint8_t> read(int size = -1);

    // Read after the buffer has data
    void read_append(std::vector<uint8_t> &out_buf, int size = -1);

    // File reading end flag
    inline bool eof() const { return this->end_flag_; }
};

