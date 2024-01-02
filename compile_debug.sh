#!/bin/sh

gcc ./src/*.c ./debug/*.c  -o ./debug/a.out -std=c89 -Og -g -Wall -Wextra -pedantic -pedantic-errors &&
chmod +x ./debug/a.out  
