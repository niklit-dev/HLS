#include "CIC.h"

void CIC(DAT_IN_T  Dat_I,  // ������� ������
		 bool      Vld_I,  // ������� ������� ������
		 DAT_OUT_T &Dat_O, // �������� ������
		 bool      &Vld_O, // ������� �������� ������
		 int R		       // ���������
		)
{
#pragma HLS INTERFACE ap_none port=Vld_O
#pragma HLS INTERFACE ap_none port=Dat_O
#pragma HLS INTERFACE ap_none port=Vld_I
#pragma HLS INTERFACE ap_none port=Dat_I
	static int countR  = 0;
	static int countCh = 0;
	DAT_Acc_T Integr8=0;
	DAT_Acc_T Dec_Dat=0;
	DAT_OUT_T Dat_i;
	bool Vld_Out = false;
	bool EnaR    = false;
	bool EnaComb = false;
	bool Dec_Vld = false;
	bool Vld_i = false;

#pragma HLS PIPELINE II=1

	// ����������
	Integr8 = Integrator(Dat_I, Vld_I, Vld_Out);

	Decimate(Integr8, Vld_Out, Dec_Dat, Dec_Vld, R);

	// ����������� ������
	Dat_O = Comb_filter(Dec_Dat, Dec_Vld, Vld_O);

}

// ������� N_Chan-��������� ������������
DAT_Acc_T Integrator(DAT_IN_T Dat_I, bool Vld_in, bool &Vld_out)
{
	static DAT_Acc_T Acc[N][N_Chan+1];
	static bool Vld_i[N];
#pragma HLS ARRAY_PARTITION variable=Acc complete dim=1
#pragma HLS ARRAY_PARTITION variable=Vld_i complete dim=1
	// ���� �� ���������� ������������
	for(int i = N-1; i>0;i--)
	{
		Vld_i[i] = Vld_i[i-1];
	}
	Vld_i[0] = Vld_in;

	// ���� �� ���������� ������������
	for(int i = N-1; i>=0;i--)
	{
		// ������ N_Chan-��������� ����������
		if(i == 0)
		{
			if(Vld_i[i])
			{
				Acc[i][0]   = Dat_I+Acc[i][N_Chan];
				// ��������� �������
				for(int j=N_Chan; j>0; j--)
				{
					Acc[i][j]   = Acc[i][j-1];
				}
			}
		}
		// ��������� N_Chan-��������� �����������
		else
		{
			if(Vld_i[i])
			{
				Acc[i][0]=Acc[i-1][0]+Acc[i][N_Chan];
				// ��������� �������
				for(int j=N_Chan; j>0; j--)
				{
					Acc[i][j]   = Acc[i][j-1];
				}
			}
		}
	}

	Vld_out = Vld_i[N-1];
	return Acc[N-1][0];
}

// ����������� ������
DAT_OUT_T Comb_filter(DAT_Acc_T Dat_I, bool Vld_I, bool &Vld_O)
{
	static DAT_Acc_T Comb[N];
	static DAT_Acc_T Delay1[N][N_Chan+1];
	static DAT_Acc_T Delay2[N][N_Chan];
	static bool Vld[N];
	DAT_OUT_T Dat_O=0;
	DAT_OUT_T ShDat=0;
#pragma HLS ARRAY_PARTITION variable=Comb complete dim=1
#pragma HLS ARRAY_PARTITION variable=Delay1 complete dim=1
#pragma HLS ARRAY_PARTITION variable=Delay2 complete dim=1

	// ���� �� ���������� ����������� ��������
	for(int i=N-1; i>0; i--)
	{
		Vld[i]=Vld[i-1];
	}
	Vld[0]=Vld_I;

	// ���� �� ���������� ����������� ��������
	for(int i=N-1; i>=0; i--)
	{
		// ������ ������������ �������
		if(i==0)
		{
			if(Vld_I)
			{
				Comb[i]=Dat_I-Delay2[i][N_Chan-1];
				// ���� ���. �������� M=1
				if(M==1)
				{
					// ��������� �������
					for(int j=N_Chan-1; j>0; j--)
					{
						Delay2[i][j]=Delay2[i][j-1];
					}
					Delay2[i][0]=Dat_I;
				}
				// ���� ���. �������� M=2
				else
				{
					// ��������� �������
					for(int j=N_Chan-1; j>0; j--)
					{
						Delay2[i][j]=Delay2[i][j-1];
					}
					for(int j=N_Chan; j>0; j--)
					{
						Delay1[i][j]=Delay1[i][j-1];
					}

					Delay2[i][0]=Delay1[i][N_Chan];
					Delay1[i][0]=Dat_I;
				}
			}
		}
		// ��������� ����������� �������
		else
		{
			if(Vld[i])
			{
				Comb[i]=Comb[i-1]-Delay2[i][N_Chan-1];
				// ���� ���. �������� M=1
				if(M==1)
				{
					// ��������� �������
					for(int j=N_Chan-1; j>0; j--)
					{
						Delay2[i][j]=Delay2[i][j-1];
					}
					Delay2[i][0]=Comb[i-1];
				}
				// ���� ���. �������� M=2
				else
				{
					// ��������� �������
					for(int j=N_Chan-1; j>0; j--)
					{
						Delay2[i][j]=Delay2[i][j-1];
					}

					for(int j=N_Chan; j>0; j--)
					{
						Delay1[i][j]=Delay1[i][j-1];
					}
					Delay2[i][0]=Delay1[i][N_Chan];
					Delay1[i][0]=Comb[i-1];
				}
			}
		}
	}
	Vld_O = Vld[N-1];
	// �������� � �������� �����������
	ShDat=Comb[N-1]>>Shift;
	return Dat_O = ShDat;
}

// ���������
void Decimate(DAT_Acc_T Dat_I, bool Vld_I, DAT_Acc_T &Dat_O, bool &Vld_O, int R)
{
	static bool EnaR = false;
	static bool EnaComb = false;
	static int count;
	int mul = R*N_Chan-1;


	if(((count>>4)==0)&Vld_I)
	{
		Vld_O = true;
		Dat_O = Dat_I;
		count++;
	}
	else if((count==mul)&Vld_I)
	{
		Vld_O = false;
		count = 0;
	}
	else if(Vld_I)
	{
		count++;
		Vld_O = false;
	}
	else
		Vld_O = false;

}

