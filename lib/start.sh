#!/bin/bash

# WATCH_DIR="./"
MAKE_DIR="./src"
EXE_FILE="./src/main"

echo "🧼 Pulizia..." && \
make clean -C $MAKE_DIR && \
echo "🔧 Compilazione..." && \
make -C $MAKE_DIR ${OBJTOCOMPILE:-} && \
echo "🚀 Running..." && \
$EXE_FILE

