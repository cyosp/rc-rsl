# rc-rsl
Drive Conrad RSL switch with Raspberry Pi

![Stable version](https://img.shields.io/badge/stable-2.0.0-blue.svg)
[![BSD-3 license](https://img.shields.io/badge/license-BSD--3--Clause-428F7E.svg)](https://tldrlegal.com/license/bsd-3-clause-license-%28revised%29)

# Prerequisite

Starting version 2.0.0, Buster is the minimum Raspbian version needed 

# How to install

A [Debian](https://www.debian.org) package is available at [http://packages.cyosp.com/debian](http://packages.cyosp.com/debian) for:
 * [Buster](https://www.debian.org/releases/buster/) version
 * `armhf` architecture

Steps to install it are:

 * Receive CYOSP GPG key from key server:

    `sudo gpg --keyserver hkp://pool.sks-keyservers.net --recv-keys D71923F61CC21365`

 * Add GPG key to apt:

    `sudo gpg -a --export D71923F61CC21365 | apt-key add -`

 * Add CYOSP repository:

    ```bash
    sudo cat << EOF > /etc/apt/sources.list.d/cyosp.list

    # CYOSP packages
    deb http://packages.cyosp.com/debian buster main

    EOF
    ```

 * Update repository database:

    `sudo apt update`

 * Install package:
 
    `sudo apt install rc-rsl`

# How to compile and install

Steps are to perform directly on the [Raspberry Pi](https://www.raspberrypi.org/products/):

* Get [rc-rsl](https://github.com/cyosp/rc-rsl) repository
```bash
# Move into sources directory
cd ~/src
# Get sources
git clone https://github.com/cyosp/rc-rsl
```
* Install dependencies
```bash
sudo apt install libgpiod-dev libgpiod2
```
* Compile and install [rc-rsl](https://github.com/cyosp/rc-rsl)
```bash
# Move into sources directory
cd ~/src/rc-rsl
# Compile rc-rsl
make
# Install rc-rsl
sudo make install
```

# How to cross compile

## Cross compilation toolchain
First, a cross compilation toolchain for `arm-linux-gnueabihf` must be installed.

This link could help you if needed: [https://github.com/Pro/raspi-toolchain](https://github.com/Pro/raspi-toolchain).

## /usr and /lib folders
Then copy file systems `/usr` and `/lib` from latest Raspbian image (Buster the 8th december 2019) into a `rootfs` folder like: `~/raspberrypi/rootfs`.

## Add GPIOD library
Last, add package content: `libgpiod-dev` and `libgpiod2` into `~/raspberrypi/rootfs` folder.

## Make cross compilation
Now, run:
`make CROSS_COMPILE=arm-linux-gnueabihf SYSTEM_ROOT=~/raspberrypi/rootfs`

# Usage

## Command line

```bash
sudo rc-rsl <GPIO device> <GPIO offset> <emitter id> <channel id> <command name> [repeat command]
``` 

Arguments detailed:
 * GPIO device
 
    Raspberry Pi GPIO pin headers are available through: `/dev/gpiochip0`.
    
 * GPIO offset
 
    Pin offset for GPIO device.
    
    Raspberry Pi mapping can be found here: [https://www.raspberrypi.org/documentation/usage/gpio/](https://www.raspberrypi.org/documentation/usage/gpio/).

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

	How many times the command must be repeated : a number greater than 0

## Examples

```bash
# Pairing a switch with remote control id: 123456 and channel: 7
sudo rc-rsl /dev/gpiochip0 17 123456 7 on 6
# Switch off a switch with remote control id: 123456 and channel: 7
sudo rc-rsl /dev/gpiochip0 17 123456 7 off
# Switch on a switch with remote control id: 123456 and channel: 7
sudo rc-rsl /dev/gpiochip0 17 123456 7 on
# Unbind a switch with remote control id: 123456 and channel: 7
sudo rc-rsl /dev/gpiochip0 17 123456 7 onoff 6
sudo rc-rsl /dev/gpiochip0 17 123456 7 off 6
```
## License

**[rc-rsl](https://github.com/cyosp/rc-rsl)** is released under the BSD 3-Clause License. See the bundled `LICENSE.md` for details.