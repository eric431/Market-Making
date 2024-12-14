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
    libcurl4-openssl-dev \
    nlohmann-json3-dev

RUN mkdir ~/Coinbase_API && cd ~/Coinbase_API

COPY ../../API/secret_key.txt .
COPY ../../API/pub_key.txt .
    
RUN echo "export API_KEY=$(cat ./pub_key.txt)" | cat >> ~/.bashrc
RUN echo "export SECRET_KEY=$(cat ./secret_key.txt)" | cat >> ~/.bashrc
RUN source ~/.bashrc

# COPY ./build/FeedHandler /FeedHandler

# WORKDIR /FeedHandler