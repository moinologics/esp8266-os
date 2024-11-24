#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

### pass --clean flag to rebuild from scratch

ESP_12F_FQBN=esp8266:esp8266:nodemcuv2


FQBN=$ESP_12F_FQBN

BUILD_DIR_PREFIX=${FQBN//\:/.}

## sketch build (local deps)
#arduino-cli compile --export-binaries --profile esp-12f "$@" $SCRIPT_DIR

## build with global deps
arduino-cli compile \
  --export-binaries \
  --fqbn $ESP_12F_FQBN \
  "$@" $SCRIPT_DIR \
  && echo "" && du -sh build/$BUILD_DIR_PREFIX/*
