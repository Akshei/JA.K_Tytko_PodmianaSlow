// JA.K_Tytko_PodmianaSlow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <process.h>
#include "../cppdll/cppdll.h"

typedef DWORD(*asmFunction)(const char*, const char*, const char*, char*);

using namespace std;

vector<string> tekst;
int index = 0;
string slowoDoZamiany,slowoNaZmiane;
asmFunction asmFunc;

void halp(){
	cout << endl << endl;
	cout << "Prawdopodobnie wpisa³es bledne paramtery. Pozwol na poprawienie tego" << endl;
	cout << "1 parametr odpowiada za skorzystanie z biblioteki z c++ lub assemblera. Wpisz odpowiednio cpp dla pierwszego, i asm dla drugiego" << endl;
	cout << "2 parametr odpowiada za plik wejœciowy. Wpisz nazwê tego pliku i upewnij siê ¿e jest on w folderze razem z plikiem wykonywalnym. Pamietaj o wpisaniu calej jego nazwe wraz z rozszerzeniem." << endl;
	cout << " Pamietaj ze dane slowo zostanie podmienione w tym samym pliku wjesciowym ktory podales" << endl; 
	cout << "3 parametr odpowiada za slowo ktore w danym tekscie ma byc zamienione." << endl;
	cout << "4 parametr odpowiada za slowo na ktore slowo z parametru 3 ma byc zmienione" << endl;
	cout << "5 parametr odpowiada za iloœæ rdzeni które u¿ytkownik chce wykorzystaæ (jest opcjonalny)" << endl;
}


int numberOfProcessorCores()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}


void __cdecl ThreadProcCpp(void * Args)
{
	char zwrot[255] = ""; 
	int i = index++;
	while ( i < tekst.size()){
		string x(cppDllClass::changeAllTheWords(tekst[i].c_str(), slowoDoZamiany.c_str(), slowoNaZmiane.c_str(), zwrot));
		tekst[i] = x;
		cout << tekst[i] << endl;
		cout << i << endl;
		i = index++;
	}
	_endthread();
}

void __cdecl ThreadProcAsm(void * Args)
{
	int i = index++;
	cout << i << endl;
	_endthread();
}

int zwroc3(const char *tekst, const char *doZmiany, const char *naCoZmienic, char* zwrot){
	return 3;
}

int main(int argc, char* argv[])
{
	int liczbaWatkow;
	clock_t t = clock();
	int kromka = 0;
	char trom[255] = "";
	zwroc3(slowoNaZmiane.c_str(), slowoNaZmiane.c_str(), slowoNaZmiane.c_str(), trom);
	

	if (argc >= 5){ // sprawdzenie ilosci arguemntow
		cout << "Dobra ilosc argumentow" << endl;
		if (argc >= 6){ // czy zostal podany i obliczenie ilosci watkow do wykorzystania
			liczbaWatkow = atoi(argv[5]);
			cout << "Podano liczbe watkow i wynods ona: " << liczbaWatkow << endl;
		}
		else{
			liczbaWatkow = numberOfProcessorCores();
			cout << "Nie Podano liczby watkow i wynods ona odczytana: " << liczbaWatkow << endl;
		}
		
		fstream plik;
		plik.open(argv[2], ios::in); // otwarcie i sprawdzenie porpawnosci pliku
		if (plik.good() == true){

			cout << "Plik otworzony" << endl;
			slowoDoZamiany = argv[3];
			slowoNaZmiane = argv[4];

			string x;
			int i = 0;
			while (getline(plik,x)){ // Tekst z pliku przeniesiony do wektora
				tekst.push_back(x);
				i++;
			}

			vector < HANDLE > threads;
			
			if (strcmp(argv[1], "asm") == 0){
				HMODULE lib;
				cout << "kromka niebiblioteczna" << endl;
				try{
					if ((lib = LoadLibrary(L"asmdll.dll")) != NULL) {
						cout << "kromka bez asm funkcjiaa" << endl;
						asmFunc = (asmFunction)GetProcAddress(lib, "asmFunction");
						cout << "kromka bez asm funkcji" << endl;
						if (asmFunc != NULL) {
							int kromka = 333;
							DWORD x;
							char zwrot[255] = "";
							x = asmFunc("kromka kromka ", "ka","bum",zwrot);
							cout << zwrot<< endl;
							/*t = clock();
							for (int j = 0; j < liczbaWatkow; j++){
							HANDLE hThread = (HANDLE)_beginthread(ThreadProcAsm, 1, NULL);
							threads.push_back(hThread);
							}
							WaitForMultipleObjects(threads.size(), &threads[0], TRUE, 10000);
							t = clock() - t;
							plik.close();
							plik.open(argv[2], ios::out);
							for (int j = 0; j < tekst.size(); j++){
							plik.write(tekst[j].c_str(), tekst[j].length());
							plik.write("\n", 1);
							}
							*/
						}
						FreeLibrary(lib);
					}
				}
				catch( exception ex){
						cout << "nie zaladowano dllki" << endl;
					}
			}
			else if (strcmp(argv[1], "cpp") == 0){
				t = clock();
				for (int j = 0; j < liczbaWatkow; j++){
					HANDLE hThread = (HANDLE)_beginthread(ThreadProcCpp, 1, NULL);
					threads.push_back(hThread);
				}
				WaitForMultipleObjects(threads.size(), &threads[0], TRUE,10000);
				t = clock() - t;
				plik.close();
				plik.open(argv[2], ios::out);
				for (int j = 0; j < tekst.size(); j++){
					plik.write(tekst[j].c_str(), tekst[j].length());
					plik.write("\n", 1);
				}
			}
			else{
				cout << "Pierwszy argument bledny" << endl;
				halp();
			}

			plik.close();
		}
		else { 
			cout << " Plik nie zostal poprawnie otworzony" << endl;
			halp();
		}
	}
	else{
		halp();
	}

	
	cout << "Czas w milisekundach to: " << t << endl;
	system("PAUSE");
	return 0;
}

