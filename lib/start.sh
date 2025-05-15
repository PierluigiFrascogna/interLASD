#!/bin/bash

# WATCH_DIR="./"
MAKE_DIR="./src"
EXE_FILE="./src/main"

# # Compilazione iniziale prima di entrare nel ciclo
# echo "🔧 Compilando il progetto per la prima volta..."
# make -C $MAKE_DIR && echo "🚀 Running..." && $EXE_FILE

# echo "🔄 Monitoring changes in $WATCH_DIR (and subfolders) for .cpp and .hpp files..."

# # Monitora tutti i file e filtra nel ciclo
# inotifywait --monitor --recursive -event modify,create,delete,move --format '%w%f' "$WATCH_DIR" | while read file; do
#     # Verifica estensione
#     if [[ "$file" == *.cpp || "$file" == *.hpp ]]; then
#         clear
#         echo "📄 File modificato: $file"
#         echo "🔧 Compilazione..."
#         make -C $MAKE_DIR
#         echo "🚀 Running..."
#         $EXE_FILE
#         echo "🔄 In attesa di nuove modifiche..."
#     fi
# done


clear
echo "🧼 Pulizia..." && \
make clean -C $MAKE_DIR && \
echo "🔧 Compilazione..." && \
make -C $MAKE_DIR ${OBJTOCOMPILE:-} && \
echo "🚀 Running..." && \
$EXE_FILE

