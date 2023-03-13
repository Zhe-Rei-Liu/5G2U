/****************************************************************************

Simulation header (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSim_NRuRLLC.h
DATE         : 2017.09.12
VERSION      : 0.2
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.05.20  Jaewon Lee      Created
2017.09.12  Minsig Han      Add variables for non-full buffer scenario
===========================================================================*/

#ifndef SYSTEMSIM_H
#define SYSTEMSIM_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>
/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Simulation
class SystemSim
{
public:
	int numerologyParameter; // 伊 in TS 38.211
	int numTTI; // # of TTIs for simulation
	double TTI;
	double c_wt5_wc = 0, c_wt4_wc = 0, c_wt0_wc = 0, c_wt5_fm = 0, c_wt4_fm = 0;
	double c_nwt5_wc = 0, c_nwt4_wc = 0, c_nwt0_wc = 0, c_nwt5_fm = 0, c_nwt4_fm = 0;
	double c_net5_wc = 0, c_net4_wc = 0, c_net0_wc = 0, c_net5_fm = 0, c_net4_fm = 0;
	//double c_et5_wc = 0, c_et2_wc = 0, c_et1_wc = 0, c_et5_fm = 0, c_et2_fm = 0;
	int wccc_prindex = 0, wca_prindex = 0, wcm_prindex = 0, fmcc_prindex = 0, fma_prindex = 0;
	double transmissionTimetoFM;
	int numSymbolperTTI;
	int numTTIperFrame;
	int feedbackPeriod;
	int numIteration; // # of iterations for different mobile station configurations
	int subcarrierSpacing;
	int CCtrigger, Atrigger, Mtrigger;
	int CCfix, Afix;
	enum SLS::Scenario scenario; // Simulation scenario
	enum SLS::LinkDirection linkDirection; // Link direction
	class Network *network; // Parameters related to network configuration
	class Scheduling *scheduling; // Parameters related to radio resource management
	class Performance *performance; // Parameters related to link performance
	class Channel *channel; // Parameters related to channel
	
	ofstream outfRR, outfWGCL_WCCC_1, outfWGCL_WCCC_2, outfWGCL_WCA_1, outfWGCL_WCA_2, outfWGCL_WCM_1, outfWGCL_WCM_2, outfWGCL_FMCC_1, outfWGCL_FMCC_2, outfWGCL_FMA_1, outfWGCL_FMA_2, outfWGCL_CCoverlap, outfWGCL_Aoverlap;
	ofstream outfLCP, outfFM, outWTrecord;
	int xback, yback, x, y, z, WTcycle=0;
	int wcccmsg_num, wcamsg_num, wcmmsg_num, fmccmsg_num, fmamsg_num;
	int quantum;
	string algorithm, scenarioNum;
	int wcccpriority[4560], wcapriority[2110], wcmpriority[10000], fmccpriority[4560], fmapriority[2110];
	int wcccPBR[4560], wcaPBR[2110], wcmPBR[10000], fmccPBR[4560], fmaPBR[2110];
	string wtofLCID000101[350000][11], wtofLCID000100[80000][11], wtofLCID000000[560000][9], ftowLCID000101[350000][11], ftowLCID000100[50000][11];  //input文字檔有10個字串 + 1個發送狀態字串
	double wtofL5S[350000][2], wtofL4S[80000][2], wtofL0S[560000][2], ftowL5S[350000][2], ftowL4S[50000][2]; //[傳到時間][封包大小]
	double WCwt5, WCwt4, WCwt0;
	double WCwt5_1, WCwt4_1, WCwt0_1;
	double WCwt5_2, WCwt4_2, WCwt0_2;
	double FMwt5, FMwt4;
	double FMwt5_1, FMwt4_1;
	double FMwt5_2, FMwt4_2;
	double START, END;
	vector <double> receiveTime;
	vector <string> LCID;
	vector <int> Length;

	
	//int main(); // Main flow
	void Initialize(string fileName); // Initialization
	//void RemoveMacHeader(string fileName);
	void Demonstration(); // Demo
	void ConcludeIteration();  // Conclude Iteration the simulation
	void Conclude(); // Concluding the simulation
	void Input5GPacket(string WCCCfile, string WCAfile, string WCMfile, string FMCCfile, string FMAfile);
	void InputRRCMsg(string WCCCe2e, string WCAe2e, string WCMe2e, string FMCCe2e, string FMAe2e);
	void InputRRCPBR(string WCCC, string WCA, string WCM, string FMCC, string FMA);
	// Demo variables
	arma::mat RateTTI;
	arma::mat LatencyTTI;
	arma::mat BufferTTI;

};



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL VARIABLES                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

extern SystemSim Sim;


#endif