/****************************************************************************

Scheduling (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NRuRLLC.cpp
DATE         : 2017.1.31
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.31	WISELAB      	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "Scheduling_NRuRLLC.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::Initialize(string fileName)
{
	// Read radio resource management parameters from the file
	ifstream inFile("../../Simulator/Data/InputData/SimulationParameter/SystemSimParameter/SimParamScheduling_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "algorithm") algorithm = RRM::Scheduling_Algorithm(stoi(result[1]));
			else if (result[0] == "dataSize") dataSize = stoi(result[1]);
			else if (result[0] == "numRB") numRB = stoi(result[1]);//resource block
			else if (result[0] == "numCB") numCB = stoi(result[1]);//code block
			else if (result[0] == "numCBG") numCBG = stoi(result[1]);//code block group
			else if (result[0] == "realisticFeedback") realisticFeedback = stoi(result[1]);
			else if (result[0] == "realisticChannelEstimation") realisticChannelEstimation = stoi(result[1]);
		}
	}
	numMaxLayer = 1;
}

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::FrameStructure(SLS::TDDType tddtype)
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->FrameStructure(bsID, tddtype);
	}
	cout << "[Scheduling]: Frame Sturcture for next frame" << endl;
}

void Scheduling::BufferUpdate()
{
	for (int i = 0; i < Sim.network->numUMS; i++)
	{
		UMS[i]->scheduling->BufferUpdate();
	}
}

//=== Point!!! ===//

void Scheduling::WCBufferUpdate(string wtofLCID000101[350000][11], string wtofLCID000010[80000][11], string wtofLCID000001[560000][9], double wtofL5S[350000][2], double wtofL2S[80000][2], double  wtofL1S[560000][2])
{
	/*for (int i = 0; i < Sim.network->numUMS; i++)
	{
		UMS[i]->scheduling->myBufferUpdate(LCID00101, LCID00010, LCID00001, L5S, L2S, L1S);
	}*/
	UMS[0]->scheduling->WCBufferUpdate(wtofLCID000101, wtofLCID000010, wtofLCID000001, wtofL5S, wtofL2S, wtofL1S);
}
void Scheduling::CCWCBufferUpdate(string wtofLCID000101[350000][11], double wtofL5S[350000][2], int CCtrigger, double CCoverlap_ts)
{
	/*for (int i = 0; i < Sim.network->numUMS; i++)
	{
	UMS[i]->scheduling->myBufferUpdate(LCID00101, LCID00010, LCID00001, L5S, L2S, L1S);
	}*/
	UMS[0]->scheduling->CCWCBufferUpdate(wtofLCID000101, wtofL5S, CCtrigger, CCoverlap_ts);
}
void Scheduling::AWCBufferUpdate(string wtofLCID000010[80000][11], double wtofL2S[80000][2], int Atrigger, double Aoverlap_ts)
{
	/*for (int i = 0; i < Sim.network->numUMS; i++)
	{
	UMS[i]->scheduling->myBufferUpdate(LCID00101, LCID00010, LCID00001, L5S, L2S, L1S);
	}*/
	UMS[0]->scheduling->AWCBufferUpdate(wtofLCID000010, wtofL2S, Atrigger, Aoverlap_ts);
}
void Scheduling::MWCBufferUpdate(string wtofLCID000001[560000][9], double wtofL1S[560000][2], int Mtrigger)
{
	/*for (int i = 0; i < Sim.network->numUMS; i++)
	{
	UMS[i]->scheduling->myBufferUpdate(LCID00101, LCID00010, LCID00001, L5S, L2S, L1S);
	}*/
	UMS[0]->scheduling->MWCBufferUpdate(wtofLCID000001, wtofL1S, Mtrigger);
}
void Scheduling::CCFMBufferUpdate(string ftowLCID000101[350000][11], double ftowL5S[350000][2], int CCsend_pos, int CClast_pos, double CCrcv_ts)
{
	/*for (int i = 0; i < Sim.network->numUMS; i++)
	{
	UMS[i]->scheduling->myBufferUpdate(LCID00101, LCID00010, LCID00001, L5S, L2S, L1S);
	}*/
	UMS[0]->scheduling->CCFMBufferUpdate(ftowLCID000101, ftowL5S, CCsend_pos, CClast_pos, CCrcv_ts);
}
void Scheduling::AFMBufferUpdate(string ftowLCID000010[50000][11], double ftowL2S[50000][2], int Asend_pos, int Alast_pos, double Arcv_ts)
{
	/*for (int i = 0; i < Sim.network->numUMS; i++)
	{
	UMS[i]->scheduling->myBufferUpdate(LCID00101, LCID00010, LCID00001, L5S, L2S, L1S);
	}*/
	UMS[0]->scheduling->AFMBufferUpdate(ftowLCID000010, ftowL2S, Asend_pos, Alast_pos, Arcv_ts);
}
void Scheduling::Feedback()   // channel status info
{
	//for (int msID = 0; msID < Sim.network->numMS; msID++)
	//{
	//	MS[msID]->scheduling->Feedback(); // Feedback(msID)
	//}
	 // Feedback(umsID)
	//for (int umsID = 0; umsID < Sim.network->numUMS; umsID++)
	//{
	//	UMS[umsID]->scheduling->Feedback(); // Feedback(umsID)
	//}

	setcolor(7, 0);
	cout << "[Scheduling]: Mobile Station Buffer state report" << endl;
	UMS[0]->scheduling->Feedback();
	/*setcolor(11, 0);
	cout << "[Scheduling]: Mobile Station CSI feedback" << endl;*/
	
}

void Scheduling::Schedule()
{
	/*for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->mySchedule();
		
	}*/
	
	BS[0]->scheduling->mySchedule();
	//BS[0]->scheduling->toFM();
	
}

void Scheduling::ReceivedSINRCalculation()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		for (int numrb = 0; numrb < Sim.scheduling->numRB; numrb++)
		{
			for (int i = 0; i < BS[bsID]->scheduling->numScheduledUMS; i++)
			{
				if (BS[bsID]->scheduling->scheduledUMS(numrb, i) != -1)
				{
					int temp = BS[bsID]->scheduling->scheduledUMS(numrb, i);
					UMS[temp]->scheduling->ReceivedSINR();
				}				
			}
		}
		if (BS[bsID]->scheduling->numScheduledUMS != Sim.scheduling->numCB)
		{
			MS[BS[bsID]->scheduling->scheduledMS]->scheduling->ReceivedSINR();
		}
			
	}
	
	cout << "[Scheduling]: Received SINR calculation " << endl;
}

void Scheduling::Conclude()
{

}



void Scheduling::ConcludeIteration()
{

}
