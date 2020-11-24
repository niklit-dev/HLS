// Блок FIR фильтра


#include "ap_fixed.h"
#include "FIR.h"
#include "FIRcoefs.h"

void FIR(In_Data x_stream, 	// Входные данные
		 Out_Data &y_stream, 	// Выходные данные
		 int Mode							// Управление коэффициентами FIR фильтра
		)
{
#pragma HLS INTERFACE ap_ovld port=y_stream
#pragma HLS INTERFACE ap_vld port=x_stream
#pragma HLS INLINE region recursive
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=B dim=1

	In_Data Input_DAT=0;
	DSP_Data Acc = 0; 					 	// Сумматор умноженных данных
	static In_Data shift_reg[2*N_Mult][N_Chen];
#pragma HLS ARRAY_PARTITION variable=shift_reg complete dim=1	

	// Сдвиговый регистр на N_Chen каналов

	Input_DAT = x_stream;

	// Сдвиговые регистры
	for(int m = 2*N_Mult-1; m >= 0; m--)
	{
		for(int ch = N_Chen-1; ch >= 0; ch--)
		{
			if(m == 0)
			{
				if(ch == 0)
				{
					shift_reg[0][0] = Input_DAT;
				}
				else
				{
					shift_reg[m][ch] = shift_reg[m][ch-1];
				}
			}
			else
			{
				if(ch == 0)
					shift_reg[m][ch] = shift_reg[m-1][N_Chen-1];
				else
					shift_reg[m][ch] = shift_reg[m][ch-1];
			}
		}
	}

	// Умножение на коэффициент
	for(int m = 0; m < N_Mult; m++)
	{
		Acc += (shift_reg[m][0] + shift_reg[(2*N_Mult-1)-m][0])*B[Mode][m];
	}

	//y_stream = Acc;
	y_stream = Round(Acc, Mode);

}

// Функция округления
Out_Data Round(DSP_Data Data_in, int Mode)
{
	Out_Data RoundDat = 0;
	DSP_Data Data1 = 0;
	DSP_Data Mult = 0;
	// Величина сдвига
	int shift = 15;
	// Константа округления
	DSP_Data Round_in = 16384;
	// Округление до разрядности 17,15
	Data1 = (Data_in + Round_in) >> shift;
	// Умножение на коэффициент
	Mult = Data1*Norm[Mode];
	// Округление до разрядности 17,15
	RoundDat = (Mult+Round_in) >> shift;

	return RoundDat;
}




