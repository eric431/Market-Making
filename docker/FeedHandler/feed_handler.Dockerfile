# Dockerfile for feed handler subsytem based on an ubuntu linux OS

FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openssh \
    g++ \
    cmake \
    net-tools \
    libboost1.83-all-dev \
    curl \
    libssl-dev \
    libcurl4-openssl-dev

RUN mkdir ~/Coinbase_API && cd ~/Coinbase_API

COPY ../../API/priv_key.txt .
COPY ../../API/pub_key.txt .
    
# COPY ./build/FeedHandler /FeedHandler

# WORKDIR /FeedHandler