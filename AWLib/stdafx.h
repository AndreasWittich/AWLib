//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

// stdafx.h : Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

#ifdef _WIN32
#define AW_FUNKTIONS_NAME __FUNCTION__
#else
#define AW_FUNKTIONS_NAME __PRETTY_FUNCTION__
#endif

#include <stdio.h>
#ifdef _WIN32
#include "targetver.h"
#include <tchar.h>
#endif

#include <stdint.h>
#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <assert.h>
#include <stdarg.h>

#include "Objekt.hpp"

