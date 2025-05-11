#! /bin/bash

docker build ${1:+--build-arg objToCompile="$1"} -t lasdimg ./src

docker run \
    -it \
    --name LASDdev \
    --mount type=bind,src=./src/app,dst=/interLASD/app \
    --rm \
    lasdimg