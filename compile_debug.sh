#!/bin/sh

gcc ./src/*.c ./debug/*.c  -o ./debug/a.out -std=c89 -Wall -Wextra -pedantic

chmod +x ./debug/a.out
./debug/a.out
