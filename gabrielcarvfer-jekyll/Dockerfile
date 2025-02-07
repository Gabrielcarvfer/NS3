FROM python:3.9 as gabrielcarvfer-base
WORKDIR .
RUN apt-get update

FROM gabrielcarvfer-base as gabrielcarvfer-jekyll:latest
WORKDIR .
RUN apt-get update
RUN apt-get install -y make rustc g++ ruby ruby-dev jekyll