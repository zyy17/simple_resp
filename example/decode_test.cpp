#include <cassert>

#include "simple_resp.h"

void TEST_CASE_1(SimpleRESP::Decoder& dec)
{
    std::string input("*2\r\n$4\r\nLLEN\r\n$6\r\nmylist\r\n");
    std::vector<std::string> expect{"LLEN", "mylist"};
    assert(dec.decode(input) == SimpleRESP::OK);
    assert(dec.redis_command == expect);
}

void TEST_CASE_2(SimpleRESP::Decoder& dec)
{
    std::string input("*3\r\n:1\r\n:2\r\n:3\r\n");
    std::vector<std::string> expect{":1", ":2", ":3"};
    assert(dec.decode(input) == SimpleRESP::OK);
    assert(dec.redis_command == expect);
}

void TEST_CASE_3(SimpleRESP::Decoder& dec)
{
    std::string input("*5\r\n:1\r\n:2\r\n:3\r\n:4\r\n$6\r\nfoobar\r\n");
    std::vector<std::string> expect{":1", ":2", ":3", ":4", "foobar"};
    assert(dec.decode(input) == SimpleRESP::OK);
    assert(dec.redis_command == expect);
}

int main()
{
    SimpleRESP::Decoder dec;
    TEST_CASE_1(dec);
    TEST_CASE_2(dec);
    TEST_CASE_3(dec);
    return 0;
}
