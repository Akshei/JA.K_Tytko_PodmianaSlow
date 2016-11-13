#include <iostream>
#include "cppdll.h"
#include <stdlib.h>
#include <cstring>
#include <stdio.h>

#define DLL_EXPORT

extern "C"
{
	DECLDIR char* changeAllTheWords(const char *tekst, const char *doZmiany, const char *naCoZmienic, char* zwrot)
	{
		int differenceInLength = strlen(doZmiany) - strlen(naCoZmienic);
		char tekstDoPodmiany[255] = "";
		char tekstDoZwrotu[255] = ""; 
		strcpy(tekstDoPodmiany, tekst);
		//char *pch = new char[];
		//strcpy(tekstDoZwrotu,"");
		while (strstr(tekstDoPodmiany, doZmiany) != NULL){
			strncat(tekstDoZwrotu, tekstDoPodmiany, strlen(tekstDoPodmiany) - strlen(strstr(tekstDoPodmiany, doZmiany)));
			strncat(tekstDoZwrotu, naCoZmienic, strlen(naCoZmienic));
			strcpy(tekstDoPodmiany, tekstDoPodmiany + strlen(doZmiany) + strlen(tekstDoPodmiany) - strlen(strstr(tekstDoPodmiany, doZmiany)));
		}
		strcat(tekstDoZwrotu, tekstDoPodmiany);
		puts(tekstDoZwrotu);
		//zwrot = tekstDoZwrotu;
		memcpy(zwrot, tekstDoZwrotu, strlen(tekstDoZwrotu) + 1);
		return (zwrot);
	}

}
