/****************************************************************************

System Level Simulation (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSim_NRuRLLC.cpp
DATE         : 2017.12.1
VERSION      : 0.5
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.5.20	Minsig Han    	Created
2017.7.10	Minsig Han    	Add variables for non-full buffer scenario
2017.11.14	Jaewon Lee    	Add variables for 
2017.12.1	Jaewon Lee    	Add variables for
===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include "SystemSim_NRuRLLC.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <time.h>

/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                   SLS Simulator class Initialize                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/
using namespace std;


//===  Point!!!   ===//
int main()
{

	clock_t START, END;
	//double cpu_time_used;
	START = clock();
	/*cout << "Enter Scenario" << endl;
	cin >> Sim.scenarioNum;*/
	Sim.CCtrigger = 0;
	Sim.Atrigger = 0;
	Sim.Mtrigger = 0;
	//Sim.Input5GPacket(Sim.scenarioNum);
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_CC_5G.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_A_5G.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_M_5G.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_CC_priority.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_A_priority.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_M_priority.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_CC_PBR.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_A_PBR.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 lukelin@192.168.0.102:/home/lukelin/Desktop/WC-CC/WC_M_PBR.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 j@192.168.0.100:/home/j/Desktop/FM-CC/FM_CC_5G.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 j@192.168.0.100:/home/j/Desktop/FM-CC/FM_A_5G.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 j@192.168.0.100:/home/j/Desktop/FM-CC/FM_CC_priority.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 j@192.168.0.100:/home/j/Desktop/FM-CC/FM_A_priority.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 j@192.168.0.100:/home/j/Desktop/FM-CC/FM_CC_PBR.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	system("pscp -P 22 -pw 0917826009 j@192.168.0.100:/home/j/Desktop/FM-CC/FM_A_PBR.txt C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/InputData/SimulationParameter/SystemSimParameter");
	Sim.Input5GPacket("WC_CC_5G","WC_A_5G","WC_M_5G","FM_CC_5G","FM_A_5G");  // Input5GPacket function請往下查看
	Sim.InputRRCMsg("WC_CC_priority", "WC_A_priority", "WC_M_priority", "FM_CC_priority", "FM_A_priority");
	Sim.InputRRCPBR("WC_CC_PBR", "WC_A_PBR", "WC_M_PBR", "FM_CC_PBR", "FM_A_PBR");

	Sim.Initialize("NRuRLLC_UrbanMacroCell"); // Simulation initialization
	Sim.network->PlaceMacroBS(); // Macro BS placement
	for (int i = 0; i < Sim.numIteration; i++)//迭代一次
	{
		//Sim.network->PlaceEMBBMS(); // eMBB MS placement (Full buffer)
		Sim.network->PlaceURLLCMS(); // uRLLC MS placement (non-Full buffer)
		Sim.network->PlaceWraparound();
		Sim.channel->LongTermChannel();
		cout << "====================== NumTTIperFrame is " << Sim.numTTIperFrame << " ==================" << endl;

		cout << "*******************Simulation Start*******************" << endl;
		cout << "Enter Scheduling Algorithm (WGCL / LCP / AW-WGCL)" << endl;
		cin >> Sim.algorithm;
		//Sim.algorithm = "LCP";
		//cout << "Enter quantum = (1=1s, 10=0.1s, 100=10ms, 1000=1ms)" << endl;
		//cin >> Sim.quantum;
		Sim.quantum = 1000;  
		Sim.outWTrecord.open("../../Simulator/Data/OutputData/WTrecord.txt");  //  out window time record 
		
		if (Sim.algorithm == "WGCL"|| Sim.algorithm == "AW-WGCL"|| Sim.algorithm == "RR" || Sim.algorithm == "LCP")
		{	
			if (Sim.algorithm == "WGCL")
				cout << "Implemented algorithm =====> WGCL !!!" << endl;
			if (Sim.algorithm == "AW-WGCL")
				cout << "Implemented algorithm =====> AW-WGCL !!!" << endl;
			if (Sim.algorithm == "RR")
				cout << "Implemented algorithm =====> RR !!!" << endl;
			if (Sim.algorithm == "LCP")
				cout << "Implemented algorithm =====> LCP !!!" << endl;
			Sim.outfWGCL_WCCC_1.open("../../Simulator/Data/OutputData/before_WCCC_5G.txt");
			Sim.outfWGCL_WCA_1.open("../../Simulator/Data/OutputData/before_WCA_5G.txt");
			Sim.outfWGCL_WCM_1.open("../../Simulator/Data/OutputData/before_WCM_5G.txt");
			Sim.outfWGCL_FMCC_1.open("../../Simulator/Data/OutputData/before_FMCC_5G.txt");
			Sim.outfWGCL_FMA_1.open("../../Simulator/Data/OutputData/before_FMA_5G.txt");
			Sim.outfWGCL_WCCC_2.open("../../Simulator/Data/OutputData/after_WCCC_5G.txt");
			Sim.outfWGCL_WCA_2.open("../../Simulator/Data/OutputData/after_WCA_5G.txt");
			Sim.outfWGCL_WCM_2.open("../../Simulator/Data/OutputData/after_WCM_5G.txt");
			Sim.outfWGCL_FMCC_2.open("../../Simulator/Data/OutputData/after_FMCC_5G.txt");
			Sim.outfWGCL_FMA_2.open("../../Simulator/Data/OutputData/after_FMA_5G.txt");
			//Sim.outfWGCL_CCoverlap.open("../../Simulator/Data/OutputData/CCoverlap.txt");
			//Sim.outfWGCL_Aoverlap.open("../../Simulator/Data/OutputData/Aoverlap.txt");
		}

		// Initial TTI is set 0 
		for (Sim.TTI = 0; Sim.TTI < 91; Sim.TTI=Sim.TTI+(double)1/Sim.quantum)
		{	 
			if (Sim.algorithm == "RR" || Sim.algorithm == "WGCL" || Sim.algorithm == "AW-WGCL"|| Sim.algorithm == "LCP")
			{
				if (Sim.TTI == 0 || (int)(Sim.TTI*Sim.quantum) % Sim.feedbackPeriod == 0)   // 判斷是否需要回報BSR
				{
					Sim.scheduling->Feedback(); // MS feedback	
				}
			}
			/*else if (Sim.algorithm == "LCP")
				Sim.scheduling->Feedback(); // MS feedback    僅開始傳輸時回報BSR*/
			setcolor(3, 0);
			printf("*************current time %.3lf *************\n", Sim.TTI);
			Sim.scheduling->Schedule();
			setcolor(9, 0);
			
		} 

		//  統計三個流量分配的Window Time總共為多少百分比
		setcolor(3, 0);
		/*cout<< Sim.c_wt5<<" "<< Sim.c_wt2 <<" "<< Sim.c_wt1<<endl;
		cout << Sim.c_nwt5 << " " << Sim.c_nwt2 << " " << Sim.c_nwt1 << endl;*/
		cout << "=========================================== In Work Cell ==========================================" << endl;
		cout <<"Window Time(%): "<< Sim.c_wt5_wc/Sim.c_nwt5_wc*100000 << " " << Sim.c_wt4_wc/Sim.c_nwt4_wc * 100000 << " " << Sim.c_wt0_wc/Sim.c_nwt0_wc * 100000<< endl;
		cout << "====================================== In Factory Management ======================================" << endl;
		cout << "Window Time(%): " << Sim.c_wt5_fm / Sim.c_nwt5_fm * 100000 << " " << Sim.c_wt4_fm / Sim.c_nwt4_fm * 100000 << endl;
																//for (Sim.TTI = 0; Sim.TTI < Sim.numTTI; Sim.TTI++)
																//{
																//	Sim.scheduling->BufferUpdate(); // System buffer update
																//	if (Sim.TTI == 0 || Sim.TTI % Sim.feedbackPeriod == 0)
																//	{
																//		Sim.scheduling->Feedback(); // MS feedback				
																//	}
																//	Sim.scheduling->Schedule(); // Scheduling
																//	Sim.performance->Measure(); // Throughput measurement
																//	cout << "******TTI " << Sim.TTI << "******" << endl;
																//	Sim.Demonstration();
		Sim.ConcludeIteration(); // Iteration conclusion
	}
	Sim.Conclude(); // Simulation conclusion
	//Sim.outfWGCL.close();
	Sim.outfWGCL_WCCC_1.close();
	Sim.outfWGCL_WCA_1.close();
	Sim.outfWGCL_WCM_1.close();
	Sim.outfWGCL_FMCC_1.close();
	Sim.outfWGCL_FMA_1.close();
	Sim.outfWGCL_WCCC_2.close();
	Sim.outfWGCL_WCA_2.close();
	Sim.outfWGCL_WCM_2.close();
	Sim.outfWGCL_FMCC_2.close();
	Sim.outfWGCL_FMA_2.close();
	Sim.outWTrecord.close();

	END = clock();
	cout << "runnung time = " << ((double)(END - START))/CLOCKS_PER_SEC << " sec" <<endl;  // 顯示模擬跑的時間
	//  將結果回傳至Ubuntu電腦內
	//system("sshpass -p \"hunt812bid687\" scp  -o 5GURLLC-simsys\Simulator\Data\OutputData\after000.txt lab207@192.168.0.102:/home/lab207/Desktop/cyh-monitor/monitor");
	system("pscp -P 22 -pw 0917826009 C:/Users/ASUS/桌面/ZRL_thesis/5G-K/5GURLLC-simsys/Simulator/Data/OutputData/*.txt lukelin@192.168.0.102:/home/lukelin/Desktop/result");
	system("pause");
	
	return 0;
}


void SystemSim::Initialize(string fileName)
{
	// Random seed
	arma::arma_rng::set_seed_random();

	// Open the file
	ifstream inFile("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/SimParamTop_" + fileName + ".txt",ios::out);  // 此txt檔紀錄了設定的參數
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) 
		{

			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "numTTI") numTTI = stoi(result[1]); //跑幾個TTI(transmission time interval)時間間隔
			else if (result[0] == "numerologyParameter") numerologyParameter = stoi(result[1]); // numerology設為 0
			else if (result[0] == "numSymbolperTTI") numSymbolperTTI = stoi(result[1]);
			else if (result[0] == "numIteration") numIteration = stoi(result[1]);//迭代次數
			else if (result[0] == "feedbackPeriod") feedbackPeriod = stoi(result[1]);  // 每5ms check BSR來調用WGCL 
			else if (result[0] == "scenario") scenario = SLS::Scenario(stoi(result[1])); // IndoorOffice
			else if (result[0] == "linkDirection") linkDirection = SLS::LinkDirection(stoi(result[1])); // Uplink
			
		}
	}
	numTTIperFrame = pow(2.0, numerologyParameter) * 10; //pow(底數, 指數)
	subcarrierSpacing = pow(2.0, numerologyParameter) * 15;

	network = new Network();
	scheduling = new Scheduling();
	performance = new Performance();
	channel = new Channel();


	network->Initialize(fileName); // Parameter initialization for network configuration
	channel->Initialize(fileName); // Parameter initialization for channel
	scheduling->Initialize(fileName); // Parameter initialization for radio resource management
	performance->Initialize(fileName); // Parameter initialization for link performance	

	Sim.RateTTI.zeros(Sim.network->numMS,Sim.numTTI);
	Sim.LatencyTTI.zeros(Sim.network->numMS, Sim.numTTI);
	Sim.BufferTTI.zeros(Sim.network->numMS, Sim.numTTI);

}

void SplitString_ini(const string& s, vector<string>& v, const string& c)
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

void SystemSim::Input5GPacket(string WCCCfile, string WCAfile, string WCMfile, string FMCCfile, string FMAfile) {
	string s;
	x = 0, y = 0, z = 0, xback = 0, yback = 0;
	vector<string> v, L1, L2;
	ifstream inf1, inf2, inf3, inf4, inf5;
	double length_macheader, total_packetsize;

	while(1)
	{
		inf1.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCCCfile + ".txt");
		inf2.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCAfile + ".txt");
		inf3.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCMfile + ".txt");
		inf4.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + FMCCfile + ".txt");
		inf5.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + FMAfile + ".txt");

		if (inf1.is_open() == true|| inf2.is_open() == true|| inf3.is_open() == true|| inf4.is_open() == true|| inf5.is_open() == true)
		{
			if (inf1.is_open() == true)
			{
				cout << "Received "<< WCCCfile<<".txt !!!!!!!!" << endl;
			}
			if (inf2.is_open() == true)
			{
				cout << "Received " << WCAfile << ".txt !!!!!!!!" << endl;
			}
			if (inf3.is_open() == true)
			{
				cout << "Received " << WCMfile << ".txt !!!!!!!!" << endl;
			}
			if (inf4.is_open() == true)
			{
				cout << "Received " << FMCCfile << ".txt !!!!!!!!" << endl;
			}
			if (inf5.is_open() == true)
			{
				cout << "Received " << FMAfile << ".txt !!!!!!!!" << endl;
			}
			Sleep(1000);
		}
		if (inf1.is_open() == true && inf2.is_open() == true && inf3.is_open() == true && inf4.is_open() == true && inf5.is_open() == true)
		{
			system("CLS");
			cout << "Received all traceFile!!!!!!!!" << endl;
			break;
		}
		else
		{
			system("CLS");
			cout << "Waiting."; 
			Sleep(100);  // 延遲100 ms
			system("CLS");  //  清除輸出的文字
			cout << "Waiting..";
			Sleep(100);
			system("CLS");
			cout << "Waiting...";
			Sleep(100);
			system("CLS");
			cout << "Waiting....";
			Sleep(100);
			system("CLS");
			cout << "Waiting.....";
			Sleep(100);
			system("CLS");
		}
			
	}
	cout << "Loading the " << WCCCfile << ".txt ..." << endl;
	while (getline(inf1, s))
	{
		
		SplitString_ini(s, v, " ");  
		{
			// 將此Message由WorkCell發送的時間儲存至L5S[x][0]
			wtofL5S[x][0] = stod(v[0]);


			// 將此Message的payload size(浮點數型態)儲存至L5[x][1]中
			wtofL5S[x][1] = stod(v[1]);

			// 將5G對應的第幾個封包的Sent更改標示為Queueing並儲存於LCID000101[x][0]中
			wtofLCID000101[x][0] = "Queueing";

			// 其他txt上封包的資訊則依序複製
			for (int i=1; i<(int)v.size()+1; i++)
			{
				wtofLCID000101[x][i] = v[i-1];
			}
			
			x++;
		}
		//s.clear;
		v.clear();
	}
	setcolor(4, 0);
	cout << "Number of Control Comment's packets sent from Work Cell is " << x << " !!!" << endl;
	setcolor(15, 0);
	cout << "Finish of loading " << WCCCfile << ".txt !!!" << endl;
	cout << "Loading the " << WCAfile << ".txt ..." << endl;
	while (getline(inf2, s))
	{
		
		SplitString_ini(s, v, " ");
		{

			// 將此Message由WorkCell發送的時間儲存至L2S[x][0]
			wtofL4S[y][0] = stod(v[0]);
			// 將此Message的payload size(浮點數型態)儲存至L2[x][1]中
			wtofL4S[y][1] = stod(v[1]);

			// 將5G對應的第幾個封包的Sent更改標示為Queueing並儲存於LCID000010[x][0]中
			wtofLCID000100[y][0] = "Queueing";

			// 其他txt上封包的資訊則依序複製
			for (int i = 1; i<(int)v.size() + 1; i++)
			{
				wtofLCID000100[y][i] = v[i - 1];
			}
			y++;
		}

		//s.clear;
		v.clear();
	}
	setcolor(4, 0);
	cout << "Number of Warning's packets sent from Work Cell is " << y << " !!!" << endl;
	setcolor(15, 0);
	cout << "Finish of loading " << WCAfile << ".txt !!!" << endl;
	cout << "Loading the " << WCMfile << ".txt ..." << endl;

	while (getline(inf3, s))
	{
		SplitString_ini(s, v, " ");
		{

			// 將此Message由WorkCell發送的時間儲存至L1S[x][0]
			wtofL0S[z][0] = stod(v[0]);


			// 將此Message的payload size(浮點數型態)儲存至L1[x][1]中
			wtofL0S[z][1] = stod(v[1]);

			// 將5G對應的第幾個封包的Sent更改標示為Queueing並儲存於LCID000001[x][0]中
			wtofLCID000000[z][0] = "Queueing";

			// 其他txt上封包的資訊則依序複製
			for (int i = 1; i<(int)v.size() + 1; i++)
			{
				wtofLCID000000[z][i] = v[i - 1];
			}
			z++;
		}

		//s.clear;
		v.clear();
	}

	setcolor(4, 0);
	cout << "Number of S.D. Uploading's packets sent from Work Cell is " << z << " !!!" << endl;
	setcolor(15, 0);
	cout << "Finish of loading " << WCMfile << ".txt !!!" << endl;
	cout << "Loading the " << FMCCfile << ".txt ..." << endl;

	while (getline(inf4, s))
	{
		SplitString_ini(s, v, " ");
		{

			// 將此Message執行延遲的時間儲存至L5S[x][0]
			ftowL5S[xback][0] = stod(v[0]);


			// 將此Message的payload size(浮點數型態)儲存至L5[x][1]中
			ftowL5S[xback][1] = stod(v[1]);

			// 將5G對應的第幾個封包的Sent更改標示為Queueing並儲存於LCID000101[x][0]中
			ftowLCID000101[xback][0] = "Queueing";

			// 其他txt上封包的資訊則依序複製
			for (int i = 1; i<(int)v.size() + 1; i++)
			{
				ftowLCID000101[xback][i] = v[i - 1];
			}
			xback++;
		}

		//s.clear;
		v.clear();
	}

	setcolor(4, 0);
	cout << "Number of Control Comment's packets sent from Factory Management is " << xback << " !!!" << endl;
	setcolor(15, 0);
	cout << "Finish of loading " << FMCCfile << ".txt !!!" << endl;
	cout << "Loading the " << FMAfile << ".txt ..." << endl;
	while (getline(inf5, s))
	{
		SplitString_ini(s, v, " ");
		{

			// 將此Message執行延遲的時間儲存至L5S[x][0]
			ftowL4S[yback][0] = stod(v[0]);


			// 將此Message的payload size(浮點數型態)儲存至L5[x][1]中
			ftowL4S[yback][1] = stod(v[1]);

			// 將5G對應的第幾個封包的Sent更改標示為Queueing並儲存於LCID000101[x][0]中
			ftowLCID000100[yback][0] = "Queueing";

			// 其他txt上封包的資訊則依序複製
			for (int i = 1; i<(int)v.size() + 1; i++)
			{
				ftowLCID000100[yback][i] = v[i - 1];
			}
			yback++;
		}

		//s.clear;
		v.clear();
	}

	setcolor(4, 0);
	cout << "Number of Warning's packets sent from Factory Management is " << yback << " !!!" << endl;
	setcolor(15, 0);
	cout << "Finish of loading " << FMAfile << ".txt !!!" << endl;
	

	
}

void SystemSim::InputRRCMsg(string WCCCe2e, string WCAe2e, string WCMe2e, string FMCCe2e, string FMAe2e)
{
	string s;
	wcccmsg_num = 0, wcamsg_num = 0, wcmmsg_num = 0, fmccmsg_num = 0, fmamsg_num = 0;
	vector<string> v, L1, L2;
	ifstream inf1, inf2, inf3, inf4, inf5;

	while (1)
	{
		inf1.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCCCe2e + ".txt");
		inf2.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCAe2e + ".txt");
		inf3.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCMe2e + ".txt");
		inf4.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + FMCCe2e + ".txt");
		inf5.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + FMAe2e + ".txt");

		if (inf1.is_open() == true && inf2.is_open() == true && inf3.is_open() == true && inf4.is_open() == true && inf5.is_open() == true)
			break;
	}

	while (getline(inf1, s))
	{
		SplitString_ini(s, v, " ");
		{
			wcccpriority[wcccmsg_num] = stoi(v[2]);
			wcccmsg_num++;
		}
		s.clear();
		v.clear();
	}
	//cout << wcccmsg_num << endl;

	while (getline(inf2, s))
	{
		SplitString_ini(s, v, " ");
		{
			wcapriority[wcamsg_num] = stoi(v[2]);
			wcamsg_num++;
		}
		s.clear();
		v.clear();
	}
	//cout << wcamsg_num << endl;

	while (getline(inf3, s))
	{
		SplitString_ini(s, v, " ");
		{
			wcmpriority[wcmmsg_num] = stoi(v[2]);
			wcmmsg_num++;
		}
		s.clear();
		v.clear();
	}
	//cout << wcmmsg_num << endl;

	while (getline(inf4, s))
	{
		SplitString_ini(s, v, " ");
		{
			fmccpriority[fmccmsg_num] = stoi(v[2]);
			fmccmsg_num++;
		}
		s.clear();
		v.clear();
	}
	//cout << fmccmsg_num << endl;

	while (getline(inf5, s))
	{
		SplitString_ini(s, v, " ");
		{
			fmapriority[fmamsg_num] = stoi(v[2]);
			fmamsg_num++;
		}
		s.clear();
		v.clear();
	}
	//cout << fmamsg_num << endl;
}

void SystemSim::InputRRCPBR(string WCCC, string WCA, string WCM, string FMCC, string FMA)
{
	string s;
	wcccmsg_num = 0, wcamsg_num = 0, wcmmsg_num = 0, fmccmsg_num = 0, fmamsg_num = 0;
	vector<string> v, L1, L2;
	ifstream inf1, inf2, inf3, inf4, inf5;

	while (1)
	{
		inf1.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCCC + ".txt");
		inf2.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCA + ".txt");
		inf3.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + WCM + ".txt");
		inf4.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + FMCC + ".txt");
		inf5.open("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/" + FMA + ".txt");

		if (inf1.is_open() == true && inf2.is_open() == true && inf3.is_open() == true && inf4.is_open() == true && inf5.is_open() == true)
			break;
	}

	while (getline(inf1, s))
	{
		SplitString_ini(s, v, "s");
		{
			wcccPBR[wcccmsg_num] = stoi(v[1]);
			wcccmsg_num++;
			
		}
		s.clear();
		v.clear();
	}

	while (getline(inf2, s))
	{
		SplitString_ini(s, v, "s");
		{
			wcaPBR[wcamsg_num] = stoi(v[1]);
			wcamsg_num++;
		}
		s.clear();
		v.clear();
	}
	
	while (getline(inf3, s))
	{
		SplitString_ini(s, v, "s");
		{
			wcmPBR[wcmmsg_num] = stoi(v[1]);
			wcmmsg_num++;
		}
		s.clear();
		v.clear();
	}
	
	while (getline(inf4, s))
	{
		SplitString_ini(s, v, "s");
		{
			fmccPBR[fmccmsg_num] = stoi(v[1]);
			fmccmsg_num++;
		}
		s.clear();
		v.clear();
	}
	
	while (getline(inf5, s))
	{
		SplitString_ini(s, v, "s");
		{
			fmaPBR[fmamsg_num] = stoi(v[1]);
			fmamsg_num++;
		}
		s.clear();
		v.clear();
	}
}

//  RemoveMacHeader此function用在何處?
/*void SystemSim::RemoveMacHeader(string fileName) 
{
	string s;
	vector<string> v;
	double v1_dou, removetime;
	ifstream inf;
	inf.open("../../Simulator/Data/OutputData/" + fileName + ".txt");
	ofstream outf1, outf2;
	outf1.open("../../Simulator/Data/OutputData/" + fileName + "_count.txt");
	outf2.open("../../Simulator/Data/OutputData/" + fileName + "_TSN.txt");
	while (getline(inf, s))
	{
		Sim.START = clock();

		SplitString(s, v, " ");

		outf1 <<"r "<< v[1] << " " << v[2] << " ";
		for (int i = 8; i < (int)v.size(); i++) 
		{
			outf1 << v[i] << " ";
		}
		outf1 <<endl;
		Sim.END = clock();

		stringstream qq(v[1].c_str());
		qq >> setprecision(10) >> v1_dou;
		removetime = v1_dou + (END - START) / 1000000;*/

		/*cout << "start   " << Sim.START << endl;
		cout << "end   " << Sim.END<< endl;
		cout << "remove time   " << (END - START) << endl;
		cout << "v1   " << v[1] << endl;
		cout << "v1 double   " << setprecision(10) << v1_dou << endl;
		cout << "加完後     " << removetime << endl;*/

		/*outf2 << "r " << setprecision(10) << removetime << " " << v[2] << " ";
		for (int i = 8; i < (int)v.size(); i++)
		{
			outf2 << v[i] << " ";
		}
		outf2 << endl;

		s.clear();
		v.clear();
	}
	
}
*/

void SystemSim::Demonstration() {
	
	//ofstream pbs, pms;

	//pbs.open("../../simulator/data/output data/demonstration/pbs.txt");
	//pms.open("../../simulator/data/output data/demonstration/pms.txt");

	//for (int bsid = 0; bsid < Sim.network->numBS; bsid++)
	//{
	//	pbs << BS[bsid]->network->pos3D(0, 0) << "	" << BS[bsid]->network->pos3D(0, 1) << "	" << BS[bsid]->network->pos3D(0, 2) << endl;
	//}

	//for (int msid = 0; msid < Sim.network->numMS; msid++)
	//{
	//	pms << MS[msid]->network->pos3D(0, 0) << "	" << MS[msid]->network->pos3D(0, 1) << "	" << MS[msid]->network->pos3D(0, 2) << endl;
	//}

	//pbs.close();
	//pms.close();
	//	
	//ofstream ms_position, clusterangleandpower, ms_aoa, ms_aod, ms_sinr, buffer, mainchart_rate, mainchart_latency;
	//arma::vec rate;
	//rate.zeros(Sim.network->numMS);
	//
	//ms_position.open("../../simulator/data/output data/demonstration/ms_position.txt");
	//mainchart_rate.open("../../simulator/data/output data/demonstration/mainchart_rate.txt");
	//mainchart_latency.open("../../simulator/data/output data/demonstration/mainchart_latency.txt");
	//
	//clusterangleandpower.open("../../simulator/data/output data/demonstration/ms_clusterinformation.txt");
	//ms_aod.open("../../simulator/data/output data/demonstration/ms_aod.txt");
	//ms_aoa.open("../../simulator/data/output data/demonstration/ms_aoa.txt");
	//buffer.open("../../simulator/data/output data/demonstration/buffer.txt");
	//
	//	//for (int msid = 0; msid < Sim.network->numMS; msid++) {
	//	//	 //ms 滌 唸婁
	//	//	ms_position << MS[msid]->network->pos3D(0, 0) << "	" << MS[msid]->network->pos3D(0, 1) << endl;
	//	//	
	//
	//	//	buffer << MS[msid]->network->MSbuffer << endl;
	//	//	for (int n = 0; n < MAX_CLUSTER; n++) { // max_cluseter = 20
	//	//		// cluster 滌 唸婁
	//	//		int servingcell = MS[msid]->channel->associatedbsindex;
	//	//		clusterangleandpower << MS[msid]->channel->demoaod(servingcell, 0)(n, 0) << "	" << MS[msid]->channel->demoaoa(servingcell, 0)(n, 0) << "	" << MS[msid]->channel->democlusterpower(servingcell, 0)(n, 0) << endl;
	//	//	}
	//	//}
	//
	//	//for (int tti = 0; tti < Sim.numTTI; tti++) {
	//	//	// tti 滌 唸婁
	//	//	mainchart_rate << Sim.rateTTI.submat(0,tti,Sim.network->numms-1,tti).max() / 1000000 << "	" << Sim.rateTTI.submat(0, tti, Sim.network->numMS - 1, tti).min() / 1000000 << "	" << arma::mean(Sim.rateTTI.submat(0, tti, Sim.network->numMS - 1, tti)) / 1000000 << endl;
	//	//	mainchart_latency << MS[0]->network->interarrivaltime(tti) << endl;
	//	//}
	//	//
	//
	//mainchart_rate.close();
	//ms_position.close();
	//clusterangleandpower.close();
	//buffer.close();
	//mainchart_latency.close();
}

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*               SLS Simulator class Conclude Iteration                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SystemSim::ConcludeIteration()
{
	channel->ConcludeIteration();
	performance->ConcludeIteration();
	scheduling->ConcludeIteration();
	network->ConcludeIteration();
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                   SLS Simulator class Conclude                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void SystemSim::Conclude()
{
	Sim.network->Conclude();
	Sim.channel->Conclude();
	Sim.performance->Conclude();
	Sim.scheduling->Conclude();

}


SystemSim Sim;