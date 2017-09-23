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

class decoder {
public:
    decoder() = default;

    STATUS decode(const std::string &input);

    std::vector<std::string> decoded_redis_command;
private:
    STATUS parse_arrays(const std::string&, std::vector<std::string>&);

public:
    // decoder is non-copyable.
    decoder(const decoder &) = delete;
    decoder operator= (const decoder &) = delete;
};

class encoder {
public:
    encoder() = default;
    std::string encode(const RESP_TYPE &type, const std::vector<std::string> &args);

    // Encoder is non-copyable.
    encoder(const encoder &) = delete;
    encoder operator= (const encoder &) = delete;
};

} // namespace simple_resp

#endif //SIMPLE_RESP_SIMPLE_RESP_H
