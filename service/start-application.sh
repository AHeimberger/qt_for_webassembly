#!/bin/sh

cd /home/pi/wasm_project/application
python3 -m http.server ${port}
