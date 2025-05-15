#! /bin/bash

docker build ${1:+--build-arg objToCompile="$1"} -t lasdimg .

docker run \
    -it \
    --name LASDdev \
    --rm \
    lasdimg