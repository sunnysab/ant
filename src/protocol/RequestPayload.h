//
// Created by sunnysab on 2021/6/29.
//

#pragma once

#include <string>
#include "Payload.h"

struct RequestPayload final : Payload {
public:
    // Name of the sender
    std::string client_name;
    // Name of file
    std::string file_name;
    // Request file id set by sender.
    uint32_t file_id;
    // The size of file given by sender.
    uint32_t file_size;
    // Block size to cut the file.
    uint16_t block_size;

public:
    // Serialize current request section to binary format.
    std::vector<uint8_t> serialize(void) override;

    // Serialize this and append to the vector `out`
    void serialize_append(std::vector<uint8_t> &out) override;

    // Deserialize from binary.
    static void deserialize(std::vector<uint8_t> &content, RequestPayload **parsed_section);

    bool operator==(const RequestPayload &other) const;
};
