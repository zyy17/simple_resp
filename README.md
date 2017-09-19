## Overview

SimpleRESP is a simple resp(REdis Serialization Protocol) decode and encode library base on C++11.

## API

As the name says, SimpleRESP is **simple**. It just has two basic class: `Decoder` and `Encoder`.
It will always follow KISS principle and just use basic C++11 features.


## How to Run

- g++ (C++11 supported, maybe g++ > 4.8);

- compile command:

    SimpleRESP is managed by CMake. You can compile the project as following commands:

      $ mkdir build
      $ cd build ; cmake ..
      $ make

    You can run test code:

      $ ./build/decode_test

## WIP

- `decoder`

- more test cases and examples

- complete RESP support
