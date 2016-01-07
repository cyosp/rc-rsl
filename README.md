# rc-rsl
Drive Conrad RSL switch

![Stable version](https://img.shields.io/badge/stable-1.0.3-blue.svg)
[![BSD-3 license](https://img.shields.io/badge/license-BSD--3--Clause-428F7E.svg)](https://tldrlegal.com/license/bsd-3-clause-license-%28revised%29)

# How To Compile

Steps are to perform directly on the [Raspberry Pi](https://www.raspberrypi.org/products/):

* Get [wirinPi](http://wiringpi.com/) library
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
* Get [rc-rsl](https://github.com/cyosp/rc-rsl) repository
```bash
# Move into sources directory
cd ~/src
# Get sources
git clone https://github.com/cyosp/rc-rsl
```
* Compile ans install [rc-rsl](https://github.com/cyosp/rc-rsl)
```bash
# Move into sources directory
cd ~/src/rc-rsl
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
# Pairing a switch with remote control id: 123456 and channel: 7
sudo rc-rsl O 123456 7 on 6
# Switch off a switch with remote control id: 123456 and channel: 7
sudo rc-rsl O 123456 7 off
# Switch on a switch with remote control id: 123456 and channel: 7
sudo rc-rsl O 123456 7 on
# Unbind a switch with remote control id: 123456 and channel: 7
sudo rc-rsl O 123456 7 onoff 6
sudo rc-rsl O 123456 7 off 6
```
## License

**[rc-rsl](https://github.com/cyosp/rc-rsl)** is released under the BSD 3-Clause License. See the bundled `LICENSE.md` for details.