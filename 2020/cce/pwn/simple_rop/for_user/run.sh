#!/bin/bash
docker build -t simple_rop .
docker run -d -p 4147:4147 simple_rop
