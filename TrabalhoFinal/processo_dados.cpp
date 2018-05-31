//									TRABALHO PRATICO DE AUTOMAÇAO EM TEMPO REAL (ATR) - UFMG
//
//	Esse arquivo destina-se a criação das seguintes tarefas:
//	- Tarefa de tratamento do teclado
//	- Tarefa de leitura do CLP
//  - Tarefa de captura de alarmes       
//	- Tarefa de captura de dados de processo
//	- Tarefa de exibição de dados de processo
//	Como decisão de implementação criamos cara uma dessas tarefas como uma thread do processo criado na execução deste arquivo.
//
//																										Autores: Josué Henrique / Gustavo Nery
//

#define WIN32_LEAN_AND_MEAN 
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>	// _beginthreadex() e _endthreadex() 
#include <conio.h>		// _getch

#define _CHECKERROR	1		// Ativa função CheckForError
#include "CheckForError.h"


// Casting para terceiro e sexto parâmetros da função _beginthreadex
typedef unsigned (WINAPI *CAST_FUNCTION)(LPVOID);
typedef unsigned *CAST_LPDWORD;

// Declaração das funções
DWORD WINAPI TaskKeyboard(LPVOID);
DWORD WINAPI TaskReadCLP(LPVOID);
DWORD WINAPI TaskAlarm(LPVOID);
DWORD WINAPI TaskData(LPVOID);
DWORD WINAPI TaskDisplayData(LPVOID);

#define NUM_THREADS 5



int main(){

	// Handle para cada uma das threads
	HANDLE hThreads[NUM_THREADS];

	DWORD dwThreadId;
	DWORD dwExitCode = 0;
	DWORD dwRet;

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, (CAST_FUNCTION)TaskKeyboard,		NULL, 0, (CAST_LPDWORD)&dwThreadId);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, (CAST_FUNCTION)TaskReadCLP,		NULL, 0, (CAST_LPDWORD)&dwThreadId);
	hThreads[2] = (HANDLE)_beginthreadex(NULL, 0, (CAST_FUNCTION)TaskAlarm,			NULL, 0, (CAST_LPDWORD)&dwThreadId);
	hThreads[3] = (HANDLE)_beginthreadex(NULL, 0, (CAST_FUNCTION)TaskData,			NULL, 0, (CAST_LPDWORD)&dwThreadId);
	hThreads[4] = (HANDLE)_beginthreadex(NULL, 0, (CAST_FUNCTION)TaskDisplayData,	NULL, 0, (CAST_LPDWORD)&dwThreadId);


	dwRet = WaitForMultipleObjects(NUM_THREADS, hThreads, TRUE, INFINITE);
	CheckForError((dwRet >= WAIT_OBJECT_0) && (dwRet < WAIT_OBJECT_0 + 3));

	for (int i = 0; i<NUM_THREADS; ++i) {
		GetExitCodeThread(hThreads[i], &dwExitCode);
		printf("thread %d terminou: codigo=%d\n", i, dwExitCode);
		CloseHandle(hThreads[i]);	// apaga referência ao objeto
	}  // for 

	printf("\nAcione uma tecla para terminar\n");
	_getch(); // // Pare aqui, caso não esteja executando no ambiente MDS

	return EXIT_SUCCESS;
}	// main



DWORD WINAPI TaskKeyboard(LPVOID index){
	printf("TaskKeyboard\n");
	int i;

	for (i = 0; i<500000; ++i) {
		printf("%d ", index);
		Sleep(1000);	// delay de 10 ms
	}
	printf("\n");
	_endthreadex((DWORD)index);

	return(0);
}

DWORD WINAPI TaskReadCLP(LPVOID index){
	printf("TaskReadCLP\n");
	int i;

	for (i = 0; i<500000; ++i) {
		printf("%d ", index);
		Sleep(1000);	// delay de 10 ms
	}
	printf("\n");
	_endthreadex((DWORD)index);

	return(0);
}

DWORD WINAPI TaskAlarm(LPVOID index){
	printf("TaskKAlarm\n");
	return(0);
}

DWORD WINAPI TaskData(LPVOID index){
	printf("TaskData\n");
	return(0);
}

DWORD WINAPI TaskDisplayData(LPVOID index){	
	printf("TaskDisplayData\n");
	return(0);
}


