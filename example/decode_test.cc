#include <cassert>

#include "simple_resp.h"

// TODO: Maybe use test framework (like gtest) will be graceful
void TEST_CASE_1(simple_resp::decoder& dec)
{
    std::string input("*2\r\n$4\r\nLLEN\r\n$6\r\nmylist\r\n");
    std::vector<std::string> expect{"LLEN", "mylist"};
    assert(dec.decode(input) == simple_resp::OK);
    assert(dec.decoded_redis_command == expect);
}

void TEST_CASE_2(simple_resp::decoder& dec)
{
    std::string input("*3\r\n:1\r\n:2\r\n:3\r\n");
    std::vector<std::string> expect{":1", ":2", ":3"};
    assert(dec.decode(input) == simple_resp::OK);
    assert(dec.decoded_redis_command == expect);
}

void TEST_CASE_3(simple_resp::decoder& dec)
{
    std::string input("*5\r\n:1\r\n:2\r\n:3\r\n:4\r\n$6\r\nfoobar\r\n");
    std::vector<std::string> expect{":1", ":2", ":3", ":4", "foobar"};
    assert(dec.decode(input) == simple_resp::OK);
    assert(dec.decoded_redis_command == expect);
}

void TEST_CASE_4(simple_resp::decoder& dec)
{
    std::string input("*3\r\n$3\r\nSET\r\n$1\r\na\r\n$1\r\nb\r\n:4\r\n$3\r\nfoo\r\n");
    std::vector<std::string> expect{"SET", "a", "b"};
    assert(dec.decode(input) == simple_resp::OK);
    assert(dec.decoded_redis_command == expect);
}

int main()
{
    simple_resp::decoder dec;
    TEST_CASE_1(dec);
    TEST_CASE_2(dec);
    TEST_CASE_3(dec);
    TEST_CASE_4(dec);
    return 0;
}
