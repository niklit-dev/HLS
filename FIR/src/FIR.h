
#ifndef FIR_H
#define FIR_H


#include <ap_fixed.h>

typedef ap_int<17>  In_Data;	// Разрядность входных данных
typedef ap_int<17>  Coef_Data;	// Разрядность коэффициентов
typedef ap_int<17>  Out_Data;	// Разрядность выходных данных
typedef ap_int<48>  DSP_Data;	// Разрядность данных после умножения
/*
typedef int  In_Data;	// Разрядность входных данных
typedef int  Coef_Data;	// Разрядность коэффициентов
typedef int  Out_Data;	// Разрядность выходных данных
typedef int  DSP_Data;	// Разрядность данных после умножения
*/
const int N_Mult = 90;	 // Количество умножителей
const int N_Chen = 16;   // Количество каналов
const int N_Test = 2880; // Длина теста
const int N_Rej  = 2;    // Количество режимов

void ReadFromFileIn(char * FileName, int Data[N_Test]);

void ReadFromFileOut(char * FileName, int Data[N_Rej][N_Test], int N_R);

Out_Data Round(DSP_Data Data_in, int Mode);

void FIR(In_Data x_stream,	 // Входные данные
		 Out_Data &y_stream, // Выходные данные
		 int ctrl			 // Управление режимами FIR фильтра
		);

#endif

