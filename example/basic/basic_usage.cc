#include <iostream>

#include "simple_resp.h"

int main()
{
    simple_resp::decoder dec;
    std::string input("*3\r\n$3\r\nSET\r\n$1\r\na\r\n$1\r\nb\r\n:4\r\n$3\r\nfoo\r\n");
    if (dec.decode(input) == simple_resp::OK) {
        std::cout << "decode OK" << std::endl;
        for (const auto &c : dec.decoded_redis_command) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "decode FAILED for input [" << input << "]" << std::endl;
    }
    return 0;
}
