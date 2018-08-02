# psx avr modchip

-- this project ist still under construction --
the source code is definitively in a heavy experimental state at the moment :)

## Features
In this early stage the Modchip injects the region code at the boot sequence
of the playstation for a certain time. 

## Target Hardware
The software is written for the **ATTiny85**, especially for the **ATTiny85 - Digispark Rev.3**
(see [link](https://www.az-delivery.de/products/digispark-board?ls=de#description). 

For the schematic see this
[link](https://s3.amazonaws.com/digistump-resources/files/97a1bb28_DigisparkSchematic.pdf). 
But watch out, the **Diode D3** is **mirrored**! On the PCB the Diode is polarized
like it should: from the 5V USB Connector to the 5V Supply of the PCB. So it's just
a schematic-drawn-failure. 

## Supported/Tested Playstation
Currently the only Playstation which I own is the *SCPH-7502 (Board PU-22)*, so
at the moment is this the only tested model. But normally all Playstations with
a PU-22 or newer Board should work. 

Please take a look at [Playstation Models](https://en.wikipedia.org/wiki/PlayStation_models)
if youre not sure which Board Version your Playstation may have. 

## Instructions
A really good video which shows how the protection works can be found on 
[youtube (Technology Connections)](https://www.youtube.com/watch?v=XUwSOfQ1D3c)

## Pinout
this is the pinout on the playstation 1 mainboard:

    C325 Minus      GND
    C325 Plus       3.3V

    IC304 Pin24     SUBQ            -> data-line for indication the position of the lens
    IC304 Pin26     SQCK            -> data-clock for SUBQ

    IC732 Pin5      Gate (WFCK)     -> needed for PU22 or newer boards (modulatet on the data-line
    for HIGH-Level)
    IC732 Pin42     Data (CEO)      -> data-line where we inject the region code
