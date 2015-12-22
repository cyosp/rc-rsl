# rc-rsl
Drive Conrad RSL switch

![Stable version](https://img.shields.io/badge/stable-0.1.0-blue.svg)
[![BSD-3 license](https://img.shields.io/badge/license-BSD--3--Clause-428F7E.svg)](https://tldrlegal.com/license/bsd-3-clause-license-%28revised%29)

# How To Compile

Steps are to perform directly on the [Raspberry Pi](https://www.raspberrypi.org/products/):

1. Get [wirinPi](http://wiringpi.com/) library
```bash
# Create directory which will host sources
mkdir -p ~/src
# Move into this directory
cd ~/src
# Get sources
git clone git://git.drogon.net/wiringPi
# Move into wiringpi directory
cd ~/src/wiringpi
# Build the library
./build
```
2. Get [rc-rsl](https://github.com/cyosp/rc-rsl) repository
```bash
# Move into sources directory
cd ~/src
# Get sources
git clone https://github.com/cyosp/rc-rsl
```
3. Get RCSwitch files from [GitHub](http://github.com) repository: [sirkubax/rcswitch-pi](http://github.com/sirkubax/rcswitch-pi):
```bash
# Move into rc-rsl directory
cd ~/src/rc-rsl
# Get RCSwitch files
wget https://raw.githubusercontent.com/sirkubax/rcswitch-pi/master/RCSwitch.h
wget https://raw.githubusercontent.com/sirkubax/rcswitch-pi/master/RCSwitch.cpp
```
4. Compile ans install [rc-rsl](https://github.com/cyosp/rc-rsl)
```bash
# Compile rc-rsl
make
# Install rc-rsl
sudo make install
```

# Usage

## Command line

```bash
sudo rc-rsl <pin number> <emitter id> <channel id> <command name> [repeat command]
``` 

Arguments detailed:
 * pin number

	[Raspberry Pi](https://www.raspberrypi.org/products/) pin following [wirinPi](http://wiringpi.com/) implementation
 * emitter id

	Unique id of the emitter: a number between 0 and 67108863
 * channel id

	Emitter channel: a number between 1 and 16
 * command name

	Command to send to the switch:
	* on
	* off
	* onoff (*on* and *off* in the same time)
 * repeat command

	How many times the command must be repeated

## Examples

```bash
sudo rc-rsl O 123456 1 off
sudo rc-rsl O 123456 7 on 60
```

