#include <iostream>
#include <string>
#include <vector>

#ifndef SIMPLE_RESP_SIMPLE_RESP_H
#define SIMPLE_RESP_SIMPLE_RESP_H

namespace simple_resp {

enum RESP_TYPE {
    SIMPLE_STRINGS = '+',
    ERRORS = '-',
    INTEGERS = ':',
    BULK_STRINGS = '$',
    ARRAYS = '*'
};

enum STATUS {
    OK = 0,
    EMPTY_INPUT = 1,
    INVAILID_RESP_TYPE = 2,
    INVAILID_RESP_FORMAT = 3,
    UNKNOWN_INTERNAL_ERROR = 3,
};

enum PARSE_STATE {
    INIT = 0,
    PARSE_ELEMENTS = 1,
    PARSE_BLUK_STRINGS = 2
};

class Decoder {
public:
    Decoder() = default;

    STATUS decode(const std::string &input);

    std::vector<std::string> decoded_redis_command;
private:
    STATUS parse_arrays(const std::string&, std::vector<std::string>&);

public:
    // Decoder is non-copyable.
    Decoder(const Decoder &) = delete;
    Decoder operator= (const Decoder &) = delete;
};

class Encoder {
public:
    Encoder() = default;
    STATUS encode(const RESP_TYPE &type, const std::vector<std::string> &args);

    std::string encoded_redis_command;

    // Encoder is non-copyable.
    Encoder(const Encoder &) = delete;
    Encoder operator= (const Encoder &) = delete;
};

} // namespace simple_resp

#endif //SIMPLE_RESP_SIMPLE_RESP_H
