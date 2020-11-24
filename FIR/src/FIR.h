
#ifndef FIR_H
#define FIR_H


#include <ap_fixed.h>

typedef ap_int<17>  In_Data;	// ����������� ������� ������
typedef ap_int<17>  Coef_Data;	// ����������� �������������
typedef ap_int<17>  Out_Data;	// ����������� �������� ������
typedef ap_int<48>  DSP_Data;	// ����������� ������ ����� ���������
/*
typedef int  In_Data;	// ����������� ������� ������
typedef int  Coef_Data;	// ����������� �������������
typedef int  Out_Data;	// ����������� �������� ������
typedef int  DSP_Data;	// ����������� ������ ����� ���������
*/
const int N_Mult = 90;	 // ���������� �����������
const int N_Chen = 16;   // ���������� �������
const int N_Test = 2880; // ����� �����
const int N_Rej  = 2;    // ���������� �������

void ReadFromFileIn(char * FileName, int Data[N_Test]);

void ReadFromFileOut(char * FileName, int Data[N_Rej][N_Test], int N_R);

Out_Data Round(DSP_Data Data_in, int Mode);

void FIR(In_Data x_stream,	 // ������� ������
		 Out_Data &y_stream, // �������� ������
		 int ctrl			 // ���������� �������� FIR �������
		);

#endif

