#!/bin/bash
docker build -t simple_pwn .
docker run -d -p 9696:9696 simple_pwn
