#include <iostream>
#include <string>
#include <vector>

#ifndef SIMPLE_RESP_SIMPLE_RESP_H
#define SIMPLE_RESP_SIMPLE_RESP_H

namespace SimpleRESP {

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
    ILLEGAL_RESP_TYPE = 2,
    PARSE_ERROR = 3,
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

    std::vector<std::string> redis_command;
private:
    STATUS parse_arrays(const std::string&, std::vector<std::string>&);

public:
    // Decoder is non-copyable.
    Decoder(const Decoder &) = delete;
    Decoder operator= (const Decoder &) = delete;
};

class Encoder {
    // I don't know how to do that yet.
};

} // namespace SimpleRESP

#endif //SIMPLE_RESP_SIMPLE_RESP_H
