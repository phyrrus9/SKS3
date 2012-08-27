/*
 Stream library copyright © 2012 phyrrus9 (Ethan Laur) <phyrrus9@gmail.com>
 This library is an attempt at making some of those nasty conversions a lot
 easier on the programmer by just linking to the library and using the .h
 file to grab the functions and classes. This library is open source, so it
 can be used in any way you wish, with some exceptions as listed below.
 This library must be distributed with the original copyright block on all
 files intact, to give proper credit to the people who have put work into
 this library as they deserve it. This library must also be distributed as
 open source under the same lisencing terms listed in this copyright block.
 This library is distributed in the hope that it will be useful, there is
 no warranty provided with this software but it would be appreciated if any
 bugs could be reported to the original author (phyrrus9) contact details
 on first line of this block. If you contribute to this project, feel free
 to add your name in the credits below and please please notify the author
 of your changes so we can add them to the oficial library with permission
 from you, as you deserve credit for your work.
 The following developers have contributed to this library:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> 2012
 If you feel this library infringes on any of your personal copyrights feel
 free to contact the authors so we can either ask for your permission to
 use the copyrighted material or remove the material from the library.
 In this library I have provided a simple versioning system, the c++ macro
 streamlib_version is an integer that tells what build number the library
 is. PLEASE ensure your program is compiling with the correct version .a
 file, this can be checked by testing streamlib_version with the const int
 in the library file GLOBAL_STREAMLIB_VERSION. If they do not match, do NOT
 compile your program as it could be harmful.
 Any comments, questions, or concerns would be appreciated so please do not
 hesitate to contact any developer and talk to us, that is what we are here
 for. Thank you and happy programming with streamlib.
 */
#include <string.h>
#include <sstream>
#include "temperatures.h"
#include "strings.h"
#ifndef streamlib_streams_h
#define streamlib_streams_h
#define streamlib_version 4
extern const int GLOBAL_STREAMLIB_VERSION;
bool check_version_compadible(void);
#endif
