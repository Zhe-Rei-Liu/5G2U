/****************************************************************************

Scheduling header (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NRuRLLC.h
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
2017.1.20   Minsig Han      Created

===========================================================================*/

#ifndef SCHEDULING_H
#define SCHEDULING_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/


#include "../../Simulation Top/Global/SystemSimConfiguration.h"
using namespace std;

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling traffic model type

namespace RRM {
	enum Scheduling_TrafficModel {
		FullBuffer,
		NonFullBuffer,
		IotTraffic
	};

	// Scheduling algorithm
	enum Scheduling_Algorithm {
		SimpleScheduling,
		RoundRobin,
		BestSINR,
		MaxMin,
		ProportionalFairness
	};

	/*enum Precoding_Matrix{
		Analogbeamforming,
		Digitalbeamforming
	};*/
}

enum Precoding_Matrix {
	Analogbeamforming,
	Digitalbeamforming
};

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling
class Scheduling
{
public:
	int checkNetworkParameter;
	enum RRM::Scheduling_TrafficModel trafficModel; // Traffic model
	enum RRM::Scheduling_Algorithm algorithm; // Scheduling algorithm
	int numMaxLayer;
	int numRB; // # of resource blocks
	int numCB;
	int numCBG;
	int realisticFeedback; // 0: Ideal, 1: Realistic	
	int realisticChannelEstimation; // 0: Ideal, 1: Realistic
	double dataSize;

	void Initialize(string fileName); // Scheduling initialization
	void FrameStructure(SLS::TDDType tddtype); // MS feedback
	void BufferUpdate(); // Buffer update
	void WCBufferUpdate(string wtofLCID000101[350000][11], string wtofLCID000100[80000][11], string wtofLCID000000[560000][9], double wtofL5S[350000][2], double wtofL4S[80000][2], double wtofL0S[560000][2]); // WC Buffer update
	void CCWCBufferUpdate(string wtofLCID000101[350000][11], double wtofL5S[350000][2], int CCtrigger, double CCoverlap_ts); // WC Buffer update
	void AWCBufferUpdate(string wtofLCID000100[80000][11], double wtofL4S[80000][2], int Atriggerdouble, double Aoverlap_ts); // WC Buffer update
	void MWCBufferUpdate(string wtofLCID000000[560000][9], double wtofL0S[560000][2], int Mtrigger); // WC Buffer update
	void CCFMBufferUpdate(string ftowLCID000101[350000][11], double ftowL5S[350000][2],int CCsend_pos, int CClast_pos, double CCrcv_ts); // FM Buffer update
	void AFMBufferUpdate(string ftowLCID000100[50000][11], double ftowL4S[50000][2], int Asend_pos, int Alast_pos, double Arcv_ts); // FM Buffer update
	void Feedback(); // MS feedback
	void Schedule(); // Scheduling
	void ReceivedSINRCalculation();
	void Conclude(); // Simulation conclusion
	void ConcludeIteration(); // Iteration conclusion 	

};


#endif