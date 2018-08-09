# psx avr modchip

-- this project ist still under construction --
the source code is definitively in a heavy experimental state at the moment :)

## Introduction
At first I have to say, I'm not a great friend of all the arduino environment out 
there. Don't get me wrong, it's great to make things easier for beginners so
more people get into programming embedded systems like that. But I don't like 
the idea to need a bigger microcontroller just because I'm using the Arduino
library with it's C++ wrapper classes which needs way more space than plain C
and is less performant. 

With this background, I searched for an implementation of an Playstation 1 Modchip
based on ATMEL 8bit microcontrollers. The best project I have found so far is
that one from **PSNEE** on [github](https://github.com/kalymos/PsNee). The guys
did a very well job and a lot of research to create a functional modchip based
on atmel microcontrollers. So thanks a lot for the inspiration!

Like I said at the beginning, I don't like the Arduion IDE with it's C++ wrapper
classes, I saw a challenge to myself to create my own modchip with plain C.

## Features
In this early stage the Modchip injects the region code at the boot sequence
of the playstation for a certain time. So currently the injection is only based
on the correct timing for the injection. 

The Pins **SUBQ** and **SQCK** for detecting on which sector of the CD the 
reader (lens) is located, is currently not used!

## Target Hardware
The software is written for the **ATTiny85** but can easily ported to every AVR
Microcontroller. 

If you want to use for example the **ATTIny85 - Digispark Rev.3** board, the 
installed bootloader [micronucleus](https://github.com/micronucleus/micronucleus) 
can not be used for this project. The bootloader waits for a certain time after
powerup to give you the chance to upload your code. Only after this timeout the
code on the chip will be executed. The problem here is that the timeout is 
to long and the controller will miss the point when it should perform the injection
to trick the copy protection.

## Supported/Tested Playstation
Currently the only Playstation which I own is the **SCPH-7502 (Board PU-22)**, so
at the moment is this the only tested model. But normally all Playstations with
a PU-22 or newer Board should work. 

Please take a look at [Playstation Models](https://en.wikipedia.org/wiki/PlayStation_models)
if youre not sure which Board Version your Playstation may have. 

## How it works
A really good video which shows how the protection works can be found on 
[youtube (Channel: Technology Connections)](https://www.youtube.com/watch?v=XUwSOfQ1D3c)

Okay, so now more detailed what we do to trick the copy protection... The 
**Data** Pin expects a stream with 250 bps (Bits-per-second) which contains the
region code. So generally we can say that one Bit must have a pulsewidth of
4ms. So the a stream must look like this example: 


```
       1       0       1       0       0       1  
    _______         _______                 _______
   |       |_______|       |_______________|       |  
    <-4ms-> <-4ms-> <-4ms-> <-4ms-> <-4ms-> <-4ms->  

```

So now we know how he bits should look like, lets concentrate on the bytes. We
do an example with the European Region Code (SCEE). 

```
    Letter  ASCII-Hex   ASCII-Binary
    S         0x53      0101 0011
    C         0x43      0100 0011
    E         0x45      0100 0101
    E         0x45      0100 0101
```

## Pinout
this is the pinout on the playstation 1 mainboard:

```
    C325 Minus      GND             -> our Ground connection
    C325 Plus       3.3V            -> do not use 5V as supply voltage!

    IC304 Pin24     SUBQ            -> data-line for indication the position of the lens
    IC304 Pin26     SQCK            -> data-clock for SUBQ

    IC732 Pin5      Gate (WFCK)     -> needed for PU22 or newer boards 
                                       (modulatet on the data-line for HIGH-Level)
    IC732 Pin42     Data (CEO)      -> data-line where we inject the region code
```




