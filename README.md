README
======

```
    RaspberryPi 64-bit:         https://www.raspberrypi.org/forums/viewtopic.php?t=275370
    Issue List:                 https://github.com/raspberrypi/Raspberry-Pi-OS-64bit
    Install Wasmer:             curl https://get.wasmer.io -sSfL | sh
    Install WasmTime:           curl https://wasmtime.dev/install.sh -sSf | bash
    
    Install WiringPi:           git clone https://github.com/Milliways2/wPi.git
                                gpio -v
                                sudo apt-get purge wiringpi
                                hash -r
                                cd wPi
                                ./build

    Install SenseHat:           git clone git@github.com:AHeimberger/SenseHat.git
                                make
                                sudo make install
                                make clean

                                cd Exemples
                                make
                                ./exemple
    
    Qt5 Default:                sudo apt-get install qt5-default \
                                    libqt5websockets5 \
                                    libqt5websockets5-dev \
                                    qtdeclarative5-dev

    Change Keyboard Layout:     sudo raspi-config
    Set Wireless:               https://www.raspberrypi.org/documentation/configuration/wireless/headless.md
    Set SSH:                    /boot/ssh
    Set I2C Enabled:            sudo raspi-config / Interfacing Options / I2C Enabled

    Services:                   sudo cp ./service/*.service /etc/systemd/system/
                                sudo systemctl daemon-reload
                                sudo systemctl enable server.service
                                sudo systemctl enable application.service

                                sudo systemctl start server.service
                                sudo systemctl status server.service
```


References:

- [Qt5](https://doc.qt.io/qt-5/wasm.html)
- [WiringPi](http://wiringpi.com/download-and-install/)
- [wPi](https://github.com/Milliways2/wPi)
- [Wiki Qt](https://wiki.qt.io/Qt_for_WebAssembly)
- [History NaCL, Asm.js](https://www.qt.io/blog/2015/09/25/qt-for-native-client-and-emscripten)
