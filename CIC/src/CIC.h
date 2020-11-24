
#ifndef _CIC_H
#define _CIC_H

//#include <fstream>
#include <iostream>
#include <ap_fixed.h>
#include <cstdio>
#include <math.h>

using namespace std;

// ���������� ��������
const int N_Points = 10000;
// ������� �������
const int N = 8;
// ���������������� �������� ������������ �������
const int M = 2;
// ������ ������������
const int SizeAcc = 51;
// ������ ������� �����
//const int SizeFract = 15;
// ������ ������� ������
const int SizeIn = 16;
// ������ �������� ������
const int SizeOut = 17;
// ���������
const int R_test = 10;
// �������� ������ ������������
const int Shift = SizeAcc-SizeOut;
// ���������� �������
const int N_Chan = 16;

// ���� ������
//typedef long long int DAT_Acc_T;
//typedef int DAT_OUT_T;

typedef ap_int<SizeIn>  DAT_IN_T;
typedef ap_int<SizeOut> DAT_OUT_T;
typedef ap_int<SizeAcc> DAT_Acc_T;

// �������
DAT_Acc_T Integrator(DAT_IN_T Dat_I, bool Vld_in, bool &Vld_out);
DAT_OUT_T Comb_filter(DAT_Acc_T Dat_I, bool Vld_I, bool &Vld_O);
void Decimate(DAT_Acc_T Dat_I, bool Vld_I, DAT_Acc_T &Dat_O, bool &Vld_O, int R);
void ReadFromFile(char* Name, DAT_IN_T* Dat, int N_Test);
void WriteFromFile(char* Name, DAT_OUT_T* Dat, int Dec);
void ReadFromEtlFile(char* Name, DAT_OUT_T* Dat, int N_Test);

void CIC(DAT_IN_T  Dat_I,  // ������� ������
		 bool      Vld_I,  // ������� ������� ������
		 DAT_OUT_T &Dat_O, // �������� ������
		 bool      &Vld_O, // ������� �������� ������
		 int       R	   // ���������
		);

#endif
