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

void RecvResponse::deserialize(std::vector<uint8_t> &buffer, RecvResponse **parsed_section) {
    auto &payload = *parsed_section;

    assert(nullptr != parsed_section && nullptr == payload);

    auto it = buffer.begin();
    auto server_ack_code = get_u32(it) != 0;
    payload = new RecvResponse();
    payload->response = server_ack_code;
}

bool RecvResponse::operator==(const Payload *other) const {
    const auto *o = dynamic_cast<const RecvResponse *>(other);

    return this->response == o->response;
}

bool RecvResponse::operator==(const Payload &other) const {
    const auto o = dynamic_cast<const RecvResponse &>(other);

    return this->response == o.response;
}
