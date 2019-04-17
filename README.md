## Building an AVR application to communicate with the USART peripheral
This project walks you through the process building an AVR application to exercise the usart peripheral on the ATMega328p microcontroller. The USART peripheral can be used to interface with many different types of sensors, modems, ic(s), and microcontrollers. Refer to your microcontroller's datasheet to determine optiomal baud rate to ensure maximum data rate and minimal error rate.

### Prerequisites:

### Installing avr-gcc

Installing avr-gcc on MacOS w/Brew
```console
brew tap osx-cross/avr
brew install avr-gcc
```
verify installation
```console
avr-gcc --version
```

### Installing Avrdude on MacOS w/Brew
```console
brew install avrdude
or
brew install avrdude --with-usb
```
verify installation
```console
avrdude -v
```

### The code
The code below initializes the led/clock/usart modules and prepares them for use. The while loop accumulates data on the USART port until a carriage return is received. Once received the console echoes back the data received. The module also toggles a led on the microcontroller once per second. 

```c++
void main()
{
    // led port
    DDRB |= _BV(PB5);

    clock_init();
    config_init();
    usart_driver_init();
    sei();
    usart_transmit_string("spike_328p_usart started...\r\n");
    usart_transmit_string("enter some text followed by a carriage return\r\n");
    while(true){

        usart_driver_tick();
        if(timeout()){
            // toggle led
            PORTB ^= _BV(PB5);
            set_timer(1000);
        }
    }
}
```

Notice the line of code listed below. This sets the global interrupt flag in SREG enabling interrupts. Since we are using the AVR's service interrupt routine to detect data on the USART line we need to set this flag.
```c++
sei();
```

### Compiling the code
To compile the source code we need to create a Makefile to autmoate the process. Makefiles allow us to place all build/clean/flash commands into one easy to use file. Each microcontroller has a unique set of parameters prior to compiling and deploying. These commands are listed a the top of the Makefile and are easily changed.

Below is a snippet of Makefile parametes that would be changed to target your project.
```console
# parameters (make changes accordingly)
# project name
PRJ = main
# avr mcu
MCU = atmega328p
# mcu clock frequency
CLK = 16000000
# avr programmer (and port if necessary)
# e.g. PRG = usbtiny -or- PRG = arduino -P /dev/tty.usbmodem411
PRG = usbtiny
```

Now that your Makefile is complete issue the make from the command start the build process.

```console
make
```


### Loading the code
Now that we compiled the code we can deploy to our microcontroller.

```console
make flash
```


#### References:
https://github.com/osx-cross/homebrew-avr

http://www.linuxandubuntu.com/home/setting-up-avr-gcc-toolchain-and-avrdude-to-program-an-avr-development-board-in-ubuntu