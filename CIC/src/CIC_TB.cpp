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

	// �������� ������
	//memset(data_out, 0, sizeof(data_out));

	int Test_in = (N_Points+2*N*R_test)*N_Chan;

	// ������ ������� ������ �� �����
	ReadFromFile(Name_in, data_in, Test_in);

	// ��������� ������
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
	// ���������� ������ � ����
	WriteFromFile(Name_out, data_out, R_test);

	int N_Test = ((N_Points/R_test)+2*N)*N_Chan;

	// ������ �������� ��������� ������ �� �����
	ReadFromEtlFile(Name_etl, data_etl, N_Test);

	// ��������� ������� � �������� ������
	for(int i=0;i<N_Test;i++)
	{
		int Error = abs(data_out[i]-data_etl[i]);
		if(Error != 0)
		{
			cout << "������ ����������: " << Error << " � " << i << " �����." << endl;
			exit(1);
		}
	}
	cout << "���� ������� ������� OK!!!" << endl;
	return 0;
}

// ������� ������ �������� ������ �� �����
void ReadFromFile(char* Name, DAT_IN_T* Dat, int N_Test)   //Dat[N_Points*N_Chan]
{
	DAT_IN_T Dat_i;
	int DatF = 0;
	FILE * F_in;
	// ��������� ����
	F_in = fopen(Name, "r");
	// ��������� ��� ��������
	if(F_in != NULL)
	{
		// ��������� ������
		for(int i=0;i<N_Test;i++)
		{
			// ������ �� ����� �������
			fscanf(F_in, "%d", &DatF);
			Dat_i = DatF;
			Dat[i] = DatF;
		}
	}
	else
	{
		cout << "���� �� ������ �� ��������!!!" << endl;
		exit(1);
	}
	fclose(F_in);
}

// ������� ������ ��������� ������ �� �����
void ReadFromEtlFile(char* Name, DAT_OUT_T* Dat, int N_Test)   //Dat[N_Points*N_Chan]
{
	DAT_OUT_T Dat_i;
	int DatF = 0;
	FILE * F_in;
	// ��������� ����
	F_in = fopen(Name, "r");
	// ��������� ��� ��������
	if(F_in != NULL)
	{
		// ��������� ������
		for(int i=0;i<N_Test;i++)
		{
			// ������ �� ����� �������
			fscanf(F_in, "%d", &DatF);
			Dat_i = DatF;
			Dat[i] = DatF;
		}
	}
	else
	{
		cout << "���� �� ������ �� ��������!!!" << endl;
		exit(1);
	}
	fclose(F_in);
}

// ������� ������ ������ � ����
void WriteFromFile(char* Name, DAT_OUT_T* Dat, int Dec)
{
	int DatF;
	FILE * F_out;
	// ��������� ����
	F_out = fopen(Name, "w+");
	// ��������� ��� ��������
	if(F_out != NULL)
	{
		// ���������� ������
		for(int i=0;i<(N_Points/Dec+2*N)*N_Chan;i++)
		{
			DatF = Dat[i];
			// ������ �� ����� �������
			fprintf(F_out, "%d\n", DatF);
		}
	}
	else
	{
		cout << "���� �� ������ �� ��������!!!" << endl;
		exit(1);
	}
	fclose(F_out);

}


