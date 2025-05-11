#! /bin/bash

docker build ${1:+--build-arg objToCompile="$1"} -t lasdimg .

docker run \
    -it \
    --name LASDdev \
    # --mount type=bind,src=./lib/src,dst=/interLASD/lib \
    --rm \
    lasdimg