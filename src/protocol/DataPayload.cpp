//
// Created by Administrator on 2021/6/30.
//

#include <vector>
#include <string>
#include <cassert>
#include "VecStream.h"
#include "Payload.h"
#include "DataPayload.h"


std::vector<uint8_t> DataPayload::serialize(void) {
    std::vector<uint8_t> result;
    serialize_append(result);
    return std::move(result);
}

void DataPayload::serialize_append(std::vector<uint8_t> &out) {
    out.insert(out.end(), this->content.begin(), this->content.end());
}

void DataPayload::deserialize(std::vector<uint8_t> &content, DataPayload **parsed_section) {
    auto &payload = *parsed_section;

    assert(nullptr != parsed_section && nullptr == payload);

    payload = new DataPayload();
    payload->content = content;
}

bool DataPayload::operator==(const Payload &other) const {
    const auto o = dynamic_cast<const DataPayload &>(other);
    return this->content == o.content;
}

bool DataPayload::operator==(const Payload *other) const {
    const auto *o = dynamic_cast<const DataPayload *>(other);
    return this->content == o->content;
}