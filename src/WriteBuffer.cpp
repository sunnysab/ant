//
// Created by sunnysab on 2021/6/30.
//

#include <cassert>
#include <fstream>
#include <filesystem>
#include "WriteBuffer.h"

WriteBuffer::WriteBuffer(std::ofstream *stream) {
    assert(nullptr != stream);

    this->open(stream);
}

void WriteBuffer::open(std::ofstream *stream) {
    assert(stream->is_open());

    this->out_stream_ = stream;
}

void WriteBuffer::write(const std::vector<uint8_t> &result) {
    this->out_stream_->write(reinterpret_cast<const char *>(result.data()), result.size());
}

void WriteBuffer::write_file() {
    auto full_size = WriteBuffer::DefaultBufferSize;
    if (this->buffer_.size() >= full_size / 2)
        return;

    auto size_to_write = buffer_.size();
    std::vector<uint8_t> disk_buffer(size_to_write);

    while (!this->buffer_.empty()) {
        disk_buffer.push_back(this->buffer_.front());
        this->buffer_.pop();
    }
    this->out_stream_->write(reinterpret_cast<char *>(disk_buffer.data()), size_to_write);

}


