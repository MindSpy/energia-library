#ifndef LOGGING_h
#define LOGGING_h

#include <inttypes.h>
#include <stdarg.h>
#include "Arduino.h"


#define LOG_LEVEL_NOOUTPUT 0 
#define LOG_LEVEL_ERRORS 1
#define LOG_LEVEL_INFOS 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_VERBOSE 4

// default loglevel if nothing is set from user


#define CR "\r\n"
#define LOGGING_VERSION 1


/*!
* Logging is a helper class to output informations over
* RS232. If you know log4j or log4net, this logging class
* is more or less similar ;-) <br>
* Different loglevels can be used to extend or reduce output
* All methods are able to handle any number of output parameters.
* All methods print out a formated string (like printf).<br>
* To reduce output, reduce loglevel.
* <br>
* Output format string can contain below wildcards. Every wildcard
* must be start with percent sign (\%)
*
* <br>
* <b>Wildcards</b><br>
* <ul>
* <li><b>\%s</b>	replace with an string (char*)</li>
* <li><b>\%c</b>	replace with an character</li>
* <li><b>\%d</b>	replace with an integer value</li>
* <li><b>\%l</b>	replace with an long value</li>
* <li><b>\%x</b>	replace and convert integer value into hex</li>
* <li><b>\%X</b>	like %x but combine with <b>0x</b>123AB</li>
* <li><b>\%b</b>	replace and convert integer value into binary</li>
* <li><b>\%B</b>	like %x but combine with <b>0b</b>10100011</li>
* <li><b>\%t</b>	replace and convert boolean value into <b>"t"</b> or <b>"f"</b></li>
* <li><b>\%T</b>	like %t but convert into <b>"true"</b> or <b>"false"</b></li>
* </ul><br>
* <b>Loglevels</b><br>
* <table border="0">
* <tr><td>0</td><td>LOG_LEVEL_NOOUTPUT</td><td>no output </td></tr>
* <tr><td>1</td><td>LOG_LEVEL_ERRORS</td><td>only errors </td></tr>
* <tr><td>2</td><td>LOG_LEVEL_INFOS</td><td>errors and info </td></tr>
* <tr><td>3</td><td>LOG_LEVEL_DEBUG</td><td>errors, info and debug </td></tr>
* <tr><td>4</td><td>LOG_LEVEL_VERBOSE</td><td>all </td></tr>
* </table>
* <br>
* <h1>History</h1><br>
* <table border="0">
* <tr><td>01 FEB 2012</td><td>initial release</td></tr>
* <tr><td>06 MAR 2012</td><td>implement a preinstanciate object (like in Wire, ...)</td></tr>
* <tr><td></td><td>method init get now loglevel and baud parameter</td></tr>
* <tr><td>05 JAN 2014</td><td>init now accepts pointer to print stream instead of baud rate, 
                               and changed branching in print method</td></tr>

* </table>
*/
class Logging {
private:
  uint8_t _level; ///<least level to produce an output
  Print* _stream; ///<pointer to output stream
public:
  /*!
   * default Constructor
   */
  Logging() {} ;
	
  /*! 
   * Initializing, must be called as first.
   * \param level least level to produce an output
   * \param stream pointer to output stream
   * \return void
   */
  void init(int, Print*);
	
  /*!
   * Output an error message. Output message contains "ERROR:"
   * followed by original msg with substituted variables.
   * Error messages are printed out, at every loglevel
   * except 0 ;-)
   * \param msg format string to output
   * \param ... any number of variables
   * \return void
   */
  void error(const String &, ...);
	
  /*!
   * Output an info message. Output message contains "INFO:"
   * followed by original msg with substituted variables.
   * Info messages are printed out at 
   * loglevels >= LOG_LEVEL_INFOS
   *
   * \param msg format string to output
   * \param ... any number of variables
   * \return void
   */
 void info(const String &, ...);
	
  /*!
   * Output an debug message. Output message contains "DEBUG:"
   * followed by original msg with substituted variables.
   * Debug messages are printed out at 
   * loglevels >= LOG_LEVEL_DEBUG
   *
   * \param msg format string to output
   * \param ... any number of variables
   * \return void
   */
  void debug(const String &, ...);

  /*!
   * Output an verbose message. Output message contains 
   * original msg with substituted variables.
   * Debug messages are printed out at 
   * loglevels >= LOG_LEVEL_VERBOSE
   *
   * \param msg format string to output
   * \param ... any number of variables
   * \return void
   */
  void verbose(const String &, ...);   

    
private:
    void print(const String &, va_list );
};

extern Logging Log;

#if defined(LOGLEVEL) && LOGLEVEL != LOG_LEVEL_NOOUTPUT

#if LOGLEVEL >= LOG_LEVEL_VERBOSE
#define VERBOSE(msg,...) Log.verbose(msg, __VA_ARGS__);
#else
#define VERBOSE(msg,...)
#endif

#if LOGLEVEL >= LOG_LEVEL_DEBUG
#define DEBUG(msg,...) Log.debug(msg, __VA_ARGS__);
#else
#define DEBUG(msg,...)
#endif

#if LOGLEVEL >= LOG_LEVEL_INFO
#define INFO(msg,...) Log.info(msg, __VA_ARGS__);
#else
#define INFO(msg,...)
#endif

#if LOGLEVEL >= LOG_LEVEL_ERROR
#define ERROR(msg,...) Log.error(msg, __VA_ARGS__);
#else
#define ERROR(msg,...)
#endif

#else

#define VERBOSE(msg,...)
#define DEBUG(msg,...)
#define INFO(msg,...)
#define ERROR(msg,...)

#endif

#endif


