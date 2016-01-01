#include "RCSwitch.h"
#include <iostream>	// cout + cerr + endl
#include <cstdlib>	// atoi
#include <unistd.h>	// setuid
#include <stdio.h>	// perror
#include <vector>	// vector
#include <bitset>	// bitset
#include <math.h>	// ceil

using namespace std;

#define version "0.1.0"

#define MAX_PIN 16
#define MAX_EMITTER ((1 << 26) - 1)
#define MAX_CHANNEL 16

#define STR_COMMAND_OFF		"off"
#define STR_COMMAND_ON		"on"
#define STR_COMMAND_ONOFF	"onoff"

#define COMMAND_OFF		0
#define COMMAND_ON		1
#define COMMAND_ONOFF	2

void usage( char ** argv )
{
  cout << "Usage: " << argv[0] << " v" << version << ": <pin number> <emitter id> <channel id> <command name> [repeat command]" << endl
  << " <pin number> wiringPi pin number " << endl
  << " <emitter id> Unique id of the emitter: a number between 0 and " << MAX_EMITTER << endl
  << " <channel id> Emitter channel: a number between 1 and " << MAX_CHANNEL << endl
  << " <command name> Command to send to the switch: on, off or onoff" << endl
  << " [repeat command] How many times the command must be repeated" << endl
  << endl;
}

void send( RCSwitch & rcSwitch , int emitter, int receiver, bool turnOn)
{

}

int main( int argc , char * argv[] )
{
	//
	// Check input arguments
	// Only 4 or 5 are managed
	//
	if( argc != 5 && argc != 6 )
	{
		usage( argv );
		return 1;
	}

	int pin        = atoi( argv[1] );
	int emitter    = atoi( argv[2] );
	int channel    = atoi( argv[3] );
	string command = argv[4];
	int repeat     = 0;

	// Set repeat number if enough arguments
	if( argc == 6 ) repeat = atoi( argv[5] );

	//
	// Check input parameters
	//
	bool canContinue = true;

	if( pin < 0 || pin > MAX_PIN )
	{
		cerr << "Invalid argument: pin number must be between 0 and " << MAX_PIN << endl;
		canContinue = false;
	}

	if( emitter < 0 || emitter > MAX_EMITTER )
	{
		cerr << "Invalid argument: emitter id must be between 0 and " << MAX_EMITTER << endl;
		canContinue = false;
	}

	if( channel <= 0 || channel > MAX_CHANNEL )
	{
		cerr << "Invalid argument: channel must be between 1 and " << MAX_CHANNEL << endl;
		canContinue = false;
	}

	int commandId = COMMAND_OFF;
	if( command != STR_COMMAND_ON && command != STR_COMMAND_OFF && command != STR_COMMAND_ONOFF )
	{
		cerr << "Invalid argument: command must be: on, off or onoff" << endl;
		canContinue = false;
	}
	else
	{
		if( command == STR_COMMAND_ON )	commandId = COMMAND_ON;
		else if( command == STR_COMMAND_ONOFF)	commandId = COMMAND_ONOFF;
	}

	// Check if program can continue
	if( ! canContinue )
	{
		usage( argv );
		return 2;
	}

	// Check if program has been run as root
	if( setuid( 0 ) )
	{
		perror( "setuid" );
		cerr << argv[0] << " must be run as root" << endl;
		return 3;
	}

	//
	// Initialize wiringPi library
	// Print instructions if necessary
	//
	if( wiringPiSetup() == -1 )
	{
		cerr << "WiringPi library not found, please install it:" << endl
		<< " mkdir -p ~/src && cd ~/src" << endl
		<< " git clone git://git.drogon.net/wiringPi" << endl
		<< " cd ~/src/wiringpi" << endl
		<< " ./build" << endl;
		return 4;
	}

	//
	// Initialize RCSwitch
	//
	RCSwitch rcSwitch = RCSwitch();
	rcSwitch.enableTransmit( pin );

	//
	// Configure RCSwitch
	//
	rcSwitch.setPulseLength( 710 );
	rcSwitch.setProtocol( 2 );

	// Code structure
	// [2 bits fixed/unique for each remote] + [2 bits switch position] + [4 bits on/off/onoff per channel] + [24 bits fixed/unique for each remote]

	vector<string> bitsFrom25to30 =
	{
		//
		// Switch position: 1
		//

		// Channel 1
		"000001",	// Off
		"001110",	// On
		"001001",	// OnOff

		// Channel 2
		"101110",	// Off
		"100110",	// On
		"100001",	// OnOff

		// Channel 3
		"011110",	// Off
		"010110",	// On
		"010001",	// OnOff

		// Channel 4
		"111110",	// Off
		"110110",	// On
		"11????",	// OnOff

		//
		// Switch position: 2
		//

		// Channel 1
		"001101",	// Off
		"000101",	// On
		"000011",	// OnOff

		// Channel 2
		"100101",	// Off
		"101001",	// On
		"101101",	// OnOff

		// Channel 3
		"010101",	// Off
		"011001",	// On
		"011101",	// OnOff

		// Channel 4
		"110101",	// Off
		"111001",	// On
		"11????",	// OnOff

		//
		// Switch position: 3
		//

		// Channel 1
		"000100",	// Off
		"001000",	// On
		"001100",	// OnOff

		// Channel 2
		"101000",	// Off
		"100000",	// On
		"100100",	// OnOff

		// Channel 3
		"011000",	// Off
		"010000",	// On
		"010100",	// OnOff

		// Channel 4
		"111000",	// Off
		"110000",	// On
		"11????",	// OnOff

		//
		// Switch position: 4
		//

		// Channel 1
		"001010",	// Off
		"000010",	// On
		"000110",	// OnOff

		// Channel 2
		"100010",	// Off
		"101100",	// On
		"101010",	// OnOff

		// Channel 3
		"010010",	// Off
		"011100",	// On
		"011010",	// OnOff

		// Channel 4
		"110010",	// Off
		"111100",	// On
		"11????"	// OnOff
	};

	// Compute switch position
	int switchPosition = ceil( (float) channel / 4 );

	//cout << "Switch position: " << switchPosition << endl;
	//cout << "Vector index: " << (switchPosition - 1) * 12 + commandId << endl;

	// Define bits for switch position, command and channel
	bitset<32> switchPositionCommandChannelBitset( bitsFrom25to30[ (switchPosition - 1) * 12 + commandId ] + string( "000000000000000000000000" ) );

	bitset<32> emitterBitset( emitter );

	// Get emitter lower bits
	bitset<32> emitterLowBitset( emitterBitset  & bitset<32>("00111111111111111111111111") );

	// Get emitter higher bits
	bitset<32> emitterHighBitset( emitterBitset & bitset<32>("11000000000000000000000000") );
	// Shift 6 bits to reach first two bits in code
	emitterHighBitset <<= 6;

	// Create code in bits
	bitset<32> codeBitset = emitterHighBitset | switchPositionCommandChannelBitset | emitterLowBitset;

	// Convert code bits into integer
	int code = (int)( codeBitset.to_ulong() );

	//cout << "Binary code to send: " << codeBitset.to_string() << endl;
	//cout << "Code to send: " << code << endl;

	// Repeat send command
	for( int i = 1 ; i <= repeat + 1 ; i++ )
	{
		rcSwitch.send( code , 32 );
	}

	cout << "Done" << endl;

    return 0;
}
