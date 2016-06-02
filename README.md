# megaman [![Build Status](https://travis-ci.org/manuporto/megaman.svg?branch=master)](https://travis-ci.org/manuporto/megaman)
Trabajo practico final de la materia Taller de Programacion - 75.42 de la FIUBA

## Integrantes
* [Agustina Barbetta](https://github.com/abrden)
* [Manuel Porto](https://github.com/manuporto)

## Pre-build
* CMake >= 2.8.4
* GCC
* `apt-get install libgtkmm-3.0-dev libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libbox2d-dev`

## Build
* `mkdir build && cd build/ && cmake .. && make`

## Run
* **Client:** `cd client/ && ./../build/client/client hostname port`
* **Server:** `cd server/ && ./../build/server/server port`
