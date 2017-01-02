#include "cppdll.h"
#include <iostream> 

char* cppDllClass::changeAllTheWords(const char *tekst, const char *doZmiany, const char *naCoZmienic, char* zwrot){
	int differenceInLength = strlen(doZmiany) - strlen(naCoZmienic);
	char tekstDoPodmiany[255] = "";
	char tekstDoZwrotu[255] = "";
	strcpy(tekstDoPodmiany, tekst);
	while (strstr(tekstDoPodmiany, doZmiany) != NULL){
		strncat(tekstDoZwrotu, tekstDoPodmiany, strlen(tekstDoPodmiany) - strlen(strstr(tekstDoPodmiany, doZmiany)));
		strncat(tekstDoZwrotu, naCoZmienic, strlen(naCoZmienic));
		strcpy(tekstDoPodmiany, tekstDoPodmiany + strlen(doZmiany) + strlen(tekstDoPodmiany) - strlen(strstr(tekstDoPodmiany, doZmiany)));
	}
	strcat(tekstDoZwrotu, tekstDoPodmiany);
	puts(tekstDoZwrotu);
	memcpy(zwrot, tekstDoZwrotu, strlen(tekstDoZwrotu) + 1);
	return (zwrot);
}