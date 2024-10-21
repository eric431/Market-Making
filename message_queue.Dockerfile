# Dockerfile for message queue subsytem based on an ubuntu linux OS

FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openssh \
    g++
