#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include "FIR.h"

using namespace std;

int main()
{
	int dat_out_r;
	int dat_in[N_Test];
	Out_Data dat_out[N_Rej][N_Test];
	int dat_out_etl[N_Rej][N_Test];
	bool comp = true;
	int Error_Num = 0;
	int Error_Mode = 0;
	int Error = 0;
	int dat_FIR_ER = 0;
	int dat_out_etl_ER = 0;

	// ���� �� �������� �������
	char * File_in;
	// ����� � ��������� �������
	char * File_out;

	File_in = "../../../../src/DataIn.txt";
	File_out = "../../../../src/DataOut.txt";

	// ������ ������� ������ �� �����
	ReadFromFileIn(File_in, dat_in);

	// ������������ �������
	for(int j=0; j<N_Rej; j++)
	{
		// ����� ������� FIR
		for(int i=0; i < N_Test; i++)
		{
			In_Data Data_in = dat_in[i];
			FIR(Data_in, dat_out[j][i], j);
		}
	}

	// ������ �������� ������ �� �����
	ReadFromFileOut(File_out, dat_out_etl, N_Rej);

	// ��������� ���������� ������ � ���������

	for(int j=0; j<N_Rej; j++)
	{
		for(int i=0; i<N_Test; i++)
		{
			int dat_FIR;
			dat_FIR = dat_out[j][i];
			if(dat_FIR != dat_out_etl[j][i])
			{
				comp = false;
				Error_Num = i + 1;
				Error_Mode = j;
				Error = dat_FIR - dat_out_etl[j][i];
				dat_FIR_ER = dat_FIR;
				dat_out_etl_ER = dat_out_etl[j][i];
				break;
			}
		}
	}

	if(comp)
		cout<<"**************** ���� ������� �������!!! ****************";
	else
		cout<<"**************** ���� �� �������, ������ � " << Error_Num << " ����� " << Error_Mode << " ������! Error = " << dat_FIR_ER << " - " << dat_out_etl_ER << " = "<< Error <<" ****************"<< endl;

	return 0;

}

// ������� ������ ������� ������ �� �����
void ReadFromFileIn(char * FileName, int *Data)
{
	// ������� ���������� �����
	FILE* fid=NULL;
	int dat;
	// ��������� ���� � ��������� ��� �� ��������
	fid=fopen(FileName, "rt");
	if(NULL==fid){
		printf("Error Opening Input Test Vector!\n");
	}
	// ������ �� ���� ������
	for(int i=0; i < N_Test; i++)
	{
		fscanf(fid, "%d", &dat);
		Data[i] = dat;
	}
	// ��������� ����
	fclose(fid);
}

// ������� ������ �������� ������ �� �����
void ReadFromFileOut(char * FileName, int Data[N_Rej][N_Test], int N_Rej)
{
	// ������� ���������� �����
	FILE* fid=NULL;
	int dat;
	// ��������� ���� � ��������� ��� �� ��������
	fid=fopen(FileName, "rt");
	if(NULL==fid){
		printf("Error Opening Input Test Vector!\n");
	}
	// ������ �� ���� ������
	for(int j=0; j < N_Rej; j++)
	{
		for(int i=0; i < N_Test; i++)
		{
			fscanf(fid, "%d", &dat);
			Data[j][i] = dat;
		}
	}
	// ��������� ����
	fclose(fid);
}



