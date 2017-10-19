## Overview

simple_resp is a simple RESP(REdis Serialization Protocol) decode and encode library base on C++11.

## API

As the name says, simple_resp is quite **simple**. It just has two basic class: `decoder` and `encoder`.
It will always follow KISS principle and just use basic C++11 features.


## How to Run

- g++ (C++11 supported, maybe g++ > 4.8);

- compile command:

    simple_resp is managed by CMake. You can compile the project as following commands:

      $ mkdir build && cd build
      $ cmake ..
      $ make

    You can run simple unit test:

      $ make test

## WIP

- complete RESP support
