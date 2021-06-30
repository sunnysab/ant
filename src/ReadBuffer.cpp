//
// Created by sunnysab on 2021/6/30.
//

#include <cassert>
#include <fstream>
#include <filesystem>
#include "ReadBuffer.h"


ReadBuffer::ReadBuffer(std::ifstream *stream) {
    assert(nullptr != stream);

    this->open(stream);
}

void ReadBuffer::open(std::ifstream *stream) {
    assert(stream->is_open());

    this->in_stream_ = stream;
}

std::vector<uint8_t> ReadBuffer::read(int size) {
    std::vector<uint8_t> result;

    this->read_append(result, size);
    return result;
}

void ReadBuffer::read_append(std::vector<uint8_t> &out_buf, int size) {
    this->read_from_file();

    if (size < 0)
        size = ReadBuffer::DefaultBufferSize;

    auto size_to_read = std::min((size_t) size, this->buffer_.size());
    while (size_to_read-- > 0) {
        auto ch = this->buffer_.front();
        out_buf.push_back(ch);

        this->buffer_.pop();
    }
}

void ReadBuffer::read_from_file() {
    auto full_size = ReadBuffer::DefaultBufferSize;
    if (this->end_flag_ || this->buffer_.size() >= full_size / 2)
        return;

    auto size_to_read = full_size - buffer_.size();
    std::vector<uint8_t> disk_buffer(size_to_read);

    this->in_stream_->read(reinterpret_cast<char *>(disk_buffer.data()), size_to_read);
    for_each(disk_buffer.begin(), disk_buffer.begin() + this->in_stream_->gcount(), [this](
            auto ch) { this->buffer_.push(ch); });

    if (this->in_stream_->eof())
        this->end_flag_ = true;
}


