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

	// Файл со входными данными
	char * File_in;
	// Файлы с выходными данными
	char * File_out;

	File_in = "../../../../src/DataIn.txt";
	File_out = "../../../../src/DataOut.txt";

	// Чтение входных данных из файла
	ReadFromFileIn(File_in, dat_in);

	// Тестирование режимов
	for(int j=0; j<N_Rej; j++)
	{
		// Вызов функции FIR
		for(int i=0; i < N_Test; i++)
		{
			In_Data Data_in = dat_in[i];
			FIR(Data_in, dat_out[j][i], j);
		}
	}

	// Чтение выходных данных из файла
	ReadFromFileOut(File_out, dat_out_etl, N_Rej);

	// Сравнение полученных данных с эталонами

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
		cout<<"**************** Тест успешно пройден!!! ****************";
	else
		cout<<"**************** Тест не пройден, ошибка в " << Error_Num << " слове " << Error_Mode << " режима! Error = " << dat_FIR_ER << " - " << dat_out_etl_ER << " = "<< Error <<" ****************"<< endl;

	return 0;

}

// Функция чтения входных данных из файла
void ReadFromFileIn(char * FileName, int *Data)
{
	// Создаем переменную файла
	FILE* fid=NULL;
	int dat;
	// Открываем файл и проверяем что он открылся
	fid=fopen(FileName, "rt");
	if(NULL==fid){
		printf("Error Opening Input Test Vector!\n");
	}
	// Читаем из него данные
	for(int i=0; i < N_Test; i++)
	{
		fscanf(fid, "%d", &dat);
		Data[i] = dat;
	}
	// Закрываем файл
	fclose(fid);
}

// Функция чтения выходных данных из файла
void ReadFromFileOut(char * FileName, int Data[N_Rej][N_Test], int N_Rej)
{
	// Создаем переменную файла
	FILE* fid=NULL;
	int dat;
	// Открываем файл и проверяем что он открылся
	fid=fopen(FileName, "rt");
	if(NULL==fid){
		printf("Error Opening Input Test Vector!\n");
	}
	// Читаем из него данные
	for(int j=0; j < N_Rej; j++)
	{
		for(int i=0; i < N_Test; i++)
		{
			fscanf(fid, "%d", &dat);
			Data[j][i] = dat;
		}
	}
	// Закрываем файл
	fclose(fid);
}



