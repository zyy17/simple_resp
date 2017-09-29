#include <iostream>
#include <cassert>

#include "simple_resp.h"

// TODO: Maybe use test framework (like gtest) will be graceful
void DECODE_TEST_CASE_1(simple_resp::decoder &dec)
{
    std::string input("*2\r\n$4\r\nLLEN\r\n$6\r\nmylist\r\n");
    std::vector<std::string> expect{"LLEN", "mylist"};
    simple_resp::decode_result result = dec.decode(input);
    assert(result.status == simple_resp::OK);
    assert(result.response == expect);
    std::cout << "=> PASS " << __FUNCTION__ << std::endl;
}

void DECODE_TEST_CASE_2(simple_resp::decoder& dec)
{
    std::string input("*3\r\n:1\r\n:2\r\n:3\r\n");
    std::vector<std::string> expect{":1", ":2", ":3"};
    simple_resp::decode_result result = dec.decode(input);
    assert(result.status == simple_resp::OK);
    assert(result.response == expect);
    std::cout << "=> PASS " << __FUNCTION__ << std::endl;
}

void DECODE_TEST_CASE_3(simple_resp::decoder& dec)
{
    std::string input("*5\r\n:1\r\n:2\r\n:3\r\n:4\r\n$6\r\nfoobar\r\n");
    std::vector<std::string> expect{":1", ":2", ":3", ":4", "foobar"};
    simple_resp::decode_result result = dec.decode(input);
    assert(result.status == simple_resp::OK);
    assert(result.response == expect);
    std::cout << "=> PASS " << __FUNCTION__ << std::endl;
}

void DECODE_TEST_CASE_4(simple_resp::decoder& dec)
{
    std::string input("*3\r\n$3\r\nSET\r\n$1\r\na\r\n$1\r\nb\r\n:4\r\n$3\r\nfoo\r\n");
    std::vector<std::string> expect{"SET", "a", "b"};
    simple_resp::decode_result result = dec.decode(input);
    assert(result.status == simple_resp::OK);
    assert(result.response == expect);
    std::cout << "=> PASS " << __FUNCTION__ << std::endl;
}

void ENCODE_TEST_CASE_1(simple_resp::encoder& enc)
{
    std::vector<std::string> args = {"SET", "a", "b"};
    std::string expect("*3\r\n$3\r\nSET\r\n$1\r\na\r\n$1\r\nb\r\n");
    simple_resp::encode_result result = enc.encode(simple_resp::ARRAYS, args);
    assert(result.status == simple_resp::OK);
    assert(result.response == expect);
    std::cout << "=> PASS " << __FUNCTION__ << std::endl;
}

void ENCODE_TEST_CASE_2(simple_resp::encoder& enc)
{
    std::vector<std::string> args = {"OK"};
    std::string expect("+OK\r\n");
    simple_resp::encode_result result = enc.encode(simple_resp::SIMPLE_STRINGS, args);
    assert(result.status == simple_resp::OK);
    assert(result.response == expect);
    std::cout << "=> PASS " << __FUNCTION__ << std::endl;
}

int main()
{
    simple_resp::decoder dec;
    simple_resp::encoder enc;

    DECODE_TEST_CASE_1(dec);
    DECODE_TEST_CASE_2(dec);
    DECODE_TEST_CASE_3(dec);
    DECODE_TEST_CASE_4(dec);
    ENCODE_TEST_CASE_1(enc);
    ENCODE_TEST_CASE_2(enc);

    return 0;
}
