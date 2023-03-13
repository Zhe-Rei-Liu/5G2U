/****************************************************************************

Scheduling (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SchedulingURLLCMS_NRuRLLC.cpp
DATE         : 2017.3.1
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han    	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "SchedulingURLLCMS_NRuRLLC.h"
#include<stdio.h>
#include<stdlib.h>
#include<atlstr.h>


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SchedulingURLLCMS::Initialize(int ms)
{
	id = ms; // MS ID
	dataSize = Sim.scheduling->dataSize;
	interArrivalTime = ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5); // first traffic generation TTI for non-full-buffer MS
	msBuffer = 0; // buffer initialization
}
/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void SchedulingURLLCMS::BufferUpdate()
{
	if ((Sim.TTI == interArrivalTime))
	{
		
		msBuffer = msBuffer + dataSize;
		interArrivalTime = Sim.TTI + ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5);
	}
}

//  Point!!!!   //

void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

// LCIDxxxxxxxxx[][9]設為9的原因是因為讀取的字串有9個vector L#S[x][0]儲存封包由WorkCell發出的時間 L#S[x][1]儲存由WorkCell發出的message size
void SchedulingURLLCMS::WCBufferUpdate(string wtofLCID000101[350000][11], string wtofLCID000100[80000][11], string wtofLCID000000[560000][9], double wtofL5S[350000][2], double wtofL4S[80000][2], double  wtofL0S[560000][2])
{
	ofstream outf1, outf2, outf3;
	outf1.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/WCBuffer_LCID000101.txt");
	outf2.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/WCBuffer_LCID000010.txt");
	outf3.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/WCBuffer_LCID000001.txt");

	for (int i = 0; i < Sim.x; i++)
	{	
		// 若封包由WorkCell發出的時間再5G NR對此流量的Window time內且狀態為Queueing則進行迴圈內的計算
		if ((wtofL5S[i][0] < Sim.TTI + Sim.WCwt5 ) && (wtofLCID000101[i][0] == "Queueing"))
		{	
			wtofUMS5TS[i][0] = wtofL5S[i][0];
			cout << i << " wtofUMS5TS[i][0]" << wtofUMS5TS[i][0] << endl;
			wtofUMS5TS[i][1] = wtofL5S[i][1];
			// 判斷此封包是否為傳輸過的，1為已傳輸，0為尚未傳輸
			if (wtofUMS5TS[i][2] != 1)
				wtofUMS5TS[i][2] = 0;

			//LCID00101[i][0] = "Buffering";
			//outf5 << "now time = " << Sim.TTI << endl;

			//  將封包狀態更改為Queueing後發送，並將Queueing時的封包資訊紀錄於新的txt中
			for (int j = 0; j < 11; j++)
			{
				wtofUMS000101[i][j] = wtofLCID000101[i][j];
				outf1 << wtofLCID000101[i][j] << " ";
			}
			outf1 << endl;
		}
	}
	for (int i = 0; i < Sim.y; i++)
	{	
		if ((wtofL4S[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4) && (wtofLCID000100[i][0] == "Queueing"))
		{
			wtofUMS4TS[i][0] = wtofL4S[i][0];
			wtofUMS4TS[i][1] = wtofL4S[i][1];
			if (wtofUMS4TS[i][2] != 1)
				wtofUMS4TS[i][2] = 0;
			for (int j = 0; j < 11; j++)
			{
				wtofUMS000100[i][j] = wtofLCID000100[i][j];
				outf2 << wtofLCID000100[i][j] << " ";
			}
			outf2 << endl;
		}
	}
	for (int i = 0; i < Sim.z; i++)
	{
		if ((wtofL0S[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4 + Sim.WCwt0) && (wtofLCID000000[i][0] == "Queueing"))
		{
			wtofUMS0TS[i][0] = wtofL0S[i][0];
			wtofUMS0TS[i][1] = wtofL0S[i][1];
			if(wtofUMS0TS[i][2]!=1)
				wtofUMS0TS[i][2] = 0;
			for (int j = 0; j < 9; j++)
			{
				wtofUMS000000[i][j] = wtofLCID000000[i][j];
				outf3 << wtofLCID000000[i][j] << " ";
			}
			outf3 << endl;
		}
	}

	//msBuffer = msBuffer + dataSize;
	//interArrivalTime = Sim.TTI + ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5);
	cout <<"WC Buffer is updated! "<< endl;
}

void SchedulingURLLCMS::CCWCBufferUpdate(string wtofLCID000101[350000][11], double wtofL5S[350000][2], int CCtrigger, double CCoverlap_ts)
{
	int i;
	double CCoverlap;
	int last_CCtrigger = CCtrigger;
	if (wtofUMS5TS[last_CCtrigger - 1][2] == 0 && last_CCtrigger != 0)  // 上一輪的Buffered的封包還沒傳完
	{
		goto breakpoint;
	}

	if (wtofLCID000101[last_CCtrigger][10] == "opn")
	{
		wtofL5S[last_CCtrigger][0] = wtofL5S[last_CCtrigger][0];
		Sim.CCtrigger = last_CCtrigger + 1;
	}

	if (Sim.CCtrigger >= (Sim.x-1))
	{
		CCoverlap = CCoverlap_ts - wtofL5S[last_CCtrigger][0]; //  傳出最後中斷連線的兩個ack
	}
	else if (Sim.CCtrigger < 12)
	{	
		//建立連線時的校正
		CCoverlap = CCoverlap_ts - wtofL5S[last_CCtrigger][0];
	}
	else
	{
		for (int k = last_CCtrigger; k <= Sim.x; k++)
		{
			if (wtofLCID000101[k][10] == "reassemble" || wtofLCID000101[k][10] == "opcua")
			{
				CCoverlap = CCoverlap_ts - wtofL5S[k][0];
				break;
			}
		}
	}

	if (wtofLCID000101[last_CCtrigger][10] != "opn")
	{
		if (CCoverlap < 0)
		{
			for (int j = last_CCtrigger; j <= Sim.x; j++)
			{
				wtofL5S[j][0] = wtofL5S[j][0];  // 修正時間戳
				if (wtofLCID000101[j][10] == "opcua")
				{
					Sim.CCtrigger = j + 1;
					//cout << "opcua CCtrigger = " << Sim.CCtrigger << endl;
					break;
				}
				else if (j >= (Sim.x - 1))
				{
					Sim.CCtrigger = Sim.x + 1;
				}
			}
		}
		else
		{
			//cout << "CCoverlap = " << CCoverlap << endl;
			for (int j = last_CCtrigger; j <= Sim.x; j++)
			{
				//cout << "還沒加overlap = " << wtofL5S[j][0] << " j = " << j << endl;
				wtofL5S[j][0] = wtofL5S[j][0] + CCoverlap;  // 修正時間戳	
				//cout << "加overlap後 = " << wtofL5S[j][0] << " j= " << j << endl;
				//Sim.outfWGCL_CCoverlap << "index = " << j << "CCoverlap = " << CCoverlap << endl ;
				if (wtofLCID000101[j][10] == "opcua")
				{
					Sim.CCtrigger = j + 1;
					//cout << "opcua CCtrigger = " << Sim.CCtrigger << endl;
					break;
				}
				else if (j >= (Sim.x - 1))
				{
					Sim.CCtrigger = Sim.x + 1;
				}
			}
		}
	}

	for (i = last_CCtrigger; i <= (Sim.CCtrigger-1); i++)
	{	
		//cout << "Sim.CCtrigger-1 = " << Sim.CCtrigger - 1 << endl;
		//cout << "Sim.TTI + Sim.WCwt5 = " << Sim.TTI + Sim.WCwt5 << endl;
		// 若封包由WorkCell發出的時間再5G NR對此流量的Window time內且狀態為Queueing則進行迴圈內的計算
		if ((wtofL5S[i][0] < Sim.TTI + 0.001 + Sim.WCwt5) && (wtofLCID000101[i][0] == "Queueing"))
		{
			wtofUMS000101[i][0] = wtofLCID000101[i][0];

			wtofUMS5TS[i][0] = wtofL5S[i][0];
			stringstream xx;
			xx << setprecision(10) << wtofUMS5TS[i][0];
			wtofUMS000101[i][1] = xx.str();

			wtofUMS5TS[i][1] = wtofL5S[i][1];

			// 判斷此封包是否為傳輸過的，1為已傳輸，0為尚未傳輸
			if (wtofUMS5TS[i][2] != 1)
			{
				for (int j = 2; j < 11; j++)
				{
					wtofUMS000101[i][j] = wtofLCID000101[i][j];
				}

				for (int k = 0; k < 11; k++)
				{
					Sim.outfWGCL_WCCC_1 << wtofUMS000101[i][k] << ' ';
				}
				Sim.outfWGCL_WCCC_1 << endl;
			}
		}
		else
		{
			Sim.CCtrigger = i;
			break;
		}
	}
	breakpoint:
		{}
}

void SchedulingURLLCMS::AWCBufferUpdate(string wtofLCID000100[80000][11], double wtofL4S[80000][2], int Atrigger, double Aoverlap_ts)
{
	int i;
	double Aoverlap = Aoverlap_ts - wtofL4S[Atrigger][0];
	int last_Atrigger = Atrigger;
	
	if (wtofUMS4TS[last_Atrigger - 1][2] == 0 && last_Atrigger != 0)  // 上一輪的Buffered的封包還沒傳完
	{
		//cout << " breakpoint is happened" << endl;
		goto breakpoint;
	}
	if (wtofLCID000100[last_Atrigger][10] == "opn")
	{
		wtofL4S[last_Atrigger][0] = wtofL4S[last_Atrigger][0];
		Sim.Atrigger = last_Atrigger + 1;
	}
	if (Sim.Atrigger >= (Sim.y - 1))
	{
		Aoverlap = Aoverlap_ts - wtofL4S[last_Atrigger][0]; //  傳出最後中斷連線的兩個ack
	}
	else if (Sim.Atrigger < 12)
	{
		//cout << "建立連線時的校正" << endl;
		Aoverlap = Aoverlap_ts - wtofL4S[last_Atrigger][0];
	}
	else
	{
		for (int k = last_Atrigger; k <= Sim.y; k++)
		{
			if (wtofLCID000100[k][10] == "reassemble" || wtofLCID000100[k][10] == "opcua")
			{
				//cout << "reassemble封包的位置 = " << k << endl;
				//cout << "Aoverlap_ts = " << Aoverlap_ts << " -  wtofL4S[k][0] = " << wtofL4S[k][0] << endl;
				Aoverlap = Aoverlap_ts - wtofL4S[k][0];
				break;
			}
		}
	}	

	if (wtofLCID000100[last_Atrigger][10] != "opn")
	{
		if (Aoverlap < 0)
		{
			for (int j = last_Atrigger; j <= Sim.y; j++)
			{
				wtofL4S[j][0] = wtofL4S[j][0];  // 修正時間戳
				if (wtofLCID000100[j][10] == "opcua")
				{
					Sim.Atrigger = j + 1;
					break;
				}
				else if (j >= (Sim.y - 1))
				{
					Sim.Atrigger = Sim.y + 1;
				}
			}
		}
		else
		{
			//cout << "Aoverlap = " << Aoverlap << endl;
			for (int j = last_Atrigger; j <= Sim.y; j++)
			{
				wtofL4S[j][0] = wtofL4S[j][0] + Aoverlap;
				//Sim.outfWGCL_Aoverlap << "index = " << j << "Aoverlap = " << Aoverlap << endl;
				if (wtofLCID000100[j][10] == "opcua")
				{
					Sim.Atrigger = j + 1;
					break;
				}
				else if (j >= (Sim.y - 1))
				{
					Sim.Atrigger = Sim.y + 1;
				}
			}
		}
	}

	for (i = last_Atrigger; i <= (Sim.Atrigger-1); i++)
	{
		// 若封包由WorkCell發出的時間再5G NR對此流量的Window time內且狀態為Queueing則進行迴圈內的計算
		if ((wtofL4S[i][0] < Sim.TTI + 0.001 + Sim.WCwt5 + Sim.WCwt4) && (wtofLCID000100[i][0] == "Queueing"))
		{	
			wtofUMS000100[i][0] = wtofLCID000100[i][0];

			wtofUMS4TS[i][0] = wtofL4S[i][0];
			stringstream xx;
			xx << setprecision(10) << wtofUMS4TS[i][0];
			wtofUMS000100[i][1] = xx.str();

			wtofUMS4TS[i][1] = wtofL4S[i][1];

			// 判斷此封包是否為傳輸過的，1為已傳輸，0為尚未傳輸
			if (wtofUMS4TS[i][2] != 1)
				wtofUMS4TS[i][2] = 0;
			
			for (int j = 2; j < 11; j++)
			{
				wtofUMS000100[i][j] = wtofLCID000100[i][j];
			}

			for (int k = 0; k < 11; k++)
			{
				Sim.outfWGCL_WCA_1 << wtofUMS000100[i][k] << ' ';
			}
			Sim.outfWGCL_WCA_1 << endl;
		}
		else
		{
			Sim.Atrigger = i;
			//cout << " WC Alarming is buffered!" << endl;
			break;
		}	
	}
	breakpoint:
		{}
}

void SchedulingURLLCMS::MWCBufferUpdate(string wtofLCID000000[560000][9], double wtofL0S[560000][2], int Mtrigger)
{
	int i;
	for (i = Mtrigger; i <= Sim.z; i++)
	{
		if ((wtofL0S[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4 + Sim.WCwt0) && (wtofLCID000000[i][0] == "Queueing"))
		{
			wtofUMS0TS[i][0] = wtofL0S[i][0];
			wtofUMS0TS[i][1] = wtofL0S[i][1];
			if (wtofUMS0TS[i][2] != 1)
				wtofUMS0TS[i][2] = 0;
			for (int j = 0; j < 9; j++)
			{
				wtofUMS000000[i][j] = wtofLCID000000[i][j];
				Sim.outfWGCL_WCM_1 << wtofUMS000000[i][j] << ' ';
			}
			Sim.outfWGCL_WCM_1 << endl;
		}
		else
		{
			Sim.Mtrigger = i;
			break;
		}
	}
}

void SchedulingURLLCMS::CCFMBufferUpdate(string FWLCID000101[350000][11], double FWL5S[350000][2], int CCsend_pos, int CClast_pos, double CCrcv_ts)
{

	for (int i = CClast_pos; i < CCsend_pos; i++)
	{
		/*if ((CCrcv_ts + FWL5S[i][0] < Sim.TTI + Sim.FMwt5) && (FWLCID000101[i][0] == "Queueing"))
		{*/
		ftowUMS5TS[i][0] = FWL5S[i][0] + CCrcv_ts;
		ftowUMS5TS[i][1] = FWL5S[i][1];
		if (ftowUMS5TS[i][2] != 1)
			ftowUMS5TS[i][2] = 0;

		ftowUMS000101[i][0] = FWLCID000101[i][0];
		stringstream aa;
		aa << setprecision(10) << ftowUMS5TS[i][0];
		ftowUMS000101[i][1] = aa.str();

		for (int j = 2; j < 11; j++)
		{
			ftowUMS000101[i][j] = FWLCID000101[i][j];
		}
		if (CClast_pos != CCsend_pos)
		{
			for (int k = 0; k < 11; k++)
			{
				Sim.outfWGCL_FMCC_1 << ftowUMS000101[i][k] << ' ';
			}
			Sim.outfWGCL_FMCC_1 << endl;
		}
		//}
	}
	//cout << "FM Buffer is updated! " << endl;
	msBuffer = msBuffer + dataSize;
	interArrivalTime = Sim.TTI + ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5);
}

void SchedulingURLLCMS::AFMBufferUpdate(string FWLCID000010[50000][11], double FWL2S[50000][2], int Asend_pos, int Alast_pos, double Arcv_ts)
{

	for (int i = Alast_pos; i < Asend_pos; i++)
	{
		if ((FWL2S[i][0] < Sim.TTI + Sim.FMwt5 + Sim.FMwt4) && (FWLCID000010[i][0] == "Queueing"))
		{
			ftowUMS4TS[i][0] = FWL2S[i][0] + Arcv_ts;
			ftowUMS4TS[i][1] = FWL2S[i][1];
			if (ftowUMS4TS[i][2] != 1)
				ftowUMS4TS[i][2] = 0;

			ftowUMS000100[i][0] = FWLCID000010[i][0];
			stringstream aa;
			aa << setprecision(10) << ftowUMS4TS[i][0];
			ftowUMS000100[i][1] = aa.str();

			for (int j = 2; j < 11; j++)
			{
				ftowUMS000100[i][j] = FWLCID000010[i][j];
			}
			if (Alast_pos != Asend_pos)
			{
				for (int k = 0; k < 11; k++)
				{
					Sim.outfWGCL_FMA_1 << ftowUMS000100[i][k] << ' ';
				}
				Sim.outfWGCL_FMA_1 << endl;
			}
		}
	}

	//cout << "FM Buffer is updated! " << endl;
	msBuffer = msBuffer + dataSize;
	interArrivalTime = Sim.TTI + ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5);
}

int send_pos_CC_2 = 0, send_pos_A_2 = 0, last_pos_CC_2 = 0, last_pos_A_2 = 0;
int CCnonsent = 0, Anonsent = 0;
int CCovrlap_tri = 0, Aovrlap_tri = 0;
double CCoverlap_ts = 0, Aoverlap_ts = 0;


void SchedulingURLLCMS::scheduler()
{
	double WFrate = 500000000;  //  WC->FM傳輸速率:500 Mbit/s
	double FWrate = 150000000;  //  FM->WC傳輸速率:150 Mbit/s
	double WCcurrent_time = Sim.TTI;
	double FMcurrent_time = Sim.TTI;
	double CCrecvtime, Arecvtime;
	int Aupdated = 0, CCupdated =0;
	string	CCtemp, Atemp;
	int Ack, Seq;
	double CCoverlap = 0.0, Aoverlap= 0.0;
	int xback_finish = 0, yback_finish = 0, y_finish = 0;
	vector<string> v1, v2, v3;

	/*if((int)(Sim.TTI*Sim.quantum) % Sim.feedbackPeriod != 0)*/
	
	WCcurrent_time = Sim.TTI;
	FMcurrent_time = Sim.TTI;

	if (CCnonsent == 1 || last_pos_CC_2 != send_pos_CC_2) // 先將FM未傳的CC回傳
	{	
		/*cout << "繼續上次FM未傳完的CC" << endl;
		cout << "Now is " << Sim.TTI << endl;
		cout << "Current time in FM is " << FMcurrent_time << endl;
		cout << "Current time in WC is " << WCcurrent_time << endl;*/
		
		/*if (CCrecvtime < FMcurrent_time)
			CCrecvtime = FMcurrent_time;*/

		CCrecvtime = Sim.TTI;

		for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
		{
			if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5)//滿足可以排成的要求   ftowUMSxTS[i][2]代表封包是否發送出去
			{
				if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
				{
					if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
					{
						setcolor(12, 0);
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS5TS[j][0];
						cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS5TS[j][0];
						ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000101[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
						}
						Sim.outfWGCL_FMCC_2 << endl;

						if (ftowUMS5TS[j][0] > Sim.TTI)
							WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

						if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
						{
							//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
							if(Sim.wccc_prindex<(Sim.wcccmsg_num-1))
								Sim.wccc_prindex = Sim.wccc_prindex + 1;

							CCoverlap_ts = ftowUMS5TS[j][0];
							CCovrlap_tri = 1;
							CCupdated = 0;
						}
					}
					else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
					{
						setcolor(12, 0);
						ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS5TS[j][0];
						cout << " priority 5 ------- " << setprecision(10) << FMcurrent_time << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS5TS[j][0];
						ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000101[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
						}
						Sim.outfWGCL_FMCC_2 << endl;

						if (ftowUMS5TS[j][0] > Sim.TTI)
							WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

						if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
						{
							//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
							if (Sim.wccc_prindex<(Sim.wcccmsg_num-1))
								Sim.wccc_prindex = Sim.wccc_prindex + 1;

							CCoverlap_ts = ftowUMS5TS[j][0];
							CCovrlap_tri = 1;
							CCupdated = 0;
						}
					}
				}
				else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
				{
					setcolor(12, 0);
					FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
					CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
					FMcurrent_time = CCrecvtime;
					ftowUMS5TS[j][0] = FMcurrent_time;
					cout << " priority 5 ------- " << setprecision(10) << FMcurrent_time << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
					ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
										   //to Work Cell
					ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
					stringstream uu;
					uu << setprecision(10) << ftowUMS5TS[j][0];
					ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
					ftowUMS000101[j][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
					}
					Sim.outfWGCL_FMCC_2 << endl;

					if (ftowUMS5TS[j][0] > Sim.TTI)
						WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

					if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
					{
						//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
						if (Sim.wccc_prindex<(Sim.wcccmsg_num-1))
							Sim.wccc_prindex = Sim.wccc_prindex + 1;

						CCoverlap_ts = ftowUMS5TS[j][0];
						CCovrlap_tri = 1;
						CCupdated = 0;
					}
				}
				last_pos_CC_2++;
			}

			else   // 回傳的封包還沒傳出去
			{
				/*setcolor(12, 1);
				cout << "CC下一週期回傳仍失敗!!!!!" << endl;
				cout << "ftowUMS5TS[j][0] = " << ftowUMS5TS[j][0] << endl;
				cout << "Sim.TTI = " << Sim.TTI << endl;
				cout << "Sim.FMwt5 = " << Sim.FMwt5 << endl;
				cout << "FMcurrent_time = " << FMcurrent_time << endl;*/
				CCnonsent = 1;
				CCovrlap_tri = 0;
				break;
			}

			CCnonsent = 0;
		}
	}


	if (CCnonsent == 0)
	{
		if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
		{
			Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
			CCovrlap_tri = 0;
			CCupdated = 1;
		}

		for (int i = 0; i < Sim.x; i++) //--------------------------------------P5
		{
			if ((wtofUMS5TS[i][0] < Sim.TTI + Sim.WCwt5) && wtofUMS5TS[i][0] != 0 && wtofUMS5TS[i][2] == 0 && WCcurrent_time < Sim.TTI + Sim.WCwt5)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
			{
				if (wtofUMS5TS[i][0] >= Sim.TTI)//在他該傳送的區間內
				{
					if (wtofUMS5TS[i][0] >= WCcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate; // 將原本發送的ts加上傳輸時間 (WC--->gNB)
						WCcurrent_time = wtofUMS5TS[i][0]; //封包完整傳輸後，下一個封包可以傳輸的時間點
						cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (+傳輸時間後) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS5TS[i][2] = 1;  //將封包標示為已朝FM發送

						//to Factory Management
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;   //將原本發送的ts加上傳輸時間 (gNB--->FM)
						stringstream xx;
						xx << setprecision(10) << wtofUMS5TS[i][0];
						wtofUMS000101[i][1] = xx.str();	//紀錄封包到達FM的時間
						wtofUMS000101[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
						}
						Sim.outfWGCL_WCCC_2 << endl;

						CCrecvtime = wtofUMS5TS[i][0];


						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包

						if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
						{
							//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

							if (wtofUMS000101[i][10] == "opcua")
								if (Sim.fmcc_prindex<(Sim.fmccmsg_num-1))
									Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

							SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
	
							for (int j = last_pos_CC_2; j <= Sim.xback; j++)
							{
								CCtemp = Sim.ftowLCID000101[j][8];
								SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									CCtemp = Sim.ftowLCID000101[j][10];
									if (CCtemp == "opn")
									{
										send_pos_CC_2 = 1;
										break;
									}
									if (CCtemp == "opcua")
									{
										send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.xback-1) && xback_finish == 0)
									{
										//cout << "最後一個CC位置 = " << j+1 << endl;
										send_pos_CC_2 = j+1;
										xback_finish = 1;
									}
								}
							}
							Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update

							for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
							{
								if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
									{
										if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;
											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}

										}
										else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;
											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
									}
									else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS5TS[j][0] = FMcurrent_time;
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;
										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
									last_pos_CC_2++;
									if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
									{
										Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
										CCovrlap_tri = 0;
										CCupdated = 1;
										CCnonsent = 0;
										
										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}

								else   // 回傳的封包還沒傳出去
								{
									CCnonsent = 1;
									break;
								}
							}
							if (CCnonsent == 1)
								break;
						}
					}
					else if (wtofUMS5TS[i][0] < WCcurrent_time) //跟該週期前面的封包撞，因為前面的封包還沒被發送出去
					{
						setcolor(10, 0);
						wtofUMS5TS[i][0] = WCcurrent_time + (double)wtofUMS5TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS5TS[i][0];
						cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS5TS[i][2] = 1; //將封包標示為已朝FM發送

						//to Factory Management
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS5TS[i][0];
						wtofUMS000101[i][1] = xx.str();  //紀錄封包到達FM的時間
						wtofUMS000101[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
						}
						Sim.outfWGCL_WCCC_2 << endl;

						CCrecvtime = wtofUMS5TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包
						if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
						{
							//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;
							
							if (wtofUMS000101[i][10] == "opcua")
								if (Sim.fmcc_prindex<(Sim.fmccmsg_num-1))
									Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

							SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_CC_2; j <= Sim.xback; j++)
							{
								CCtemp = Sim.ftowLCID000101[j][8];
								SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									CCtemp = Sim.ftowLCID000101[j][10];
									if (CCtemp == "opn")
									{
										send_pos_CC_2 = 1;
										break;
									}
									if (CCtemp == "opcua")
									{
										send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.xback-1) && xback_finish == 0)  //  最後一個回傳的ACK
									{
										//cout << "最後一個CC位置 = " << j+1 << endl;
										send_pos_CC_2 = j+1;
										xback_finish = 1;
									}
								}
							}
							Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update


							for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
							{
								if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
									{
										if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}

										}
										else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
									}
									else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS5TS[j][0] = FMcurrent_time;
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
									last_pos_CC_2++;
									if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
									{
										Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
										CCovrlap_tri = 0;
										CCupdated = 1;
										CCnonsent = 0;
										
										//FM回傳完成，WC準備下一輪Req的發布
									}
								}
								else    // 回傳的封包還沒傳出去
								{
									CCnonsent = 1;
									break;
								}
							}
							if (CCnonsent == 1)
							{
								break;
							}
						}
					}
				}
				else if (wtofUMS5TS[i][0] < Sim.TTI) //不在他該傳送的區間內
				{
					setcolor(10, 0);
					//cout << " CCtrigger = " << Sim.CCtrigger << endl;
					//cout << " wtofUMS5TS[i][0] = " << wtofUMS5TS[i][0] << endl;
					//cout << " wtofUMS5TS[i+1][0] = " << wtofUMS5TS[i+1][0] << endl;
					WCcurrent_time = WCcurrent_time + (double)wtofUMS5TS[i][1] * 8 / WFrate;
					wtofUMS5TS[i][0] = WCcurrent_time;
					cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
					wtofUMS5TS[i][2] = 1;
					//to Factory Management
					wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS5TS[i][0];
					wtofUMS000101[i][1] = xx.str();	//紀錄封包到達FM的時間
					wtofUMS000101[i][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
					}
					Sim.outfWGCL_WCCC_2 << endl;

					CCrecvtime = wtofUMS5TS[i][0];


					/*******************開始進行回傳 FM->WC *********************/
					if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
					{
						//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;
						
						if (wtofUMS000101[i][10] == "opcua")
							if (Sim.fmcc_prindex<(Sim.fmccmsg_num-1))
								Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

						SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
						Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
						setcolor(13, 0);
						//cout << "Ack_num = " << Ack << endl;
						v1.clear();
						for (int j = last_pos_CC_2; j <= Sim.xback; j++)
						{
							CCtemp = Sim.ftowLCID000101[j][8];
							SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
							Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
							v2.clear();
							if (Seq >= Ack)
							{
								CCtemp = Sim.ftowLCID000101[j][10];
								if (CCtemp == "opn")
								{
									send_pos_CC_2 = 1;
									break;
								}
								if (CCtemp == "opcua")
								{
									send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
									break;
								}
								if (j == (Sim.xback-1) && xback_finish == 0)
								{
									//cout << "最後一個CC位置 = " << j+1 << endl;
									send_pos_CC_2 = j+1;
									xback_finish = 1;
								}
		
							}
						}
						Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update


						for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
						{
							if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
							{
								if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
								{
									if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
									{
										setcolor(12, 0);
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS5TS[j][0];
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}

									}
									else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
									{
										setcolor(12, 0);
										ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS5TS[j][0];
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
								}
								else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
								{
									setcolor(12, 0);
									FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
									CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
									ftowUMS5TS[j][0] = FMcurrent_time;
									cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
									ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
														   //to Work Cell
									ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
									stringstream uu;
									uu << setprecision(10) << ftowUMS5TS[j][0];
									ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
									ftowUMS000101[j][0] = "Received";
									for (int t = 0; t < 11; t++)
									{
										Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
									}
									Sim.outfWGCL_FMCC_2 << endl;

									WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

									if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
									{
										//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
										if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
											Sim.wccc_prindex = Sim.wccc_prindex + 1;

										CCoverlap_ts = ftowUMS5TS[j][0];
										CCovrlap_tri = 1;
										CCupdated = 0;
									}
								}
								last_pos_CC_2++;
								if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
								{
									Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
									CCovrlap_tri = 0;
									CCupdated = 1;
									CCnonsent = 0;
									
									//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
								}
							}
							else //if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5)   // 回傳的封包還沒傳出去
							{
								CCnonsent = 1;
								break;
							}
						}
						if (CCnonsent == 1)
							break;
					}
				}
			}
		}
	}

	WCcurrent_time = Sim.TTI + Sim.WCwt5;
	FMcurrent_time = Sim.TTI + Sim.FMwt5;


	if (Anonsent == 1 || last_pos_A_2 != send_pos_A_2) // 先將FM未傳的Alarming回傳
	{
		//cout << "繼續上次FM未傳完的A" << endl;

		Arecvtime = Sim.TTI + Sim.FMwt5;

		for (int j = last_pos_A_2; j < send_pos_A_2; j++)
		{
			if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5 + Sim.FMwt4) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5 + Sim.FMwt4)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
			{
				if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5)//在他該傳送的區間內
				{
					if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
					{
						setcolor(12, 0);
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS4TS[j][0];
						cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS4TS[j][0];
						ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000100[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
						}
						Sim.outfWGCL_FMA_2 << endl;

						if (ftowUMS4TS[j][0] > (Sim.TTI + Sim.WCwt5))
							WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

						if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
						{
							//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
							if (Sim.wca_prindex<(Sim.wcamsg_num-1))
								Sim.wca_prindex = Sim.wca_prindex + 1;

							Aoverlap_ts = ftowUMS4TS[j][0];
							Aovrlap_tri = 1;
							Aupdated = 0;
						}

					}
					else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
					{
						setcolor(12, 0);
						ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS4TS[j][0];
						cout << " priority 4 ------- " << setprecision(10) << FMcurrent_time << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS4TS[j][0];
						ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000100[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
						}
						Sim.outfWGCL_FMA_2 << endl;

						if (ftowUMS4TS[j][0] >(Sim.TTI + Sim.WCwt5))
							WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
						
						if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
						{
							//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
							if (Sim.wca_prindex<(Sim.wcamsg_num-1))
								Sim.wca_prindex = Sim.wca_prindex + 1;

							Aoverlap_ts = ftowUMS4TS[j][0];
							Aovrlap_tri = 1;
							Aupdated = 0;
						}
					}
				}
				else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI + Sim.FMwt5 +  Sim.FMwt4)
				{
					setcolor(12, 0);
					FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
					Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
					ftowUMS4TS[j][0] = FMcurrent_time;
					cout << " priority 4 ------- " << setprecision(10) << FMcurrent_time << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
					ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
										   //to Work Cell
					ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
					stringstream uu;
					uu << setprecision(10) << ftowUMS4TS[j][0];
					ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
					ftowUMS000100[j][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
					}
					Sim.outfWGCL_FMA_2 << endl;
					
					if (ftowUMS4TS[j][0] >(Sim.TTI + Sim.WCwt5))
						WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
					
					if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
					{
						//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
						if (Sim.wca_prindex<(Sim.wcamsg_num-1))
							Sim.wca_prindex = Sim.wca_prindex + 1;

						Aoverlap_ts = ftowUMS4TS[j][0];
						Aovrlap_tri = 1;
						Aupdated = 0;
					}
				}
				last_pos_A_2++;
			}
			else    // 回傳的封包還沒傳出去
			{
				Anonsent = 1;
				Aovrlap_tri = 0;
				break;
			}
			Anonsent = 0;
		}
	}

	if (Anonsent == 0)
	{	
		//cout << "Sim.Atrigger = " << Sim.Atrigger << endl;
		if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
		{
			Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
			Aupdated = 1;
			Aovrlap_tri = 0;
		}		

		for (int i = 0; i < Sim.y; i++)//--------------------------------------P2
		{
			if ((wtofUMS4TS[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4) && wtofUMS4TS[i][0] != 0 && wtofUMS4TS[i][2] == 0 && WCcurrent_time < Sim.TTI + Sim.WCwt5 + Sim.WCwt4)//滿足可以排成的要求
			{
				if (wtofUMS4TS[i][0] >= Sim.TTI + Sim.WCwt5)//在他該傳送的區間內
				{
					if (wtofUMS4TS[i][0] >= WCcurrent_time)//沒跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS4TS[i][0];
						cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (+傳輸時間後) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS4TS[i][2] = 1;
						//to Factory Management
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS4TS[i][0];
						wtofUMS000100[i][1] = xx.str();
						wtofUMS000100[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
						}
						Sim.outfWGCL_WCA_2 << endl;

						Arecvtime = wtofUMS4TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包
						if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
						{
							//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

							if (wtofUMS000100[i][10] == "opcua")
								if (Sim.fma_prindex<(Sim.fmamsg_num-1))
									Sim.fma_prindex = Sim.fma_prindex + 1;

							SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_A_2; j < Sim.yback; j++)
							{
								Atemp = Sim.ftowLCID000100[j][8];
								SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									Atemp = Sim.ftowLCID000100[j][10];
									if (Atemp == "opn")
									{
										send_pos_A_2 = 1;
										break;
									}
									if (Atemp == "opcua")
									{
										send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.yback - 1) && yback_finish == 0)
									{
										//cout << "最後一個A位置 = " << j + 1 << endl;
										send_pos_A_2 = j + 1;
										yback_finish = 1;
									}
								}
							}
							Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

							for (int j = last_pos_A_2; j < send_pos_A_2; j++)
							{
								if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5 + Sim.FMwt4) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5 + Sim.FMwt4)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5)//在他該傳送的區間內
									{
										if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
										else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
										}
									}
									else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS4TS[j][0] = FMcurrent_time;
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

									}
									last_pos_A_2++;
									if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
									{
										Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
										Aupdated = 1;
										Aovrlap_tri = 0;
										Anonsent = 0;
										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}
								else //if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5 + Sim.FMwt4)   // 回傳的封包還沒傳出去
								{
									/*setcolor(12, 1);
									cout << "Window_2 is closed~" << endl;
									cout << "ftowUMS4TS[j][0] = " << ftowUMS4TS[j][0] << endl;
									cout << "Sim.TTI = " << Sim.TTI << endl;
									cout << "Sim.FMwt5 = " << Sim.FMwt5 << endl;
									cout << "Sim.FMwt4 = " << Sim.FMwt4 << endl;
									cout << "FMcurrent_time = " << FMcurrent_time << endl;*/
									Anonsent = 1;
									break;
									//Sim.TTI + (double)1 / Sim.quantum;
								}

							}
							if (Anonsent == 1)
								break;
						}
					}
					else if (wtofUMS4TS[i][0] < WCcurrent_time)//跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS4TS[i][0] = WCcurrent_time + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS4TS[i][0];
						cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS4TS[i][2] = 1;
						//to Factory Management
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS4TS[i][0];
						wtofUMS000100[i][1] = xx.str();
						wtofUMS000100[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
						}
						Sim.outfWGCL_WCA_2 << endl;

						Arecvtime = wtofUMS4TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包

						if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
						{
							//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

							if (wtofUMS000100[i][10] == "opcua")
								if (Sim.fma_prindex<(Sim.fmamsg_num-1))
									Sim.fma_prindex = Sim.fma_prindex + 1;

							SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_A_2; j < Sim.yback; j++)
							{
								Atemp = Sim.ftowLCID000100[j][8];
								SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									Atemp = Sim.ftowLCID000100[j][10];
									if (Atemp == "opn")
									{
										send_pos_A_2 = 1;
										break;
									}
									if (Atemp == "opcua")
									{
										send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.yback - 1) && yback_finish == 0)
									{
										//cout << "最後一個A位置 = " << j + 1 << endl;
										send_pos_A_2 = j + 1;
										yback_finish = 1;
									}
								}
							}
							Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

							for (int j = last_pos_A_2; j < send_pos_A_2; j++)
							{
								if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5 + Sim.FMwt4) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5 + Sim.FMwt4)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5)//在他該傳送的區間內
									{
										if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time


										}
										else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
									}
									else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS4TS[j][0] = FMcurrent_time;
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
									}
									last_pos_A_2++;
									if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
									{
										Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
										Aupdated = 1;
										Aovrlap_tri = 0;
										Anonsent = 0;
										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}
								else    // 回傳的封包還沒傳出去
								{
									Anonsent = 1;
									break;
								}

							}
							if (Anonsent == 1)
								break;
						}					
					}
				}
				else  //不在他該傳送的區間內  (UMS2TS[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4)
				{
					/*cout << "wtofUMS4TS[i][0] = " << wtofUMS4TS[i][0] << "i = " << i << endl;
					cout << " Sim.TTI = " << Sim.TTI << endl;
					cout << "Sim.WCwt5 = " << Sim.WCwt5 << endl;
					cout << "Sim.WCwt4 = " << Sim.WCwt4 << endl;
					cout << "WCcurrent_time = " << WCcurrent_time << endl;*/
					setcolor(10, 0);
					WCcurrent_time = WCcurrent_time + (double)wtofUMS4TS[i][1] * 8 / WFrate;
					/*stringstream ss;
					ss << setprecision(10) << WCcurrent_time;
					wtofUMS000100[i][1] = ss.str();*/
					wtofUMS4TS[i][0] = WCcurrent_time;
					cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
					wtofUMS4TS[i][2] = 1;

					//to Factory Management
					wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS4TS[i][0];
					wtofUMS000100[i][1] = xx.str();
					wtofUMS000100[i][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
					}
					Sim.outfWGCL_WCA_2 << endl;

					Arecvtime = wtofUMS4TS[i][0];

					/*******************開始進行回傳 FM->WC *********************/
					// TODO //
					// 先找出FM需要回傳到第幾個封包

					if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
					{
						//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

						if (wtofUMS000100[i][10] == "opcua")
							if (Sim.fma_prindex<(Sim.fmamsg_num-1))
								Sim.fma_prindex = Sim.fma_prindex + 1;

						SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
						Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
						setcolor(13, 0);
						//cout << "Ack_num = " << Ack << endl;
						v1.clear();
						for (int j = last_pos_A_2; j < Sim.yback; j++)
						{
							Atemp = Sim.ftowLCID000100[j][8];
							SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
							Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
							v2.clear();
							if (Seq >= Ack)
							{
								Atemp = Sim.ftowLCID000100[j][10];
								if (Atemp == "opn")
								{
									send_pos_A_2 = 1;
									break;
								}
								if (Atemp == "opcua")
								{
									send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
									break;
								}
								if (j == (Sim.yback - 1) && yback_finish == 0)
								{
									//cout << "最後一個A位置 = " << j + 1 << endl;
									send_pos_A_2 = j + 1;
									yback_finish = 1;
								}
							}
						}
						Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

						for (int j = last_pos_A_2; j < send_pos_A_2; j++)
						{
							if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5 + Sim.FMwt4) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5 + Sim.FMwt4)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
							{
								if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5)//在他該傳送的區間內
								{
									if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
									{
										setcolor(12, 0);
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS4TS[j][0];
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

									}
									else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
									{
										setcolor(12, 0);
										ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS4TS[j][0];
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

									}
								}
								else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
								{
									setcolor(12, 0);
									FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
									Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
									ftowUMS4TS[j][0] = FMcurrent_time;
									cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
									ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
														   //to Work Cell
									ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
									stringstream uu;
									uu << setprecision(10) << ftowUMS4TS[j][0];
									ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
									ftowUMS000100[j][0] = "Received";
									for (int t = 0; t < 11; t++)
									{
										Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
									}
									Sim.outfWGCL_FMA_2 << endl;

									if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
									{
										//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
										if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
											Sim.wca_prindex = Sim.wca_prindex + 1;

										Aoverlap_ts = ftowUMS4TS[j][0];
										Aovrlap_tri = 1;
										Aupdated = 0;
									}

									WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
								}
								last_pos_A_2++;
								if (last_pos_A_2 == send_pos_A_2 && Anonsent == 0)
								{
									Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
									Aupdated = 1;
									Aovrlap_tri = 0;
									Anonsent = 0;
									//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
								}
							}
							else  // 回傳的封包還沒傳出去
							{
								Anonsent = 1;
								break;

							}
						}
						if (Anonsent == 1)
							break;
					}
				}
			}
		}
	}

	WCcurrent_time = Sim.TTI + Sim.WCwt5 + Sim.WCwt4;

	Sim.scheduling->MWCBufferUpdate(Sim.wtofLCID000000, Sim.wtofL0S, Sim.Mtrigger);  // Buffer update

	for (int i = 0; i < Sim.z; i++)//--------------------------------------P1  UDP無須回傳
	{
		if ((wtofUMS0TS[i][0] < Sim.TTI + Sim.WCwt0 + Sim.WCwt4 + Sim.WCwt5) && wtofUMS0TS[i][0] != 0 && wtofUMS0TS[i][2] == 0 && WCcurrent_time<Sim.TTI + Sim.WCwt5 + Sim.WCwt4 + Sim.WCwt0)//滿足可以排成的要求
		{
			if (wtofUMS0TS[i][0] >= Sim.TTI + Sim.WCwt4 + Sim.WCwt5)//在他該傳送的區間內
			{
				if (wtofUMS0TS[i][0] >= WCcurrent_time)//沒跟前面的封包撞
				{	
					setcolor(10, 0);
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;

					WCcurrent_time = wtofUMS0TS[i][0];
					cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (+傳輸時間後) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
					wtofUMS0TS[i][2] = 1;
					//to Factory Management
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = xx.str();
					wtofUMS000000[i][0] = "Received";
					if (wtofUMS000000[i][8] == "opcua")
					{
						//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
						if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
							Sim.wcm_prindex = Sim.wcm_prindex + 1;
					}
					for (int t = 0; t < 9; t++)
					{
						Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
					}
					Sim.outfWGCL_WCM_2 << endl;
				}
				else if (wtofUMS0TS[i][0] < WCcurrent_time)//跟前面的封包撞
				{
					setcolor(10, 0);
					wtofUMS0TS[i][0] = WCcurrent_time + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					WCcurrent_time = wtofUMS0TS[i][0];
					/*stringstream ss;
					ss << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = ss.str();*/
					cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
					wtofUMS0TS[i][2] = 1;
					//to Factory Management
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = xx.str();
					wtofUMS000000[i][0] = "Received";
					if (wtofUMS000000[i][8] == "opcua")
					{
						//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
						if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
							Sim.wcm_prindex = Sim.wcm_prindex + 1;
					}
					for (int t = 0; t < 9; t++)
					{
						Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
					}
					Sim.outfWGCL_WCM_2 << endl;
				}
			}
			else
			{
				setcolor(10, 0);
				WCcurrent_time = WCcurrent_time + (double)wtofUMS0TS[i][1] * 8 / WFrate;
				wtofUMS0TS[i][0] = WCcurrent_time;
				cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
				wtofUMS0TS[i][2] = 1;
				//to Factory Management
				wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
				stringstream xx;
				xx << setprecision(10) << wtofUMS0TS[i][0];
				wtofUMS000000[i][1] = xx.str();
				wtofUMS000000[i][0] = "Received";
				if (wtofUMS000000[i][8] == "opcua")
				{
					//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
					if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
						Sim.wcm_prindex = Sim.wcm_prindex + 1;
				}
				for (int t = 0; t < 9; t++)
				{
					Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
				}
				Sim.outfWGCL_WCM_2 << endl;
			}
		}
	}	
}

void SchedulingURLLCMS::LCP()
{
	double WFrate = 500000000;  //  WC->FM傳輸速率:500 Mbit/s
	double FWrate = 150000000;  //  FM->WC傳輸速率:150 Mbit/s
	double WCcurrent_time = Sim.TTI;
	double FMcurrent_time = Sim.TTI;
	double CCrecvtime, Arecvtime;
	int Aupdated = 0, CCupdated = 0;
	string	CCtemp, Atemp;
	int Ack, Seq;
	double CCoverlap = 0.0, Aoverlap = 0.0;
	int xback_finish = 0, yback_finish = 0, y_finish = 0;
	vector<string> v1, v2, v3;

	/*if((int)(Sim.TTI*Sim.quantum) % Sim.feedbackPeriod != 0)*/

	WCcurrent_time = Sim.TTI;
	FMcurrent_time = Sim.TTI;

	if (CCnonsent == 1 || last_pos_CC_2 != send_pos_CC_2) // 先將FM未傳的CC回傳
	{
		/*cout << "繼續上次FM未傳完的CC" << endl;
		cout << "Now is " << Sim.TTI << endl;
		cout << "Current time in FM is " << FMcurrent_time << endl;
		cout << "Current time in WC is " << WCcurrent_time << endl;*/

		/*if (CCrecvtime < FMcurrent_time)
		CCrecvtime = FMcurrent_time;*/

		CCrecvtime = Sim.TTI;

		for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
		{
			if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1)//滿足可以排成的要求   ftowUMSxTS[i][2]代表封包是否發送出去
			{
				if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
				{
					if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
					{
						setcolor(12, 0);
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS5TS[j][0];
						cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS5TS[j][0];
						ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000101[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
						}
						Sim.outfWGCL_FMCC_2 << endl;

						if (ftowUMS5TS[j][0] > Sim.TTI)
							WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

						if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
						{
							//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
							if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
								Sim.wccc_prindex = Sim.wccc_prindex + 1;

							CCoverlap_ts = ftowUMS5TS[j][0];
							CCovrlap_tri = 1;
							CCupdated = 0;
						}
					}
					else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
					{
						setcolor(12, 0);
						ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS5TS[j][0];
						cout << " priority 5 ------- " << setprecision(10) << FMcurrent_time << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS5TS[j][0];
						ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000101[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
						}
						Sim.outfWGCL_FMCC_2 << endl;

						if (ftowUMS5TS[j][0] > Sim.TTI)
							WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

						if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
						{
							//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
							if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
								Sim.wccc_prindex = Sim.wccc_prindex + 1;

							CCoverlap_ts = ftowUMS5TS[j][0];
							CCovrlap_tri = 1;
							CCupdated = 0;
						}
					}
				}
				else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
				{
					setcolor(12, 0);
					FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
					CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
					FMcurrent_time = CCrecvtime;
					ftowUMS5TS[j][0] = FMcurrent_time;
					cout << " priority 5 ------- " << setprecision(10) << FMcurrent_time << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
					ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
										   //to Work Cell
					ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
					stringstream uu;
					uu << setprecision(10) << ftowUMS5TS[j][0];
					ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
					ftowUMS000101[j][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
					}
					Sim.outfWGCL_FMCC_2 << endl;

					if (ftowUMS5TS[j][0] > Sim.TTI)
						WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

					if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
					{
						//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
						if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
							Sim.wccc_prindex = Sim.wccc_prindex + 1;

						CCoverlap_ts = ftowUMS5TS[j][0];
						CCovrlap_tri = 1;
						CCupdated = 0;
					}
				}
				last_pos_CC_2++;
			}

			else   // 回傳的封包還沒傳出去
			{
				CCnonsent = 1;
				CCovrlap_tri = 0;
				break;
			}

			CCnonsent = 0;
		}
	}


	if (CCnonsent == 0)
	{
		if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
		{
			Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
			CCovrlap_tri = 0;
			CCupdated = 1;
		}

		for (int i = 0; i < Sim.x; i++) //--------------------------------------P5
		{
			if ((wtofUMS5TS[i][0] < Sim.TTI + Sim.WCwt5_1) && wtofUMS5TS[i][0] != 0 && wtofUMS5TS[i][2] == 0 && WCcurrent_time < Sim.TTI + Sim.WCwt5_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
			{
				if (wtofUMS5TS[i][0] >= Sim.TTI)//在他該傳送的區間內
				{
					if (wtofUMS5TS[i][0] >= WCcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate; // 將原本發送的ts加上傳輸時間 (WC--->gNB)
						WCcurrent_time = wtofUMS5TS[i][0]; //封包完整傳輸後，下一個封包可以傳輸的時間點
						cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (+傳輸時間後) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS5TS[i][2] = 1;  //將封包標示為已朝FM發送

											   //to Factory Management
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;   //將原本發送的ts加上傳輸時間 (gNB--->FM)
						stringstream xx;
						xx << setprecision(10) << wtofUMS5TS[i][0];
						wtofUMS000101[i][1] = xx.str();	//紀錄封包到達FM的時間
						wtofUMS000101[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
						}
						Sim.outfWGCL_WCCC_2 << endl;

						CCrecvtime = wtofUMS5TS[i][0];


						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包

						if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
						{
							//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

							if (wtofUMS000101[i][10] == "opcua")
								if (Sim.fmcc_prindex<(Sim.fmccmsg_num - 1))
									Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

							SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();

							for (int j = last_pos_CC_2; j <= Sim.xback; j++)
							{
								CCtemp = Sim.ftowLCID000101[j][8];
								SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									CCtemp = Sim.ftowLCID000101[j][10];
									if (CCtemp == "opn")
									{
										send_pos_CC_2 = 1;
										break;
									}
									if (CCtemp == "opcua")
									{
										send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.xback - 1) && xback_finish == 0)
									{
										//cout << "最後一個CC位置 = " << j+1 << endl;
										send_pos_CC_2 = j + 1;
										xback_finish = 1;
									}
								}
							}
							Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update

							for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
							{
								if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
									{
										if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;
											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}

										}
										else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;
											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
									}
									else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS5TS[j][0] = FMcurrent_time;
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;
										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
									last_pos_CC_2++;
									if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
									{
										Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
										CCovrlap_tri = 0;
										CCupdated = 1;
										CCnonsent = 0;

										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}

								else   // 回傳的封包還沒傳出去
								{
									CCnonsent = 1;
									break;
								}
							}
							if (CCnonsent == 1)
								break;
						}
					}
					else if (wtofUMS5TS[i][0] < WCcurrent_time) //跟該週期前面的封包撞，因為前面的封包還沒被發送出去
					{
						setcolor(10, 0);
						wtofUMS5TS[i][0] = WCcurrent_time + (double)wtofUMS5TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS5TS[i][0];
						cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS5TS[i][2] = 1; //將封包標示為已朝FM發送

											  //to Factory Management
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS5TS[i][0];
						wtofUMS000101[i][1] = xx.str();  //紀錄封包到達FM的時間
						wtofUMS000101[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
						}
						Sim.outfWGCL_WCCC_2 << endl;

						CCrecvtime = wtofUMS5TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包
						if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
						{
							//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

							if (wtofUMS000101[i][10] == "opcua")
								if (Sim.fmcc_prindex<(Sim.fmccmsg_num - 1))
									Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

							SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_CC_2; j <= Sim.xback; j++)
							{
								CCtemp = Sim.ftowLCID000101[j][8];
								SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									CCtemp = Sim.ftowLCID000101[j][10];
									if (CCtemp == "opn")
									{
										send_pos_CC_2 = 1;
										break;
									}
									if (CCtemp == "opcua")
									{
										send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.xback - 1) && xback_finish == 0)  //  最後一個回傳的ACK
									{
										//cout << "最後一個CC位置 = " << j+1 << endl;
										send_pos_CC_2 = j + 1;
										xback_finish = 1;
									}
								}
							}
							Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update


							for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
							{
								if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
									{
										if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}

										}
										else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
									}
									else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS5TS[j][0] = FMcurrent_time;
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
									last_pos_CC_2++;
									if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
									{
										Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
										CCovrlap_tri = 0;
										CCupdated = 1;
										CCnonsent = 0;

										//FM回傳完成，WC準備下一輪Req的發布
									}
								}
								else    // 回傳的封包還沒傳出去
								{
									CCnonsent = 1;
									break;
								}
							}
							if (CCnonsent == 1)
							{
								break;
							}
						}
					}
				}
				else if (wtofUMS5TS[i][0] < Sim.TTI) //不在他該傳送的區間內
				{
					setcolor(10, 0);
					//cout << " CCtrigger = " << Sim.CCtrigger << endl;
					//cout << " wtofUMS5TS[i][0] = " << wtofUMS5TS[i][0] << endl;
					//cout << " wtofUMS5TS[i+1][0] = " << wtofUMS5TS[i+1][0] << endl;
					WCcurrent_time = WCcurrent_time + (double)wtofUMS5TS[i][1] * 8 / WFrate;
					wtofUMS5TS[i][0] = WCcurrent_time;
					cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
					wtofUMS5TS[i][2] = 1;
					//to Factory Management
					wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS5TS[i][0];
					wtofUMS000101[i][1] = xx.str();	//紀錄封包到達FM的時間
					wtofUMS000101[i][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
					}
					Sim.outfWGCL_WCCC_2 << endl;

					CCrecvtime = wtofUMS5TS[i][0];


					/*******************開始進行回傳 FM->WC *********************/
					if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
					{
						//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

						if (wtofUMS000101[i][10] == "opcua")
							if (Sim.fmcc_prindex<(Sim.fmccmsg_num - 1))
								Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

						SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
						Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
						setcolor(13, 0);
						//cout << "Ack_num = " << Ack << endl;
						v1.clear();
						for (int j = last_pos_CC_2; j <= Sim.xback; j++)
						{
							CCtemp = Sim.ftowLCID000101[j][8];
							SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
							Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
							v2.clear();
							if (Seq >= Ack)
							{
								CCtemp = Sim.ftowLCID000101[j][10];
								if (CCtemp == "opn")
								{
									send_pos_CC_2 = 1;
									break;
								}
								if (CCtemp == "opcua")
								{
									send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
									break;
								}
								if (j == (Sim.xback - 1) && xback_finish == 0)
								{
									//cout << "最後一個CC位置 = " << j+1 << endl;
									send_pos_CC_2 = j + 1;
									xback_finish = 1;
								}

							}
						}
						Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update


						for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
						{
							if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
							{
								if (ftowUMS5TS[j][0] >= Sim.TTI)//在他該傳送的區間內
								{
									if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
									{
										setcolor(12, 0);
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS5TS[j][0];
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}

									}
									else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
									{
										setcolor(12, 0);
										ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS5TS[j][0];
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
								}
								else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
								{
									setcolor(12, 0);
									FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
									CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
									ftowUMS5TS[j][0] = FMcurrent_time;
									cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
									ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
														   //to Work Cell
									ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
									stringstream uu;
									uu << setprecision(10) << ftowUMS5TS[j][0];
									ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
									ftowUMS000101[j][0] = "Received";
									for (int t = 0; t < 11; t++)
									{
										Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
									}
									Sim.outfWGCL_FMCC_2 << endl;

									WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

									if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
									{
										//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
										if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
											Sim.wccc_prindex = Sim.wccc_prindex + 1;

										CCoverlap_ts = ftowUMS5TS[j][0];
										CCovrlap_tri = 1;
										CCupdated = 0;
									}
								}
								last_pos_CC_2++;
								if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
								{
									Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
									CCovrlap_tri = 0;
									CCupdated = 1;
									CCnonsent = 0;

									//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
								}
							}
							else //if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5)   // 回傳的封包還沒傳出去
							{
								CCnonsent = 1;
								break;
							}
						}
						if (CCnonsent == 1)
							break;
					}
				}
			}
		}
	}

	WCcurrent_time = Sim.TTI + Sim.WCwt5_1;
	FMcurrent_time = Sim.TTI + Sim.FMwt5_1;

	if (Anonsent == 1 || last_pos_A_2 != send_pos_A_2) // 先將FM未傳的Alarming回傳
	{
		//cout << "繼續上次FM未傳完的A" << endl;

		Arecvtime = Sim.TTI + Sim.FMwt5;

		for (int j = last_pos_A_2; j < send_pos_A_2; j++)
		{
			if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
			{
				if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1)//在他該傳送的區間內
				{
					if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
					{
						setcolor(12, 0);
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS4TS[j][0];
						cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS4TS[j][0];
						ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000100[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
						}
						Sim.outfWGCL_FMA_2 << endl;

						if (ftowUMS4TS[j][0] >(Sim.TTI + Sim.WCwt5))
							WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

						if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
						{
							//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
							if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
								Sim.wca_prindex = Sim.wca_prindex + 1;

							Aoverlap_ts = ftowUMS4TS[j][0];
							Aovrlap_tri = 1;
							Aupdated = 0;
						}

					}
					else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
					{
						setcolor(12, 0);
						ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = ftowUMS4TS[j][0];
						cout << " priority 4 ------- " << setprecision(10) << FMcurrent_time << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS4TS[j][0];
						ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000100[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
						}
						Sim.outfWGCL_FMA_2 << endl;

						if (ftowUMS4TS[j][0] >(Sim.TTI + Sim.WCwt5))
							WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

						if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
						{
							//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
							if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
								Sim.wca_prindex = Sim.wca_prindex + 1;

							Aoverlap_ts = ftowUMS4TS[j][0];
							Aovrlap_tri = 1;
							Aupdated = 0;
						}
					}
				}
				else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI + Sim.FMwt5 +  Sim.FMwt4)
				{
					setcolor(12, 0);
					FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
					Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
					ftowUMS4TS[j][0] = FMcurrent_time;
					cout << " priority 4 ------- " << setprecision(10) << FMcurrent_time << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
					ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
										   //to Work Cell
					ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
					stringstream uu;
					uu << setprecision(10) << ftowUMS4TS[j][0];
					ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
					ftowUMS000100[j][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
					}
					Sim.outfWGCL_FMA_2 << endl;

					if (ftowUMS4TS[j][0] >(Sim.TTI + Sim.WCwt5))
						WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

					if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
					{
						//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
						if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
							Sim.wca_prindex = Sim.wca_prindex + 1;

						Aoverlap_ts = ftowUMS4TS[j][0];
						Aovrlap_tri = 1;
						Aupdated = 0;
					}
				}
				last_pos_A_2++;
			}
			else    // 回傳的封包還沒傳出去
			{
				Anonsent = 1;
				Aovrlap_tri = 0;
				break;
			}
			Anonsent = 0;
		}
	}

	if (Anonsent == 0)
	{
		//cout << "Sim.Atrigger = " << Sim.Atrigger << endl;
		if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
		{
			Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
			Aupdated = 1;
			Aovrlap_tri = 0;
		}

		for (int i = 0; i < Sim.y; i++)//--------------------------------------P2
		{
			if ((wtofUMS4TS[i][0] < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1) && wtofUMS4TS[i][0] != 0 && wtofUMS4TS[i][2] == 0 && WCcurrent_time < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1)//滿足可以排成的要求
			{
				if (wtofUMS4TS[i][0] >= Sim.TTI + Sim.WCwt5_1)//在他該傳送的區間內
				{
					if (wtofUMS4TS[i][0] >= WCcurrent_time)//沒跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS4TS[i][0];
						cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (+傳輸時間後) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS4TS[i][2] = 1;
						//to Factory Management
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS4TS[i][0];
						wtofUMS000100[i][1] = xx.str();
						wtofUMS000100[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
						}
						Sim.outfWGCL_WCA_2 << endl;

						Arecvtime = wtofUMS4TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包
						if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
						{
							//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

							if (wtofUMS000100[i][10] == "opcua")
								if (Sim.fma_prindex<(Sim.fmamsg_num - 1))
									Sim.fma_prindex = Sim.fma_prindex + 1;

							SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_A_2; j < Sim.yback; j++)
							{
								Atemp = Sim.ftowLCID000100[j][8];
								SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									Atemp = Sim.ftowLCID000100[j][10];
									if (Atemp == "opn")
									{
										send_pos_A_2 = 1;
										break;
									}
									if (Atemp == "opcua")
									{
										send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.yback - 1) && yback_finish == 0)
									{
										//cout << "最後一個A位置 = " << j + 1 << endl;
										send_pos_A_2 = j + 1;
										yback_finish = 1;
									}
								}
							}
							Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

							for (int j = last_pos_A_2; j < send_pos_A_2; j++)
							{
								if (Sim.FMwt4_2 != 0)
								{
									if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
									{
										if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1)//在他該傳送的區間內
										{
											if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
											{
												setcolor(12, 0);
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS4TS[j][0];
												cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS4TS[j][0];
												ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000100[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
												}
												Sim.outfWGCL_FMA_2 << endl;

												if ((ftowUMS000100[j][10] == "opn" || ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
												{
													//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
													if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
														Sim.wca_prindex = Sim.wca_prindex + 1;

													Aoverlap_ts = ftowUMS4TS[j][0];
													Aovrlap_tri = 1;
													Aupdated = 0;
												}

												WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

											}
											else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
											{
												setcolor(12, 0);
												ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS4TS[j][0];
												cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS4TS[j][0];
												ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000100[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
												}
												Sim.outfWGCL_FMA_2 << endl;

												if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
												{
													//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
													if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
														Sim.wca_prindex = Sim.wca_prindex + 1;

													Aoverlap_ts = ftowUMS4TS[j][0];
													Aovrlap_tri = 1;
													Aupdated = 0;
												}

												WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
											}
										}
										else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
										{
											setcolor(12, 0);
											FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											ftowUMS4TS[j][0] = FMcurrent_time;
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
										last_pos_A_2++;
										if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
										{
											Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
											Aupdated = 1;
											Aovrlap_tri = 0;
											Anonsent = 0;
											//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
										}
									}
									else //if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5 + Sim.FMwt4)   // 回傳的封包還沒傳出去
									{
										/*setcolor(12, 1);
										cout << "Window_2 is closed~" << endl;
										cout << "ftowUMS4TS[j][0] = " << ftowUMS4TS[j][0] << endl;
										cout << "Sim.TTI = " << Sim.TTI << endl;
										cout << "Sim.FMwt5 = " << Sim.FMwt5 << endl;
										cout << "Sim.FMwt4 = " << Sim.FMwt4 << endl;
										cout << "FMcurrent_time = " << FMcurrent_time << endl;*/
										Anonsent = 1;
										break;
										//Sim.TTI + (double)1 / Sim.quantum;
									}
								}

							}
							if (Anonsent == 1)
								break;
						}
					}
					else if (wtofUMS4TS[i][0] < WCcurrent_time)//跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS4TS[i][0] = WCcurrent_time + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS4TS[i][0];
						cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS4TS[i][2] = 1;
						//to Factory Management
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS4TS[i][0];
						wtofUMS000100[i][1] = xx.str();
						wtofUMS000100[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
						}
						Sim.outfWGCL_WCA_2 << endl;

						Arecvtime = wtofUMS4TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包

						if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
						{
							//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

							if (wtofUMS000100[i][10] == "opcua")
								if (Sim.fma_prindex<(Sim.fmamsg_num - 1))
									Sim.fma_prindex = Sim.fma_prindex + 1;

							SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_A_2; j < Sim.yback; j++)
							{
								Atemp = Sim.ftowLCID000100[j][8];
								SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									Atemp = Sim.ftowLCID000100[j][10];
									if (Atemp == "opn")
									{
										send_pos_A_2 = 1;
										break;
									}
									if (Atemp == "opcua")
									{
										send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.yback - 1) && yback_finish == 0)
									{
										//cout << "最後一個A位置 = " << j + 1 << endl;
										send_pos_A_2 = j + 1;
										yback_finish = 1;
									}
								}
							}
							Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

							for (int j = last_pos_A_2; j < send_pos_A_2; j++)
							{
								if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1)//在他該傳送的區間內
									{
										if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time


										}
										else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
									}
									else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS4TS[j][0] = FMcurrent_time;
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
									}
									last_pos_A_2++;
									if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
									{
										Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
										Aupdated = 1;
										Aovrlap_tri = 0;
										Anonsent = 0;
										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}
								else    // 回傳的封包還沒傳出去
								{
									Anonsent = 1;
									break;
								}

							}
							if (Anonsent == 1)
								break;
						}
					}
				}
				else  //不在他該傳送的區間內  (UMS2TS[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4)
				{
					/*cout << "wtofUMS4TS[i][0] = " << wtofUMS4TS[i][0] << "i = " << i << endl;
					cout << " Sim.TTI = " << Sim.TTI << endl;
					cout << "Sim.WCwt5 = " << Sim.WCwt5 << endl;
					cout << "Sim.WCwt4 = " << Sim.WCwt4 << endl;
					cout << "WCcurrent_time = " << WCcurrent_time << endl;*/
					setcolor(10, 0);
					WCcurrent_time = WCcurrent_time + (double)wtofUMS4TS[i][1] * 8 / WFrate;
					/*stringstream ss;
					ss << setprecision(10) << WCcurrent_time;
					wtofUMS000100[i][1] = ss.str();*/
					wtofUMS4TS[i][0] = WCcurrent_time;
					cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
					wtofUMS4TS[i][2] = 1;

					//to Factory Management
					wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS4TS[i][0];
					wtofUMS000100[i][1] = xx.str();
					wtofUMS000100[i][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
					}
					Sim.outfWGCL_WCA_2 << endl;

					Arecvtime = wtofUMS4TS[i][0];

					/*******************開始進行回傳 FM->WC *********************/
					// TODO //
					// 先找出FM需要回傳到第幾個封包

					if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
					{
						//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

						if (wtofUMS000100[i][10] == "opcua")
							if (Sim.fma_prindex<(Sim.fmamsg_num - 1))
								Sim.fma_prindex = Sim.fma_prindex + 1;

						SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
						Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
						setcolor(13, 0);
						//cout << "Ack_num = " << Ack << endl;
						v1.clear();
						for (int j = last_pos_A_2; j < Sim.yback; j++)
						{
							Atemp = Sim.ftowLCID000100[j][8];
							SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
							Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
							v2.clear();
							if (Seq >= Ack)
							{
								Atemp = Sim.ftowLCID000100[j][10];
								if (Atemp == "opn")
								{
									send_pos_A_2 = 1;
									break;
								}
								if (Atemp == "opcua")
								{
									send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
									break;
								}
								if (j == (Sim.yback - 1) && yback_finish == 0)
								{
									//cout << "最後一個A位置 = " << j + 1 << endl;
									send_pos_A_2 = j + 1;
									yback_finish = 1;
								}
							}
						}
						Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

						for (int j = last_pos_A_2; j < send_pos_A_2; j++)
						{
							if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
							{
								if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1)//在他該傳送的區間內
								{
									if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
									{
										setcolor(12, 0);
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS4TS[j][0];
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

									}
									else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
									{
										setcolor(12, 0);
										ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										FMcurrent_time = ftowUMS4TS[j][0];
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

									}
								}
								else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
								{
									setcolor(12, 0);
									FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
									Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
									ftowUMS4TS[j][0] = FMcurrent_time;
									cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
									ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
														   //to Work Cell
									ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
									stringstream uu;
									uu << setprecision(10) << ftowUMS4TS[j][0];
									ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
									ftowUMS000100[j][0] = "Received";
									for (int t = 0; t < 11; t++)
									{
										Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
									}
									Sim.outfWGCL_FMA_2 << endl;

									if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
									{
										//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
										if (Sim.wca_prindex<(Sim.wcamsg_num - 1))
											Sim.wca_prindex = Sim.wca_prindex + 1;

										Aoverlap_ts = ftowUMS4TS[j][0];
										Aovrlap_tri = 1;
										Aupdated = 0;
									}

									WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
								}
								last_pos_A_2++;
								if (last_pos_A_2 == send_pos_A_2 && Anonsent == 0)
								{
									Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
									Aupdated = 1;
									Aovrlap_tri = 0;
									Anonsent = 0;
									//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
								}
							}
							else  // 回傳的封包還沒傳出去
							{
								Anonsent = 1;
								break;

							}
						}
						if (Anonsent == 1)
							break;
					}
				}
			}
		}
	}

	WCcurrent_time = Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1;
	FMcurrent_time = Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1;

	Sim.scheduling->MWCBufferUpdate(Sim.wtofLCID000000, Sim.wtofL0S, Sim.Mtrigger);  // Buffer update
	

	for (int i = 0; i < Sim.z; i++)//--------------------------------------P1  UDP無須回傳
	{
		if ((wtofUMS0TS[i][0] < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1) && wtofUMS0TS[i][0] != 0 && wtofUMS0TS[i][2] == 0 && WCcurrent_time<Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1)//滿足可以排成的要求
		{
			if (wtofUMS0TS[i][0] >= Sim.TTI + Sim.WCwt4_1 + Sim.WCwt5_1)//在他該傳送的區間內
			{
				if (wtofUMS0TS[i][0] >= WCcurrent_time)//沒跟前面的封包撞
				{
					setcolor(10, 0);
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;

					WCcurrent_time = wtofUMS0TS[i][0];
					cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (+傳輸時間後) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
					wtofUMS0TS[i][2] = 1;
					//to Factory Management
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = xx.str();
					wtofUMS000000[i][0] = "Received";
					if (wtofUMS000000[i][8] == "opcua")
					{
						//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
						if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
							Sim.wcm_prindex = Sim.wcm_prindex + 1;
					}
					for (int t = 0; t < 9; t++)
					{
						Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
					}
					Sim.outfWGCL_WCM_2 << endl;
				}
				else if (wtofUMS0TS[i][0] < WCcurrent_time)//跟前面的封包撞
				{
					setcolor(10, 0);
					wtofUMS0TS[i][0] = WCcurrent_time + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					WCcurrent_time = wtofUMS0TS[i][0];
					/*stringstream ss;
					ss << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = ss.str();*/
					cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
					wtofUMS0TS[i][2] = 1;
					//to Factory Management
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = xx.str();
					wtofUMS000000[i][0] = "Received";
					if (wtofUMS000000[i][8] == "opcua")
					{
						//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
						if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
							Sim.wcm_prindex = Sim.wcm_prindex + 1;
					}
					for (int t = 0; t < 9; t++)
					{
						Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
					}
					Sim.outfWGCL_WCM_2 << endl;
				}
			}
			else
			{
				setcolor(10, 0);
				WCcurrent_time = WCcurrent_time + (double)wtofUMS0TS[i][1] * 8 / WFrate;
				wtofUMS0TS[i][0] = WCcurrent_time;
				cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
				wtofUMS0TS[i][2] = 1;
				//to Factory Management
				wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
				stringstream xx;
				xx << setprecision(10) << wtofUMS0TS[i][0];
				wtofUMS000000[i][1] = xx.str();
				wtofUMS000000[i][0] = "Received";
				if (wtofUMS000000[i][8] == "opcua")
				{
					//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
					if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
						Sim.wcm_prindex = Sim.wcm_prindex + 1;
				}
				for (int t = 0; t < 9; t++)
				{
					Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
				}
				Sim.outfWGCL_WCM_2 << endl;
			}
		}
	}
	
	
	WCcurrent_time = Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1;


	if (Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 < 0.001)
	{
		if (CCnonsent == 1 || last_pos_CC_2 != send_pos_CC_2) // 先將FM未傳的CC回傳
		{
			/*cout << "繼續上次FM未傳完的CC" << endl;
			cout << "Now is " << Sim.TTI << endl;
			cout << "Current time in FM is " << FMcurrent_time << endl;
			cout << "Current time in WC is " << WCcurrent_time << endl;*/

			/*if (CCrecvtime < FMcurrent_time)
			CCrecvtime = FMcurrent_time;*/

			CCrecvtime = Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1;

			for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
			{
				if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//滿足可以排成的要求   ftowUMSxTS[i][2]代表封包是否發送出去
				{
					if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//在他該傳送的區間內
					{
						if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
						{
							setcolor(12, 0);
							ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
							CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
							FMcurrent_time = ftowUMS5TS[j][0];
							cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
							ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
												   //to Work Cell
							ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
							stringstream uu;
							uu << setprecision(10) << ftowUMS5TS[j][0];
							ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
							ftowUMS000101[j][0] = "Received";
							for (int t = 0; t < 11; t++)
							{
								Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
							}
							Sim.outfWGCL_FMCC_2 << endl;

							if (ftowUMS5TS[j][0] > Sim.TTI)
								WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

							if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
							{
								//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
								if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
									Sim.wccc_prindex = Sim.wccc_prindex + 1;

								CCoverlap_ts = ftowUMS5TS[j][0];
								CCovrlap_tri = 1;
								CCupdated = 0;
							}
						}
						else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
						{
							setcolor(12, 0);
							ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
							CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
							FMcurrent_time = ftowUMS5TS[j][0];
							cout << " priority 5 ------- " << setprecision(10) << FMcurrent_time << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
							ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
												   //to Work Cell
							ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
							stringstream uu;
							uu << setprecision(10) << ftowUMS5TS[j][0];
							ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
							ftowUMS000101[j][0] = "Received";
							for (int t = 0; t < 11; t++)
							{
								Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
							}
							Sim.outfWGCL_FMCC_2 << endl;

							if (ftowUMS5TS[j][0] > Sim.TTI)
								WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

							if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
							{
								//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
								if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
									Sim.wccc_prindex = Sim.wccc_prindex + 1;

								CCoverlap_ts = ftowUMS5TS[j][0];
								CCovrlap_tri = 1;
								CCupdated = 0;
							}
						}
					}
					else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
					{
						setcolor(12, 0);
						FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						FMcurrent_time = CCrecvtime;
						ftowUMS5TS[j][0] = FMcurrent_time;
						cout << " priority 5 ------- " << setprecision(10) << FMcurrent_time << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS5TS[j][0];
						ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000101[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
						}
						Sim.outfWGCL_FMCC_2 << endl;

						if (ftowUMS5TS[j][0] > Sim.TTI)
							WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

						if ((/*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
						{
							//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
							if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
								Sim.wccc_prindex = Sim.wccc_prindex + 1;

							CCoverlap_ts = ftowUMS5TS[j][0];
							CCovrlap_tri = 1;
							CCupdated = 0;
						}
					}
					last_pos_CC_2++;
				}

				else   // 回傳的封包還沒傳出去
				{
					CCnonsent = 1;
					CCovrlap_tri = 0;
					break;
				}

				CCnonsent = 0;
			}
		}


		if (CCnonsent == 0)
		{
			if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
			{
				Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
				CCovrlap_tri = 0;
				CCupdated = 1;
			}

			for (int i = 0; i < Sim.x; i++) //--------------------------------------P5
			{
				if ((wtofUMS5TS[i][0] < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2) && wtofUMS5TS[i][0] != 0 && wtofUMS5TS[i][2] == 0 && WCcurrent_time < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
				{
					if (wtofUMS5TS[i][0] >= Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1)//在他該傳送的區間內
					{
						if (wtofUMS5TS[i][0] >= WCcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
						{
							setcolor(10, 0);
							wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate; // 將原本發送的ts加上傳輸時間 (WC--->gNB)
							WCcurrent_time = wtofUMS5TS[i][0]; //封包完整傳輸後，下一個封包可以傳輸的時間點
							cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (+傳輸時間後) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
							wtofUMS5TS[i][2] = 1;  //將封包標示為已朝FM發送

												   //to Factory Management
							wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;   //將原本發送的ts加上傳輸時間 (gNB--->FM)
							stringstream xx;
							xx << setprecision(10) << wtofUMS5TS[i][0];
							wtofUMS000101[i][1] = xx.str();	//紀錄封包到達FM的時間
							wtofUMS000101[i][0] = "Received";
							for (int t = 0; t < 11; t++)
							{
								Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
							}
							Sim.outfWGCL_WCCC_2 << endl;

							CCrecvtime = wtofUMS5TS[i][0];


							/*******************開始進行回傳 FM->WC *********************/
							// TODO //
							// 先找出FM需要回傳到第幾個封包

							if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
							{
								//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

								if (wtofUMS000101[i][10] == "opcua")
									if (Sim.fmcc_prindex<(Sim.fmccmsg_num - 1))
										Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

								SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
								Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
								setcolor(13, 0);
								//cout << "Ack_num = " << Ack << endl;
								v1.clear();

								for (int j = last_pos_CC_2; j <= Sim.xback; j++)
								{
									CCtemp = Sim.ftowLCID000101[j][8];
									SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
									Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
									v2.clear();
									if (Seq >= Ack)
									{
										CCtemp = Sim.ftowLCID000101[j][10];
										if (CCtemp == "opn")
										{
											send_pos_CC_2 = 1;
											break;
										}
										if (CCtemp == "opcua")
										{
											send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
											break;
										}
										if (j == (Sim.xback - 1) && xback_finish == 0)
										{
											//cout << "最後一個CC位置 = " << j+1 << endl;
											send_pos_CC_2 = j + 1;
											xback_finish = 1;
										}
									}
								}
								Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update

								for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
								{
									if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
									{
										if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//在他該傳送的區間內
										{
											if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
											{
												setcolor(12, 0);
												ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS5TS[j][0];
												cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS5TS[j][0];
												ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000101[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
												}
												Sim.outfWGCL_FMCC_2 << endl;
												WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

												if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
												{
													//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
													if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
														Sim.wccc_prindex = Sim.wccc_prindex + 1;

													CCoverlap_ts = ftowUMS5TS[j][0];
													CCovrlap_tri = 1;
													CCupdated = 0;
												}

											}
											else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
											{
												setcolor(12, 0);
												ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS5TS[j][0];
												cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS5TS[j][0];
												ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000101[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
												}
												Sim.outfWGCL_FMCC_2 << endl;
												WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

												if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
												{
													//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
													if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
														Sim.wccc_prindex = Sim.wccc_prindex + 1;

													CCoverlap_ts = ftowUMS5TS[j][0];
													CCovrlap_tri = 1;
													CCupdated = 0;
												}
											}
										}
										else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
										{
											setcolor(12, 0);
											FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											ftowUMS5TS[j][0] = FMcurrent_time;
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;
											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" ||*/ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
										last_pos_CC_2++;
										if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
										{
											Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
											CCovrlap_tri = 0;
											CCupdated = 1;
											CCnonsent = 0;

											//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
										}
									}

									else   // 回傳的封包還沒傳出去
									{
										CCnonsent = 1;
										break;
									}
								}
								if (CCnonsent == 1)
									break;
							}
						}
						else if (wtofUMS5TS[i][0] < WCcurrent_time) //跟該週期前面的封包撞，因為前面的封包還沒被發送出去
						{
							setcolor(10, 0);
							wtofUMS5TS[i][0] = WCcurrent_time + (double)wtofUMS5TS[i][1] * 8 / WFrate;
							WCcurrent_time = wtofUMS5TS[i][0];
							cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
							wtofUMS5TS[i][2] = 1; //將封包標示為已朝FM發送

												  //to Factory Management
							wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;
							stringstream xx;
							xx << setprecision(10) << wtofUMS5TS[i][0];
							wtofUMS000101[i][1] = xx.str();  //紀錄封包到達FM的時間
							wtofUMS000101[i][0] = "Received";
							for (int t = 0; t < 11; t++)
							{
								Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
							}
							Sim.outfWGCL_WCCC_2 << endl;

							CCrecvtime = wtofUMS5TS[i][0];

							/*******************開始進行回傳 FM->WC *********************/
							// TODO //
							// 先找出FM需要回傳到第幾個封包
							if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
							{
								//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

								if (wtofUMS000101[i][10] == "opcua")
									if (Sim.fmcc_prindex<(Sim.fmccmsg_num - 1))
										Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

								SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
								Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
								setcolor(13, 0);
								//cout << "Ack_num = " << Ack << endl;
								v1.clear();
								for (int j = last_pos_CC_2; j <= Sim.xback; j++)
								{
									CCtemp = Sim.ftowLCID000101[j][8];
									SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
									Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
									v2.clear();
									if (Seq >= Ack)
									{
										CCtemp = Sim.ftowLCID000101[j][10];
										if (CCtemp == "opn")
										{
											send_pos_CC_2 = 1;
											break;
										}
										if (CCtemp == "opcua")
										{
											send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
											break;
										}
										if (j == (Sim.xback - 1) && xback_finish == 0)  //  最後一個回傳的ACK
										{
											//cout << "最後一個CC位置 = " << j+1 << endl;
											send_pos_CC_2 = j + 1;
											xback_finish = 1;
										}
									}
								}
								Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update


								for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
								{
									if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
									{
										if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//在他該傳送的區間內
										{
											if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
											{
												setcolor(12, 0);
												ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS5TS[j][0];
												cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS5TS[j][0];
												ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000101[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
												}
												Sim.outfWGCL_FMCC_2 << endl;

												WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

												if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
												{
													//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
													if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
														Sim.wccc_prindex = Sim.wccc_prindex + 1;

													CCoverlap_ts = ftowUMS5TS[j][0];
													CCovrlap_tri = 1;
													CCupdated = 0;
												}

											}
											else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
											{
												setcolor(12, 0);
												ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS5TS[j][0];
												cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS5TS[j][0];
												ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000101[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
												}
												Sim.outfWGCL_FMCC_2 << endl;

												WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

												if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
												{
													//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
													if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
														Sim.wccc_prindex = Sim.wccc_prindex + 1;

													CCoverlap_ts = ftowUMS5TS[j][0];
													CCovrlap_tri = 1;
													CCupdated = 0;
												}
											}
										}
										else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
										{
											setcolor(12, 0);
											FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											ftowUMS5TS[j][0] = FMcurrent_time;
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
										last_pos_CC_2++;
										if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
										{
											Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
											CCovrlap_tri = 0;
											CCupdated = 1;
											CCnonsent = 0;

											//FM回傳完成，WC準備下一輪Req的發布
										}
									}
									else    // 回傳的封包還沒傳出去
									{
										CCnonsent = 1;
										break;
									}
								}
								if (CCnonsent == 1)
								{
									break;
								}
							}
						}
					}
					else if (wtofUMS5TS[i][0] < WCcurrent_time) //不在他該傳送的區間內
					{
						setcolor(10, 0);
						//cout << " CCtrigger = " << Sim.CCtrigger << endl;
						//cout << " wtofUMS5TS[i][0] = " << wtofUMS5TS[i][0] << endl;
						//cout << " wtofUMS5TS[i+1][0] = " << wtofUMS5TS[i+1][0] << endl;
						WCcurrent_time = WCcurrent_time + (double)wtofUMS5TS[i][1] * 8 / WFrate;
						wtofUMS5TS[i][0] = WCcurrent_time;
						cout << " priority 5 ------- " << setprecision(10) << wtofUMS5TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS5TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS5TS[i][2] = 1;
						//to Factory Management
						wtofUMS5TS[i][0] = wtofUMS5TS[i][0] + (double)wtofUMS5TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS5TS[i][0];
						wtofUMS000101[i][1] = xx.str();	//紀錄封包到達FM的時間
						wtofUMS000101[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCCC_2 << wtofUMS000101[i][t] << ' ';
						}
						Sim.outfWGCL_WCCC_2 << endl;

						CCrecvtime = wtofUMS5TS[i][0];


						/*******************開始進行回傳 FM->WC *********************/
						if (wtofUMS000101[i][10] == "opn" || wtofUMS000101[i][10] == "opcua")
						{
							//cout << "Sim.wccc_prindex = " << Sim.wccc_prindex << endl;

							if (wtofUMS000101[i][10] == "opcua")
								if (Sim.fmcc_prindex<(Sim.fmccmsg_num - 1))
									Sim.fmcc_prindex = Sim.fmcc_prindex + 1;

							SplitString(wtofUMS000101[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_CC_2; j <= Sim.xback; j++)
							{
								CCtemp = Sim.ftowLCID000101[j][8];
								SplitString(CCtemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									CCtemp = Sim.ftowLCID000101[j][10];
									if (CCtemp == "opn")
									{
										send_pos_CC_2 = 1;
										break;
									}
									if (CCtemp == "opcua")
									{
										send_pos_CC_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.xback - 1) && xback_finish == 0)
									{
										//cout << "最後一個CC位置 = " << j+1 << endl;
										send_pos_CC_2 = j + 1;
										xback_finish = 1;
									}

								}
							}
							Sim.scheduling->CCFMBufferUpdate(Sim.ftowLCID000101, Sim.ftowL5S, send_pos_CC_2, last_pos_CC_2, CCrecvtime);  // Buffer update


							for (int j = last_pos_CC_2; j < send_pos_CC_2; j++)
							{
								if ((ftowUMS5TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2) && ftowUMS5TS[j][0] != 0 && ftowUMS5TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1)//在他該傳送的區間內
									{
										if (ftowUMS5TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}

										}
										else if (ftowUMS5TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS5TS[j][0] = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS5TS[j][0];
											cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS5TS[j][0];
											ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000101[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
											}
											Sim.outfWGCL_FMCC_2 << endl;

											WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

											if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
											{
												//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
												if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
													Sim.wccc_prindex = Sim.wccc_prindex + 1;

												CCoverlap_ts = ftowUMS5TS[j][0];
												CCovrlap_tri = 1;
												CCupdated = 0;
											}
										}
									}
									else //不在他該傳送的區間內  (UMS5TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										CCrecvtime = CCrecvtime + (double)ftowUMS5TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS5TS[j][0] = FMcurrent_time;
										cout << " priority 5 ------- " << setprecision(10) << ftowUMS5TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS5TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS5TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS5TS[j][0] = ftowUMS5TS[j][0] + (double)ftowUMS5TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS5TS[j][0];
										ftowUMS000101[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000101[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMCC_2 << ftowUMS000101[j][t] << ' ';
										}
										Sim.outfWGCL_FMCC_2 << endl;

										WCcurrent_time = ftowUMS5TS[j][0];   //調整現在WCcurrent time

										if ((ftowUMS000101[j][10] == "opn" || /*ftowUMS000101[j][10] == "reassemble" || */ftowUMS000101[j][10] == "opcua") && CCovrlap_tri == 0)
										{
											//cout << "Sim.fmcc_prindex = " << Sim.fmcc_prindex << endl;
											if (Sim.wccc_prindex<(Sim.wcccmsg_num - 1))
												Sim.wccc_prindex = Sim.wccc_prindex + 1;

											CCoverlap_ts = ftowUMS5TS[j][0];
											CCovrlap_tri = 1;
											CCupdated = 0;
										}
									}
									last_pos_CC_2++;
									if (last_pos_CC_2 == send_pos_CC_2 && CCupdated == 0)
									{
										Sim.scheduling->CCWCBufferUpdate(Sim.wtofLCID000101, Sim.wtofL5S, Sim.CCtrigger, CCoverlap_ts);  // Buffer update
										CCovrlap_tri = 0;
										CCupdated = 1;
										CCnonsent = 0;

										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}
								else //if (ftowUMS5TS[j][0] >= Sim.TTI + Sim.FMwt5)   // 回傳的封包還沒傳出去
								{
									CCnonsent = 1;
									break;
								}
							}
							if (CCnonsent == 1)
								break;
						}
					}
				}
			}
		}
	}

	WCcurrent_time = Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2;
	FMcurrent_time = Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2;

	
	if ((Anonsent == 1 || last_pos_A_2 != send_pos_A_2) && Sim.FMwt4_2 != 0) // 先將FM未傳的Alarming回傳
	{
		//cout << "繼續上次FM未傳完的A" << endl;

		Arecvtime = Sim.TTI + Sim.FMwt5;

		for (int j = last_pos_A_2; j < send_pos_A_2; j++)
		{
			if (Sim.FMwt4_2 != 0)
			{
				if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
				{
					if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//在他該傳送的區間內
					{
						if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
						{
							setcolor(12, 0);
							ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
							Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
							FMcurrent_time = ftowUMS4TS[j][0];
							cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
							ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
												   //to Work Cell
							ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
							stringstream uu;
							uu << setprecision(10) << ftowUMS4TS[j][0];
							ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
							ftowUMS000100[j][0] = "Received";
							for (int t = 0; t < 11; t++)
							{
								Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
							}
							Sim.outfWGCL_FMA_2 << endl;

							if (ftowUMS4TS[j][0] > (Sim.TTI + Sim.WCwt5))
								WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

							if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
							{
								//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
								if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
									Sim.wca_prindex = Sim.wca_prindex + 1;

								Aoverlap_ts = ftowUMS4TS[j][0];
								Aovrlap_tri = 1;
								Aupdated = 0;
							}

						}
						else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
						{
							setcolor(12, 0);
							ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
							Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
							FMcurrent_time = ftowUMS4TS[j][0];
							cout << " priority 4 ------- " << setprecision(10) << FMcurrent_time << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
							ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
												   //to Work Cell
							ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
							stringstream uu;
							uu << setprecision(10) << ftowUMS4TS[j][0];
							ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
							ftowUMS000100[j][0] = "Received";
							for (int t = 0; t < 11; t++)
							{
								Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
							}
							Sim.outfWGCL_FMA_2 << endl;

							if (ftowUMS4TS[j][0] > (Sim.TTI + Sim.WCwt5))
								WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

							if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
							{
								//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
								if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
									Sim.wca_prindex = Sim.wca_prindex + 1;

								Aoverlap_ts = ftowUMS4TS[j][0];
								Aovrlap_tri = 1;
								Aupdated = 0;
							}
						}
					}
					else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI + Sim.FMwt5 +  Sim.FMwt4)
					{
						setcolor(12, 0);
						FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
						Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
						ftowUMS4TS[j][0] = FMcurrent_time;
						cout << " priority 4 ------- " << setprecision(10) << FMcurrent_time << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
						ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
											   //to Work Cell
						ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
						stringstream uu;
						uu << setprecision(10) << ftowUMS4TS[j][0];
						ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
						ftowUMS000100[j][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
						}
						Sim.outfWGCL_FMA_2 << endl;

						if (ftowUMS4TS[j][0] > (Sim.TTI + Sim.WCwt5))
							WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

						if ((ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
						{
							//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
							if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
								Sim.wca_prindex = Sim.wca_prindex + 1;

							Aoverlap_ts = ftowUMS4TS[j][0];
							Aovrlap_tri = 1;
							Aupdated = 0;
						}
					}
					last_pos_A_2++;
				}
				else    // 回傳的封包還沒傳出去
				{
					Anonsent = 1;
					Aovrlap_tri = 0;
					break;
				}
				Anonsent = 0;
			}
			else
				break;
		}
	}

	if (Anonsent == 0)
	{
		//cout << "Sim.Atrigger = " << Sim.Atrigger << endl;
		if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
		{
			Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
			Aupdated = 1;
			Aovrlap_tri = 0;
		}

		for (int i = 0; i < Sim.y; i++)//--------------------------------------P2
		{
			if ((wtofUMS4TS[i][0] < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt5_2 + Sim.WCwt4_2) && wtofUMS4TS[i][0] != 0 && wtofUMS4TS[i][2] == 0 && WCcurrent_time < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt5_2 + Sim.WCwt4_2)//滿足可以排成的要求
			{
				if (wtofUMS4TS[i][0] >= Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt5_2)//在他該傳送的區間內
				{
					if (wtofUMS4TS[i][0] >= WCcurrent_time)//沒跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS4TS[i][0];
						cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (+傳輸時間後) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS4TS[i][2] = 1;
						//to Factory Management
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS4TS[i][0];
						wtofUMS000100[i][1] = xx.str();
						wtofUMS000100[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
						}
						Sim.outfWGCL_WCA_2 << endl;

						Arecvtime = wtofUMS4TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包
						if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
						{
							//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

							if (wtofUMS000100[i][10] == "opcua")
								if (Sim.fma_prindex<(Sim.fmamsg_num - 1))
									Sim.fma_prindex = Sim.fma_prindex + 1;

							SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_A_2; j < Sim.yback; j++)
							{
								Atemp = Sim.ftowLCID000100[j][8];
								SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									Atemp = Sim.ftowLCID000100[j][10];
									if (Atemp == "opn")
									{
										send_pos_A_2 = 1;
										break;
									}
									if (Atemp == "opcua")
									{
										send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.yback - 1) && yback_finish == 0)
									{
										//cout << "最後一個A位置 = " << j + 1 << endl;
										send_pos_A_2 = j + 1;
										yback_finish = 1;
									}
								}
							}
							Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

							if (Sim.FMwt4_2 != 2)
							{
								for (int j = last_pos_A_2; j < send_pos_A_2; j++)
								{
									if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
									{
										if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//在他該傳送的區間內
										{
											if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
											{
												setcolor(12, 0);
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS4TS[j][0];
												cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS4TS[j][0];
												ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000100[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
												}
												Sim.outfWGCL_FMA_2 << endl;

												if ((ftowUMS000100[j][10] == "opn" || ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
												{
													//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
													if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
														Sim.wca_prindex = Sim.wca_prindex + 1;

													Aoverlap_ts = ftowUMS4TS[j][0];
													Aovrlap_tri = 1;
													Aupdated = 0;
												}

												WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

											}
											else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
											{
												setcolor(12, 0);
												ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS4TS[j][0];
												cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS4TS[j][0];
												ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000100[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
												}
												Sim.outfWGCL_FMA_2 << endl;

												if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
												{
													//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
													if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
														Sim.wca_prindex = Sim.wca_prindex + 1;

													Aoverlap_ts = ftowUMS4TS[j][0];
													Aovrlap_tri = 1;
													Aupdated = 0;
												}

												WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
											}
										}
										else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
										{
											setcolor(12, 0);
											FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											ftowUMS4TS[j][0] = FMcurrent_time;
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
										last_pos_A_2++;
										if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
										{
											Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
											Aupdated = 1;
											Aovrlap_tri = 0;
											Anonsent = 0;
											//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
										}
									}
									else //if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5 + Sim.FMwt4)   // 回傳的封包還沒傳出去
									{
										/*setcolor(12, 1);
										cout << "Window_2 is closed~" << endl;
										cout << "ftowUMS4TS[j][0] = " << ftowUMS4TS[j][0] << endl;
										cout << "Sim.TTI = " << Sim.TTI << endl;
										cout << "Sim.FMwt5 = " << Sim.FMwt5 << endl;
										cout << "Sim.FMwt4 = " << Sim.FMwt4 << endl;
										cout << "FMcurrent_time = " << FMcurrent_time << endl;*/
										Anonsent = 1;
										break;
										//Sim.TTI + (double)1 / Sim.quantum;
									}
								}
							}
							if (Anonsent == 1)
								break;
						}
					}
					else if (wtofUMS4TS[i][0] < WCcurrent_time)//跟前面的封包撞
					{
						setcolor(10, 0);
						wtofUMS4TS[i][0] = WCcurrent_time + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						WCcurrent_time = wtofUMS4TS[i][0];
						cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
						wtofUMS4TS[i][2] = 1;
						//to Factory Management
						wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
						stringstream xx;
						xx << setprecision(10) << wtofUMS4TS[i][0];
						wtofUMS000100[i][1] = xx.str();
						wtofUMS000100[i][0] = "Received";
						for (int t = 0; t < 11; t++)
						{
							Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
						}
						Sim.outfWGCL_WCA_2 << endl;

						Arecvtime = wtofUMS4TS[i][0];

						/*******************開始進行回傳 FM->WC *********************/
						// TODO //
						// 先找出FM需要回傳到第幾個封包

						if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
						{
							//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

							if (wtofUMS000100[i][10] == "opcua")
								if (Sim.fma_prindex<(Sim.fmamsg_num - 1))
									Sim.fma_prindex = Sim.fma_prindex + 1;

							SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
							Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
							setcolor(13, 0);
							//cout << "Ack_num = " << Ack << endl;
							v1.clear();
							for (int j = last_pos_A_2; j < Sim.yback; j++)
							{
								Atemp = Sim.ftowLCID000100[j][8];
								SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
								Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
								v2.clear();
								if (Seq >= Ack)
								{
									Atemp = Sim.ftowLCID000100[j][10];
									if (Atemp == "opn")
									{
										send_pos_A_2 = 1;
										break;
									}
									if (Atemp == "opcua")
									{
										send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
										break;
									}
									if (j == (Sim.yback - 1) && yback_finish == 0)
									{
										//cout << "最後一個A位置 = " << j + 1 << endl;
										send_pos_A_2 = j + 1;
										yback_finish = 1;
									}
								}
							}
							Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

							if (Sim.FMwt4_2 != 2)
							{
								for (int j = last_pos_A_2; j < send_pos_A_2; j++)
								{
									if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
									{
										if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//在他該傳送的區間內
										{
											if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
											{
												setcolor(12, 0);
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS4TS[j][0];
												cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS4TS[j][0];
												ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000100[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
												}
												Sim.outfWGCL_FMA_2 << endl;

												if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
												{
													//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
													if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
														Sim.wca_prindex = Sim.wca_prindex + 1;

													Aoverlap_ts = ftowUMS4TS[j][0];
													Aovrlap_tri = 1;
													Aupdated = 0;
												}

												WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time


											}
											else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
											{
												setcolor(12, 0);
												ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
												Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
												FMcurrent_time = ftowUMS4TS[j][0];
												cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
												ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																	   //to Work Cell
												ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
												stringstream uu;
												uu << setprecision(10) << ftowUMS4TS[j][0];
												ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
												ftowUMS000100[j][0] = "Received";
												for (int t = 0; t < 11; t++)
												{
													Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
												}
												Sim.outfWGCL_FMA_2 << endl;

												if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
												{
													//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
													if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
														Sim.wca_prindex = Sim.wca_prindex + 1;

													Aoverlap_ts = ftowUMS4TS[j][0];
													Aovrlap_tri = 1;
													Aupdated = 0;
												}

												WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

											}
										}
										else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
										{
											setcolor(12, 0);
											FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											ftowUMS4TS[j][0] = FMcurrent_time;
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
										}
										last_pos_A_2++;
										if (last_pos_A_2 == send_pos_A_2 && Aupdated == 0)
										{
											Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
											Aupdated = 1;
											Aovrlap_tri = 0;
											Anonsent = 0;
											//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
										}
									}
									else    // 回傳的封包還沒傳出去
									{
										Anonsent = 1;
										break;
									}

								}
							}
							if (Anonsent == 1)
								break;
						}
					}
				}
				else  //不在他該傳送的區間內  (UMS2TS[i][0] < Sim.TTI + Sim.WCwt5 + Sim.WCwt4)
				{
					/*cout << "wtofUMS4TS[i][0] = " << wtofUMS4TS[i][0] << "i = " << i << endl;
					cout << " Sim.TTI = " << Sim.TTI << endl;
					cout << "Sim.WCwt5 = " << Sim.WCwt5 << endl;
					cout << "Sim.WCwt4 = " << Sim.WCwt4 << endl;
					cout << "WCcurrent_time = " << WCcurrent_time << endl;*/
					setcolor(10, 0);
					WCcurrent_time = WCcurrent_time + (double)wtofUMS4TS[i][1] * 8 / WFrate;
					/*stringstream ss;
					ss << setprecision(10) << WCcurrent_time;
					wtofUMS000100[i][1] = ss.str();*/
					wtofUMS4TS[i][0] = WCcurrent_time;
					cout << " priority 4 ------- " << setprecision(10) << wtofUMS4TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS4TS[i][1] << "  " << "sent from Work Cell" << endl;
					wtofUMS4TS[i][2] = 1;

					//to Factory Management
					wtofUMS4TS[i][0] = wtofUMS4TS[i][0] + (double)wtofUMS4TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS4TS[i][0];
					wtofUMS000100[i][1] = xx.str();
					wtofUMS000100[i][0] = "Received";
					for (int t = 0; t < 11; t++)
					{
						Sim.outfWGCL_WCA_2 << wtofUMS000100[i][t] << ' ';
					}
					Sim.outfWGCL_WCA_2 << endl;

					Arecvtime = wtofUMS4TS[i][0];

					/*******************開始進行回傳 FM->WC *********************/
					// TODO //
					// 先找出FM需要回傳到第幾個封包

					if (wtofUMS000100[i][10] == "opn" || wtofUMS000100[i][10] == "opcua")
					{
						//cout << "Sim.wca_prindex = " << Sim.wca_prindex << endl;

						if (wtofUMS000100[i][10] == "opcua")
							if (Sim.fma_prindex<(Sim.fmamsg_num - 1))
								Sim.fma_prindex = Sim.fma_prindex + 1;

						SplitString(wtofUMS000100[i][9], v1, "TCP_ACK=");   //將TCP的ACK存在v1中，以辨識FM要傳哪些封包
						Ack = (atoi(v1[1].c_str()));  // 將Ack由字串轉成整數型態並記錄下來
						setcolor(13, 0);
						//cout << "Ack_num = " << Ack << endl;
						v1.clear();
						for (int j = last_pos_A_2; j < Sim.yback; j++)
						{
							Atemp = Sim.ftowLCID000100[j][8];
							SplitString(Atemp, v2, "TCP_SEQ=");   //將TCP的SEQ存在v2中，以辨識FM該傳哪些封包
							Seq = (atoi(v2[1].c_str()));  // 將Seq由字串轉成整數型態並記錄下來
							v2.clear();
							if (Seq >= Ack)
							{
								Atemp = Sim.ftowLCID000100[j][10];
								if (Atemp == "opn")
								{
									send_pos_A_2 = 1;
									break;
								}
								if (Atemp == "opcua")
								{
									send_pos_A_2 = j + 1; //  紀錄當前FM發送到第幾個封包
									break;
								}
								if (j == (Sim.yback - 1) && yback_finish == 0)
								{
									//cout << "最後一個A位置 = " << j + 1 << endl;
									send_pos_A_2 = j + 1;
									yback_finish = 1;
								}
							}
						}
						Sim.scheduling->AFMBufferUpdate(Sim.ftowLCID000100, Sim.ftowL4S, send_pos_A_2, last_pos_A_2, Arecvtime);  // Buffer update

						if (Sim.FMwt4_2 != 2)
						{
							for (int j = last_pos_A_2; j < send_pos_A_2; j++)
							{
								if ((ftowUMS4TS[j][0] < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2) && ftowUMS4TS[j][0] != 0 && ftowUMS4TS[j][2] == 0 && FMcurrent_time < Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2)//滿足可以排成的要求   wtofUMSxTS[i][2]代表封包是否發送出去
								{
									if (ftowUMS4TS[j][0] >= Sim.TTI + Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2)//在他該傳送的區間內
									{
										if (ftowUMS4TS[j][0] >= FMcurrent_time)//封包準備傳輸時，沒跟前面的封包撞
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
										else if (ftowUMS4TS[j][0] < FMcurrent_time)  //跟前面的封包撞，因為前面的封包還沒被發送出去
										{
											setcolor(12, 0);
											ftowUMS4TS[j][0] = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
											Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
											FMcurrent_time = ftowUMS4TS[j][0];
											cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (撞到前幾個該週期沒傳的封包) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
											ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
																   //to Work Cell
											ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
											stringstream uu;
											uu << setprecision(10) << ftowUMS4TS[j][0];
											ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
											ftowUMS000100[j][0] = "Received";
											for (int t = 0; t < 11; t++)
											{
												Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
											}
											Sim.outfWGCL_FMA_2 << endl;

											if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
											{
												//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
												if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
													Sim.wca_prindex = Sim.wca_prindex + 1;

												Aoverlap_ts = ftowUMS4TS[j][0];
												Aovrlap_tri = 1;
												Aupdated = 0;
											}

											WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time

										}
									}
									else //不在他該傳送的區間內  (UMS2TS[j][0] < Sim.TTI)
									{
										setcolor(12, 0);
										FMcurrent_time = FMcurrent_time + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 將原本發送的ts加上傳輸時間 (FM--->gNB)
										Arecvtime = Arecvtime + (double)ftowUMS4TS[j][1] * 8 / FWrate;   // 額外考慮封包傳出後，下個封包的時間戳需加入Queing的時間
										ftowUMS4TS[j][0] = FMcurrent_time;
										cout << " priority 4 ------- " << setprecision(10) << ftowUMS4TS[j][0] << " (新週期+傳輸時間後) " << ftowUMS4TS[j][1] << "  " << "sent from Factory Management" << endl;
										ftowUMS4TS[j][2] = 1;  //將封包標示為已朝WC發送
															   //to Work Cell
										ftowUMS4TS[j][0] = ftowUMS4TS[j][0] + (double)ftowUMS4TS[j][1] * 8 / FWrate;   //將原本發送的ts加上傳輸時間 (gNB--->WC)
										stringstream uu;
										uu << setprecision(10) << ftowUMS4TS[j][0];
										ftowUMS000100[j][1] = uu.str();	 //紀錄封包到達WC的時間
										ftowUMS000100[j][0] = "Received";
										for (int t = 0; t < 11; t++)
										{
											Sim.outfWGCL_FMA_2 << ftowUMS000100[j][t] << ' ';
										}
										Sim.outfWGCL_FMA_2 << endl;

										if ((ftowUMS000100[j][10] == "opn" || /*ftowUMS000100[j][10] == "reassemble" || */ftowUMS000100[j][10] == "opcua") && Aovrlap_tri == 0)
										{
											//cout << "Sim.fma_prindex = " << Sim.fma_prindex << endl;
											if (Sim.wca_prindex < (Sim.wcamsg_num - 1))
												Sim.wca_prindex = Sim.wca_prindex + 1;

											Aoverlap_ts = ftowUMS4TS[j][0];
											Aovrlap_tri = 1;
											Aupdated = 0;
										}

										WCcurrent_time = ftowUMS4TS[j][0];   //調整現在WCcurrent time
									}
									last_pos_A_2++;
									if (last_pos_A_2 == send_pos_A_2 && Anonsent == 0)
									{
										Sim.scheduling->AWCBufferUpdate(Sim.wtofLCID000100, Sim.wtofL4S, Sim.Atrigger, Aoverlap_ts);  // Buffer update
										Aupdated = 1;
										Aovrlap_tri = 0;
										Anonsent = 0;
										//cout << "FM回傳完成，WC準備下一輪Req的發布" << endl;
									}
								}
								else  // 回傳的封包還沒傳出去
								{
									Anonsent = 1;
									break;

								}
							}
						}
						if (Anonsent == 1)
							break;
					}
				}
			}
		}
	}

	WCcurrent_time = Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2 + Sim.WCwt4_2;
	Sim.scheduling->MWCBufferUpdate(Sim.wtofLCID000000, Sim.wtofL0S, Sim.Mtrigger);  // Buffer update


	for (int i = 0; i < Sim.z; i++)//--------------------------------------P1  UDP無須回傳
	{
		if ((wtofUMS0TS[i][0] < Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2 + Sim.WCwt4_2 + Sim.WCwt0_2) && wtofUMS0TS[i][0] != 0 && wtofUMS0TS[i][2] == 0 && WCcurrent_time<Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2 + Sim.WCwt4_2 + Sim.WCwt0_2)//滿足可以排成的要求
		{
			if (wtofUMS0TS[i][0] >= Sim.TTI + Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2 + Sim.WCwt4_2)//在他該傳送的區間內
			{
				if (wtofUMS0TS[i][0] >= WCcurrent_time)//沒跟前面的封包撞
				{
					setcolor(10, 0);
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;

					WCcurrent_time = wtofUMS0TS[i][0];
					cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (+傳輸時間後) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
					wtofUMS0TS[i][2] = 1;
					//to Factory Management
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = xx.str();
					wtofUMS000000[i][0] = "Received";
					if (wtofUMS000000[i][8] == "opcua")
					{
						//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
						if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
							Sim.wcm_prindex = Sim.wcm_prindex + 1;
					}
					for (int t = 0; t < 9; t++)
					{
						Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
					}
					Sim.outfWGCL_WCM_2 << endl;
				}
				else if (wtofUMS0TS[i][0] < WCcurrent_time)//跟前面的封包撞
				{
					setcolor(10, 0);
					wtofUMS0TS[i][0] = WCcurrent_time + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					WCcurrent_time = wtofUMS0TS[i][0];
					/*stringstream ss;
					ss << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = ss.str();*/
					cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (撞到前幾個週期沒傳的封包) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
					wtofUMS0TS[i][2] = 1;
					//to Factory Management
					wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
					stringstream xx;
					xx << setprecision(10) << wtofUMS0TS[i][0];
					wtofUMS000000[i][1] = xx.str();
					wtofUMS000000[i][0] = "Received";
					if (wtofUMS000000[i][8] == "opcua")
					{
						//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
						if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
							Sim.wcm_prindex = Sim.wcm_prindex + 1;
					}
					for (int t = 0; t < 9; t++)
					{
						Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
					}
					Sim.outfWGCL_WCM_2 << endl;
				}
			}
			else
			{
				setcolor(10, 0);
				WCcurrent_time = WCcurrent_time + (double)wtofUMS0TS[i][1] * 8 / WFrate;
				wtofUMS0TS[i][0] = WCcurrent_time;
				cout << " priority 0 ------- " << setprecision(10) << wtofUMS0TS[i][0] << " (新週期+傳輸時間後) " << wtofUMS0TS[i][1] << "  " << "sent" << endl;
				wtofUMS0TS[i][2] = 1;
				//to Factory Management
				wtofUMS0TS[i][0] = wtofUMS0TS[i][0] + (double)wtofUMS0TS[i][1] * 8 / WFrate;
				stringstream xx;
				xx << setprecision(10) << wtofUMS0TS[i][0];
				wtofUMS000000[i][1] = xx.str();
				wtofUMS000000[i][0] = "Received";
				if (wtofUMS000000[i][8] == "opcua")
				{
					//cout << "Sim.wcm_prindex = " << Sim.wcm_prindex << endl;
					if (Sim.wcm_prindex<(Sim.wcmmsg_num - 1))
						Sim.wcm_prindex = Sim.wcm_prindex + 1;
				}
				for (int t = 0; t < 9; t++)
				{
					Sim.outfWGCL_WCM_2 << wtofUMS000000[i][t] << ' ';
				}
				Sim.outfWGCL_WCM_2 << endl;
			}
		}
	}
	
}		


double SchedulingURLLCMS::GetSpectralEfficiency(double SINR, int &MCS)
{   

	if (SINR < -7.595) { MCS = -1; return 0.0; }
	else if (SINR >= -7.595&&SINR < -5.712) { MCS = 0; return  0.1523; }
	else if (SINR >= -5.712&&SINR < -3.591) { MCS = 1; return 0.2344; }
	else if (SINR >= -3.591&&SINR < -1.578) { MCS = 2; return 0.3770; }
	else if (SINR >= -1.578&&SINR < 0.4483) { MCS = 3; return 0.6016; }
	else if (SINR >= 0.4483&&SINR < 2.345) { MCS = 4; return 0.8770; }
	else if (SINR >= 2.345&&SINR < 4.312) { MCS = 5; return 1.1758; }
	else if (SINR >= 4.312&&SINR < 6.264) { MCS = 6; return 1.4766; }
	else if (SINR >= 6.264&&SINR < 8.248) { MCS = 7; return 1.9141; }
	else if (SINR >= 8.248&&SINR < 10.24) { MCS = 8; return 2.4063; }
	else if (SINR >= 10.24&&SINR < 12.05) { MCS = 9; return 2.7305; }
	else if (SINR >= 12.05&&SINR < 13.93) { MCS = 10; return 3.3223; }
	else if (SINR >= 13.93&&SINR < 16.02) { MCS = 11; return 3.9023; }
	else if (SINR >= 16.02&&SINR < 17.83) { MCS = 12; return 4.5234; }
	else if (SINR >= 17.83&&SINR < 20.06) { MCS = 13; return 5.1152; }
	else if (SINR >= 20.06) { MCS = 14; return 5.5547; }
	return -1.0;

}
void SplitStringMS(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
//  check the long BSR table
double BSRIndex(double BSR_B)
{
	double size = BSR_B;
	int big0 = 0, big63 = 0, big127 = 0, big191 = 0;

	//  切成四個bolcks
	if (size >= 0 && size <= 526)
	{
		big0 = 1;
	}
	else if (size > 526 && size <= 29431)
	{
		big63 = 1;
	}
	else if (size > 29431 && size <= 1647644)
	{
		big127 = 1;
	}
	else if (size > 1647644)
	{
		big191 = 1;
	}
	// 第一個block 0~63
	if (big0 == 1)
	{
		if (size == 0.0)    // index = 0
		{
			return 0.0;
		}
		else if (size > 0.0 && size <= 10.0)   // index = 1  
		{
			return 10.0;
		}
		else if (size > 10.0 && size <= 11.0)   // index = 2  
		{
			return 11.0;
		}
		else if (size > 11.0 && size <= 12.0)   // index = 3  
		{
			return 12.0;
		}
		else if (size > 12.0 && size <= 13.0)   // index = 4  
		{
			return 13.0;
		}
		else if (size > 13.0 && size <= 14.0)   // index = 5  
		{
			return 14.0;
		}
		else if (size > 14.0 && size <= 15.0)   // index = 6 
		{
			return 15.0;
		}
		else if (size > 15.0 && size <= 16.0)   // index = 7 
		{
			return 16.0;
		}
		else if (size > 16.0 && size <= 17.0)   // index = 8  
		{
			return 17.0;
		}
		else if (size > 17.0 && size <= 18.0)   // index = 9  
		{
			return 18.0;
		}
		else if (size > 18.0 && size <= 19.0)   // index = 10  
		{
			return 19.0;
		}
		else if (size > 19.0 && size <= 20.0)   // index = 11  
		{
			return 20.0;
		}
		else if (size > 20.0 && size <= 22.0)   // index = 12  
		{
			return 22.0;
		}
		else if (size > 22.0 && size <= 23.0)   // index = 13  
		{
			return 23.0;
		}
		else if (size > 23.0 && size <= 25.0)   // index = 14  
		{
			return 25.0;
		}
		else if (size > 25.0 && size <= 26.0)   // index = 15  
		{
			return 26.0;
		}
		else if (size > 26.0 && size <= 28.0)   // index = 16  
		{
			return 28.0;
		}
		else if (size > 28.0 && size <= 30.0)   // index = 17  
		{
			return 30.0;
		}
		else if (size > 30.0 && size <= 32.0)   // index = 18  
		{
			return 32.0;
		}
		else if (size > 32.0 && size <= 34.0)   // index = 19  
		{
			return 34.0;
		}
		else if (size > 34.0 && size <= 36.0)   // index = 20  
		{
			return 36.0;
		}
		else if (size > 36.0 && size <= 38.0)   // index = 21  
		{
			return 38.0;
		}
		else if (size > 38.0 && size <= 40.0)   // index = 22  
		{
			return 40.0;
		}
		else if (size > 40.0 && size <= 43.0)   // index = 23  
		{
			return 43.0;
		}
		else if (size > 43.0 && size <= 46.0)   // index = 24  
		{
			return 46.0;
		}
		else if (size > 46.0 && size <= 49.0)   // index = 25  
		{
			return 49.0;
		}
		else if (size > 49.0 && size <= 52.0)   // index = 26  
		{
			return 52.0;
		}
		else if (size > 52.0 && size <= 55.0)   // index = 27  
		{
			return 55.0;
		}
		else if (size > 55.0 && size <= 59.0)   // index = 28  
		{
			return 59.0;
		}
		else if (size > 59.0 && size <= 62.0)   // index = 29  
		{
			return 62.0;
		}
		else if (size > 62.0 && size <= 66.0)   // index = 30  
		{
			return 66.0;
		}
		else if (size > 66.0 && size <= 71.0)   // index = 31  
		{
			return 71.0;
		}
		else if (size > 71.0 && size <= 75.0)   // index = 32  
		{
			return 75.0;
		}
		else if (size > 75.0 && size <= 80.0)   // index = 33  
		{
			return 80.0;
		}
		else if (size > 80.0 && size <= 85.0)   // index = 34  
		{
			return 85.0;
		}
		else if (size > 85.0 && size <= 91.0)   // index = 35  
		{
			return 91.0;
		}
		else if (size > 91.0 && size <= 97.0)   // index = 36  
		{
			return 97.0;
		}
		else if (size > 97.0 && size <= 103.0)   // index = 37  
		{
			return 103.0;
		}
		else if (size > 103.0 && size <= 110.0)   // index = 38  
		{
			return 110.0;
		}
		else if (size > 110.0 && size <= 117.0)   // index = 39  
		{
			return 117.0;
		}
		else if (size > 117.0 && size <= 124.0)   // index = 40  
		{
			return 124.0;
		}
		else if (size > 124.0 && size <= 132.0)   // index = 41  
		{
			return 132.0;
		}
		else if (size > 132.0 && size <= 141.0)   // index = 42  
		{
			return 141.0;
		}
		else if (size > 141.0 && size <= 150.0)   // index = 43  
		{
			return 150.0;
		}
		else if (size > 150.0 && size <= 160.0)   // index = 44  
		{
			return 160.0;
		}
		else if (size > 160.0 && size <= 170.0)   // index = 45  
		{
			return 170.0;
		}
		else if (size > 170.0 && size <= 181.0)   // index = 46  
		{
			return 181.0;
		}
		else if (size > 181.0 && size <= 193.0)   // index = 47  
		{
			return 193.0;
		}
		else if (size > 193.0 && size <= 205.0)   // index = 48  
		{
			return 205.0;
		}
		else if (size > 205.0 && size <= 218.0)   // index = 49  
		{
			return 218.0;
		}
		else if (size > 218.0 && size <= 233.0)   // index = 50  
		{
			return 233.0;
		}
		else if (size > 233.0 && size <= 248.0)   // index = 51  
		{
			return 248.0;
		}
		else if (size > 248.0 && size <= 264.0)   // index = 52  
		{
			return 264.0;
		}
		else if (size > 264.0 && size <= 281.0)   // index = 53  
		{
			return 281.0;
		}
		else if (size > 281.0 && size <= 299.0)   // index = 54  
		{
			return 299.0;
		}
		else if (size > 299.0 && size <= 318.0)   // index = 55  
		{
			return 318.0;
		}
		else if (size > 318.0 && size <= 339.0)   // index = 56  
		{
			return 339.0;
		}
		else if (size > 339.0 && size <= 361.0)   // index = 57  
		{
			return 361.0;
		}
		else if (size > 361.0 && size <= 384.0)   // index = 58  
		{
			return 384.0;
		}
		else if (size > 384.0 && size <= 409.0)   // index = 59  
		{
			return 409.0;
		}
		else if (size > 409.0 && size <= 436.0)   // index = 60  
		{
			return 436.0;
		}
		else if (size > 436.0 && size <= 464.0)   // index = 61  
		{
			return 464.0;
		}
		else if (size > 464.0 && size <= 494.0)   // index = 62  
		{
			return 494.0;
		}
		else if (size > 494.0 && size <= 526.0)   // index = 63  
		{
			return 526.0;
		}
	}
	if (big63 == 1)
	{
		if (size > 526.0 && size <= 560.0)   // index = 64  
		{
			return 560.0;
		}
		else if (size > 560.0 && size <= 597.0)   // index = 65  
		{
			return 597.0;
		}
		else if (size > 597.0 && size <= 635.0)   // index = 66  
		{
			return 635.0;
		}
		else if (size > 635.0 && size <= 677.0)   // index = 67  
		{
			return 677.0;
		}
		else if (size > 677.0 && size <= 720.0)   // index = 68  
		{
			return 720.0;
		}
		else if (size > 720.0 && size <= 767.0)   // index = 69  
		{
			return 767.0;
		}
		else if (size > 767.0 && size <= 817.0)   // index = 70  
		{
			return 817.0;
		}
		else if (size > 817.0 && size <= 870.0)   // index = 71  
		{
			return 870.0;
		}
		else if (size > 870.0 && size <= 926.0)   // index = 72  
		{
			return 926.0;
		}
		else if (size > 926.0 && size <= 987.0)   // index = 73  
		{
			return 987.0;
		}
		else if (size > 987.0 && size <= 1051.0)   // index = 74  
		{
			return 1051.0;
		}
		else if (size > 1051.0 && size <= 1119.0)   // index = 75  
		{
			return 1119.0;
		}
		else if (size > 1119.0 && size <= 1191.0)   // index = 76  
		{
			return 1191.0;
		}
		else if (size > 1191.0 && size <= 1269.0)   // index = 77  
		{
			return 1269.0;
		}
		else if (size > 1269.0 && size <= 1351.0)   // index = 78  
		{
			return 1351.0;
		}
		else if (size > 1351.0 && size <= 1439.0)   // index = 79  
		{
			return 1439.0;
		}
		else if (size > 1439.0 && size <= 1532.0)   // index = 80  
		{
			return 1532.0;
		}
		else if (size > 1532.0 && size <= 1631.0)   // index = 81  
		{
			return 1631.0;
		}
		else if (size > 1631.0 && size <= 1737.0)   // index = 82  
		{
			return 1737.0;
		}
		else if (size > 1737.0 && size <= 1850.0)   // index = 83  
		{
			return 1850.0;
		}
		else if (size > 1850.0 && size <= 1970.0)   // index = 84  
		{
			return 1970.0;
		}
		else if (size > 1970.0 && size <= 2098.0)   // index = 85  
		{
			return 2098.0;
		}
		else if (size > 2098.0 && size <= 2234.0)   // index = 86  
		{
			return 2234.0;
		}
		else if (size > 2234.0 && size <= 2379.0)   // index = 87  
		{
			return 2379.0;
		}
		else if (size > 2379.0 && size <= 2533.0)   // index = 88  
		{
			return 2533.0;
		}
		else if (size > 2533.0 && size <= 2698.0)   // index = 89  
		{
			return 2698.0;
		}
		else if (size > 2698.0 && size <= 2873.0)   // index = 90  
		{
			return 2873.0;
		}
		else if (size > 2873.0 && size <= 3059.0)   // index = 91  
		{
			return 3059.0;
		}
		else if (size > 3059.0 && size <= 3258.0)   // index = 92  
		{
			return 3258.0;
		}
		else if (size > 3258.0 && size <= 3469.0)   // index = 93  
		{
			return 3469.0;
		}
		else if (size > 3469.0 && size <= 3694.0)   // index = 94  
		{
			return 3694.0;
		}
		else if (size > 3694.0 && size <= 3934.0)   // index = 95  
		{
			return 3934.0;
		}
		else if (size > 3934.0 && size <= 4189.0)   // index = 96  
		{
			return 4189.0;
		}
		else if (size > 4189.0 && size <= 4461.0)   // index = 97  
		{
			return 4461.0;
		}
		else if (size > 4461.0 && size <= 4751.0)   // index = 98  
		{
			return 4751.0;
		}
		else if (size > 4751.0 && size <= 5059.0)   // index = 99  
		{
			return 5059.0;
		}
		else if (size > 5059.0 && size <= 5387.0)   // index = 100  
		{
			return 5387.0;
		}
		else if (size > 5387.0 && size <= 5737.0)   // index = 101  
		{
			return 5737.0;
		}
		else if (size > 5737.0 && size <= 6109.0)   // index = 102  
		{
			return 6109.0;
		}
		else if (size > 6109.0 && size <= 6506.0)   // index = 103  
		{
			return 6506.0;
		}
		else if (size > 6506.0 && size <= 6928.0)   // index = 104  
		{
			return 6928.0;
		}
		else if (size > 6928.0 && size <= 7378.0)   // index = 105  
		{
			return 7378.0;
		}
		else if (size > 7378.0 && size <= 7857.0)   // index = 106  
		{
			return 7857.0;
		}
		else if (size > 7857.0 && size <= 8367.0)   // index = 107  
		{
			return 8367.0;
		}
		else if (size > 8367.0 && size <= 8910.0)   // index = 108  
		{
			return 8910.0;
		}
		else if (size > 8910.0 && size <= 9488.0)   // index = 109  
		{
			return 9488.0;
		}
		else if (size > 9488.0 && size <= 10104.0)   // index = 110  
		{
			return 10104.0;
		}
		else if (size > 10104.0 && size <= 10760.0)   // index = 111  
		{
			return 10760.0;
		}
		else if (size > 10760.0 && size <= 11458.0)   // index = 112  
		{
			return 11458.0;
		}
		else if (size > 11458.0 && size <= 12202.0)   // index = 113  
		{
			return 12202.0;
		}
		else if (size > 12202.0 && size <= 12994.0)   // index = 114  
		{
			return 12994.0;
		}
		else if (size > 12994.0 && size <= 13838.0)   // index = 115  
		{
			return 13838.0;
		}
		else if (size > 13838.0 && size <= 14736.0)   // index = 116  
		{
			return 14736.0;
		}
		else if (size > 14736.0 && size <= 15692.0)   // index = 117  
		{
			return 15692.0;
		}
		else if (size > 15692.0 && size <= 16711.0)   // index = 118  
		{
			return 16711.0;
		}
		else if (size > 16711.0 && size <= 17795.0)   // index = 119  
		{
			return 17795.0;
		}
		else if (size > 17795.0 && size <= 18951.0)   // index = 120  
		{
			return 18951.0;
		}
		else if (size > 18951.0 && size <= 20181.0)   // index = 121  
		{
			return 20181.0;
		}
		else if (size > 20181.0 && size <= 21491.0)   // index = 122  
		{
			return 21491.0;
		}
		else if (size > 21491.0 && size <= 22885.0)   // index = 123  
		{
			return 22885.0;
		}
		else if (size > 22885.0 && size <= 24371.0)   // index = 124  
		{
			return 24371.0;
		}
		else if (size > 24371.0 && size <= 25953.0)   // index = 125  
		{
			return 25953.0;
		}
		else if (size > 25953.0 && size <= 27638.0)   // index = 126  
		{
			return 27638.0;
		}
		else if (size > 27638.0 && size <= 29431.0)   // index = 127  
		{
			return 29431.0;
		}
	}
	
	if (big127 == 1)
	{
		if (size > 29431.0 && size <= 31342.0)   // index = 128  
		{
			return 31342.0;
		}
		else if (size > 31342.0 && size <= 33376.0)   // index = 129  
		{
			return 33376.0;
		}
		else if (size > 33376.0 && size <= 35543.0)   // index = 130  
		{
			return 35543.0;
		}
		else if (size > 35543.0 && size <= 37850.0)   // index = 131  
		{
			return 37850.0;
		}
		else if (size > 37850.0 && size <= 40307.0)   // index = 132  
		{
			return 40307.0;
		}
		else if (size > 40307.0 && size <= 42923.0)   // index = 133  
		{
			return 42923.0;
		}
		else if (size > 42923.0 && size <= 45709.0)   // index = 134  
		{
			return 45709.0;
		}
		else if (size > 45709.0 && size <= 48676.0)   // index = 135  
		{
			return 48676.0;
		}
		else if (size > 48676.0 && size <= 51836.0)   // index = 136  
		{
			return 51836.0;
		}
		else if (size > 51836.0 && size <= 55200.0)   // index = 137  
		{
			return 55200.0;
		}
		else if (size > 55200.0 && size <= 58784.0)   // index = 138  
		{
			return 58784.0;
		}
		else if (size > 58784.0 && size <= 62599.0)   // index = 139  
		{
			return 62599.0;
		}
		else if (size > 62599.0 && size <= 66663.0)   // index = 140  
		{
			return 66663.0;
		}
		else if (size > 66663.0 && size <= 70990.0)   // index = 141  
		{
			return 70990.0;
		}
		else if (size > 70990.0 && size <= 75598.0)   // index = 142  
		{
			return 75598.0;
		}
		else if (size > 75598.0 && size <= 80505.0)   // index = 143  
		{
			return 80505.0;
		}
		else if (size > 80505.0 && size <= 85730.0)   // index = 144 
		{
			return 85730.0;
		}
		else if (size > 85730.0 && size <= 91295.0)   // index = 145 
		{
			return 91295.0;
		}
		else if (size > 91295.0 && size <= 97221.0)   // index = 146 
		{
			return 97221.0;
		}
		else if (size > 97221.0 && size <= 103532.0)   // index = 147 
		{
			return 103532.0;
		}
		else if (size > 103532.0 && size <= 110252.0)   // index = 148 
		{
			return 110252.0;
		}
		else if (size > 110252.0 && size <= 117409.0)   // index = 149 
		{
			return 117409.0;
		}
		else if (size > 117409.0 && size <= 125030.0)   // index = 150 
		{
			return 125030.0;
		}
		else if (size > 125030.0 && size <= 133146.0)   // index = 151 
		{
			return 133146.0;
		}
		else if (size > 133146.0 && size <= 141789.0)   // index = 152 
		{
			return 141789.0;
		}
		else if (size > 141789.0 && size <= 150992.0)   // index = 153 
		{
			return 150992.0;
		}
		else if (size > 150992.0 && size <= 160793.0)   // index = 154 
		{
			return 160793.0;
		}
		else if (size > 160793.0 && size <= 171231.0)   // index = 155 
		{
			return 171231.0;
		}
		else if (size > 171231.0 && size <= 182345.0)   // index = 156 
		{
			return 182345.0;
		}
		else if (size > 182345.0 && size <= 194182.0)   // index = 157 
		{
			return 194182.0;
		}
		else if (size > 194182.0 && size <= 206786.0)   // index = 158 
		{
			return 206786.0;
		}
		else if (size > 206786.0 && size <= 220209.0)   // index = 159 
		{
			return 220209.0;
		}
		else if (size > 220209.0 && size <= 234503.0)   // index = 160 
		{
			return 234503.0;
		}
		else if (size > 234503.0 && size <= 249725.0)   // index = 161 
		{
			return 249725.0;
		}
		else if (size > 249725.0 && size <= 265935.0)   // index = 162 
		{
			return 265935.0;
		}
		else if (size > 265935.0 && size <= 283197.0)   // index = 163 
		{
			return 283197.0;
		}
		else if (size > 283197.0 && size <= 301579.0)   // index = 164 
		{
			return 301579.0;
		}
		else if (size > 301579.0 && size <= 321155.0)   // index = 165 
		{
			return 321155.0;
		}
		else if (size > 321155.0 && size <= 342002.0)   // index = 166 
		{
			return 342002.0;
		}
		else if (size > 342002.0 && size <= 364202.0)   // index = 167 
		{
			return 364202.0;
		}
		else if (size > 364202.0 && size <= 387842.0)   // index = 168 
		{
			return 387842.0;
		}
		else if (size > 387842.0 && size <= 413018.0)   // index = 169 
		{
			return 413018.0;
		}
		else if (size > 413018.0 && size <= 439827.0)   // index = 170 
		{
			return 439827.0;
		}
		else if (size > 439827.0 && size <= 468377.0)   // index = 171 
		{
			return 468377.0;
		}
		else if (size > 468377.0 && size <= 498780.0)   // index = 172 
		{
			return 498780.0;
		}
		else if (size > 498780.0 && size <= 531156.0)   // index = 173 
		{
			return 531156.0;
		}
		else if (size > 531156.0 && size <= 565634.0)   // index = 174 
		{
			return 565634.0;
		}
		else if (size > 565634.0 && size <= 602350.0)   // index = 175 
		{
			return 602350.0;
		}
		else if (size > 602350.0 && size <= 641449.0)   // index = 176 
		{
			return 641449.0;
		}
		else if (size > 641449.0 && size <= 683087.0)   // index = 177 
		{
			return 683087.0;
		}
		else if (size > 683087.0 && size <= 727427.0)   // index = 178 
		{
			return 727427.0;
		}
		else if (size > 727427.0 && size <= 774645.0)   // index = 179 
		{
			return 774645.0;
		}
		else if (size > 774645.0 && size <= 824928.0)   // index = 180 
		{
			return 824928.0;
		}
		else if (size > 824928.0 && size <= 878475.0)   // index = 181 
		{
			return 878475.0;
		}
		else if (size > 878475.0 && size <= 935498.0)   // index = 182 
		{
			return 935498.0;
		}
		else if (size > 935498.0 && size <= 996222.0)   // index = 183 
		{
			return 996222.0;
		}
		else if (size > 996222.0 && size <= 1060888.0)   // index = 184 
		{
			return 1060888.0;
		}
		else if (size > 1060888.0 && size <= 1129752.0)   // index = 185 
		{
			return 1129752.0;
		}
		else if (size > 1129752.0 && size <= 1203085.0)   // index = 186 
		{
			return 1203085.0;
		}
		else if (size > 1203085.0 && size <= 1281179.0)   // index = 187 
		{
			return 1281179.0;
		}
		else if (size > 1281179.0 && size <= 1364342.0)   // index = 188 
		{
			return 1364342.0;
		}
		else if (size > 1364342.0 && size <= 1452903.0)   // index = 189 
		{
			return 1452903.0;
		}
		else if (size > 1452903.0 && size <= 1547213.0)   // index = 190 
		{
			return 1547213.0;
		}
		else if (size > 1547213.0 && size <= 1647644.0)   // index = 191 
		{
			return 1647644.0;
		}
	}

	if(big191 == 1)
	{ 
		if (size > 1647644.0 && size <= 1754595.0)   // index = 192 
		{
			return 1754595.0;
		}
		else if (size > 1754595.0 && size <= 1868488.0)   // index = 193 
		{
			return 1868488.0;
		}
		else if (size > 1868488.0 && size <= 1989774.0)   // index = 194 
		{
			return 1989774.0;
		}
		else if (size > 1989774.0 && size <= 2118933.0)   // index = 195 
		{
			return 2118933.0;
		}
		else if (size > 2118933.0 && size <= 2256475.0)   // index = 196 
		{
			return 2256475.0;
		}
		else if (size > 2256475.0 && size <= 2402946.0)   // index = 197 
		{
			return 2402946.0;
		}
		else if (size > 2402946.0 && size <= 2558924.0)   // index = 198 
		{
			return 2558924.0;
		}
		else if (size > 2558924.0 && size <= 2725027.0)   // index = 199 
		{
			return 2725027.0;
		}
		else if (size > 2725027.0 && size <= 2901912.0)   // index = 200 
		{
			return 2901912.0;
		}
		else if (size > 2901912.0 && size <= 3090279.0)   // index = 201 
		{
			return 3090279.0;
		}
		else if (size > 3090279.0 && size <= 3290873.0)   // index = 202 
		{
			return 3290873.0;
		}
		else if (size > 3290873.0 && size <= 3504487.0)   // index = 203 
		{
			return 3504487.0;
		}
		else if (size > 3504487.0 && size <= 3731968.0)   // index = 204 
		{
			return 3731968.0;
		}
		else if (size > 3731968.0 && size <= 3974215.0)   // index = 205 
		{
			return 3974215.0;
		}
		else if (size > 3974215.0 && size <= 4232186.0)   // index = 206 
		{
			return 4232186.0;
		}
		else if (size > 4232186.0 && size <= 4506902.0)   // index = 207 
		{
			return 4506902.0;
		}
		else if (size > 4506902.0 && size <= 4799451.0)   // index = 208 
		{
			return 4799451.0;
		}
		else if (size > 4799451.0 && size <= 5110989.0)   // index = 209 
		{
			return 5110989.0;
		}
		else if (size > 5110989.0 && size <= 5442750.0)   // index = 210 
		{
			return 5442750.0;
		}
		else if (size > 5442750.0 && size <= 5796046.0)   // index = 211 
		{
			return 5796046.0;
		}
		else if (size > 5796046.0 && size <= 6172275.0)   // index = 212 
		{
			return 6172275.0;
		}
		else if (size > 6172275.0 && size <= 6572925.0)   // index = 213 
		{
			return 6572925.0;
		}
		else if (size > 6572925.0 && size <= 6999582.0)   // index = 214 
		{
			return 6999582.0;
		}
		else if (size > 6999582.0 && size <= 7453933.0)   // index = 215 
		{
			return 7453933.0;
		}
		else if (size > 7453933.0 && size <= 7937777.0)   // index = 216 
		{
			return 7937777.0;
		}
		else if (size > 7937777.0 && size <= 8453028.0)   // index = 217 
		{
			return 8453028.0;
		}
		else if (size > 8453028.0 && size <= 9001725.0)   // index = 218 
		{
			return 9001725.0;
		}
		else if (size > 9001725.0 && size <= 9586039.0)   // index = 219 
		{
			return 9586039.0;
		}
		else if (size > 9586039.0 && size <= 10208280.0)   // index = 220 
		{
			return 10208280.0;
		}
		else if (size > 10208280.0 && size <= 10870913.0)   // index = 221 
		{
			return 10870913.0;
		}
		else if (size > 10870913.0 && size <= 11576557.0)   // index = 222 
		{
			return 11576557.0;
		}
		else if (size > 11576557.0 && size <= 12328006.0)   // index = 223 
		{
			return 12328006.0;
		}
		else if (size > 12328006.0 && size <= 13128233.0)   // index = 224 
		{
			return 13128233.0;
		}
		else if (size > 13128233.0 && size <= 13980403.0)   // index = 225 
		{
			return 13980403.0;
		}
		else if (size > 13980403.0 && size <= 14887889.0)   // index = 226 
		{
			return 14887889.0;
		}
		else if (size > 14887889.0 && size <= 15854280.0)   // index = 227 
		{
			return 15854280.0;
		}
		else if (size > 15854280.0 && size <= 16883401.0)   // index = 228 
		{
			return 16883401.0;
		}
		else if (size > 16883401.0 && size <= 17979324.0)   // index = 229 
		{
			return 17979324.0;
		}
		else if (size > 17979324.0 && size <= 19146385.0)   // index = 230 
		{
			return 19146385.0;
		}
		else if (size > 19146385.0 && size <= 20389201.0)   // index = 231 
		{
			return 20389201.0;
		}
		else if (size > 20389201.0 && size <= 21712690.0)   // index = 232 
		{
			return 21712690.0;
		}
		else if (size > 21712690.0 && size <= 23122088.0)   // index = 233 
		{
			return 23122088.0;
		}
		else if (size > 23122088.0 && size <= 24622972.0)   // index = 234 
		{
			return 24622972.0;
		}
		else if (size > 24622972.0 && size <= 26221280.0)   // index = 235 
		{
			return 26221280.0;
		}
		else if (size > 26221280.0 && size <= 27923336.0)   // index = 236 
		{
			return 27923336.0;
		}
		else if (size > 27923336.0 && size <= 29735875.0)   // index = 237 
		{
			return 29735875.0;
		}
		else if (size > 29735875.0 && size <= 31666069.0)   // index = 238 
		{
			return 31666069.0;
		}
		else if (size > 31666069.0 && size <= 33721553.0)   // index = 239 
		{
			return 33721553.0;
		}
		else if (size > 33721553.0 && size <= 35910462.0)   // index = 240 
		{
			return 35910462.0;
		}
		else if (size > 35910462.0 && size <= 38241455.0)   // index = 241 
		{
			return 38241455.0;
		}
		else if (size > 38241455.0 && size <= 40723756.0)   // index = 242 
		{
			return 40723756.0;
		}
		else if (size > 40723756.0 && size <= 43367187.0)   // index = 243 
		{
			return 43367187.0;
		}
		else if (size > 43367187.0 && size <= 46182206.0)   // index = 244 
		{
			return 46182206.0;
		}
		else if (size > 46182206.0 && size <= 49179951.0)   // index = 245 
		{
			return 49179951.0;
		}
		else if (size > 49179951.0 && size <= 52372284.0)   // index = 246 
		{
			return 52372284.0;
		}
		else if (size > 52372284.0 && size <= 55771835.0)   // index = 247 
		{
			return 55771835.0;
		}
		else if (size > 55771835.0 && size <= 59392055.0)   // index = 248 
		{
			return 59392055.0;
		}
		else if (size > 59392055.0 && size <= 63247269.0)   // index = 249 
		{
			return 63247269.0;
		}
		else if (size > 63247269.0 && size <= 67352729.0)   // index = 250 
		{
			return 67352729.0;
		}
		else if (size > 67352729.0 && size <= 71724679.0)   // index = 251 
		{
			return 71724679.0;
		}
		else if (size > 71724679.0 && size <= 76380419.0)   // index = 252 
		{
			return 76380419.0;
		}
		else if (size > 76380419.0 && size <= 81338368.0)   // index = 253 
		{
			return 81338368.0;
		}
		else if (size > 81338368.0)   // index = 254 
		{
			return size;
		}
	}
}

void SchedulingURLLCMS::Feedback()
{
	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NRuRLLC.bandwidth * 1e6 / 1000;
	arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NRuRLLC.bandwidth / 10 * 50), temps;

	tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
	UMS[id]->channel->ShortTermChannel(id);
	for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
	{
		tempRHr = tempRHr + UMS[id]->channel->FrequencyChannel(0, 0, RBindex)	*	(UMS[id]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50);
		tempRH = tempRH + (UMS[id]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(UMS[id]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50);
	}

	arma::svd(tempU, temps, tempV, tempRH, "std");
	for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
	{
		tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
		for (int si = 1; si < SLS_MAX_BS; si++)
		{
			tempRI = tempRI + UMS[id]->channel->FrequencyChannel(si, 0, RBindex)*UMS[id]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
		}
		tempM = UMS[id]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
		temph = tempIRC*UMS[id]->channel->FrequencyChannel(0, 0, RBindex);
		signal = temph*temph.t();
		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
	}

	UMS[id]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / 50) - 1 + UMS[id]->scheduling->HARQeSINR;
	UMS[id]->scheduling->downlinkESINRdB = 10.0 * log10(UMS[id]->scheduling->downlinkESINR);
	UMS[id]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(UMS[id]->scheduling->downlinkESINRdB, UMS[id]->scheduling->MCS);	


	//================= Point ====================//
	double WCbuffer5 = 0, WCbuffer4 = 0, WCbuffer0 = 0, FMbuffer5=0, FMbuffer4=0;
	double WCbuffer5_B = 0, WCbuffer4_B = 0, WCbuffer0_B = 0, FMbuffer5_B = 0, FMbuffer4_B = 0;
	double temp;
	if (Sim.TTI == 0)
	{
		WCbuffer5 = 0, WCbuffer4 = 0, WCbuffer0 = 0, FMbuffer5 = 0, FMbuffer4 = 0;
	}
	else
	{	
		//cout << " Sim.CCtrigger = " << Sim.CCtrigger << endl;
		for (int i = Sim.CCtrigger; i < Sim.x; i++)
		{	
			if (last_pos_CC_2 == send_pos_CC_2)
			{
				if (wtofUMS5TS[i][0] < Sim.TTI && wtofUMS5TS[i][0] != 0 && wtofUMS5TS[i][2] == 0)
				{
					if (Sim.wtofLCID000101[i][10] == "opcua")
					{
						temp = stod(Sim.wtofLCID000101[i][2]);
						WCbuffer5_B = WCbuffer5_B + temp;
						break;
					}
					else
					{
						temp = stod(Sim.wtofLCID000101[i][2]);
						WCbuffer5_B = WCbuffer5_B + temp;
					}
				}
			}
			else if (wtofUMS5TS[i][0] > Sim.TTI || last_pos_CC_2 != send_pos_CC_2)
			{
				break;
			}
		}
		
		WCbuffer5 = BSRIndex(WCbuffer5_B);
		

		//cout << " Sim.Atrigger = " << Sim.Atrigger << endl;
		for (int i = Sim.Atrigger; i < Sim.y; i++)
		{
			if (last_pos_A_2 == send_pos_A_2)
			{
				if (wtofUMS4TS[i][0] < Sim.TTI && wtofUMS4TS[i][0] != 0 && wtofUMS4TS[i][2] == 0)
				{
					if (Sim.wtofLCID000100[i][10] == "opcua")
					{
						temp = stod(Sim.wtofLCID000100[i][2]);
						WCbuffer4_B = WCbuffer4_B + temp;
						break;
					}
					else
					{
						temp = stod(Sim.wtofLCID000100[i][2]);
						WCbuffer4_B = WCbuffer4_B + temp;
					}
				}
			}
			else if (wtofUMS4TS[i][0] > Sim.TTI || last_pos_A_2 != send_pos_A_2)
			{
				break;
			}
		}
		WCbuffer4 = BSRIndex(WCbuffer4_B);

		//cout << " Sim.Mtrigger = " << Sim.Mtrigger << endl;
		for (int i = 0; i < Sim.Mtrigger; i++)
		{
			if (wtofUMS0TS[i][0] < Sim.TTI && wtofUMS0TS[i][0] != 0 && wtofUMS0TS[i][2] == 0)
			{
				temp = stod(Sim.wtofLCID000000[i][2]);
				WCbuffer0_B = WCbuffer0_B + temp;
			}
		}
		WCbuffer0 = BSRIndex(WCbuffer0_B);

		for (int i = last_pos_CC_2; i < send_pos_CC_2; i++)
		{
			if (ftowUMS5TS[i][0] < Sim.TTI && ftowUMS5TS[i][0] != 0 && ftowUMS5TS[i][2] == 0)   //  當封包由FM-->gNB的時間小於傳輸間格時間
			{
				temp = stod(Sim.ftowLCID000101[i][2]);
				FMbuffer5_B = FMbuffer5_B + temp;
			}
		}
		FMbuffer5 = BSRIndex(FMbuffer5_B);

		for (int i = last_pos_A_2; i < send_pos_A_2; i++)
		{
			if (ftowUMS4TS[i][0] < Sim.TTI && ftowUMS4TS[i][0] != 0 && ftowUMS4TS[i][2] == 0)   //  當封包由FM-->gNB的時間小於傳輸間格時間
			{
				temp = stod(Sim.ftowLCID000100[i][2]);
				FMbuffer4_B = FMbuffer4_B + temp;
			}
		}
		FMbuffer4 = BSRIndex(FMbuffer4_B);
	}
	BS[0]->scheduling->BSR(WCbuffer5, WCbuffer4, WCbuffer0, FMbuffer5, FMbuffer4);
}

void SchedulingURLLCMS::ReceivedSINR()
{
	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NRuRLLC.bandwidth * 1e6 / 1000;
	arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NRuRLLC.bandwidth / 10 * 50), temps;

	tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
	UMS[id]->channel->ShortTermChannel(id);
	for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
	{
		tempRHr = tempRHr + UMS[id]->channel->FrequencyChannel(0, 0, RBindex)	*	(UMS[id]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50);
		tempRH = tempRH + (UMS[id]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(UMS[id]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50);
	}

	arma::svd(tempU, temps, tempV, tempRH, "std");
	for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
	{
		tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
		for (int si = 1; si < SLS_MAX_BS; si++)
		{
			tempRI = tempRI + UMS[id]->channel->FrequencyChannel(si, 0, RBindex)*UMS[id]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
		}
		tempM = UMS[id]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
		temph = tempIRC*UMS[id]->channel->FrequencyChannel(0, 0, RBindex);
		signal = temph*temph.t();
		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
	}

	UMS[id]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / 50) - 1 + UMS[id]->scheduling->HARQeSINR;
	UMS[id]->scheduling->downlinkESINRdB = 10.0 * log10(UMS[id]->scheduling->downlinkESINR);
}

arma::cx_mat* SchedulingURLLCMS::PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type)
{
	codebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort * 2];
	arma::cx_mat tempanalogCodebook;
	//tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
	int index_t1, index_t2;
	std::complex <double> *phase_a = new std::complex <double>[2];
	std::complex <double> phase;
	if (type == 0);
	else
	{
		switch (precodingtype)
		{
		case Analogbeamforming:
			//codebook = new arma::cx_mat[Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2];
			tempanalogCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);

			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
				{
					phase.real(0.0);
					phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
					tempanalogCodebook(j, i) = exp(phase);
				}
			}
			index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;
			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort; j++)
				{
					if (i % 2 == 0)
					{
						codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t1 = index_t1 + 1;
					}
					else
					{
						codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t2 = index_t2 + 1;
					}
				}
			}
			//arma::cx_mat tempanalogCodebook;
			/*tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);

			for (int i = 0; i < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; i++)
			{
			for (int j = 0; j < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2; j++)
			{
			phase.real(0.0);
			phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna));
			tempanalogCodebook(j, i) = exp(phase);
			}
			}
			index_t1 = 0; index_t2 = Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna;
			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
			for (int i = 0; i < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; i++)
			{
			for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort; j++)
			{
			if (i % 2 == 0)
			{
			codebook[index_t1].zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, 1);
			codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
			index_t1 = index_t1 + 1;
			}
			else
			{
			codebook[index_t2].zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, 1);
			codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t2].submat(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
			index_t2 = index_t2 + 1;
			}
			}
			}*/
			return codebook;
			break;

		case Digitalbeamforming:
			arma::cx_mat tempdigitalCodebook;
			tempdigitalCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);

			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
				{
					phase.real(0.0);
					phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
					tempdigitalCodebook(j, i) = exp(phase);
				}
			}
			index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;
			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort; j++)
				{
					if (i % 2 == 0)
					{
						codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t1 = index_t1 + 1;
					}
					else
					{
						codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t2 = index_t2 + 1;
					}
				}
			}
			return codebook;
			break;
		}
	}	
	
}

void SchedulingURLLCMS::ConcludeIteration()
{

}

void SchedulingURLLCMS::Conclude()
{

}
