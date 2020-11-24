
#ifndef _CIC_H
#define _CIC_H

//#include <fstream>
#include <iostream>
#include <ap_fixed.h>
#include <cstdio>
#include <math.h>

using namespace std;

// Количество отсчетов
const int N_Points = 10000;
// Порядок фильтра
const int N = 8;
// Дифференциальная задержка гребенчатого фильтра
const int M = 2;
// Размер аккумулятора
const int SizeAcc = 51;
// Размер дробной части
//const int SizeFract = 15;
// Размер входных данных
const int SizeIn = 16;
// Размер выходных данных
const int SizeOut = 17;
// Децимация
const int R_test = 10;
// Величина сдвига аккумулятора
const int Shift = SizeAcc-SizeOut;
// Количество каналов
const int N_Chan = 16;

// Типы данных
//typedef long long int DAT_Acc_T;
//typedef int DAT_OUT_T;

typedef ap_int<SizeIn>  DAT_IN_T;
typedef ap_int<SizeOut> DAT_OUT_T;
typedef ap_int<SizeAcc> DAT_Acc_T;

// Функции
DAT_Acc_T Integrator(DAT_IN_T Dat_I, bool Vld_in, bool &Vld_out);
DAT_OUT_T Comb_filter(DAT_Acc_T Dat_I, bool Vld_I, bool &Vld_O);
void Decimate(DAT_Acc_T Dat_I, bool Vld_I, DAT_Acc_T &Dat_O, bool &Vld_O, int R);
void ReadFromFile(char* Name, DAT_IN_T* Dat, int N_Test);
void WriteFromFile(char* Name, DAT_OUT_T* Dat, int Dec);
void ReadFromEtlFile(char* Name, DAT_OUT_T* Dat, int N_Test);

void CIC(DAT_IN_T  Dat_I,  // Входные данные
		 bool      Vld_I,  // Наличие входных данных
		 DAT_OUT_T &Dat_O, // Выходные данные
		 bool      &Vld_O, // Наличие выходных данных
		 int       R	   // Децимация
		);

#endif
