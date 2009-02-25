/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

// Include
#include "Util.h"

int Printf(const char * format,...)
{
	// Save the list of parameters
	va_list ap;

	// Start the processing
	va_start(ap, format);

	// Sucess
	int i = 0;

	// If we are logging, place to log file
	if( Logging )
		i = vfprintf(LoggingFile, format, ap);

	// If we are not in silence, print to stdio
	if( !Logging && !Silence )
		i = vprintf(format, ap);

	return i;
}

int _Printf(const char * format,...)
{
	// Save the list of parameters
	va_list ap;

	// Start the processing
	va_start(ap, format);

	// Sucess
	int i = 0;

	// If we are logging, place to log file
	if( Logging )
		i = vfprintf(LoggingFile, format, ap);

	// If we are not in silence, print to stdio
	i = vprintf(format, ap);

	return i;
}