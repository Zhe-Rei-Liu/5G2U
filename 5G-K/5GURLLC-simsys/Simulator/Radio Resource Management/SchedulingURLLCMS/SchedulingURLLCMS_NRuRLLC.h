/****************************************************************************

Scheduling header (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SchedulingURLLCMS_NRuRLLC.h
DATE         : 2016.10.5
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1    Minsig Han      Created

===========================================================================*/

#ifndef SCHEDULINGURLLCMS_H
#define SCHEDULINGURLLCMS_H

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

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling Mobile Station
class SchedulingURLLCMS
{
public:
	int id; // MS ID
	int interArrivalTime; // inter arrival time for non-full buffer traffic
	double msBuffer; // MS buffer for non-full buffer traffic
	int dataSize; // Data size per traffic
	int MCS;
	double downlinkaveragedThroghput, uplinkaveragedThroghput;
	double downlinkspectralEfficiency, uplinkspectralEfficiency;
	double averageUserPerceviedThroughput;
	double downlinkBuffer;
	double uplinkBuffer;
	string wtofUMS000101[350000][11], wtofUMS000100[80000][11], wtofUMS000000[560000][9], ftowUMS000101[350000][11], ftowUMS000100[50000][11];
	double wtofUMS5TS[350000][3], wtofUMS4TS[80000][3], wtofUMS0TS[560000][3], ftowUMS5TS[350000][3], ftowUMS4TS[50000][3];//時間/封包大小/有沒有傳過(0 or 1)
	
	
	
	arma::cx_mat analogPrecodingMatrix;
	arma::cx_mat digitalPrecodingMatrix;
	double CQI;
	double downlinkESINRdB, uplinkESINRdB;
	double downlinkESINR, uplinkESINR;
	double HARQeSINR;

	void Initialize(int ms);
	void BufferUpdate();
	void scheduler();
	void LCP();
	void RR();
	void WCBufferUpdate(string wtofLCID000101[350000][11], string wtofLCID000100[80000][11], string wtofLCID000000[560000][9], double wtofL5S[350000][2], double wtofL4S[80000][2], double  wtofL0S[560000][2]);//時間/封包大小
	void CCWCBufferUpdate(string wtofLCID000101[350000][11], double wtofL5S[350000][2], int CCpos, double CCoverlap_ts);
	void AWCBufferUpdate(string wtofLCID000100[80000][11], double wtofL4S[80000][2], int Atrigger, double Aoverlap_ts);
	void MWCBufferUpdate(string wtofLCID000000[560000][9], double wtofL0S[560000][2], int Mtrigger);
	void CCFMBufferUpdate(string ftowLCID000101[350000][11], double ftowL5S[350000][2], int CCsend_pos, int CClast_pos, double CCrcv_ts);
	void AFMBufferUpdate(string ftowLCID000100[50000][11], double ftowL4S[50000][2], int Asend_pos, int Alast_pos, double Arcv_ts);
	void Feedback();
	void ReceivedSINR();
	arma::cx_mat* PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type);
	double GetSpectralEfficiency(double SINR, int &MCS);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif