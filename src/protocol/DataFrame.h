//
// Created by sunnysab on 2021/6/29.
//

#pragma once

#include <vector>


enum class FrameType {
    /* Transfer control related. */

    // Client send SendRequest to server.
    // The request includes some file properties and some client attributes.
    SendRequest = 1,
    // Server response RecvResponse to client,
    // to show its acceptation or denial.
    RecvResponse = 2,

    /* Data related. */

    // Frame that carries file content.
    Data = 10,
};

// Frame sequence type.
using seq_type = uint32_t;

struct Payload;


struct DataFrame {
public:
    // Frame sequence number.
    uint32_t seq;
    // Frame acknowledge number.
    uint32_t ack;
    // Frame type.
    FrameType type;
    // Checksum
    // uint32_t crc32;
    // Sections
    Payload *payload = nullptr;

public:
    DataFrame() = default;

    DataFrame(seq_type seq, seq_type ack, FrameType type);

    // Push a section on the back of the frame.
    void put(Payload *_payload);

    // Convert DataFrame to binary content
    std::vector<uint8_t> serialize(void) const;

    // Deserialize DataFrame from binary content
    static DataFrame deserialize(std::vector<uint8_t> &frame);

    bool operator==(const DataFrame &other) const;
};


/* Calculates CRC32 number for vector<byte> */
uint32_t calc_crc32(const std::vector<uint8_t> &content);