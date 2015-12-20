#include "RCSwitch.h"
#include <iostream>	// cout + cerr + endl
#include <cstdlib>	// atoi
#include <unistd.h>	// setuid
#include <stdio.h>	// perror

using namespace std;

#define MAX_PIN 16
#define MAX_EMITTER 16777216
#define MAX_CHANNEL 16

void usage( char ** argv )
{
  cout << "Usage: " << argv[0] << " <pin number> <emitter id> <channel id> <command name> [repeat command]" << endl
  << " <pin number> wiringPi pin number " << endl
  << " <emitter id> Unique id of the emitter: a number between 0 and " << MAX_EMITTER << endl
  << " <channel id> Emitter channel: a number between 1 and " << MAX_CHANNEL << endl
  << " <command name> Command to send to the switch: on, off or onoff" << endl
  << " [repeat command] How many times the command must be repeated" << endl
  << endl;
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

	if( channel < 0 || channel > MAX_CHANNEL )
	{
		cerr << "Invalid argument: channel must be between 1 and " << MAX_CHANNEL << endl;
		canContinue = false;
	}

	if( command != "on" && command != "off" && command != "onoff" )
	{
		cerr << "Invalid argument: command must be: on, off or onoff" << endl;
		canContinue = false;
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

    return 0;
}
