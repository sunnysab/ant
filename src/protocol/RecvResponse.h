//
// Created by Administrator on 2021/6/30.
//

#include <vector>
#include <string>
#include "Payload.h"

struct RecvResponse final : Payload {
public:
    // Response
    bool response;

public:
    // Serialize current request section to binary format.
    std::vector<uint8_t> serialize(void) override;

    // Serialize this and append to the vector `out`
    void serialize_append(std::vector<uint8_t> &out) override;

    // Deserialize from binary.
    static void deserialize(bool response, RecvResponse **parsed_section);

    bool operator==(const RecvResponse &other) const;
};


