#!/bin/bash
docker build -t simple_cmdshell .
docker run -d -p 7147:7147 simple_cmdshell
