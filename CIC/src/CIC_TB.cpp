#include "CIC.h"

int main()
{
	DAT_IN_T data_in[N_Points*N_Chan+2*N*R_test*N_Chan];
	DAT_OUT_T data_out[(N_Points/R_test)*N_Chan+2*N*N_Chan];
	DAT_OUT_T data_etl[(N_Points/R_test)*N_Chan+2*N*N_Chan];
	bool Vld;
	int CountI = 0;
	char* Name_in  = "D:/Repositories/hardware/src/Vivado-HLS/CIC/src/InData.txt";
	char* Name_out = "D:/Repositories/hardware/src/Vivado-HLS/CIC/src/OutData.txt";
	char* Name_etl = "D:/Repositories/hardware/src/Vivado-HLS/CIC/src/EtlData.txt";

	// Обнуляем массив
	//memset(data_out, 0, sizeof(data_out));

	int Test_in = (N_Points+2*N*R_test)*N_Chan;

	// Чтение входных данных из файла
	ReadFromFile(Name_in, data_in, Test_in);

	// Фильтруем данные
	for(int i=0;i<Test_in;i++)
	{
		DAT_OUT_T Dat_O;
		CIC(data_in[i], true, Dat_O, Vld, R_test);

		if(Vld==1)
		{
			data_out[CountI] = Dat_O;
			CountI++;
		}
	}
	// Записываем данные в файл
	WriteFromFile(Name_out, data_out, R_test);

	int N_Test = ((N_Points/R_test)+2*N)*N_Chan;

	// Чтение выходных эталонных данных из файла
	ReadFromEtlFile(Name_etl, data_etl, N_Test);

	// Проверяем наличие и величину ошибки
	for(int i=0;i<N_Test;i++)
	{
		int Error = abs(data_out[i]-data_etl[i]);
		if(Error != 0)
		{
			cout << "Ошибка вычислений: " << Error << " в " << i << " слове." << endl;
			exit(1);
		}
	}
	cout << "Тест успешно пройден OK!!!" << endl;
	return 0;
}

// Функция чтения входеных данных из файла
void ReadFromFile(char* Name, DAT_IN_T* Dat, int N_Test)   //Dat[N_Points*N_Chan]
{
	DAT_IN_T Dat_i;
	int DatF = 0;
	FILE * F_in;
	// Открываем файл
	F_in = fopen(Name, "r");
	// Проверяем что открылся
	if(F_in != NULL)
	{
		// Считываем данные
		for(int i=0;i<N_Test;i++)
		{
			// Чтение из файла массива
			fscanf(F_in, "%d", &DatF);
			Dat_i = DatF;
			Dat[i] = DatF;
		}
	}
	else
	{
		cout << "Файл на чтение не открылся!!!" << endl;
		exit(1);
	}
	fclose(F_in);
}

// Функция чтения эталонных данных из файла
void ReadFromEtlFile(char* Name, DAT_OUT_T* Dat, int N_Test)   //Dat[N_Points*N_Chan]
{
	DAT_OUT_T Dat_i;
	int DatF = 0;
	FILE * F_in;
	// Открываем файл
	F_in = fopen(Name, "r");
	// Проверяем что открылся
	if(F_in != NULL)
	{
		// Считываем данные
		for(int i=0;i<N_Test;i++)
		{
			// Чтение из файла массива
			fscanf(F_in, "%d", &DatF);
			Dat_i = DatF;
			Dat[i] = DatF;
		}
	}
	else
	{
		cout << "Файл на чтение не открылся!!!" << endl;
		exit(1);
	}
	fclose(F_in);
}

// Функция записи данных в файл
void WriteFromFile(char* Name, DAT_OUT_T* Dat, int Dec)
{
	int DatF;
	FILE * F_out;
	// Открываем файл
	F_out = fopen(Name, "w+");
	// Проверяем что открылся
	if(F_out != NULL)
	{
		// Записываем данные
		for(int i=0;i<(N_Points/Dec+2*N)*N_Chan;i++)
		{
			DatF = Dat[i];
			// Чтение из файла массива
			fprintf(F_out, "%d\n", DatF);
		}
	}
	else
	{
		cout << "Файл на запись не открылся!!!" << endl;
		exit(1);
	}
	fclose(F_out);

}


