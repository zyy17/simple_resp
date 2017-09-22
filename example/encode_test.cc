#include <cassert>

#include "simple_resp.h"

void TEST_CASE_1(simple_resp::Encoder& enc)
{
    std::vector<std::string> args = {"SET", "a", "b"};
    std::string expect("*3\r\n$3\r\nSET\r\n$1\r\na\r\n$1\r\nb\r\n");
    assert(enc.encode(simple_resp::ARRAYS, args)== expect);
}

void TEST_CASE_2(simple_resp::Encoder& enc)
{
    std::vector<std::string> args = {"OK"};
    std::string expect("+OK\r\n");
    assert(enc.encode(simple_resp::ARRAYS, args) == expect);
}

int main()
{
    simple_resp::Encoder enc;
    TEST_CASE_1(enc);
    TEST_CASE_2(enc);
    return 0;
}
