/****************************************************************************

Scheduling (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SchedulingBS_NRuRLLC.cpp
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

#include "SchedulingBS_NRuRLLC.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SchedulingBS::Initialize(int bs)
{
	id = bs; // BS ID
	scheduledUMS.zeros(Sim.scheduling->numRB, Sim.scheduling->numCB);
	for (int numrb = 0; numrb < Sim.scheduling->numRB; numrb++)
	{
		for (int umsID = 0; umsID < Sim.scheduling->numCB; umsID++)
		{
			scheduledUMS(numrb, umsID) = -1;//����t��UMS ID��RB�M��
		}
	}
	
}

void SchedulingBS::FrameStructure(int bsID, SLS::TDDType tddtype)
{
	
	BS[bsID]->scheduling->downlinkBuffer = 0;
	BS[bsID]->scheduling->uplinkBuffer = 0;

	for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
	{
		int msID = BS[bsID]->network->attachedMS[attachedMsID];
		BS[bsID]->scheduling->downlinkBuffer = BS[bsID]->scheduling->downlinkBuffer + MS[msID]->scheduling->downlinkBuffer;
		BS[bsID]->scheduling->uplinkBuffer = BS[bsID]->scheduling->uplinkBuffer + MS[msID]->scheduling->uplinkBuffer;
	}
	double trafficRatio = BS[bsID]->scheduling->downlinkBuffer / (BS[bsID]->scheduling->downlinkBuffer + BS[bsID]->scheduling->uplinkBuffer);
	trafficRatio = 0.5;
	arma::mat lteTDDframestructure;

	switch (tddtype)
	{
	case SLS::StaticTDD: // Sim.numTTIperFrame==10�� ��쿡�� ���� ����
		lteTDDframestructure.zeros(7, 10);
		lteTDDframestructure << 0 << 0 << 1 << 1 << 1 << 0 << 0 << 1 << 1 << 1 << 1 << arma::endr
			<< 0 << 0 << 1 << 1 << 0 << 0 << 1 << 1 << 1 << 0 << arma::endr
			<< 0 << 0 << 1 << 0 << 0 << 0 << 1 << 1 << 0 << 0 << arma::endr
			<< 0 << 0 << 1 << 1 << 1 << 0 << 0 << 0 << 0 << 0 << arma::endr
			<< 0 << 0 << 1 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr
			<< 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr
			<< 0 << 0 << 1 << 1 << 1 << 0 << 1 << 1 << 1 << 0 << arma::endr;

//		BS[bsID]->scheduling->framestructure = abs(1.0 - (find(lteTDDframestructure == 1) / Sim.numTTIperFrame) - trafficRatio).index_min;
		break;
	case SLS::DynamicTDD:
		BS[bsID]->scheduling->framestructure.zeros(Sim.numTTIperFrame);
		for (int link = 0; link < Sim.numTTIperFrame; link++)
		{
			if (arma::randu() > trafficRatio)
				BS[bsID]->scheduling->framestructure(link) = 0;
			else
				BS[bsID]->scheduling->framestructure(link) = 1;
		}
		break;
	case SLS::HybridTDD:
		BS[bsID]->scheduling->framestructure = sort(arma::randu(Sim.numTTIperFrame > trafficRatio));
		break;
	}
	
}

void SchedulingBS::BSR(double WCbuffer5, double WCbuffer4, double WCbuffer0, double FMbuffer5, double FMbuffer4)
{
	setcolor(7, 0);
	cout << "BSR------Buffer5 in WC = " << WCbuffer5 << "   Buffer4 in WC = " << WCbuffer4 << "   Buffer0 in WC = " << WCbuffer0 << endl;
	cout << "BSR------Buffer5 in FM = " << FMbuffer5 << "   Buffer4 in FM = " << FMbuffer4 <<endl;
	
	if (Sim.algorithm == "RR")
	{
		Sim.WCwt5 = (double)1 / Sim.quantum * 46 / 100;
		Sim.WCwt4 = (double)1 / Sim.quantum * 14 / 100;
		Sim.WCwt0 = (double)1 / Sim.quantum * 40 / 100;
		Sim.FMwt5 = (double)1 / Sim.quantum * 15 / 16;
		Sim.FMwt4 = (double)1 / Sim.quantum * 1 / 16;

		setcolor(14, 0);
		cout << "==================================================== In Work Cell ======================================================" << endl;
		cout << "RR------window5 = " << setprecision(3) << Sim.WCwt5 << "   window4 = " << setprecision(3) << Sim.WCwt4 << "   window0 = " << setprecision(3) << Sim.WCwt0 << endl;

		cout << "=============================================== In Factory Management ==================================================" << endl;
		cout << "RR------window5 = " << setprecision(3) << Sim.FMwt5 << "   window4 = " << setprecision(3) << Sim.FMwt4 << endl;
		Sim.WTcycle++;
		Sim.outWTrecord << "[" << Sim.WTcycle << "] " << "WC==>" << " " << setprecision(9) << Sim.WCwt5 * 1000 << " ms " << setprecision(9) << Sim.WCwt4 * 1000 << " ms " << setprecision(9) << Sim.WCwt0 * 1000 << " ms FM==>" << " " << setprecision(9) << Sim.FMwt5 * 1000 << " ms " << setprecision(9) << Sim.FMwt4 * 1000 << " ms" << endl;
		Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5;
		Sim.c_wt4_wc = Sim.c_wt4_wc + Sim.WCwt4;
		Sim.c_wt0_wc = Sim.c_wt0_wc + Sim.WCwt0;
		Sim.c_nwt5_wc++;
		Sim.c_nwt4_wc++;
		Sim.c_nwt0_wc++;
		Sim.c_wt5_fm = Sim.c_wt5_fm + Sim.FMwt5;
		Sim.c_wt4_fm = Sim.c_wt4_fm + Sim.FMwt4;
		Sim.c_nwt5_fm++;
		Sim.c_nwt4_fm++;
	}
	else if (Sim.algorithm=="WGCL")
	{
		float wtofweight5, wtofweight4, wtofweight0, ftowweight5, ftowweight4;
		wtofweight5 = 1000.0 / (double)(15 * 3 / 13);
		wtofweight4 = 1000.0 / (double)(22.5 * 3 / 5);
		wtofweight0 = 1000.0 / (double)225;
		ftowweight5 = 1000.0 / (double)(15 * 10 / 13);
		ftowweight4 = 1000.0 / (double)(22.5 * 2 / 5);

		Sim.WCwt5 = ((double)1 / Sim.quantum)*((WCbuffer5 +1) * wtofweight5) / (((WCbuffer5 + 1) * wtofweight5) + ((WCbuffer4 + 1) * wtofweight4) + ((WCbuffer0 * + 1) * wtofweight0));
		Sim.WCwt4 = ((double)1 / Sim.quantum)*((WCbuffer4 +1) * wtofweight4) / (((WCbuffer5 + 1) * wtofweight5) + ((WCbuffer4 + 1) * wtofweight4) + ((WCbuffer0 * + 1) * wtofweight0));
		Sim.WCwt0 = ((double)1 / Sim.quantum)*((WCbuffer0 +1) * wtofweight0) / (((WCbuffer5 + 1) * wtofweight5) + ((WCbuffer4 + 1) * wtofweight4) + ((WCbuffer0 * + 1) * wtofweight0));
		Sim.FMwt5 = ((double)1 / Sim.quantum)*((FMbuffer5 + 1) * ftowweight5) / (((FMbuffer5 + 1) * ftowweight5) + ((FMbuffer4 + 1) * ftowweight4));
		Sim.FMwt4 = ((double)1 / Sim.quantum)*((FMbuffer4 + 1) * ftowweight4) / (((FMbuffer5 + 1) * ftowweight5) + ((FMbuffer4 + 1) * ftowweight4));
		
		setcolor(14, 0);
		cout << "==================================================== In Work Cell ======================================================" << endl;
		cout << "WGCL------window5 = " << setprecision(3) << Sim.WCwt5 << "   window4 = " << setprecision(3) << Sim.WCwt4 << "   window0 = " << setprecision(3) << Sim.WCwt0 << endl;
		
		cout << "=============================================== In Factory Management ==================================================" << endl;
		cout << "WGCL------window5 = " << setprecision(3) << Sim.FMwt5 << "   window4 = " << setprecision(3) << Sim.FMwt4 << endl;
		Sim.WTcycle++;
		Sim.outWTrecord << "[" << Sim.WTcycle << "] " << "WC==>"<< " " << setprecision(9) << Sim.WCwt5*1000 << " ms " << setprecision(9) << Sim.WCwt4*1000 << " ms " << setprecision(9) << Sim.WCwt0*1000 << " ms FM==>" << " " << setprecision(9) << Sim.FMwt5 * 1000 << " ms " << setprecision(9) << Sim.FMwt4 * 1000 <<" ms" << endl;
		Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5;
		Sim.c_wt4_wc = Sim.c_wt4_wc + Sim.WCwt4;
		Sim.c_wt0_wc = Sim.c_wt0_wc + Sim.WCwt0;
		Sim.c_nwt5_wc++;
		Sim.c_nwt4_wc++;
		Sim.c_nwt0_wc++;
		Sim.c_wt5_fm = Sim.c_wt5_fm + Sim.FMwt5;
		Sim.c_wt4_fm = Sim.c_wt4_fm + Sim.FMwt4;
		Sim.c_nwt5_fm++;
		Sim.c_nwt4_fm++;
	}
	else if (Sim.algorithm == "AW-WGCL")
	{
		float wtofe2e_5, wtofe2e_4, wtofe2e_0, ftowe2e_5, ftowe2e_4;
		wtofe2e_5 = (pow(2, (((double)Sim.wcccpriority[Sim.wccc_prindex] - 1.0))));
		wtofe2e_4 = (pow(2, (((double)Sim.wcapriority[Sim.wca_prindex] - 1.0))));
		wtofe2e_0 = (pow(2, (((double)Sim.wcmpriority[Sim.wcm_prindex] - 1.0))));
		ftowe2e_5 = (pow(2, (((double)Sim.fmccpriority[Sim.fmcc_prindex] - 1.0))));
		ftowe2e_4 = (pow(2, (((double)Sim.fmapriority[Sim.fma_prindex] - 1.0))));

		float wtofBW5, wtofBW4, wtofBW0, ftowBW5, ftowBW4;
		wtofBW5 = (WCbuffer5 + 1) / wtofe2e_5;
		wtofBW4 = (WCbuffer4 + 1) / wtofe2e_4;
		wtofBW0 = (WCbuffer0 + 1) / wtofe2e_0;
		ftowBW5 = (FMbuffer5 + 1) / ftowe2e_5;
		ftowBW4 = (FMbuffer4 + 1) / ftowe2e_4;

		float wtofbeta, ftowgamma, wtofgamma;

		if ((wtofBW5 + wtofBW4 + wtofBW0) < ((double)500000 / 8.0))
		{
			wtofbeta = (wtofBW5 + wtofBW4) / (((double)500000 / 8.0) - wtofBW0);
			wtofgamma = 1;
			//cout << "^^^^^^^^^^^^^^^^scenaio 1^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		}
		else if ((wtofBW5 + wtofBW4 + wtofBW0) > ((double)500000 / 8.0) && (wtofBW5 + wtofBW4) < ((double)500000 / 8.0))
		{
			wtofbeta = ((double)(500000 / 8.0) - wtofBW5 - wtofBW4) / wtofBW0;
			wtofgamma = 1;
			//cout << "^^^^^^^^^^^^^^^^scenaio 2^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		}
		else if ((wtofBW5 + wtofBW4 + wtofBW0) > ((double)500000 / 8.0) && (wtofBW5 + wtofBW4) > ((double)500000 / 8.0) && wtofBW5 < ((double)500000 / 8.0))
		{
			//cout << "^^^^^^^^^^^^^^^^scenaio 3^^^^^^^^^^^^^^^^^^^^^^^" << endl;
			wtofbeta = 0.0;
			wtofgamma = ((double)(500000 / 8.0) - wtofBW5) / wtofBW4;
		}
		else if ((wtofBW5 + wtofBW4 + wtofBW0) >((double)500000 / 8.0) && (wtofBW5 + wtofBW4) > ((double)500000 / 8.0) && wtofBW5 > ((double)500000 / 8.0))
		{
			//cout << "^^^^^^^^^^^^^^^^scenaio 4^^^^^^^^^^^^^^^^^^^^^^^" << endl;
			wtofbeta = 0.0;
			wtofgamma = 0.0;
		}
		
		if ((ftowBW5 + ftowBW4) > ((double)150000 / 8.0) && ftowBW5 < ((double)150000 / 8.0))
		{
			ftowgamma = ((double)(150000 / 8.0) - ftowBW5) / ftowBW4;
		}
		else if ((ftowBW5 + ftowBW4) >((double)150000 / 8.0) && ftowBW5 > ((double)150000 / 8.0))
		{
			ftowgamma = 0;
		}
		else
		{
			ftowgamma = 1;
		}

		//cout << " wtofgamma = " << wtofgamma << endl;
		//cout << " wtofbeta = " << wtofbeta << endl;
		//cout << " ftowgamma = " << ftowgamma << endl;

		Sim.WCwt5 = ((double)1 / Sim.quantum) * wtofBW5 / (wtofBW5 + wtofBW4 *wtofgamma + wtofBW0 * wtofbeta);
		Sim.WCwt4 = ((double)1 / Sim.quantum) * wtofBW4 *wtofgamma / (wtofBW5 + wtofBW4 *wtofgamma + wtofBW0 * wtofbeta);
		Sim.WCwt0 = ((double)1 / Sim.quantum) * wtofBW0 * wtofbeta / (wtofBW5 + wtofBW4 *wtofgamma + wtofBW0 * wtofbeta);
		Sim.FMwt5 = ((double)1 / Sim.quantum) * ftowBW5 / (ftowBW5 + ftowBW4 *ftowgamma);
		Sim.FMwt4 = ((double)1 / Sim.quantum) * ftowBW4 *ftowgamma / (ftowBW5 + ftowBW4 *ftowgamma);

		setcolor(14, 0);
		cout << "=========================================== In Work Cell ==========================================" << endl;
		cout << "AW-WGCL------window5 = " << setprecision(3) << Sim.WCwt5 << "   window4 = " << setprecision(3) << Sim.WCwt4 << "   window0 = " << setprecision(3) << Sim.WCwt0 << endl;

		cout << "====================================== In Factory Management ======================================" << endl;
		cout << "AW-WGCL------window5 = " << setprecision(3) << Sim.FMwt5 << "   window4 = " << setprecision(3) << Sim.FMwt4 << endl;
		Sim.WTcycle++;
		Sim.outWTrecord << "[" << Sim.WTcycle << "] " << "WC==>" << " " << setprecision(9) << Sim.WCwt5 * 1000 << " ms " << setprecision(9) << Sim.WCwt4 * 1000 << " ms " << setprecision(9) << Sim.WCwt0 * 1000 << " ms FM==>" << " " << setprecision(9) << Sim.FMwt5 * 1000 << " ms " << setprecision(9) << Sim.FMwt4 * 1000 << " ms" << endl;
		Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5;
		Sim.c_wt4_wc = Sim.c_wt4_wc + Sim.WCwt4;
		Sim.c_wt0_wc = Sim.c_wt0_wc + Sim.WCwt0;
		Sim.c_nwt5_wc++;
		Sim.c_nwt4_wc++;
		Sim.c_nwt0_wc++;
		Sim.c_wt5_fm = Sim.c_wt5_fm + Sim.FMwt5;
		Sim.c_wt4_fm = Sim.c_wt4_fm + Sim.FMwt4;
		Sim.c_nwt5_fm++;
		Sim.c_nwt4_fm++;
	}
	else if (Sim.algorithm == "LCP")
	{
		float wtofPBR_5, wtofPBR_2, wtofPBR_1, ftowPBR_5, ftowPBR_2;
		wtofPBR_5 = Sim.wcccPBR[Sim.wccc_prindex];
		wtofPBR_2 = Sim.wcaPBR[Sim.wca_prindex];
		wtofPBR_1 = Sim.wcmPBR[Sim.wcm_prindex];
		ftowPBR_5 = Sim.fmccPBR[Sim.fmcc_prindex];
		ftowPBR_2 = Sim.fmaPBR[Sim.fma_prindex];

		Sim.WCwt5_1 = ((double)1 / Sim.quantum) *wtofPBR_5/62500.0;
		Sim.WCwt4_1 = ((double)1 / Sim.quantum) *wtofPBR_2/62500.0;
		Sim.WCwt0_1 = ((double)1 / Sim.quantum) *wtofPBR_1/62500.0;

		Sim.WCwt5_2 = ((double)1 / Sim.quantum) *wtofPBR_5 * 4/ 62500.0;
		Sim.WCwt4_2 = ((double)1 / Sim.quantum) *wtofPBR_2 * 4/ 62500.0;
		Sim.WCwt0_2 = ((double)1 / Sim.quantum) *wtofPBR_1 * 4/ 62500.0;

		if (Sim.WCwt5_1 > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_wc = Sim.c_wt5_wc + ((double)1 / Sim.quantum);
			Sim.WCwt5 = ((double)1 / Sim.quantum);
			Sim.WCwt4 = 0;
			Sim.WCwt0 = 0;

			Sim.WCwt5_1 = ((double)1 / Sim.quantum);
			Sim.WCwt4_1 = 0;
			Sim.WCwt0_1 = 0;

			Sim.WCwt5_2 = 0;
			Sim.WCwt4_2 = 0;
			Sim.WCwt0_2 = 0;
		}
		else if ((Sim.WCwt5_1 + Sim.WCwt4_1) > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5_1;
			Sim.WCwt5 = Sim.WCwt5_1;
			Sim.c_wt4_wc = Sim.c_wt4_wc + ((double)1 / Sim.quantum) - Sim.WCwt5_1;
			Sim.WCwt4 = ((double)1 / Sim.quantum) - Sim.WCwt5_1;
			Sim.WCwt0 = 0;

			Sim.WCwt4_1 = ((double)1 / Sim.quantum) - Sim.WCwt5_1;
			Sim.WCwt0_1 = 0;

			Sim.WCwt5_2 = 0;
			Sim.WCwt4_2 = 0;
			Sim.WCwt0_2 = 0;
		}
		else if ((Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1) > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5_1;
			Sim.WCwt5 = Sim.WCwt5_1;
			Sim.c_wt4_wc = Sim.c_wt4_wc + Sim.WCwt4_1;
			Sim.WCwt4 = Sim.WCwt4_1;
			Sim.c_wt0_wc = Sim.c_wt0_wc + ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1;
			Sim.WCwt0 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1;

			Sim.WCwt0_1 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1;

			Sim.WCwt5_2 = 0;
			Sim.WCwt4_2 = 0;
			Sim.WCwt0_2 = 0;
		}
		else if ((Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2) > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_wc = Sim.c_wt5_wc + ((double)1 / Sim.quantum) - Sim.WCwt4_1 - Sim.WCwt0_1;
			Sim.WCwt5 = ((double)1 / Sim.quantum) - Sim.WCwt4_1 - Sim.WCwt0_1;
			Sim.c_wt4_wc = Sim.c_wt4_wc + Sim.WCwt4_1;
			Sim.WCwt4 = Sim.WCwt4_1;
			Sim.c_wt0_wc = Sim.c_wt0_wc + Sim.WCwt0_1;
			Sim.WCwt0 = Sim.WCwt0_1;

			Sim.WCwt5_2 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1 - Sim.WCwt0_1;
			Sim.WCwt4_2 = 0;
			Sim.WCwt0_2 = 0;
			
		}
		else if ((Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2 + Sim.WCwt4_2) > ((double)1 / Sim.quantum))
		{	
			Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5_1 + Sim.WCwt5_2;
			Sim.WCwt5 = Sim.WCwt5_1 + Sim.WCwt5_2;
			Sim.c_wt4_wc = Sim.c_wt4_wc + ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt0_1 - Sim.WCwt5_2;
			Sim.WCwt4 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt0_1 - Sim.WCwt5_2;
			Sim.c_wt0_wc = Sim.c_wt0_wc + Sim.WCwt0_1;
			Sim.WCwt0 = +Sim.WCwt0_1;

			Sim.WCwt4_2 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1 - Sim.WCwt0_1 - Sim.WCwt5_2;
			Sim.WCwt0_2 = 0;
		}
		else if ((Sim.WCwt5_1 + Sim.WCwt4_1 + Sim.WCwt0_1 + Sim.WCwt5_2 + Sim.WCwt4_2 + Sim.WCwt0_2) > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_wc = Sim.c_wt5_wc + Sim.WCwt5_1 + Sim.WCwt5_2;
			Sim.WCwt5 = Sim.WCwt5_1 + Sim.WCwt5_2;
			Sim.c_wt4_wc = Sim.c_wt4_wc + Sim.WCwt4_1 + Sim.WCwt4_2;
			Sim.WCwt4 = Sim.WCwt4_1 + Sim.WCwt4_2;
			Sim.c_wt0_wc = Sim.c_wt0_wc + ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1 - Sim.WCwt5_2 - Sim.WCwt4_2;
			Sim.WCwt0 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1 - Sim.WCwt5_2 - Sim.WCwt4_2;

			Sim.WCwt0_2 = ((double)1 / Sim.quantum) - Sim.WCwt5_1 - Sim.WCwt4_1 - Sim.WCwt0_1 - Sim.WCwt5_2 - Sim.WCwt4_2;
		}
		/*else
		{
			cout << "shit" << endl;
			cout << Sim.WCwt5_1 << endl;
			cout << Sim.WCwt4_1 << endl;
			cout << Sim.WCwt0_1 << endl;
			cout << Sim.WCwt5_2 << endl;
			cout << Sim.WCwt4_2 << endl;
			cout << Sim.WCwt0_2 << endl;
		}*/
		Sim.c_nwt5_wc++;
		Sim.c_nwt4_wc++;
		Sim.c_nwt0_wc++;

		Sim.FMwt5_1 = ((double)1 / Sim.quantum) *ftowPBR_5 / 18750.0;
		Sim.FMwt4_1 = ((double)1 / Sim.quantum) *ftowPBR_2 / 18750.0;
		Sim.FMwt5_2 = ((double)1 / Sim.quantum) *ftowPBR_5 * 4/ 18750.0;
		Sim.FMwt4_2 = ((double)1 / Sim.quantum) *ftowPBR_2 * 4/ 18750.0;


		if (Sim.FMwt5_1 > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_fm = Sim.c_wt5_fm + ((double)1 / Sim.quantum);
			Sim.FMwt5 = ((double)1 / Sim.quantum);

			Sim.FMwt5_1 = ((double)1 / Sim.quantum);
			Sim.FMwt4_1 = 0;
			Sim.FMwt5_2 = 0;
			Sim.FMwt4_2 = 0;
		}
		else if ((Sim.FMwt5_1 + Sim.FMwt4_1) > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_fm = Sim.c_wt5_fm + Sim.FMwt5_1;
			Sim.FMwt5 = Sim.FMwt5_1;
			Sim.c_wt4_fm = Sim.c_wt4_fm + ((double)1 / Sim.quantum) - Sim.FMwt5_1;
			Sim.FMwt4 = ((double)1 / Sim.quantum) - Sim.FMwt5_1;

			Sim.FMwt4_1 =((double)1 / Sim.quantum) - Sim.FMwt5_1;
			Sim.FMwt5_2 = 0;
			Sim.FMwt4_2 = 0;
		}
		else if ((Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2) > ((double)1 / Sim.quantum))
		{	
			Sim.c_wt5_fm = Sim.c_wt5_fm + ((double)1 / Sim.quantum) - Sim.FMwt4_1;
			Sim.FMwt5 = ((double)1 / Sim.quantum) - Sim.FMwt4_1;
			Sim.c_wt4_fm = Sim.c_wt4_fm + Sim.FMwt4_1;
			Sim.FMwt4 = Sim.FMwt4_1;

			Sim.FMwt5_2 = ((double)1 / Sim.quantum) - Sim.FMwt5_1 - Sim.FMwt4_1;
			Sim.FMwt4_2 = 0;
		}
		else if ((Sim.FMwt5_1 + Sim.FMwt4_1 + Sim.FMwt5_2 + Sim.FMwt4_2) > ((double)1 / Sim.quantum))
		{
			Sim.c_wt5_fm = Sim.c_wt5_fm + Sim.FMwt5_1 + Sim.FMwt5_2;
			Sim.FMwt5 = Sim.FMwt5_1 + Sim.FMwt5_2;
			Sim.c_wt4_fm = Sim.c_wt4_fm +((double)1 / Sim.quantum) - Sim.FMwt5_1 - Sim.FMwt5_2;
			Sim.FMwt4 = ((double)1 / Sim.quantum) - Sim.FMwt5_1 - Sim.FMwt5_2;

			Sim.FMwt4_2 = ((double)1 / Sim.quantum) - Sim.FMwt5_1 - Sim.FMwt4_1 - Sim.FMwt5_2;
		}
		Sim.c_nwt5_fm++;
		Sim.c_nwt4_fm++;
		setcolor(14, 0);
		cout << "==================================================== In Work Cell ======================================================" << endl;
		cout << "LCP------window5 = " << setprecision(3) << Sim.WCwt5 << "   window4 = " << setprecision(3) << Sim.WCwt4 << "   window0 = " << setprecision(3) << Sim.WCwt0 << endl;

		cout << "=============================================== In Factory Management ==================================================" << endl;
		cout << "LCP------window5 = " << setprecision(3) << Sim.FMwt5 << "   window4 = " << setprecision(3) << Sim.FMwt4 << endl;

		Sim.WTcycle++;
		Sim.outWTrecord << "[" << Sim.WTcycle << "] " << "WC==>" << " " << setprecision(9) << Sim.WCwt5 * 1000 << " ms " << setprecision(9) << Sim.WCwt4 * 1000 << " ms " << setprecision(9) << Sim.WCwt0 * 1000 << " ms FM==>" << " " << setprecision(9) << Sim.FMwt5 * 1000 << " ms " << setprecision(9) << Sim.FMwt4 * 1000 << " ms" << endl;
	}
}

void SchedulingBS::mySchedule()
{
	setcolor(12, 0);
	cout << "[Scheduling]: Mobile Station Multiplexing " << endl;
	if(Sim.algorithm == "RR")
		UMS[0]->scheduling->scheduler();
	else if(Sim.algorithm == "WGCL"|| Sim.algorithm == "AW-WGCL")
		UMS[0]->scheduling->scheduler();
	else if (Sim.algorithm == "LCP")
		UMS[0]->scheduling->LCP();

}

void static SplitString(const string& s, vector<string>& v, const string& c)
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

void SchedulingBS::Schedule(int bsID)
{
	if (BS[bsID]->channel->NumAssociatedMS > 0)
	{
		double temp = 0; int tempCB = 0; BS[bsID]->scheduling->numScheduledUMS = 0;
		for (int umsID = 0; umsID < BS[bsID]->channel->NumAssociatedUMS; umsID++)
		{
			temp = temp + UMS[umsID]->scheduling->msBuffer;
			if (UMS[umsID]->scheduling->msBuffer > 0)
			{				
				BS[bsID]->scheduling->scheduledUMS(arma::randu()*Sim.scheduling->numRB,tempCB) = umsID;
				tempCB++;
				BS[bsID]->scheduling->numScheduledUMS++;
			}			
		}
		if (numScheduledUMS == Sim.scheduling->numCB)
		{
			BS[bsID]->scheduling->scheduledMS = -1;
		}
		else
		{
			arma::vec PFMetric(BS[bsID]->channel->NumAssociatedMS);
			for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
			{
				int msID = BS[bsID]->network->attachedMS[attachedMsID];
				PFMetric(attachedMsID) = MS[msID]->scheduling->downlinkspectralEfficiency / MS[msID]->scheduling->downlinkaveragedThroghput;
			}
			int ScheduledAttachedMsID = PFMetric.index_max();
			BS[bsID]->scheduling->scheduledMS = BS[bsID]->network->attachedMS[ScheduledAttachedMsID];
		}
		
	}

	else
	{
		BS[bsID]->scheduling->scheduledMS = -1;
		//BS[bsID]->scheduling->precodingMatrix.zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
	}
	
}

void SchedulingBS::MuMimoSchedule(int bsID, int subband, arma::uvec scheduluedMS, int link)
{
	
	
}

void SchedulingBS::printCombination(arma::uvec arr, arma::uvec groupMetric, double value, int n, int r, int link)
{
	arma::uvec data;
	data.zeros(r);
	combinationUtil(arr, data, groupMetric, value, 0, n - 1, 0, r, link);
}

void SchedulingBS::combinationUtil(arma::uvec arr, arma::uvec data, arma::uvec groupMetric, double value, int start, int end, int index, int r, int link)
{
	if (index == r)
	{
		double temp = 0; double metricTemp = 0;
		for (int j = 0; j < r; j++)
		{
			double spectralEfficiency, averagedThroghput;
			if (link == 0)
			{				
				spectralEfficiency = MS[arr(j)]->scheduling->downlinkspectralEfficiency;
				averagedThroghput = MS[arr(j)]->scheduling->downlinkaveragedThroghput;
			}
			else
			{
				spectralEfficiency = MS[arr(j)]->scheduling->uplinkspectralEfficiency;
				averagedThroghput = MS[arr(j)]->scheduling->uplinkaveragedThroghput;
			}

			if (averagedThroghput == 0)
				metricTemp = spectralEfficiency / double(r);
			else
				metricTemp = (spectralEfficiency / averagedThroghput) / double(r);

			temp = temp + metricTemp;			
		}
		index = 0;
		if (value < temp)
		{
			groupMetric = data;
			value = temp;
		}
	}

	for (int i = start; i <= end && (end - i + 1) >= (r - index); i++)
	{
		data(index) = arr(i);
		combinationUtil(arr, data, groupMetric, value, i + 1, end, index + 1, r, link);
	}
}

double SchedulingBS::GetSpectralEfficiency(double SINR, int &MCS) // uplink���� ���� �� ���� ����?
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

void SchedulingBS::Feedback(int msID)
{
	/*
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NRuRLLC.bandwidth * 1e6 / 1000;
	arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NRuRLLC.bandwidth / 10 * 50), temps;

	tempRI.zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna);
	tempRHr.zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna);
	tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);

	for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
	{
		tempRHr = tempRHr + MS[msID]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50);
		tempRH = tempRH + (MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50);
	}

	arma::svd(tempU, temps, tempV, tempRH, "std");
	for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
	{
		tempRI.zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna);
		for (int si = 1; si < SLS_MAX_BS; si++)
		{
			tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
		}
		tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna)).i();
		temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
		signal = temph*temph.t();
		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna))*tempIRC.t();
		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
	}

	MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(10.0 * log10(pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50)) - 1), MS[msID]->scheduling->MCS);
	//MS[msID]->scheduling->PrecodingMatrix = tempV.col(0);
	*/
}

void SchedulingBS::MuMimoFeedback(int msID, int type)
{
	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NRuRLLC.bandwidth * 1e6 / 1000;
	arma::cx_mat tempRI, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NRuRLLC.bandwidth / 10 * 50), temps;
	arma::cx_mat *analogCodebook, *digitalCodebook;
	if (type == 0)
	{
		for (int RBindex = 0; RBindex < (50); RBindex++)
		{
			tempRI.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
			for (int si = 1; si < SLS_MAX_BS; si++)
			{
				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t()*MS[msID]->channel->FrequencyChannel(si, 0, RBindex) / double(Sim.channel->NumberOfReceiveAntennaPort);
			}
			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort)).i();
			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
			signal = temph*temph.t();
			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort))*tempIRC.t();
			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
		}
	}
	else
	{
		analogCodebook = new arma::cx_mat[16];
		digitalCodebook = new arma::cx_mat[16];
		analogCodebook = PrecodingMatrix(Analogbeamforming, analogCodebook);
		digitalCodebook = PrecodingMatrix(Digitalbeamforming, digitalCodebook);
		double temp = 0; double maxtemp = 0;
		for (int analogbeam = 0; analogbeam < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2; analogbeam++)
		{
			for (int digitalbeam = 0; digitalbeam < Sim.channel->NumberOfTransmitAntennaPort * 2; digitalbeam++)
			{
				for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
				{
					tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t() * analogCodebook[analogbeam] * digitalCodebook[digitalbeam];
					tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
					temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
					temp = temp + trace(real(temph*temph.t()));
				}
				if (maxtemp < temp) maxtemp = temp;
				MS[msID]->scheduling->analogPrecodingMatrix = analogCodebook[analogbeam];
				MS[msID]->scheduling->digitalPrecodingMatrix = digitalCodebook[digitalbeam];
			}
		}

		for (int RBindex = 0; RBindex < (Sim.channel->NRuRLLC.bandwidth / 10 * 50); RBindex++)
		{
			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			for (int si = 1; si < SLS_MAX_BS; si++)
			{
				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
			}
			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()*MS[msID]->scheduling->analogPrecodingMatrix*MS[msID]->scheduling->digitalPrecodingMatrix;
			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
			signal = temph*temph.t();
			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
		}
	}
	

	MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(10.0 * log10(pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NRuRLLC.bandwidth / 10 * 50)) - 1), MS[msID]->scheduling->MCS);
	
}

void SchedulingBS::ReceivedSINR(int msID, int link, int slotnumber)
{

}


arma::cx_mat* SchedulingBS::PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook)
{
	
	codebook = new arma::cx_mat[Sim.channel->NumberOfReceiveAntennaPort * 2];
	arma::cx_mat tempanalogCodebook;
	tempanalogCodebook.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	std::complex <double> phase;
	int index_t1, index_t2;
	std::complex <double> *phase_a = new std::complex <double>[2];

	switch (precodingtype)
	{
	case Analogbeamforming:
		for (int i = 0; i < Sim.channel->NumberOfReceiveAntennaPort; i++)
		{
			for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort / 2; j++)
			{
				phase.real(0.0);
				phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfReceiveAntennaPort));
				tempanalogCodebook(j, i) = exp(phase);
			}
		}
		index_t1 = 0; index_t2 = Sim.channel->NumberOfReceiveAntennaPort;
		phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
		for (int i = 0; i < Sim.channel->NumberOfReceiveAntennaPort; i++)
		{
			for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort; j++)
			{
				if (i % 2 == 0)
				{
					codebook[index_t1].zeros(Sim.channel->NumberOfReceiveAntennaPort, 1);
					codebook[index_t1].submat(0, 0, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
					codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfReceiveAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
					codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfReceiveAntennaPort);
					index_t1 = index_t1 + 1;
				}
				else
				{
					codebook[index_t2].zeros(Sim.channel->NumberOfReceiveAntennaPort, 1);
					codebook[index_t2].submat(0, 0, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
					codebook[index_t2].submat(Sim.channel->NumberOfReceiveAntennaPort / 2, 0, Sim.channel->NumberOfReceiveAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
					codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfReceiveAntennaPort);
					index_t2 = index_t2 + 1;
				}
			}
		}
		return codebook;
		break;

	case Digitalbeamforming:
		codebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort * 2];
		arma::cx_mat tempdigitalCodebook;
		tempdigitalCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);
		std::complex <double> phase;
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
			for (int j = 0; j < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; j++)
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


void SchedulingBS::ConcludeIteration()
{

}

void SchedulingBS::Conclude()
{

}
