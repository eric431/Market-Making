# Dockerfile for feed handler subsytem based on an ubuntu linux OS

FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openssh \
    g++ \
    cmake \
    net-tools \
    libboost-all-dev \