FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y g++ \
            make \
            libncurses5-dev

COPY . /CChess

WORKDIR /CChess

RUN make

CMD [ "./CChess" ]