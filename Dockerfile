FROM ubuntu:22.04

RUN apt update && apt install -y g++

WORKDIR /app

COPY . .

RUN g++ -std=c++17 main.cpp -o log_server

CMD ["./log_server"]
