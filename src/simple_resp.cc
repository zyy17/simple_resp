
#include "simple_resp.h"

namespace SimpleRESP {

using vector_num_type = std::vector<std::string>::size_type;
using string_num_type = std::string::size_type;

STATUS Decoder::decode(const std::string &input) {
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

STATUS Decoder::parse_arrays(const std::string &input, std::vector<std::string>& redis_command)
{
    PARSE_STATE state = INIT;
    std::string token;
    string_num_type bulk_string_length = 0;
    vector_num_type args_num = 0;

    if (*input.begin() != ARRAYS) {
        return PARSE_ERROR;
    }

    for (auto it = input.begin() + 1, token_start = input.begin() + 1; it != input.end(); it++) {
        if (*it == '\r' && *(it + 1) == '\n') {
            token = std::string(token_start, it);
            switch (state) {
                case INIT:
                    args_num = static_cast<vector_num_type>(std::stoi(token));
                    state = PARSE_ELEMENTS;
                    break;
                case PARSE_ELEMENTS:
                    switch (token[0]) {
                        case INTEGERS:
                            redis_command.emplace_back(token);
                            break;
                        case BULK_STRINGS:
                            bulk_string_length = static_cast<string_num_type>(std::stoi(token.substr(1, token.length() - 1)));
                            state = PARSE_BLUK_STRINGS;
                            break;
                        default:
                            return PARSE_ERROR;
                    }
                    break;
                case PARSE_BLUK_STRINGS:
                    if (bulk_string_length <= 0) {
                        return PARSE_ERROR;
                    }
                    if (token.length() != bulk_string_length) {
                        return PARSE_ERROR;
                    }
                    redis_command.emplace_back(token);
                    state = PARSE_ELEMENTS;
                    break;
            }
            it = it + 1;             // skip '\n'
            token_start = it + 1;    // point to next char (not '\r' or '\n')
            continue;
        }
    }

    if (args_num > 0 && redis_command.size() == args_num) {
        return OK;
    } else {
        return PARSE_ERROR;
    }
}

} // namespace SimpleRESP