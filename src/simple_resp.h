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

enum STATE {
    INIT = 0,
    PARSE_ELEMENTS = 1,
    PARSE_BLUK_STRINGS = 2
};

class Decoder {
public:
    Decoder() = default;

    STATUS decode(const std::string &input) {
        STATUS status = OK;
        redis_command.erase(redis_command.begin(), redis_command.end());  // clean output buffer
        if (input.length() < 0) {
            return EMPTY_INPUT;
        }
        switch (input[0]) {
            case SIMPLE_STRINGS:
                break;
            case ERRORS:
                break;
            case INTEGERS:
                break;
            case BULK_STRINGS:
                break;
            case ARRAYS:
                status = parse_arrays(input, redis_command);
                break;
            default:
                return ILLEGAL_RESP_TYPE;
        }
        return status;
    }
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

} // SimpleRESP

#endif //SIMPLE_RESP_SIMPLE_RESP_H
