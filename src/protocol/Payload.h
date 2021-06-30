//
// Created by sunnysab on 2021/6/29.
//

#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "Frame.h"


struct Payload {
public:
    /* Fields */

    /* Methods */
    virtual std::vector<uint8_t> serialize(void) = 0;

    virtual void serialize_append(std::vector<uint8_t> &out) = 0;

    static void deserialize(std::vector<uint8_t> &content, Payload **payload) {
        throw std::exception("You can not use deserialize function in abstract Payload.");
    }

    virtual bool operator==(const Payload *other) const = 0;

    virtual bool operator==(const Payload &other) const = 0;
};

