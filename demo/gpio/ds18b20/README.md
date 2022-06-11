# DS18B20

A very popular digital thermometer, temperature monitoring with 2-wire or 3-wire Connections.

# Wiring

## Normal Power Mode

3-wire connection of normal power mode

* P35         -> DQ
* GND         -> GND
* 5V/3.3V     -> VDD

## Parasite Power Mode:

In parasite power mode, it's a 2-wire connection. It requires both DS18B20 GND and Vdd to be connected to ground. The DQ pin is the data/parasite power line, which requires a pull-up resistor (set by PxPU command).

It has to be noted that **not** all DS18B20 you bought online works in parasite mode. There are cheap units that output `0` only in parasite mode, in this case you need some modifications to make it work.

* P35   -> DQ
* GND   -> GND -> VDD
* 5V

## Parasite Power Mode Emulation:

In case some DS18B20 doesn't work in parasite mode, you can add one 0.1uF capacitor and one 1N4148 to achieve 2-wire connection. 
In thise way DS18B20 actually works in normal power mode

```
      +-----1N4148-|>|-----+
      |                    |
      |     |DS18B20|-VCC--+
      |     |       |      |
P35 --+-DQ--|DS18B20|     0.1uF
            |       |      |
GND ----GND-|DS18B20|-GND--+
```

