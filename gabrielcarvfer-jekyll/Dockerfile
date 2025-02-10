FROM python:3.9 AS gabrielcarvfer-base
WORKDIR .
RUN apt-get update

FROM gabrielcarvfer-base as gabrielcarvfer-jekyll
WORKDIR .
RUN apt-get update
RUN apt-get install -y make rustc g++ ruby ruby-dev jekyll
