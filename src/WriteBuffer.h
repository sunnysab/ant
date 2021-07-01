//
// Created by sunnysab on 2021/6/30.
//

#pragma once

#include <fstream>
#include <queue>

class WriteBuffer {
protected:
    std::ofstream *out_stream_ = nullptr;
    std::queue<uint8_t> buffer_;

    bool end_flag_ = false;

public:
    constexpr static size_t DefaultBufferSize = 1 * 1024 * 1024;

protected:
    void write_file();

public:
    WriteBuffer() = default;

    ~WriteBuffer();

    // Construct with a file stream
    explicit WriteBuffer(std::ofstream *stream);

    // Open a file stream for saving
    void open(std::ofstream *stream);

    void write(const std::vector<uint8_t> &result);

    void flush();
};

