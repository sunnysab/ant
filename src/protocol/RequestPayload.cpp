//
// Created by sunnysab on 2021/6/29.
//

#include <vector>
#include <string>
#include <cassert>
#include "VecStream.h"
#include "Payload.h"
#include "RequestPayload.h"


std::vector<uint8_t> RequestPayload::serialize() {
    std::vector<uint8_t> result;

    serialize_append(result);
    return std::move(result);
}

void RequestPayload::serialize_append(std::vector<uint8_t> &out) {
    push_string(out, this->client_name);
    push_string(out, this->file_name);
    push_u32(out, file_id);
    push_u32(out, file_size);
    push_u16(out, block_size);
}

void RequestPayload::deserialize(std::vector<uint8_t> &content, RequestPayload **parsed_section) {
    auto &payload = *parsed_section;
    auto it = content.begin();

    assert(nullptr != parsed_section && nullptr == payload);

    payload = new RequestPayload();
    payload->client_name = get_string(it);
    payload->file_name = get_string(it);
    payload->file_id = get_u32(it);
    payload->file_size = get_u32(it);
    payload->block_size = get_u16(it);
}

