# Dockerfile for feed handler subsytem based on an ubuntu linux OS

FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openssh \
    g++ \
    cmake \
    net-tools \
    libboost-all-dev 

RUN mkdir ~/Coinbase_API && cd ~/Coinbase_API

COPY ../../Coinbase_API/priv_key.txt .
COPY ../../Coinbase_API/pub_key.txt .
    
# COPY ./build/FeedHandler /FeedHandler

# WORKDIR /FeedHandler