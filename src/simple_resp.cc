#include "simple_resp.h"

namespace simple_resp {

using vector_num_type = std::vector<std::string>::size_type;
using string_num_type = std::string::size_type;

STATUS decoder::decode(const std::string &input)
{
    STATUS status = OK;
    decoded_redis_command.erase(decoded_redis_command.begin(), decoded_redis_command.end());  // clean output buffer
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
            status = parse_arrays(input, decoded_redis_command);
            break;
        default:
            return INVAILID_RESP_TYPE;
    }
    return status;
}

STATUS decoder::parse_arrays(const std::string &input, std::vector<std::string>& redis_command)
{
    PARSE_STATE state = INIT;
    std::string token;
    string_num_type bulk_string_length = 0;
    vector_num_type args_num = 0;

    if (*input.begin() != ARRAYS) {
        return INVAILID_RESP_TYPE;
    }

    for (auto it = input.begin() + 1, token_start = input.begin() + 1; it != input.end(); it++) {
        if (args_num > 0 && redis_command.size() == args_num) {
            return OK;
        }
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
                            return INVAILID_RESP_FORMAT;
                    }
                    break;
                case PARSE_BLUK_STRINGS:
                    if (bulk_string_length <= 0) {
                        return INVAILID_RESP_FORMAT;
                    }
                    if (token.length() != bulk_string_length) {
                        return INVAILID_RESP_FORMAT;
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
        return UNKNOWN_INTERNAL_ERROR;
    }
}

std::string encoder::encode(const RESP_TYPE &type, const std::vector<std::string> &args)
{
    std::string response;

    switch (type) {
        case SIMPLE_STRINGS:
            response = "+" + args[0] + "\r\n";  // only takes the first element and ignore rest
            break;
        case ERRORS:
            response = "-" + args[0] + "\r\n";  // only takes the first element and ignore rest
            break;
        case INTEGERS:
            break;
        case BULK_STRINGS:
            break;
        case ARRAYS:
            response = "*" + std::to_string(args.size()) + "\r\n";
            for (auto it = args.begin(); it != args.end(); ++it) {
                response += "$" + std::to_string(it->length()) + "\r\n" + *it + "\r\n";
            }
            break;
    }
    return response;
}
} // namespace simple_resp
