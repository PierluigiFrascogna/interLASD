# Use the official Ubuntu 24.04 image as the base image
FROM ubuntu:24.04

LABEL Description="Primo progetto per LASD 2025" \
      Version="1.0" \
      Maintainer="Pierluigi Frascogna"

# Aggiorna pacchetti e installa le dipendenze per aggiungere il PPA
RUN apt update && apt install -y software-properties-common

# Aggiungi il PPA per g++-13
RUN add-apt-repository ppa:ubuntu-toolchain-r/test

# Installa g++-13, make ed il tool per notificare cambi di file
RUN apt update && apt install -y \
    g++-13 \
    make \
    inotify-tools

# Imposta g++-13 come compilatore predefinito
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100

# Crea la directory di lavoro e ci entra
WORKDIR /interLASD1/lib

# Copia la libreria e cambia i permessi di esecuzione
COPY ./lib /interLASD1/lib
RUN chmod +x /interLASD1/lib/start.sh

ARG objToCompile
ENV OBJTOCOMPILE=$objToCompile

# Command to run when the container starts
CMD ["./start.sh"]