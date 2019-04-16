## Building an AVR application to communicate with the USART peripheral
This project walks you through the process building an AVR application to exercise the usart peripheral on the ATMega328p microcontroller.

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
To compile our source code we want to create a Makefile to autmoate the process. The Makefile also converts the object files to avr compatible hex format. This hex file is then used to update the code on the microcontroller. To compile the code run the Makefile by issuing the following command:

```console
make
```


### Running the code
Now that we compiled the code we can deploy to our microcontroller.

```console
make flash
```


#### References:
https://github.com/osx-cross/homebrew-avr

http://www.linuxandubuntu.com/home/setting-up-avr-gcc-toolchain-and-avrdude-to-program-an-avr-development-board-in-ubuntu