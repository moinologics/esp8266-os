#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

arduino-cli compile --clean --export-binaries --profile esp-12f $SCRIPT_DIR