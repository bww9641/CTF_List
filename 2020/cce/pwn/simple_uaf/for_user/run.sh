#!/bin/bash
docker build -t simple_uaf .
docker run -d -p 7714:7714 simple_uaf
