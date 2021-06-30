//
// Created by Administrator on 2021/6/30.
//

#include <vector>
#include <string>
#include <cassert>
#include "VecStream.h"
#include "Payload.h"
#include "RecvResponse.h"

std::vector<uint8_t> RecvResponse::serialize() {
    std::vector<uint8_t> result;
    serialize_append(result);
    return std::move(result);
}

void RecvResponse::serialize_append(std::vector<uint8_t> &out) {
    push_u32(out, this->response);
}

void RecvResponse::deserialize(bool response, RecvResponse **parsed_section) {
    auto &payload = *parsed_section;

    assert(nullptr != parsed_section && nullptr == payload);

    payload = new RecvResponse();
    payload->response = response;
}

bool RecvResponse::operator==(const RecvResponse &other) const {
    return this->response == other.response;
}