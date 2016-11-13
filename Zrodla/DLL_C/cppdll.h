#ifndef _DLL_CPP_H_
#define _DLL_CPP_H_
#include <iostream>
#include <string.h>
#include <string>
#include "..\stdafx.h"

#define DLL_EXPORT

#if defined DLL_EXPORT
	#define DECLDIR __declspec(dllexport)
#else
	#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
	DECLDIR char* changeAllTheWords(const char *tekst, const char *doZmiany, const char *naCoZmienic, char* zwrot);
}

#endif
