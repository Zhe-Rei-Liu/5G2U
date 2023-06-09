/****************************************************************************

Channel Model for Mobile Station (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SpatialChannel_NRuRLLC.cpp
DATE         : 2017.01.02
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.01.31	Minsig Han		Created
2017.02.22	Minsig Han		RSRP
2017.02.26  Minsig Han		DFT
2017.03.01	Minsig Han		Short-term Channel
2017.03.07  Minsig Han		Apply PL and Shadowing

===========================================================================*/

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "3DSpatialChannelModel_NRuRLLC.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         LOCAL VARIABLE DECLARATION                      */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void SpatialChannel::Initialize()
{
#ifdef NRuRLLC_UrbanMacroCell
	UrbanMacroCellLOS.sigmaShadowing = 3;
	UrbanMacroCellLOS.muRiceanK = 9;
	UrbanMacroCellLOS.sigmaRiceanK = 5;
	UrbanMacroCellLOS.muDelaySpread = -7.19;
	UrbanMacroCellLOS.epsilonDelaySpread = 0.40;
	UrbanMacroCellLOS.muASD = 1.20;
	UrbanMacroCellLOS.epsilonASD = 0.43;
	UrbanMacroCellLOS.muASA = 1.75;
	UrbanMacroCellLOS.epsilonASA = 0.19;
	UrbanMacroCellLOS.muZSD = 0;
	UrbanMacroCellLOS.epsilonZSD = 0.4;
	UrbanMacroCellLOS.muZSA = 0.60;
	UrbanMacroCellLOS.epsilonZSA = 0.16;
	UrbanMacroCellLOS.ASDvsDS = 0.5;
	UrbanMacroCellLOS.ASAvsDS = 0.8;
	UrbanMacroCellLOS.ASAvsSF = -0.4;
	UrbanMacroCellLOS.ASDvsSF = -0.5;
	UrbanMacroCellLOS.DSvsSF = -0.4;
	UrbanMacroCellLOS.ASDvsASA = 0.4;
	UrbanMacroCellLOS.ASDvsK = -0.2;
	UrbanMacroCellLOS.ASAvsK = -0.3;
	UrbanMacroCellLOS.DSvsK = -0.7;
	UrbanMacroCellLOS.SFvsK = 0.5;
	UrbanMacroCellLOS.ZSDvsSF = 0;
	UrbanMacroCellLOS.ZSAvsSF = 0;
	UrbanMacroCellLOS.ZSDvsK = 0;
	UrbanMacroCellLOS.ZSAvsK = 0;
	UrbanMacroCellLOS.ZSDvsDS = 0;
	UrbanMacroCellLOS.ZSAvsDS = 0.2;
	UrbanMacroCellLOS.ZSDvsASD = 0.5;
	UrbanMacroCellLOS.ZSAvsASD = 0.3;
	UrbanMacroCellLOS.ZSDvsASA = 0;
	UrbanMacroCellLOS.ZSAvsASA = 0;
	UrbanMacroCellLOS.ZSDvsZSA = 0;
	UrbanMacroCellLOS.delayScalingParameter = 3.2;
	UrbanMacroCellLOS.muXPR = 9;
	UrbanMacroCellLOS.sigmaXPR = 3;
	UrbanMacroCellLOS.numberOfClusters = 12;
	UrbanMacroCellLOS.numberOfRaysPerClusters = 20;
	UrbanMacroCellLOS.cluserASD = 3;
	UrbanMacroCellLOS.cluserASA = 17;
	UrbanMacroCellLOS.cluserZSA = 7;
	UrbanMacroCellLOS.perClusterShadowing = 3;
	UrbanMacroCellNLOS.sigmaShadowing = 4;
	UrbanMacroCellNLOS.muRiceanK = 0;
	UrbanMacroCellNLOS.sigmaRiceanK = 0;
	UrbanMacroCellNLOS.muDelaySpread = -6.89;
	UrbanMacroCellNLOS.epsilonDelaySpread = 0.54;
	UrbanMacroCellNLOS.muASD = 1.41;
	UrbanMacroCellNLOS.epsilonASD = 0.17;
	UrbanMacroCellNLOS.muASA = 1.84;
	UrbanMacroCellNLOS.epsilonASA = 0.15;
	UrbanMacroCellNLOS.muZSD = 0;
	UrbanMacroCellNLOS.epsilonZSD = 0.6;
	UrbanMacroCellNLOS.muZSA = 0.88;
	UrbanMacroCellNLOS.epsilonZSA = 0.16;
	UrbanMacroCellNLOS.ASDvsDS = 0;
	UrbanMacroCellNLOS.ASAvsDS = 0.4;
	UrbanMacroCellNLOS.ASAvsSF = -0.4;
	UrbanMacroCellNLOS.ASDvsSF = 0;
	UrbanMacroCellNLOS.DSvsSF = -0.7;
	UrbanMacroCellNLOS.ASDvsASA = 0;
	UrbanMacroCellNLOS.ASDvsK = 0;
	UrbanMacroCellNLOS.ASAvsK = 0;
	UrbanMacroCellNLOS.DSvsK = 0;
	UrbanMacroCellNLOS.SFvsK = 0;
	UrbanMacroCellNLOS.ZSDvsSF = 0;
	UrbanMacroCellNLOS.ZSAvsSF = 0;
	UrbanMacroCellNLOS.ZSDvsK = 0;
	UrbanMacroCellNLOS.ZSAvsK = 0;
	UrbanMacroCellNLOS.ZSDvsDS = -0.5;
	UrbanMacroCellNLOS.ZSAvsDS = 0;
	UrbanMacroCellNLOS.ZSDvsASD = 0.5;
	UrbanMacroCellNLOS.ZSAvsASD = 0.5;
	UrbanMacroCellNLOS.ZSDvsASA = 0;
	UrbanMacroCellNLOS.ZSAvsASA = 0.2;
	UrbanMacroCellNLOS.ZSDvsZSA = 0;
	UrbanMacroCellNLOS.delayScalingParameter = 3;
	UrbanMacroCellNLOS.muXPR = 8.0;
	UrbanMacroCellNLOS.sigmaXPR = 3;
	UrbanMacroCellNLOS.numberOfClusters = 19;
	UrbanMacroCellNLOS.numberOfRaysPerClusters = 20;
	UrbanMacroCellNLOS.cluserASD = 10;
	UrbanMacroCellNLOS.cluserASA = 22;
	UrbanMacroCellNLOS.cluserZSA = 7;
	UrbanMacroCellNLOS.perClusterShadowing = 3;
	UrbanMacroCellOtoI.sigmaShadowing = 7;
	UrbanMacroCellOtoI.muRiceanK = 0;
	UrbanMacroCellOtoI.sigmaRiceanK = 0;
	UrbanMacroCellOtoI.muDelaySpread = -6.62;
	UrbanMacroCellOtoI.epsilonDelaySpread = 0.32;
	UrbanMacroCellOtoI.muASD = 1.25;
	UrbanMacroCellOtoI.epsilonASD = 0.42;
	UrbanMacroCellOtoI.muASA = 1.76;
	UrbanMacroCellOtoI.epsilonASA = 0.16;
	UrbanMacroCellOtoI.muZSD = 0;
	UrbanMacroCellOtoI.epsilonZSD = 0.4;
	UrbanMacroCellOtoI.muZSA = 1.01;
	UrbanMacroCellOtoI.epsilonZSA = 0.43;
	UrbanMacroCellOtoI.ASDvsDS = 0.4;
	UrbanMacroCellOtoI.ASAvsDS = 0.4;
	UrbanMacroCellOtoI.ASAvsSF = 0;
	UrbanMacroCellOtoI.ASDvsSF = 0.2;
	UrbanMacroCellOtoI.DSvsSF = -0.5;
	UrbanMacroCellOtoI.ASDvsASA = 0;
	UrbanMacroCellOtoI.ASDvsK = 0;
	UrbanMacroCellOtoI.ASAvsK = 0;
	UrbanMacroCellOtoI.DSvsK = 0;
	UrbanMacroCellOtoI.SFvsK = 0;
	UrbanMacroCellOtoI.ZSDvsSF = 0;
	UrbanMacroCellOtoI.ZSAvsSF = 0;
	UrbanMacroCellOtoI.ZSDvsK = 0;
	UrbanMacroCellOtoI.ZSAvsK = 0;
	UrbanMacroCellOtoI.ZSDvsDS = -0.6;
	UrbanMacroCellOtoI.ZSAvsDS = -0.2;
	UrbanMacroCellOtoI.ZSDvsASD = -0.2;
	UrbanMacroCellOtoI.ZSAvsASD = 0;
	UrbanMacroCellOtoI.ZSDvsASA = 0;
	UrbanMacroCellOtoI.ZSAvsASA = 0.5;
	UrbanMacroCellOtoI.ZSDvsZSA = 0.5;
	UrbanMacroCellOtoI.delayScalingParameter = 2.2;
	UrbanMacroCellOtoI.muXPR = 9;
	UrbanMacroCellOtoI.sigmaXPR = 5;
	UrbanMacroCellOtoI.numberOfClusters = 12;
	UrbanMacroCellOtoI.numberOfRaysPerClusters = 20;
	UrbanMacroCellOtoI.cluserASD = 5;
	UrbanMacroCellOtoI.cluserASA = 8;
	UrbanMacroCellOtoI.cluserZSA = 3;
	UrbanMacroCellOtoI.perClusterShadowing = 4;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         Level 2 Functions                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/
//int msID, int site
//void SpatialChannel::GeneralParameters(int source, int destination, int type) {
//	if (type == 0) // BS-to-MS
//	{
//		arma::mat pos3D = MS[destination]->network->pos3D;
//		arma::mat wraparoundposBS = MS[destination]->network->wraparoundposBS;
//	}
//	else if (type == 1) // BS-to-BS
//	{
//		arma::mat pos3D = MS[destination]->network->pos3D;
//		arma::mat wraparoundposBS = MS[destination]->network->wraparoundposBS;
//	}
//	else // MS-to-MS
//	{
//		arma::mat pos3D = MS[destination]->network->pos3D;
//		arma::mat wraparoundposBS = MS[destination]->network->wraparoundposBS;
//	}
//
//	if (Sim.network->NetworkModel == ((NETWORK::UrbanMacroCell) || (NETWORK::DenseUrban) || (NETWORK::RuralMacroCell))) {
//		MS[msID]->channel->distance2D = Distance2D(pos3D(0, 0), pos3D(0, 1), wraparoundposBS(site, 0), MS[msID]->network->wraparoundposBS(site, 1));
//		MS[msID]->channel->distance3D = Distance3D(pos3D(0, 0), pos3D(0, 1), pos3D(0, 2), MS[msID]->network->wraparoundposBS(site, 0), MS[msID]->network->wraparoundposBS(site, 1), MS[msID]->network->wraparoundposBS(site, 2));
//	}
//	else if (Sim.network->NetworkModel == NETWORK::IndoorOffice) {
//		MS[msID]->channel->distance2D = spatialChannel.Distance2D(MS[msID]->network->pos3D(0, 0), MS[msID]->network->pos3D(0, 1), BS[site]->network->pos3D(0, 0), BS[site]->network->pos3D(0, 1));
//		MS[msID]->channel->distance3D = spatialChannel.Distance3D(MS[msID]->network->pos3D(0, 0), MS[msID]->network->pos3D(0, 1), MS[msID]->network->pos3D(0, 2), BS[site]->network->pos3D(0, 0), BS[site]->network->pos3D(0, 1), BS[site]->network->pos3D(0, 2));
//	}
//	// cout << "Pathloss calculated" << endl;
//	spatialChannel.Pathloss(msID, site);
//	MS[msID]->channel->largeScaleParameter = MS[msID]->network->LargeScaleParameter(Sim.channel->ChannelModel, MS[msID]->channel->channelCondition, msID, site); // ShadowFading, RiceanK, DelaySpread, rmsASD, rmsASA, rmsZSD, rmsZSA
//}
//
//void SmallScaleParameter(int msID, int bsID, int site, int sector) {
//	SpatialChannel spatialChannel;
//
//	spatialChannel.Delay(msID);
//	// cout << "Delay genereated" << endl;
//
//	spatialChannel.ClusterPower(msID, bsID);
//	// cout << "Cluster Power Generated" << endl;
//
//	spatialChannel.ArrivalAndDepartureAngle(msID, bsID, site, sector);
//	// cout << "Generate Arrival And Departure Angles"<< endl;
//
//	spatialChannel.ArrivalAndDepartureAntennaGain(msID, bsID, site, sector);
//	// cout << "Generate Arrival And Departure AntennaGains" << endl;
//
//}
//
//void CoefficientGeneration(int msID, int bsID, int site, int sector) {
//	RSRP(msID, bsID, site, sector);
//}
//
//void RSRP(int src, int dst, int site, int sector) {
//	double muXPR, sigmaXPR;
//	switch (Sim.channel->ChannelModel)
//	{
//	case SLS::DenseUrban:
//
//		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
//			muXPR = UrbanMacroCellLOS.muXPR;
//			sigmaXPR = UrbanMacroCellLOS.sigmaXPR;
//		}
//		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
//			muXPR = UrbanMacroCellNLOS.muXPR;
//			sigmaXPR = UrbanMacroCellNLOS.sigmaXPR;
//		}
//		else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS)) {
//			muXPR = UrbanMacroCellOtoI.muXPR;
//			sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
//		}
//		else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == NLOS)) {
//			muXPR = UrbanMacroCellOtoI.muXPR;
//			sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
//		}
//		break;
//
//	case SLS::UrbanMacroCell:
//
//		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
//			muXPR = UrbanMacroCellLOS.muXPR;
//			sigmaXPR = UrbanMacroCellLOS.sigmaXPR;
//		}
//		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
//			muXPR = UrbanMacroCellNLOS.muXPR;
//			sigmaXPR = UrbanMacroCellNLOS.sigmaXPR;
//		}
//		else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS)) {
//			muXPR = UrbanMacroCellOtoI.muXPR;
//			sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
//		}
//		else {
//			muXPR = UrbanMacroCellOtoI.muXPR;
//			sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
//		}
//
//		break;
//	}
//
//	int numRealCluster = MS[src]->channel->numRealCluster;
//	int numRay = 20;
//	int numProcess = Sim.channel->NumberOfChannelProcess;
//	int numRxAntenna = Sim.channel->NumberOfRxAntenna;
//	double kR = pow(10.0, MS[src]->channel->largeScaleParameter[1] / 10.0);
//	double K_R1;
//	double XPR = pow(10.0, (muXPR + sigmaXPR*arma::randn()) / 10.0);
//
//	std::complex<double> Big_pi_NLOS_thetatheta(0, (360 * arma::randu() - 180.0)*PI / 180.0);
//	std::complex<double> Big_pi_NLOS_thetapi(0, (360 * arma::randu() - 180.0)*PI / 180.0);
//	std::complex<double> Big_pi_NLOS_pitheta(0, (360 * arma::randu() - 180.0)*PI / 180.0);
//	std::complex<double> Big_pi_NLOS_pipi(0, (360 * arma::randu() - 180.0)*PI / 180.0);
//	arma::field<arma::cx_mat> alpha_nmup_temp(numProcess);
//	alpha_nmup_temp(0).zeros(numRealCluster, numRay);
//	arma::field<arma::cx_mat> alpha_nmup_temp_x(numProcess);
//	alpha_nmup_temp_x(0).zeros(numRealCluster, numRay);
//	arma::field<arma::cx_mat> alpha_nmup_temp1(numProcess);
//	alpha_nmup_temp1(0).zeros(numRealCluster, numRay);
//	arma::field<arma::cx_mat> alpha_nmup_temp_x1(numProcess);
//	alpha_nmup_temp_x1(0).zeros(numRealCluster, numRay);
//
//	arma::vec RSRP_cal;
//	RSRP_cal.zeros(57);
//	arma::mat RSRP;
//	RSRP.zeros(numProcess, 1);
//
//	arma::mat cluster_P_1;
//	arma::mat F_rx_smallUH;
//	arma::mat F_rx_smallUV;
//	arma::mat F_rx_smallXH;
//	arma::mat F_rx_smallXV;
//
//	arma::cx_mat F_tx_smallUH;
//	arma::cx_mat F_tx_smallUV;
//	arma::cx_mat F_tx_smallXH;
//	arma::cx_mat F_tx_smallXV;
//
//	arma::mat F_rx_UH;
//	arma::mat F_rx_UV;
//	arma::mat F_rx_XH;
//	arma::mat F_rx_XV;
//
//	arma::cx_mat F_tx_UH;
//	arma::cx_mat F_tx_UV;
//	arma::cx_mat F_tx_XH;
//	arma::cx_mat F_tx_XV;
//	arma::cx_mat f_urd_LOS = MS[src]->channel->F_urd_LOS(dst, 0);
//	arma::field<arma::mat> Alpha_nmup(Sim.channel->NumberOfRxAntenna, numProcess);
//	arma::mat velocity(MAX_CLUSTER + 4, numRay);
//
//
//	double AngleAODLOS = MS[src]->channel->GCSAOD;
//	double AngleZODLOS = MS[src]->channel->GCSZOD;
//	double AngleAOALOS = MS[src]->channel->GCSAOA;
//	double AngleZOALOS = MS[src]->channel->GCSZOA;
//	double GCSAOA = MS[src]->channel->GCSAOA;
//	double GCSAOD = MS[src]->channel->GCSAOD;
//	double GCSZOA = MS[src]->channel->GCSZOA;
//	double GCSZOD = MS[src]->channel->GCSZOD;
//
//	double velocityLOS = 2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(PI - AngleZODLOS)*cos(AngleAOALOS)*5.0 / 6.0*sin(MS[src]->network->velocityVertical)*cos(MS[src]->network->velocityHorizontal) + sin(PI - GCSZOD)*sin(GCSAOA)*5.0 / 6.0*sin(MS[src]->network->velocityVertical)*sin(MS[src]->network->velocityHorizontal) + cos(PI - GCSZOD)*5.0 / 6.0*cos(MS[src]->network->velocityVertical));
//	MS[src]->channel->VelocityLOS(dst, 0) = velocityLOS;
//
//	arma::field<arma::mat> alpha_sum(numProcess, 1);
//
//	double rayAOA, rayAOD, rayZOA, rayZOD;
//
//	cluster_P_1 = MS[src]->channel->realClusterPowersForLOS;
//	if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) K_R1 = kR;
//	else K_R1 = 0.0;
//	int abb = 0;
//
//
//	arma::cx_mat alpha_zero_temp(numProcess, 1);
//	arma::cx_mat alpha_zero_temp_x(numProcess, 1);
//	arma::cx_mat alpha_zero_temp1(numProcess, 1);
//	arma::cx_mat alpha_zero_temp_x1(numProcess, 1);
//	arma::cx_mat Alpha_zero(numRxAntenna, numProcess);
//
//	F_rx_UH = MS[src]->channel->ReceiverAntennaGainLOSUH;
//	F_rx_UV = MS[src]->channel->ReceiverAntennaGainLOSUV;
//	F_rx_XH = MS[src]->channel->ReceiverAntennaGainLOSXH;
//	F_rx_XV = MS[src]->channel->ReceiverAntennaGainLOSXV;
//
//	F_tx_UH = MS[src]->channel->TransmitterAntennaGainLOSUH;
//	F_tx_UV = MS[src]->channel->TransmitterAntennaGainLOSUV;
//	F_tx_XH = MS[src]->channel->TransmitterAntennaGainLOSXH;
//	F_tx_XV = MS[src]->channel->TransmitterAntennaGainLOSXV;
//
//	std::complex<double> Big_PI_LOS(0.0, (360 * arma::randu() - 180.0)*PI / 180.0);
//
//	int processIndex = MS[src]->channel->processIndex;
//
//	if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray))
//		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0));
//	else if ((Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray)) {
//		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
//		alpha_zero_temp_x[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_XV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_XH(0, 0));
//	}
//	else if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization)) {
//		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
//		alpha_zero_temp_x[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_XV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_XH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
//	}
//	else {
//		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
//		alpha_zero_temp1[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_XV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_XH(0, 0)); // tx x
//		alpha_zero_temp_x[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_XV(0, 0) * exp(Big_PI_LOS) * F_tx_XV(0, 0) - F_rx_XH(0, 0) * exp(Big_PI_LOS) * F_tx_XH(0, 0));
//		alpha_zero_temp_x1[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_XV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_XH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0)); // rx x
//	}
//
//	for (int u = 0; u < Sim.channel->NumberOfRxAntenna; u++) {
//		Alpha_zero(u, processIndex) = alpha_zero_temp[processIndex] * exp(f_urd_LOS[u]);
//		Alpha_nmup(u, processIndex) = 0.0;
//	}
//
//
//
//	for (int n = 0; n < numRealCluster; n++) {
//		for (int m = 0; m < numRay; m++) {
//			F_rx_smallUH = MS[src]->channel->SmallScaleReceiverAntennaGainUH(n, m);
//			F_rx_smallUV = MS[src]->channel->SmallScaleReceiverAntennaGainUV(n, m);
//			F_rx_smallXH = MS[src]->channel->SmallScaleReceiverAntennaGainXH(n, m);
//			F_rx_smallXV = MS[src]->channel->SmallScaleReceiverAntennaGainXV(n, m);
//
//			F_tx_smallUH = MS[src]->channel->SmallScaleTransmitterAntennaGainUH(n, m);
//			F_tx_smallUV = MS[src]->channel->SmallScaleTransmitterAntennaGainUV(n, m);
//			F_tx_smallXH = MS[src]->channel->SmallScaleTransmitterAntennaGainXH(n, m);
//			F_tx_smallXV = MS[src]->channel->SmallScaleTransmitterAntennaGainXV(n, m);
//
//			rayAOA = MS[src]->channel->SmallScaleAOA(n, m);
//			rayAOD = MS[src]->channel->SmallScaleAOD(n, m);
//			rayZOA = MS[src]->channel->SmallScaleZOA(n, m);
//			rayZOD = MS[src]->channel->SmallScaleZOD(n, m);
//
//			for (int processIndex = 0; processIndex < numProcess; processIndex++) {
//				for (int u = 0; u < numRxAntenna; u++) {
//					if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray))
//						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*(F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) * F_tx_smallUV(0, 0));
//					else if ((Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray)) {
//						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
//						alpha_nmup_temp_x(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallXV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallXH(0, 0));
//					}
//					else if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization)) {
//						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
//						alpha_nmup_temp_x(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallXV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallXH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallXV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallXH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
//					}
//					else {
//						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
//						alpha_nmup_temp1(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallXV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallXH(0, 0)); // tx x
//						alpha_nmup_temp_x(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallXV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallXH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallXV(0, 0) + (F_rx_smallXV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallXH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallXH(0, 0));
//						alpha_nmup_temp_x1(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallXV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallXH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallXV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallXH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0)); // rx x
//					}
//
//					Alpha_nmup(u, processIndex) = Alpha_nmup(u, processIndex) + pow(abs(alpha_nmup_temp(processIndex)(n, m) * exp(MS[src]->channel->F_urd(n, m)(u, 0))), 2.0);
//				}
//
//				if (n == 0 || n == 1) {
//					velocity(abb, m) = 2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(rayZOA*PI / 180.0)*cos(rayAOA*PI / 180.0)*5.0 / 6.0*sin(MS[src]->network->velocityVertical)*cos(MS[src]->network->velocityHorizontal) + sin(rayZOA*PI / 180.0)*sin(rayAOA*PI / 180.0)*5.0 / 6.0*sin(MS[src]->network->velocityVertical)*sin(MS[src]->network->velocityHorizontal) + cos(rayZOA*PI / 180.0)*5.0 / 6.0*cos(MS[src]->network->velocityVertical));
//					velocity(abb + 1, m) = velocity(abb, m);
//					velocity(abb + 2, m) = velocity(abb, m);
//					if ((m == 19) && (processIndex == numProcess - 1))
//						abb = abb + 3;
//				}
//				else {
//					velocity[abb, m] = 2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(rayZOA*PI / 180.0)*cos(rayAOA*PI / 180.0)*5.0 / 6.0*sin(MS[src]->network->velocityVertical)*cos(MS[src]->network->velocityHorizontal) + sin(rayZOA*PI / 180.0)*sin(rayAOA*PI / 180.0)*5.0 / 6.0*sin(MS[src]->network->velocityVertical)*sin(MS[src]->network->velocityHorizontal) + cos(rayZOA*PI / 180.0)*5.0 / 6.0*cos(MS[src]->network->velocityVertical));
//					if ((m == 19) && (processIndex == numProcess - 1))
//						abb++;
//				}
//
//			}
//			//			MS[src]->channel->Velocity = velocity;
//			MS[src]->channel->VelocityBS(dst) = velocity;
//		}
//	}
//
//	double couplingLoss = pow(10.0, -MS[src]->channel->pathloss / 10.0) * pow(10.0, -MS[src]->channel->largeScaleParameter(0, 0) / 10.0)* pow(10, (Sim.channel->NRuRLLC.txPower / 10.0));
//	MS[src]->channel->CouplingLoss(dst) = couplingLoss;
//
//	for (int processIndex = 0; processIndex < numProcess; processIndex++) {
//		alpha_sum[processIndex] = 0.0;
//		for (int u = 0; u < numRxAntenna; u++) {
//			alpha_sum[processIndex] = alpha_sum[processIndex] + pow(abs(Alpha_zero(u, processIndex)), 2.0) + Alpha_nmup(u, processIndex);
//		}
//		RSRP[processIndex] = couplingLoss * alpha_sum[processIndex](0, 0) / numRxAntenna / numProcess;
//	}
//
//	RSRP_cal(3 * site + sector) = RSRP[0];
//
//	MS[src]->channel->Alpha_zero_temp(dst) = alpha_zero_temp;
//	MS[src]->channel->Alpha_zero_temp_x(dst, 0) = alpha_zero_temp_x;
//	MS[src]->channel->Alpha_zero_temp1(dst, 0) = alpha_zero_temp1;
//	MS[src]->channel->Alpha_zero_temp_x1(dst, 0) = alpha_zero_temp_x1;
//
//	MS[src]->channel->Alpha_nmup_temp(dst, 0) = alpha_nmup_temp(0);
//	MS[src]->channel->Alpha_nmup_temp_x(dst, 0) = alpha_nmup_temp_x(0);
//	MS[src]->channel->Alpha_nmup_temp1(dst, 0) = alpha_nmup_temp1(0);
//	MS[src]->channel->Alpha_nmup_temp_x1(dst, 0) = alpha_nmup_temp_x1(0);
//
//	MS[src]->channel->RSRPout(3 * site + sector, 0) = RSRP_cal(3 * site + sector, 0);
//}
//
//void ChannelCoefficient(int src) {
//	int numProcess = Sim.channel->NumberOfChannelProcess;
//	int numPort = Sim.channel->NumberOfTransmitAntennaPort;
//	int numRxAntenna = Sim.channel->NumberOfRxAntenna;
//
//	arma::mat RSRP = MS[src]->channel->RSRPout;
//	arma::field<arma::cx_mat> alpha_zero_temp = MS[src]->channel->Alpha_zero_temp;
//	arma::field<arma::cx_mat> alpha_zero_temp_x = MS[src]->channel->Alpha_zero_temp_x;
//	arma::field<arma::cx_mat> alpha_zero_temp1 = MS[src]->channel->Alpha_zero_temp1;
//	arma::field<arma::cx_mat> alpha_zero_temp_x1 = MS[src]->channel->Alpha_zero_temp_x1;
//
//	arma::field<arma::cx_mat> F_urd_LOS = MS[src]->channel->F_urd_LOS;
//	arma::field<arma::cx_mat> F_prd_LOS = MS[src]->channel->F_prd_LOS;
//	arma::field<arma::cx_mat> F_urd_BS = MS[src]->channel->F_urd_BS;
//	arma::field<arma::cx_mat> F_prd_BS = MS[src]->channel->F_prd_BS;
//
//
//	arma::field<arma::cx_mat> SI_H_t_los(SLS_MAX_BS, 1); //이거랑
//	arma::field<arma::cx_mat> SI_H_t(SLS_MAX_BS, numProcess, MAX_CLUSTER); //이거 process 지우기
//	MS[src]->channel->HtLOS = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
//	MS[src]->channel->Ht = arma::field<arma::cx_mat>(Sim.network->numBS, 1, MAX_CLUSTER);
//
//
//	for (int bsIndex = 0; bsIndex < SLS_MAX_BS; bsIndex++) {
//		SI_H_t_los(bsIndex, 0).zeros(numRxAntenna*numPort, 1);
//		MS[src]->channel->HtLOS(bsIndex, 0).zeros(numRxAntenna*numPort, 1);
//	}
//
//	for (int siIndex = 0; siIndex < Sim.channel->NumberOfBS; siIndex++) {
//		for (int processIndex = 0; processIndex < numProcess; processIndex++) {
//			for (int n = 0; n < MAX_CLUSTER; n++) {
//				SI_H_t(siIndex, processIndex, n).zeros(numRxAntenna*numPort, MAX_RAY);
//				MS[src]->channel->Ht(siIndex, processIndex, n).zeros(numRxAntenna*numPort, MAX_RAY);
//			}
//		}
//	}
//
//	// Strong Interference
//	MS[src]->channel->numRay = 20;
//	arma::uvec BSindex = MS[src]->channel->BSindex;
//	for (int siIndex = 0; siIndex < Sim.channel->NumberOfBS; siIndex++) {
//		int dst = BSindex(siIndex);
//		for (int u = 0; u < numRxAntenna; u++) {
//			for (int p = 0; p < numPort; p++) {
//				for (int processIndex = 0; processIndex < numProcess; processIndex++) {
//					if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 0))
//						SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex, 0) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//					else if ((Sim.channel->BsAntennaModel == 1) && (Sim.channel->MsAntennaModel == 0)) {
//						if (p < numProcess / 2)
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//						else
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//					}
//					else if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 1)) {
//						if (u % 2 == 0)
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//						else
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//					}
//					else {
//						if ((u % 2 == 0) && (p < numProcess / 2))
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex) *exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//						else if ((u % 2 == 0) && (p >= numProcess / 2))
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp1(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//						else if ((u % 2 == 1) && (p >= numProcess / 2))
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//						else
//							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x1(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
//					}
//
//					MS[src]->channel->HtLOS(siIndex, processIndex)(u*numProcess + p, 0) = SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0);
//				}
//			}
//		}
//
//		//SI_H_t_los(0, 0).print();
//		//alpha_zero_temp(siIndex).print();
//
//		arma::field<arma::cx_mat> Alpha_nmup_temp = MS[src]->channel->Alpha_nmup_temp;
//		arma::field<arma::cx_mat> Alpha_nmup_temp1 = MS[src]->channel->Alpha_nmup_temp1;
//		arma::field<arma::cx_mat> Alpha_nmup_temp_x = MS[src]->channel->Alpha_nmup_temp_x;
//		arma::field<arma::cx_mat> Alpha_nmup_temp_x1 = MS[src]->channel->Alpha_nmup_temp_x1;
//		arma::Mat<int> NumRealCluseter = MS[src]->channel->NumRealCluseter;
//
//		for (int processIndex = 0; processIndex < numProcess; processIndex++) {
//			int clst = 0;
//			for (int n = 0; n < NumRealCluseter(dst); n++) {
//				for (int m = 0; m < 20; m++) {
//					for (int u = 0; u < numRxAntenna; u++) {
//						for (int p = 0; p < numPort; p++) {
//							if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 0)) {
//								if (n == 0 || n == 1) {
//									if (m < 10) {
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//									else if (m < 16) {
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//									else {
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								else { //n>=2
//									SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//									if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//										clst++;
//									}
//								}
//							}
//							else if ((Sim.channel->BsAntennaModel == 1) && (Sim.channel->MsAntennaModel == 0)) {
//								if (p < numPort / 2) {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								else {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//							}
//							else if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 1)) {
//								if (u % 2 == 0) {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								else {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//							}
//							else {
//								if ((u % 2 == 0) && (p < numPort / 2)) {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								else if ((u % 2 == 0) && (p >= numPort / 2)) {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								else if ((u % 2 == 1) && (p >= numPort / 2)) {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								else {
//									if (n == 0 || n == 1) {
//										if (m < 10) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else if (m < 16) {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//										else {
//											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//												clst++;
//											}
//										}
//									}
//									else { //n>=2
//										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
//										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
//											clst++;
//										}
//									}
//								}
//								//
//							}
//
//						}
//					}
//				}
//			}
//		}
//	}
//
//}
//
//void ApplyPathLossAndShadowing(int src) {
//	arma::cx_mat x(57, 1);
//	arma::cx_mat y(1, 1);
//	for (int si = 0; si < Sim.channel->NumberOfBS; si++) {
//		int dst = MS[src]->channel->BSindex(si);
//		//MS[src]->channel->BSindex.print();
//		//MS[src]->channel->Ht(si, 0).print();
//		y.zeros(1, 1);
//		for (int n = 0; n < MS[src]->channel->NumRealCluseter(dst); n++)
//		{
//			MS[src]->channel->Ht(si, 0, n) = (MS[src]->channel->CouplingLoss(dst)) * MS[src]->channel->Ht(si, 0, n);
//			y = y + MS[src]->channel->Ht(si, 0, n)*MS[src]->channel->Ht(si, 0, n).t();
//			//y = MS[src]->channel->Ht(si, 0, n)*MS[src]->channel->Ht(si, 0, n).t();
//			//y.print();
//		}
//
//		//MS[src]->channel->HtLOS(si,0) = (MS[src]->channel->CouplingLoss(dst)) * MS[src]->channel->HtLOS(si,0);
//		//cout << MS[src]->channel->channelCondition << endl;
//		//MS[src]->channel->HtLOS(si, 0).print();
//		//y = y+ MS[src]->channel->HtLOS(si, 0)*MS[src]->channel->HtLOS(si, 0).t();
//		x(si, 0) = y(0, 0);
//	}
//	//y = x(0, 0) /(sum(x)- x(0, 0));
//	//y.print();
//
//}
//
//void DftParameterSetting(int src)
//{
//
//	for (int si = 0; si < SLS_MAX_BS; si++)
//	{
//		int siIndex = MS[src]->channel->BSindex(si);
//
//		for (int c = 0; c < 50; c++)
//		{
//			MS[src]->channel->DftParameter(si, c).zeros(1, MAX_CLUSTER + 4);
//			int f = 213 + c * 12 + 6;
//			int abb1 = 0;
//			for (int n = 0; n < MS[src]->channel->NumRealCluseter(siIndex); n++) {
//				if (n == 0 || n == 1) {
//					std::complex<double> dft, dft1, dft2;
//					if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {
//						dft.real(0.0);
//						dft.imag(-2.0 * PI*double(f)*MS[src]->channel->tauLOS(siIndex)(n) * 15360000.0 / 1024.0);
//						dft1.real(0.0);
//						dft1.imag(-2.0 * PI*double(f)*(MS[src]->channel->tauLOS(siIndex)(n) + 5e-9) * 15360000.0 / 1024.0);
//						dft2.real(0.0);
//						dft2.imag(-2.0 * PI*double(f)*(MS[src]->channel->tauLOS(siIndex)(n) + 10e-9) * 15360000.0 / 1024.0);
//					}
//					else {
//						dft.real(0.0);
//						dft.imag(-2.0 * PI*double(f)*MS[src]->channel->tau(siIndex)(n) * 15360000.0 / 1024.0);
//						dft1.real(0.0);
//						dft1.imag(-2.0 * PI*double(f)*(MS[src]->channel->tau(siIndex)(n) + 5e-9) * 15360000.0 / 1024.0);
//						dft2.real(0.0);
//						dft2.imag(-2.0 * PI*double(f)*(MS[src]->channel->tau(siIndex)(n) + 10e-9) * 15360000.0 / 1024.0);
//					}
//					MS[src]->channel->DftParameter(si, c)(0, abb1) = exp(dft);
//					MS[src]->channel->DftParameter(si, c)(0, abb1 + 1) = exp(dft1);
//					MS[src]->channel->DftParameter(si, c)(0, abb1 + 2) = exp(dft2);
//					abb1 = abb1 + 3;
//				}
//				else {
//					std::complex<double> dft;
//					if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {
//						dft.real(0.0);
//						dft.imag(-2.0 * PI*double(f)*MS[src]->channel->tauLOS(siIndex)(n) * 15360000.0 / 1024.0);
//					}
//					else {
//						dft.real(0.0);
//						dft.imag(-2.0 * PI*double(f)*MS[src]->channel->tau(siIndex)(n) * 15360000.0 / 1024.0);
//					}
//					MS[src]->channel->DftParameter(si, c)(0, abb1) = exp(dft);
//					abb1 = abb1 + 1;
//				}
//			}
//		}
//	}
//
//}
//
//void DiscreteFourierTransform(int src)
//{
//	arma::cx_mat x(57, 1);
//	arma::cx_mat y;
//	arma::field<arma::cx_mat> exp_vt(MAX_CLUSTER + 4); // dft 용
//	arma::cx_mat h_k;
//	arma::cx_mat h_k1;
//	arma::cx_mat tmpp;
//	tmpp.zeros(Sim.channel->NumberOfRxAntenna*Sim.channel->NumberOfTransmitAntennaPort, 1);
//	std::complex<double> vt(0.0, 0.0);
//	for (int si = 0; si < SLS_MAX_BS; si++) {
//		y.zeros(1, 1);
//		h_k.zeros(Sim.channel->NumberOfRxAntenna*Sim.channel->NumberOfTransmitAntennaPort, MAX_CLUSTER + 4);
//		h_k1.zeros(Sim.channel->NumberOfRxAntenna*Sim.channel->NumberOfTransmitAntennaPort, MAX_CLUSTER + 4);
//		//int l_ = wrap(i, si/3);
//		int siIndex = MS[src]->channel->BSindex(si);
//		for (int pr = 0; pr < Sim.channel->NumberOfChannelProcess; pr++) {
//			for (int n = 0; n < MS[src]->channel->NumRealCluseter(siIndex); n++) {
//				exp_vt(n).zeros(20, 1);
//				for (int m = 0; m < 20; m++) {
//					vt.real(0.0);
//					vt.imag(2.0 * PI*MS[src]->channel->VelocityBS(siIndex)(n, m) * double(Sim.TTI) / 1000.0); //[si] 빼고
//					exp_vt[n](m, 0) = exp(vt);
//				}
//				//h_k.col(n) = MS[src]->channel->Ht[si, pr, n] * exp_vt[n];
//				//MS[src]->channel->Ht(si, pr, n).print();
//				h_k.col(n) = MS[src]->channel->Ht(si, pr, n) * exp_vt[n];
//				//y = y+ MS[src]->channel->Ht(si, pr, n)* MS[src]->channel->Ht(si, pr, n).t();
//				if (n == 0) //라이시안 부분 
//				{
//					vt.real(0.0);
//					vt.imag(2.0 * PI*MS[src]->channel->VelocityLOS[siIndex] * double(Sim.TTI) / 1000.0);
//					h_k.col(n) = h_k.col(n) + MS[src]->channel->HtLOS[si, pr] * exp(vt);
//					//h_k.col(n) = h_k.col(n) + MS[src]->channel->HtLOS(si, pr);
//				}
//			}
//			for (int c = 0; c < 50; c++) {
//				tmpp = MS[src]->channel->DftParameter(si, c) * strans(h_k);
//				MS[src]->channel->FrequencyChannel(si, pr, c).zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfTransmitAntennaPort);
//
//				for (int rx_ant = 0; rx_ant < Sim.channel->NumberOfRxAntenna; rx_ant++)
//				{
//					MS[src]->channel->FrequencyChannel(si, pr, c).row(rx_ant) = tmpp.submat(0, rx_ant*Sim.channel->NumberOfTransmitAntennaPort, 0, rx_ant*Sim.channel->NumberOfTransmitAntennaPort + Sim.channel->NumberOfTransmitAntennaPort - 1);
//				}
//			}
//		}
//	}
//
//}

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         Level 3 Functions                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SpatialChannel::Pathloss(int src, int dst, int type) {
	int channelModel = Sim.channel->ChannelModel;
	double distance2D, distance3D, srcZ;
	double indoorDistance2D, outdoorDistance2D, pathlossLOS, pathlossNLOS, gdistance2D, cdistance2D, losProbability;
	if (type == 0)
	{
		distance2D = MS[src]->channel->distance2D;
		distance3D = MS[src]->channel->distance3D;
		srcZ = MS[src]->network->pos3D(2);
		indoorDistance2D = MS[src]->network->indoorDistance2D; // indoor ue case 0~25, outdoor 0
	}
	else
	{
		distance2D = UMS[src]->channel->distance2D;
		distance3D = UMS[src]->channel->distance3D;
		srcZ = UMS[src]->network->pos3D(2);
		indoorDistance2D = UMS[src]->network->indoorDistance2D; // indoor ue case 0~25, outdoor 0
	}
	
	double dstZ = BS[dst]->network->pos3D(2);
	double breakPointDistance2D = 4.0 * (dstZ - 1.0) * (srcZ - 1.0) * (Sim.channel->NRuRLLC.carrierFrequency*1e9) / 3e8;

	// Indoor distance & Outdoor distance
	
	if (indoorDistance2D > distance2D) {
		outdoorDistance2D = 0;
		indoorDistance2D = distance2D;
	}
	else if (indoorDistance2D <= distance2D) {
		outdoorDistance2D = distance2D - indoorDistance2D;
	}

	// Pathloss model based on TR 38.901
	breakPointDistance2D = 4.0 * (dstZ - 1.0) * (srcZ - 1.0) * (Sim.channel->NRuRLLC.carrierFrequency*1e9) / 3e8;

	if (distance2D >= 10 && distance2D <= breakPointDistance2D) {
		pathlossLOS = 28.0 + 22.0 * log10(distance3D) + 20.0 * log10(Sim.channel->NRuRLLC.carrierFrequency);
	}
	else if (breakPointDistance2D < distance2D && distance2D < 5000.0) {
		pathlossLOS = 40.0 * log10(distance3D) + 28.0 + 20.0 * log10(Sim.channel->NRuRLLC.carrierFrequency) - 9.0 * log10(pow(breakPointDistance2D, 2.0) + pow((srcZ - dstZ), 2.0));
	}
	pathlossNLOS = 13.54 + 39.08 * log10(distance3D) + 20.0 * log10(Sim.channel->NRuRLLC.carrierFrequency) - 0.6 * (dstZ - 1.5);

	// LOS probability cacluation
	if (outdoorDistance2D <= 18)
		losProbability = 1;
	else
	{
		double C;
		if (dstZ <= 13)
			C = 0;
		else
			C = pow((dstZ - 13) / 10, 1.5);
		losProbability = 18.0 / outdoorDistance2D + exp(-outdoorDistance2D / 63.0) * (1 - (18.0 / outdoorDistance2D)) * (1 + C * 5 / 4 * pow(outdoorDistance2D / 100, 3) * exp(-outdoorDistance2D / 150));
	}
}

void SpatialChannel::Delay(int src, int type) {
	double riceanKdB, lsp2;
	int location, channelCondition;
	if (type == 0)
	{
		riceanKdB = MS[src]->channel->largeScaleParameter(1, 0);
		location = MS[src]->network->location;
		channelCondition = MS[src]->channel->channelCondition;
		lsp2 = MS[src]->channel->largeScaleParameter(2, 0);
	}
	else
	{
		riceanKdB = UMS[src]->channel->largeScaleParameter(1, 0);
		location = UMS[src]->network->location;
		channelCondition = UMS[src]->channel->channelCondition;
		lsp2 = UMS[src]->channel->largeScaleParameter(2, 0);
	}

	double riceanKfactorDependentScalingConstantdB = 0.7705 - 0.0433 *riceanKdB + 0.0002 * pow(riceanKdB, 2.0) + 0.000017 * pow(riceanKdB, 3.0);
	double temp;
	double rTau, numCluster;
	arma::mat tauPrime(UrbanMacroCellLOS.numberOfClusters, 1);
	arma::mat tau(UrbanMacroCellLOS.numberOfClusters, 1);
	temp = SLS_INFINITY;

	if ((location == Outdoor) && (channelCondition == LOS)) { // Outdoor LOS
		rTau = UrbanMacroCellLOS.delayScalingParameter;
		numCluster = UrbanMacroCellLOS.numberOfClusters;
	}
	else if ((location == Outdoor) && (channelCondition == NLOS)) {
		rTau = UrbanMacroCellNLOS.delayScalingParameter;
		numCluster = UrbanMacroCellNLOS.numberOfClusters;
	}
	else {
		rTau = UrbanMacroCellOtoI.delayScalingParameter;
		numCluster = UrbanMacroCellOtoI.numberOfClusters;
	}

	for (int n = 0; n < numCluster; n++) {

		tauPrime(n, 0) = -rTau * lsp2 * log(arma::randu<double>());

		double test = log(10);
		if (temp > tauPrime(n, 0))
			temp = tauPrime(n, 0);
	}

	for (int n = 0; n < numCluster; n++) {
		tau(n, 0) = tauPrime(n, 0) - temp;
	}

	arma::mat delay = arma::sort(tau, "ascend");

	if (type == 0)
	{
		MS[src]->channel->numCluster = numCluster;
		MS[src]->channel->delay = delay;
	}
	else
	{
		UMS[src]->channel->numCluster = numCluster;
		UMS[src]->channel->delay = delay;
	}
	
}

void SpatialChannel::ClusterPower(int src, int dst, int type) {
	int numRealCluster = 0;
	double numCluster,rTau, perClusterShadowingStd; // model specific parameter
	double riceanKdB, lsp2;
	int location, channelCondition;
	arma::mat delay;
	if (type == 0)
	{
		riceanKdB = MS[src]->channel->largeScaleParameter(1, 0);
		location = MS[src]->network->location;
		channelCondition = MS[src]->channel->channelCondition;
		lsp2 = MS[src]->channel->largeScaleParameter(2, 0);
		delay = MS[src]->channel->delay;
	}
	else
	{
		riceanKdB = UMS[src]->channel->largeScaleParameter(1, 0);
		location = UMS[src]->network->location;
		channelCondition = UMS[src]->channel->channelCondition;
		lsp2 = UMS[src]->channel->largeScaleParameter(2, 0);
		delay = UMS[src]->channel->delay;
	}
	double riceanKfactorDependentScalingConstantdB = 0.7705 - 0.0433 *riceanKdB + 0.0002 * pow(riceanKdB, 2.0) + 0.000017 * pow(riceanKdB, 3.0);
	double sumPowerPrime = 0.0;
	double maxClusterPower = 0.0;
	double kR = pow(10.0, riceanKdB / 10.0);
	// Load Channel model parameter
	if ((location == Outdoor) && (channelCondition == LOS)) {			// Outdoor LOS
		rTau = UrbanMacroCellLOS.delayScalingParameter;
		numCluster = UrbanMacroCellLOS.numberOfClusters;
		perClusterShadowingStd = UrbanMacroCellLOS.perClusterShadowing;
	}
	else if ((location == Outdoor) && (channelCondition == NLOS)) {	// Outdoor NLOS
		rTau = UrbanMacroCellNLOS.delayScalingParameter;
		numCluster = UrbanMacroCellNLOS.numberOfClusters;
		perClusterShadowingStd = UrbanMacroCellNLOS.perClusterShadowing;
	}
	else {																								// Indoor
		rTau = UrbanMacroCellOtoI.delayScalingParameter;
		numCluster = UrbanMacroCellOtoI.numberOfClusters;
		perClusterShadowingStd = UrbanMacroCellOtoI.perClusterShadowing;
	}
	arma::mat powerPrime(numCluster, 1);
	arma::mat delaysLOS(numCluster, 1);
	arma::mat clusterPower(numCluster, 1);
	arma::mat clusterPower1(numCluster, 1);
	arma::mat delayReduced(numCluster, 1);
	arma::mat delayLOSReduced(numCluster, 1);
	arma::mat clusterPowerReduced(numCluster, 1);  //Cluster power for equations in (7.3-9) and (7.3-14)
	arma::mat realClusterPowersForLOS(numCluster, 1); //Cluster power for equations in (7.3-22)
	
	for (int n = 0; n < numCluster; n++) {
		powerPrime[n] = exp(-delay(n,0) * (rTau - 1.0) / (rTau * lsp2)) * pow(10.0, -(perClusterShadowingStd * arma::randn()) / 10.0);
		if ((location == Outdoor) && (channelCondition == LOS)) // outdoor LOS인 경우
			delaysLOS[n] = delay[n] / riceanKfactorDependentScalingConstantdB;
		sumPowerPrime = sumPowerPrime + powerPrime[n];
	}
	
	for (int n = 0; n < numCluster; n++) {
		clusterPower1[n] = powerPrime[n] / sumPowerPrime;
		
		if ((location == Outdoor) && (channelCondition == LOS))
			clusterPower[n] = 1.0 / (kR + 1.0) * clusterPower1[n] + (n == 0) * kR / (kR + 1.0);
		else
			clusterPower[n] = clusterPower1[n];


		if (maxClusterPower < clusterPower[n])
			maxClusterPower = clusterPower[n];
	}
	
	for (int n = 0; n < numCluster; n++) {
		if (10.0*log10(clusterPower[n]) - 10.0*log10(maxClusterPower) < -25.0)
			clusterPower[n] = -100.0;

		if (clusterPower[n] != -100.0) {
			clusterPowerReduced[numRealCluster] = clusterPower[n];	//KR 적용한거
			realClusterPowersForLOS[numRealCluster] = clusterPower1[n]; //KR 적용안한거(뒤에서 쓸꺼)
			delayReduced[numRealCluster] = delay[n];
			delayLOSReduced[numRealCluster] = delaysLOS[n];
			numRealCluster++;
		}
	}
	if (type == 0)
	{
		MS[src]->channel->tau(dst) = delayReduced;
		MS[src]->channel->tauLOS(dst) = delayLOSReduced;
		MS[src]->channel->maxClusterPower = maxClusterPower;
		MS[src]->channel->numRealCluster = numRealCluster;
		MS[src]->channel->NumRealCluseter(dst, 0) = numRealCluster;
		MS[src]->channel->delayReduced = delayReduced;
		MS[src]->channel->clusterPowerReduced = clusterPowerReduced;
		MS[src]->channel->realClusterPowersForLOS = realClusterPowersForLOS;
	}
	else
	{
		UMS[src]->channel->tau(dst) = delayReduced;
		UMS[src]->channel->tauLOS(dst) = delayLOSReduced;
		UMS[src]->channel->maxClusterPower = maxClusterPower;
		UMS[src]->channel->numRealCluster = numRealCluster;
		UMS[src]->channel->NumRealCluseter(dst, 0) = numRealCluster;
		UMS[src]->channel->delayReduced = delayReduced;
		UMS[src]->channel->clusterPowerReduced = clusterPowerReduced;
		UMS[src]->channel->realClusterPowersForLOS = realClusterPowersForLOS;
	}
	
}

void SpatialChannel::ArrivalAndDepartureAngle(int src, int dst, int site, int sector, int type) {
	double riceanKdB, lsp2, maxClusterPower, distance2D;
	int location, channelCondition, numCluster, numRealCluster;
	arma::mat largeScaleParameter, wraparoundposBS, pos3D, clusterPowerReduced;
	
	if (type == 0)
	{
		largeScaleParameter = MS[src]->channel->largeScaleParameter;
		location = MS[src]->network->location;
		channelCondition = MS[src]->channel->channelCondition;
		lsp2 = MS[src]->channel->largeScaleParameter(2, 0);
		MS[src]->network->velocityHorizontal = (360 * arma::randu()*PI) / 180;
		MS[src]->network->velocityVertical = (90 * PI) / 180;
		pos3D = MS[src]->network->pos3D;
		wraparoundposBS = MS[src]->network->wraparoundposBS;
		numCluster = MS[src]->channel->numCluster;
		numRealCluster = MS[src]->channel->numRealCluster;
		maxClusterPower = MS[src]->channel->maxClusterPower;
		clusterPowerReduced = MS[src]->channel->clusterPowerReduced;
		MS[src]->channel->SmallScaleAOA.zeros(numRealCluster, 20); // n,m
		MS[src]->channel->SmallScaleAOD.zeros(numRealCluster, 20); // n,m
		MS[src]->channel->SmallScaleZOA.zeros(numRealCluster, 20); // n,m
		MS[src]->channel->SmallScaleZOD.zeros(numRealCluster, 20); // n,m
		distance2D = MS[src]->channel->distance2D;
	}
	else
	{
		largeScaleParameter = UMS[src]->channel->largeScaleParameter;
		location = UMS[src]->network->location;
		channelCondition = UMS[src]->channel->channelCondition;
		lsp2 = UMS[src]->channel->largeScaleParameter(2, 0);
		UMS[src]->network->velocityHorizontal = (360 * arma::randu()*PI) / 180;
		UMS[src]->network->velocityVertical = (90 * PI) / 180;
		pos3D = UMS[src]->network->pos3D;
		wraparoundposBS = UMS[src]->network->wraparoundposBS;
		numCluster = UMS[src]->channel->numCluster;
		numRealCluster = UMS[src]->channel->numRealCluster;
		maxClusterPower = UMS[src]->channel->maxClusterPower;
		clusterPowerReduced = UMS[src]->channel->clusterPowerReduced;
		UMS[src]->channel->SmallScaleAOA.zeros(numRealCluster, 20); // n,m
		UMS[src]->channel->SmallScaleAOD.zeros(numRealCluster, 20); // n,m
		UMS[src]->channel->SmallScaleZOA.zeros(numRealCluster, 20); // n,m
		UMS[src]->channel->SmallScaleZOD.zeros(numRealCluster, 20); // n,m
		distance2D = UMS[src]->channel->distance2D;
	}
	arma::mat departureAngleGCS(2, 1);
	arma::mat arrivalAngleGCS(2, 1);

	double cAOAAOD, cZOAZOD;
	double clusterASA, clusterASD, clusterZSA, muZSD, muOffsetZOD, muXPR, sigmaXPR;
	
	arma::mat subCluster0(1, 10);
	subCluster0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 19 << 20 << arma::endr;
	arma::mat subCluster1(1, 6);
	subCluster1 << 9 << 10 << 11 << 12 << 17 << 18 << arma::endr;
	arma::mat subCluster2(1, 4);
	subCluster2 << 13 << 14 << 15 << 16 << arma::endr;
	arma::mat wholeCluster(1, 20);
	wholeCluster << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << arma::endr;
	arma::mat offsetAngle(1, 20);
	offsetAngle << 0.0447 << -0.0447 << 0.1413 << -0.1413 << 0.2492 << -0.2492 << 0.3715 << -0.3715 << 0.5129 << -0.5129 << 0.6797 << -0.6797 << 0.8844 << -0.8844 << 1.1481 << -1.1481 << 1.5195 << -1.5195 << 2.1551 << -2.1551 << arma::endr;

	// Table 7.3-2 Scaling factors for AOA, AOD generation 
	arma::mat scalingFactorForAOAandAOD(2, 11);
	scalingFactorForAOAandAOD << 4 << 5 << 8 << 10 << 11 << 12 << 14 << 15 << 16 << 19 << 20 << arma::endr
		<< 0.779 << 0.860 << 1.018 << 1.090 << 1.123 << 1.146 << 1.190 << 1.211 << 1.226 << 1.273 << 1.289 << arma::endr;
	// Table 7.3-3 Scaling factors for ZOA, ZOD generation 
	arma::mat scalingFactorForZOAandZOD(2, 3);
	scalingFactorForZOAandZOD << 12 << 19 << 20 << arma::endr
		<< 1.104 << 1.184 << 1.178 << arma::endr;
	// Sector offset angle
	arma::mat alpha(3, 1);
	alpha << (PI / 180) * 30 << (PI / 180) * 150 << (PI / 180) *(-90) << arma::endr;

	// muOFFSEZZOD CLUSTERASA CLUSTERASD ZSA muZSD
	if ((location == Outdoor) && (channelCondition == LOS)) { // Outdoor LOS
		clusterASA = UrbanMacroCellLOS.cluserASA;
		clusterASD = UrbanMacroCellLOS.cluserASD;
		clusterZSA = UrbanMacroCellLOS.cluserZSA;
		muZSD = UrbanMacroCellLOS.muZSD;
		muOffsetZOD = 0.0;
		muXPR = UrbanMacroCellLOS.muXPR;
		sigmaXPR = UrbanMacroCellLOS.sigmaXPR;
	}
	else if ((location == Outdoor) && (channelCondition == NLOS)) {
		clusterASA = UrbanMacroCellNLOS.cluserASA;
		clusterASD = UrbanMacroCellNLOS.cluserASD;
		clusterZSA = UrbanMacroCellNLOS.cluserZSA;
		muZSD = UrbanMacroCellNLOS.muZSD;
		muOffsetZOD = -pow(10.0, (-0.62*log10(max(10.0, distance2D)) + 1.93 - 0.07*(abs(pos3D(2)) - 1.5)));
		muXPR = UrbanMacroCellNLOS.muXPR;
		sigmaXPR = UrbanMacroCellNLOS.sigmaXPR;
	}
	else if ((location == Indoor) && (channelCondition == LOS)) {
		clusterASA = UrbanMacroCellOtoI.cluserASA;
		clusterASD = UrbanMacroCellOtoI.cluserASD;
		clusterZSA = UrbanMacroCellOtoI.cluserZSA;
		muZSD = UrbanMacroCellOtoI.muZSD;
		muOffsetZOD = 0.0;
		muXPR = UrbanMacroCellOtoI.muXPR;
		sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
	}
	else {
		clusterASA = UrbanMacroCellOtoI.cluserASA;
		clusterASD = UrbanMacroCellOtoI.cluserASD;
		clusterZSA = UrbanMacroCellOtoI.cluserZSA;
		muZSD = UrbanMacroCellOtoI.muZSD;
		muOffsetZOD = -pow(10.0, (-0.62*log10(max(10.0, distance2D)) + 1.93 - 0.07*(abs(pos3D(2)) - 1.5)));
		muXPR = UrbanMacroCellOtoI.muXPR;
		sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
	}

	departureAngleGCS(0, 0) = AzimuthAngleOfGlobalCoordinateSystem(wraparoundposBS(site, 0), wraparoundposBS(site, 1), pos3D(0, 0), pos3D(0, 1));
	departureAngleGCS(1, 0) = ZenithAngleOfGlobalCoordinateSystem(wraparoundposBS(site, 0), wraparoundposBS(site, 1), wraparoundposBS(site, 2), pos3D(0, 0), pos3D(0, 1), pos3D(0, 2));

	arrivalAngleGCS(0, 0) = AzimuthAngleOfGlobalCoordinateSystem(pos3D(0, 0), pos3D(1), wraparoundposBS(site, 0), wraparoundposBS(site, 1));
	arrivalAngleGCS(1, 0) = ZenithAngleOfGlobalCoordinateSystem(pos3D(0), pos3D(1), pos3D(2), wraparoundposBS(site, 0), wraparoundposBS(site, 1), wraparoundposBS(site, 2));

	if (sector == 0) {
		arma::mat departureAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha0, Sim.network->beta, Sim.network->gamma, departureAngleGCS);
		arma::mat arrivalAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha0, Sim.network->beta, Sim.network->gamma, arrivalAngleGCS);
	}
	else if (sector == 1) {
		arma::mat departureAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha1, Sim.network->beta, Sim.network->gamma, departureAngleGCS);
		arma::mat arrivalAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha1, Sim.network->beta, Sim.network->gamma, arrivalAngleGCS);
	}
	else if (sector == 2) {
		arma::mat departureAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha2, Sim.network->beta, Sim.network->gamma, departureAngleGCS);
		arma::mat arrivalAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha2, Sim.network->beta, Sim.network->gamma, arrivalAngleGCS);
	}

	for (int m = 0; m < 11; m++) {
		if (numCluster == scalingFactorForAOAandAOD(0, m)) {
			cAOAAOD = scalingFactorForAOAandAOD(1, m);
		}
	}

	for (int m = 0; m < 3; m++) {
		if (numCluster == scalingFactorForZOAandZOD(0, m)) {
			cZOAZOD = scalingFactorForZOAandZOD(1, m);
		}
	}

	double K = largeScaleParameter(1, 0);
	if ((location == Outdoor) && (channelCondition == LOS)) {
		cAOAAOD = cAOAAOD * (1.1035 - 0.028 *K - 0.002 * pow(K, 2.0) + 0.0001 * pow(K, 3.0));
		cZOAZOD = cZOAZOD * (1.3086 + 0.0339 *K - 0.0077 * pow(K, 2.0) + 0.0002 * pow(K, 3.0));
	}

	double sigmaASA = largeScaleParameter(4, 0);
	double sigmaASD = largeScaleParameter(3, 0);
	double sigmaZSA = largeScaleParameter(6, 0);
	double sigmaZSD = largeScaleParameter(5, 0);
	double clusterZOA, clusterZOD, clusterAOA, clusterAOD;

	int abb = 0;
	arma::mat piAOAPrime(numRealCluster, 1);
	arma::mat piAODPrime(numRealCluster, 1);
	arma::mat thetaZOAPrime(numRealCluster, 1);
	arma::mat thetaZODPrime(numRealCluster, 1);

	arma::mat thetaRxRay(1, 20);
	arma::mat piRxRay(1, 20);
	arma::mat thetaTxRay(1, 20);
	arma::mat piTxRay(1, 20);

	arma::mat RayAOAtemp(1, 20);
	arma::mat RayAODtemp(1, 20);
	arma::mat RayZOAtemp(1, 20);
	arma::mat RayZODtemp(1, 20);
	
	arma::mat RayAOA(20, 1);
	arma::mat RayAOD(20, 1);
	arma::mat RayZOA(20, 1);
	arma::mat RayZOD(20, 1);

	arma::mat xAOA(20, 1);
	arma::mat xAOD(20, 1);
	arma::mat xZOA(20, 1);
	arma::mat xZOD(20, 1);
	arma::mat yAOA(20, 1);
	arma::mat yAOD(20, 1);
	arma::mat yZOA(20, 1);
	arma::mat yZOD(20, 1);

	arma::mat SmallScaleAOA, SmallScaleAOD, SmallScaleZOA, SmallScaleZOD;

	SmallScaleAOA.zeros(numRealCluster,20); // n,m
	SmallScaleAOD.zeros(numRealCluster, 20); // n,m
	SmallScaleZOA.zeros(numRealCluster, 20); // n,m
	SmallScaleZOD.zeros(numRealCluster, 20); // n,m

	for (int n = 0; n < numRealCluster; n++) {
		piAOAPrime(n, 0) = (2.0 * (sigmaASA / 1.4) * sqrt(-log(clusterPowerReduced(n, 0) / maxClusterPower))) / cAOAAOD;
		piAODPrime(n, 0) = (2.0 * (sigmaASD / 1.4) * sqrt(-log(clusterPowerReduced(n, 0) / maxClusterPower))) / cAOAAOD;
		thetaZOAPrime(n, 0) = (-sigmaZSA * log(clusterPowerReduced(n, 0) / maxClusterPower)) / cZOAZOD;
		thetaZODPrime(n, 0) = (-sigmaZSD * log(clusterPowerReduced(n, 0) / maxClusterPower)) / cZOAZOD;
		
		// Random Coupling
		if (n == 0 || n == 1) {
			arma::mat thetaRayRxTemp0 = subCluster0;
			thetaRayRxTemp0 = shuffle(thetaRayRxTemp0, 1);
			arma::mat thetaRayRxTemp1 = subCluster1;
			thetaRayRxTemp1 = shuffle(thetaRayRxTemp1, 1);
			arma::mat thetaRayRxTemp2 = subCluster2;
			thetaRayRxTemp2 = shuffle(thetaRayRxTemp2, 1);

			arma::mat thetaRayTxTemp0 = subCluster0;
			thetaRayTxTemp0 = shuffle(thetaRayTxTemp0, 1);
			arma::mat thetaRayTxTemp1 = subCluster1;
			thetaRayTxTemp1 = shuffle(thetaRayTxTemp1, 1);
			arma::mat thetaRayTxTemp2 = subCluster2;
			thetaRayTxTemp2 = shuffle(thetaRayTxTemp2, 1);

			arma::mat piRayRxTemp0 = subCluster0;
			piRayRxTemp0 = shuffle(piRayRxTemp0, 1);
			arma::mat piRayRxTemp1 = subCluster1;
			piRayRxTemp1 = shuffle(piRayRxTemp1, 1);
			arma::mat piRayRxTemp2 = subCluster2;
			piRayRxTemp2 = shuffle(piRayRxTemp2, 1);

			arma::mat piRayTxTemp0 = subCluster0;
			piRayTxTemp0 = shuffle(piRayTxTemp0, 1);
			arma::mat piRayTxTemp1 = subCluster1;
			piRayTxTemp1 = shuffle(piRayTxTemp1, 1);
			arma::mat piRayTxTemp2 = subCluster2;
			piRayTxTemp2 = shuffle(piRayTxTemp2, 1);


			for (int numRay = 0; numRay < 20; numRay++) {
				if (numRay < 10) {
					thetaRxRay[numRay] = thetaRayRxTemp0[numRay] - 1;
					thetaTxRay[numRay] = thetaRayTxTemp0[numRay] - 1;
					piRxRay[numRay] = piRayRxTemp0[numRay] - 1;
					piTxRay[numRay] = piRayTxTemp0[numRay] - 1;

				}
				else if (numRay >= 10 && numRay < 16) {
					thetaRxRay[numRay] = thetaRayRxTemp1[numRay - 10] - 1;
					thetaTxRay[numRay] = thetaRayTxTemp1[numRay - 10] - 1;
					piRxRay[numRay] = piRayRxTemp1[numRay - 10] - 1;
					piTxRay[numRay] = piRayTxTemp1[numRay - 10] - 1;
				}
				else {
					thetaRxRay[numRay] = thetaRayRxTemp2[numRay - 16] - 1;
					thetaTxRay[numRay] = thetaRayTxTemp2[numRay - 16] - 1;
					piRxRay[numRay] = piRayRxTemp2[numRay - 16] - 1;
					piTxRay[numRay] = piRayTxTemp2[numRay - 16] - 1;
				}
			}
		}


		else { // n >=2
			arma::mat thetaRayRxTemp3 = wholeCluster;
			thetaRayRxTemp3 = shuffle(thetaRayRxTemp3, 1);
			arma::mat thetaRayTxTemp3 = wholeCluster;
			thetaRayTxTemp3 = shuffle(thetaRayTxTemp3, 1);
			arma::mat piRayRxTemp3 = wholeCluster;
			piRayRxTemp3 = shuffle(piRayRxTemp3, 1);
			arma::mat piRayTxTemp3 = wholeCluster;
			piRayTxTemp3 = shuffle(piRayTxTemp3, 1);


			for (int numRay = 0; numRay < 20; numRay++) {
				thetaRxRay[numRay] = thetaRayRxTemp3[numRay] - 1;
				thetaTxRay[numRay] = thetaRayTxTemp3[numRay] - 1;
				piRxRay[numRay] = piRayRxTemp3[numRay] - 1;
				piTxRay[numRay] = piRayTxTemp3[numRay] - 1;

			}
		}

		xAOA[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		xAOD[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		xZOA[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		xZOD[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		yAOA[n] = arma::randn() * (largeScaleParameter(4, 0) / 7.0);
		yAOD[n] = arma::randn() * (largeScaleParameter(3, 0) / 7.0);
		yZOA[n] = arma::randn() * (largeScaleParameter(6, 0) / 7.0);
		yZOD[n] = arma::randn() * (largeScaleParameter(5, 0) / 7.0);


		// muOFFSEZZOD CLUSTERASA CLUSTERASD ZSA muZSD

		if ((location == Outdoor) && (channelCondition == LOS)) {
			clusterAOA = (xAOA[n] * piAOAPrime[n] + yAOA[n]) - (xAOA[0] * piAOAPrime[0] + yAOA[0] - (arrivalAngleGCS(0, 0)*180.0 / PI));
			clusterAOD = (xAOD[n] * piAODPrime[n] + yAOD[n]) - (xAOD[0] * piAODPrime[0] + yAOD[0] - (departureAngleGCS(0, 0)*180.0 / PI));
			clusterZOA = (xZOA[n] * thetaZOAPrime[n] + yZOA[n]) - (xZOA[0] * thetaZOAPrime[0] + yZOA[0] - ((PI - arrivalAngleGCS(1, 0))*180.0 / PI));
			clusterZOD = (xZOD[n] * thetaZODPrime[n] + yZOD[n]) - (xZOD[0] * thetaZODPrime[0] + yZOD[0] - (departureAngleGCS(1, 0)*180.0 / PI));
		}
		else  {
			clusterAOA = xAOA[n] * piAOAPrime[n] + yAOA[n] + (arrivalAngleGCS(0, 0)*180.0 / PI);
			clusterAOD = xAOD[n] * piAODPrime[n] + yAOD[n] + (departureAngleGCS(0, 0)*180.0 / PI);
			clusterZOA = xZOA[n] * thetaZOAPrime[n] + yZOA[n] + ((PI - arrivalAngleGCS(1, 0))*180.0 / PI);
			clusterZOD = xZOD[n] * thetaZODPrime[n] + yZOD[n] + (departureAngleGCS(1, 0)*180.0 / PI) + muOffsetZOD;
		}
		if ((location == Indoor) && (channelCondition == LOS) || (location == Indoor) && (channelCondition == NLOS))
			clusterZOA = xZOA[n] * thetaZOAPrime[n] + yZOA[n] + 90.0;

		for (int m = 0; m < 20; m++) {
			RayAOD(m) = Modulo((clusterAOD + clusterASD * offsetAngle[m]), 360.0);
			RayZOD(m) = Modulo((clusterZOD + (3.0 / 8.0) * pow(10.0, muZSD) * offsetAngle[m]), 360.0);

			RayAOA(m) = Modulo((clusterAOA + clusterASA * offsetAngle[m]), 360.0);
			RayZOA(m) = Modulo((clusterZOA + clusterZSA * offsetAngle[m]), 360.0);

			if (RayAOA(m) >= 180.0 && RayAOA(m) <= 360.0)
				RayAOA(m) = -360.0 + RayAOA(m);
			if (RayAOD(m) >= 180.0 && RayAOD(m) <= 360.0)
				RayAOD(m) = -360.0 + RayAOD(m);
			if (RayZOA(m) >= 180.0 && RayZOA(m) <= 360.0)
				RayZOA(m) = 360.0 - RayZOA(m);
			if (RayZOD(m) >= 180.0 && RayZOD(m) <= 360.0)
				RayZOD(m) = 360.0 - RayZOD(m);
		}

		for (int m = 0; m < 20; m++) {
			RayAOAtemp(m) = RayAOA[piRxRay[m]];
			RayAODtemp[m] = RayAOD[piTxRay[m]];
			RayZOAtemp[m] = RayZOA[thetaRxRay[m]];
			RayZODtemp[m] = RayZOD[thetaTxRay[m]];
		}

		for (int m = 0; m < 20; m++) {
			RayAOA(m) = RayAOAtemp[m];
			RayAOD(m) = RayAODtemp[m];
			RayZOA(m) = RayZOAtemp[m];
			RayZOD(m) = RayZODtemp[m];
		}

		if (type == 0)
		{
			MS[src]->channel->GCSAOA = arrivalAngleGCS(0, 0);
			MS[src]->channel->GCSAOD = departureAngleGCS(0, 0);
			MS[src]->channel->GCSZOA = arrivalAngleGCS(1, 0);
			MS[src]->channel->GCSZOD = departureAngleGCS(1, 0);
			MS[src]->channel->AnalogBeamPhase.zeros(2);
			MS[src]->channel->DigitalBeamPhase.zeros(2);
			MS[src]->channel->BeamAmplitude.zeros(2);

			MS[src]->channel->AnalogBeamPhase(1) = MS[src]->channel->GCSZOD;
			MS[src]->channel->AnalogBeamPhase(0) = MS[src]->channel->GCSZOA;
			MS[src]->channel->DigitalBeamPhase(1) = MS[src]->channel->GCSAOD;
			MS[src]->channel->DigitalBeamPhase(0) = MS[src]->channel->GCSAOD;

			MS[src]->channel->SmallScaleAOA.row(n) = RayAOAtemp;
			MS[src]->channel->SmallScaleAOD.row(n) = RayAODtemp;
			MS[src]->channel->SmallScaleZOA.row(n) = RayZOAtemp;
			MS[src]->channel->SmallScaleZOD.row(n) = RayZODtemp;
		}
		else
		{
			UMS[src]->channel->GCSAOA = arrivalAngleGCS(0, 0);
			UMS[src]->channel->GCSAOD = departureAngleGCS(0, 0);
			UMS[src]->channel->GCSZOA = arrivalAngleGCS(1, 0);
			UMS[src]->channel->GCSZOD = departureAngleGCS(1, 0);
			UMS[src]->channel->AnalogBeamPhase.zeros(2);
			UMS[src]->channel->DigitalBeamPhase.zeros(2);
			UMS[src]->channel->BeamAmplitude.zeros(2);

			UMS[src]->channel->AnalogBeamPhase(1) = UMS[src]->channel->GCSZOD;
			UMS[src]->channel->AnalogBeamPhase(0) = UMS[src]->channel->GCSZOA;
			UMS[src]->channel->DigitalBeamPhase(1) = UMS[src]->channel->GCSAOD;
			UMS[src]->channel->DigitalBeamPhase(0) = UMS[src]->channel->GCSAOD;

			UMS[src]->channel->SmallScaleAOA.row(n) = RayAOAtemp;
			UMS[src]->channel->SmallScaleAOD.row(n) = RayAODtemp;
			UMS[src]->channel->SmallScaleZOA.row(n) = RayZOAtemp;
			UMS[src]->channel->SmallScaleZOD.row(n) = RayZODtemp;
		}

		

	}
}
 
void SpatialChannel::ArrivalAndDepartureAntennaGain(int src, int dst, int site, int sector, int type) {
	double riceanKdB, lsp2, maxClusterPower;
	int location, channelCondition, numCluster, numRealCluster;
	arma::mat largeScaleParameter, wraparoundposBS, pos3D, clusterPowerReduced;

	if (type == 0)
	{
		largeScaleParameter = MS[src]->channel->largeScaleParameter;
		location = MS[src]->network->location;
		channelCondition = MS[src]->channel->channelCondition;
		lsp2 = MS[src]->channel->largeScaleParameter(2, 0);
		MS[src]->network->velocityHorizontal = (360 * arma::randu()*PI) / 180;
		MS[src]->network->velocityVertical = (90 * PI) / 180;
		pos3D = MS[src]->network->pos3D;
		wraparoundposBS = MS[src]->network->wraparoundposBS;
		numCluster = MS[src]->channel->numCluster;
		numRealCluster = MS[src]->channel->numRealCluster;
		maxClusterPower = MS[src]->channel->maxClusterPower;
		clusterPowerReduced = MS[src]->channel->clusterPowerReduced;
		MS[src]->channel->SmallScaleReceiverAntennaGainUH.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleReceiverAntennaGainUV.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleReceiverAntennaGainXH.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleReceiverAntennaGainXV.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleTransmitterAntennaGainUH.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleTransmitterAntennaGainUV.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleTransmitterAntennaGainXH.zeros(numRealCluster, 20);
		MS[src]->channel->SmallScaleTransmitterAntennaGainXV.zeros(numRealCluster, 20);
	}
	else
	{
		largeScaleParameter = UMS[src]->channel->largeScaleParameter;
		location = UMS[src]->network->location;
		channelCondition = UMS[src]->channel->channelCondition;
		lsp2 = UMS[src]->channel->largeScaleParameter(2, 0);
		UMS[src]->network->velocityHorizontal = (360 * arma::randu()*PI) / 180;
		UMS[src]->network->velocityVertical = (90 * PI) / 180;
		pos3D = UMS[src]->network->pos3D;
		wraparoundposBS = UMS[src]->network->wraparoundposBS;
		numCluster = UMS[src]->channel->numCluster;
		numRealCluster = UMS[src]->channel->numRealCluster;
		maxClusterPower = UMS[src]->channel->maxClusterPower;
		clusterPowerReduced = UMS[src]->channel->clusterPowerReduced;
		UMS[src]->channel->SmallScaleReceiverAntennaGainUH.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleReceiverAntennaGainUV.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleReceiverAntennaGainXH.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleReceiverAntennaGainXV.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleTransmitterAntennaGainUH.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleTransmitterAntennaGainUV.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleTransmitterAntennaGainXH.zeros(numRealCluster, 20);
		UMS[src]->channel->SmallScaleTransmitterAntennaGainXV.zeros(numRealCluster, 20);
	}

	int numProcess = Sim.channel->NumberOfChannelProcess;
	int numRxAntenna = Sim.channel->NumberOfReceiveAntennaPort;
	int	numTxHorizontalAntenna= Sim.channel->NumberOfTxHorizontalAntenna;
	int numTxVerticalAntenna= Sim.channel->numberOfTxVerticalAntenna;
	int numTxPort= Sim.channel->NumberOfTransmitAntennaPort;
	double zetaRx1, zetaRx2, zetaTx1, zetaTx2;
	
	arma::mat SmallScaleReceiverAntennaGainUH, SmallScaleReceiverAntennaGainUV, SmallScaleReceiverAntennaGainXH, SmallScaleReceiverAntennaGainXV, SmallScaleTransmitterAntennaGainUH, SmallScaleTransmitterAntennaGainUV, SmallScaleTransmitterAntennaGainXH, SmallScaleTransmitterAntennaGainXV;

	SmallScaleReceiverAntennaGainUH.zeros(numRealCluster, 20);
	SmallScaleReceiverAntennaGainUV.zeros(numRealCluster, 20);
	SmallScaleReceiverAntennaGainXH.zeros(numRealCluster, 20);
	SmallScaleReceiverAntennaGainXV.zeros(numRealCluster, 20);
	SmallScaleTransmitterAntennaGainUH.zeros(numRealCluster, 20);
	SmallScaleTransmitterAntennaGainUV.zeros(numRealCluster, 20);
	SmallScaleTransmitterAntennaGainXH.zeros(numRealCluster, 20);
	SmallScaleTransmitterAntennaGainXV.zeros(numRealCluster, 20);
	
	arma::mat alpha(3, 1);
	alpha << (PI / 180) * 30 << (PI / 180) * 150 << (PI / 180) *(-90) << arma::endr;
	double  beta = 0.0;
	double gamma = 0.0;

	// Antenna configuration zeta1, zeta2
	if (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray) {
		zetaRx1 = 0.0;
		zetaRx2 = 0.0;
	}
	else if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) {
		zetaRx1 = 0.0;
		zetaRx2 = PI / 2;
	}
	if (Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) {
		zetaTx1 = 0.0;
		zetaTx2 = 0.0;
	}
	else if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) {
		zetaTx1 = -PI / 4;
		zetaTx2 = PI / 4;
	}

	arma::mat receiveAngle(2, 1);
	arma::mat transmitAngle(2, 1);

	arma::mat transmitAngleLOS(2, 1);
	arma::mat receiverAngleLOS(2, 1);
	if (type == 0)
	{
		transmitAngleLOS(0, 0) = MS[src]->channel->GCSAOD;
		transmitAngleLOS(1, 0) = MS[src]->channel->GCSZOD;
		receiverAngleLOS(0, 0) = MS[src]->channel->GCSAOA;
		receiverAngleLOS(1, 0) = MS[src]->channel->GCSZOA;
	}
	else
	{
		transmitAngleLOS(0, 0) = UMS[src]->channel->GCSAOD;
		transmitAngleLOS(1, 0) = UMS[src]->channel->GCSZOD;
		receiverAngleLOS(0, 0) = UMS[src]->channel->GCSAOA;
		receiverAngleLOS(1, 0) = UMS[src]->channel->GCSZOA;
	}

	arma::mat ReceiverAntennaGainXLOS;
	arma::mat ReceiverAntennaGainULOS = ReceiverAntennaGain(src,zetaRx1, receiverAngleLOS, type);
	if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) ReceiverAntennaGainXLOS = ReceiverAntennaGain(src, zetaRx2, receiverAngleLOS, type);
	arma::cx_mat f_prd_LOS = exp_F_prd(src, alpha[sector], beta, gamma, transmitAngleLOS * 180 / PI, numTxHorizontalAntenna, numTxVerticalAntenna, numTxPort);
	arma::cx_mat f_urd_LOS = exp_F_urd(src, receiverAngleLOS * 180 / PI, numRxAntenna, type);

	if (type == 0)
	{
		MS[src]->channel->F_prd_LOS(dst, 0) = f_prd_LOS;
		MS[src]->channel->F_urd_LOS(dst, 0) = f_urd_LOS;
	}
	else
	{
		UMS[src]->channel->F_prd_LOS(dst, 0) = f_prd_LOS;
		UMS[src]->channel->F_urd_LOS(dst, 0) = f_urd_LOS;
	}
	
	arma::cx_mat TransmitterAntennaGainXLOS;
	arma::cx_mat TransmitterAntennaGainULOS;
	for (int processIndex = 0; processIndex < numProcess; processIndex++) {
		TransmitterAntennaGainULOS = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx1, transmitAngleLOS, dst, numProcess);
		if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) TransmitterAntennaGainXLOS = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx2, transmitAngleLOS, dst, numProcess);
	}

// Save
	if (type == 0)
	{
		MS[src]->channel->ReceiverAntennaGainLOSUH = ReceiverAntennaGainULOS(0, 0);
		MS[src]->channel->ReceiverAntennaGainLOSUV = ReceiverAntennaGainULOS(1, 0);

		if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization)
		{
			MS[src]->channel->ReceiverAntennaGainLOSXH = ReceiverAntennaGainXLOS(0, 0);
			MS[src]->channel->ReceiverAntennaGainLOSXV = ReceiverAntennaGainXLOS(1, 0);
		}

		MS[src]->channel->TransmitterAntennaGainLOSUH = TransmitterAntennaGainULOS(0, 0);
		MS[src]->channel->TransmitterAntennaGainLOSUV = TransmitterAntennaGainULOS(1, 0);

		if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization)
		{
			MS[src]->channel->TransmitterAntennaGainLOSXH = TransmitterAntennaGainXLOS(0, 0);
			MS[src]->channel->TransmitterAntennaGainLOSXV = TransmitterAntennaGainXLOS(1, 0);
		}
	}
	else
	{
		UMS[src]->channel->ReceiverAntennaGainLOSUH = ReceiverAntennaGainULOS(0, 0);
		UMS[src]->channel->ReceiverAntennaGainLOSUV = ReceiverAntennaGainULOS(1, 0);

		if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization)
		{
			UMS[src]->channel->ReceiverAntennaGainLOSXH = ReceiverAntennaGainXLOS(0, 0);
			UMS[src]->channel->ReceiverAntennaGainLOSXV = ReceiverAntennaGainXLOS(1, 0);
		}

		UMS[src]->channel->TransmitterAntennaGainLOSUH = TransmitterAntennaGainULOS(0, 0);
		UMS[src]->channel->TransmitterAntennaGainLOSUV = TransmitterAntennaGainULOS(1, 0);

		if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization)
		{
			UMS[src]->channel->TransmitterAntennaGainLOSXH = TransmitterAntennaGainXLOS(0, 0);
			UMS[src]->channel->TransmitterAntennaGainLOSXV = TransmitterAntennaGainXLOS(1, 0);
		}
	}

	for (int n = 0; n < numRealCluster; n++) {
		for (int m = 0; m < 20; m++) {

			if (type == 0)
			{
				receiveAngle(0, 0) = MS[src]->channel->SmallScaleAOA(n, m);
				receiveAngle(1, 0) = MS[src]->channel->SmallScaleZOA(n, m);
				receiveAngle = receiveAngle*PI / 180.0;

				transmitAngle(0, 0) = MS[src]->channel->SmallScaleAOD(n, m);
				transmitAngle(1, 0) = MS[src]->channel->SmallScaleZOD(n, m);
			}
			else
			{
				receiveAngle(0, 0) = UMS[src]->channel->SmallScaleAOA(n, m);
				receiveAngle(1, 0) = UMS[src]->channel->SmallScaleZOA(n, m);
				receiveAngle = receiveAngle*PI / 180.0;

				transmitAngle(0, 0) = UMS[src]->channel->SmallScaleAOD(n, m);
				transmitAngle(1, 0) = UMS[src]->channel->SmallScaleZOD(n, m);
			}
			//transmitAngle = transmitAngle*PI / 180.0;

			arma::mat antennaGainRxSmallX;
			arma::mat antennaGainRxSmallU = ReceiverAntennaGain(src, zetaRx1, receiveAngle, type);
			if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) antennaGainRxSmallX = ReceiverAntennaGain(src, zetaRx2, receiveAngle, type);

			if (type == 0)
			{
				MS[src]->channel->SmallScaleReceiverAntennaGainUH(n, m) = antennaGainRxSmallU(0, 0);
				MS[src]->channel->SmallScaleReceiverAntennaGainUV(n, m) = antennaGainRxSmallU(1, 0);

				if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) {
					MS[src]->channel->SmallScaleReceiverAntennaGainXH(n, m) = antennaGainRxSmallX(0, 0);
					MS[src]->channel->SmallScaleReceiverAntennaGainXV(n, m) = antennaGainRxSmallX(1, 0);
				}

				MS[src]->channel->F_urd(n, m) = exp_F_urd(src, receiveAngle*(180 / PI), numRxAntenna, type);
				MS[src]->channel->F_urd_BS(dst, n, m) = MS[src]->channel->F_urd(n, m);
				MS[src]->channel->F_prd(n, m) = exp_F_prd(src, alpha[sector], 0.0, 0.0, transmitAngle *PI / 180.0, numTxHorizontalAntenna, numTxVerticalAntenna, numTxPort);
				MS[src]->channel->F_prd_BS(dst, n, m) = MS[src]->channel->F_prd(n, m);
			}
			else
			{
				UMS[src]->channel->SmallScaleReceiverAntennaGainUH(n, m) = antennaGainRxSmallU(0, 0);
				UMS[src]->channel->SmallScaleReceiverAntennaGainUV(n, m) = antennaGainRxSmallU(1, 0);

				if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) {
					UMS[src]->channel->SmallScaleReceiverAntennaGainXH(n, m) = antennaGainRxSmallX(0, 0);
					UMS[src]->channel->SmallScaleReceiverAntennaGainXV(n, m) = antennaGainRxSmallX(1, 0);
				}

				UMS[src]->channel->F_urd(n, m) = exp_F_urd(src, receiveAngle*(180 / PI), numRxAntenna, type);
				UMS[src]->channel->F_urd_BS(dst, n, m) = UMS[src]->channel->F_urd(n, m);
				UMS[src]->channel->F_prd(n, m) = exp_F_prd(src, alpha[sector], 0.0, 0.0, transmitAngle *PI / 180.0, numTxHorizontalAntenna, numTxVerticalAntenna, numTxPort);
				UMS[src]->channel->F_prd_BS(dst, n, m) = UMS[src]->channel->F_prd(n, m);
			}

			arma::cx_mat antennaGainTxSmallX;
			for (int indexProcess = 0; indexProcess < numProcess; indexProcess++) {
				arma::cx_mat antennaGainTxSmallU = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx1, transmitAngle *PI / 180.0, dst, numProcess);
				if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) antennaGainTxSmallX = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx1, transmitAngle *PI / 180.0, dst, numProcess);
			
				if (type == 0)
				{
					MS[src]->channel->SmallScaleTransmitterAntennaGainUH(n, m) = antennaGainTxSmallU(0, 0);
					MS[src]->channel->SmallScaleTransmitterAntennaGainUV(n, m) = antennaGainTxSmallU(1, 0);

					if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) {
						MS[src]->channel->SmallScaleTransmitterAntennaGainXH(n, m) = antennaGainTxSmallX(0, 0);
						MS[src]->channel->SmallScaleTransmitterAntennaGainXV(n, m) = antennaGainTxSmallX(1, 0);
					}
				}
				else
				{
					UMS[src]->channel->SmallScaleTransmitterAntennaGainUH(n, m) = antennaGainTxSmallU(0, 0);
					UMS[src]->channel->SmallScaleTransmitterAntennaGainUV(n, m) = antennaGainTxSmallU(1, 0);

					if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) {
						UMS[src]->channel->SmallScaleTransmitterAntennaGainXH(n, m) = antennaGainTxSmallX(0, 0);
						UMS[src]->channel->SmallScaleTransmitterAntennaGainXV(n, m) = antennaGainTxSmallX(1, 0);
					}
				}
			}
		}
	}

}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         Level 4 Functions                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

double SpatialChannel::Distance2D(double srcX, double srcY, double dstX, double dstY) {
	double distance2D;

	distance2D = sqrt(pow((dstX - srcX), 2) + pow((dstY - srcY), 2));

	return distance2D;
}

double SpatialChannel::Distance3D(double srcX, double srcY, double srcZ, double dstX, double dstY, double dstZ) {
	double distance3D;

	distance3D = sqrt(pow((dstX - srcX), 2) + pow((dstY - srcY), 2) + pow((dstZ - srcZ), 2));

	return distance3D;
}

double SpatialChannel::AzimuthAngleOfGlobalCoordinateSystem(double srcX, double srcY, double dstX, double dstY) {
	double azimuthAngle;

	azimuthAngle = atan2(dstY-srcY,dstX-srcX);

	return azimuthAngle;
}

double SpatialChannel::ZenithAngleOfGlobalCoordinateSystem(double srcX, double srcY, double srcZ, double dstX, double dstY, double dstZ){
	double zenithAngle;

	zenithAngle = atan2(Distance2D(srcX, srcY, dstX, dstY), dstZ - srcZ);

	return zenithAngle;
}

arma::mat SpatialChannel::GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(double alpha, double beta, double gamma, arma::mat angleGCS){ //GCS to LCS angle A Z / H V / pi theta
	arma::mat angleLCS(2,1);
	
	double pi = angleGCS(0, 0);		// ahpi
	double theta = angleGCS(1, 0);	// zvth
	angleLCS(1,0) = acosl(cos(beta) * cos(gamma) * cos(theta) + (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*sin(theta));
	angleLCS(0,0) = atan2l((cos(beta)*sin(gamma)*cos(theta) + (sin(beta)*sin(gamma)*cos(pi - alpha) + cos(gamma)*sin(pi - alpha))*sin(theta)), (cos(beta)*sin(theta)*cos(pi - alpha) - sin(beta)*cos(theta)));

	return angleLCS;
}

arma::mat SpatialChannel::LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(double alpha, double beta, double gamma, double theta, double pi, arma::mat antennaGain) { // LCS to GCS antenna gain
	arma::mat antennaGainGCS(2, 1);
	arma::mat psi(2,1);

	psi(0,0) = (cos(beta)*cos(gamma)*sin(theta) - (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*cos(theta)) / sqrt(1.0 - pow(cos(beta)*cos(gamma)*cos(theta) + (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*sin(theta), 2)); // cos psi
	psi(1,0) = (sin(beta)*cos(gamma)*sin(pi - alpha) + sin(gamma)*cos(pi - alpha)) / sqrt(1.0 - pow(cos(beta)*cos(gamma)*cos(theta) + (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*sin(theta), 2));												  // sin psi

	antennaGainGCS(1, 0) = psi(0, 0) * antennaGain(1, 0) - psi(1, 0) *antennaGain(0, 0);
	antennaGainGCS(0, 0) = psi(1, 0) * antennaGain(1, 0) + psi(0, 0) * antennaGain(0, 0);

	return antennaGainGCS;
}

double SpatialChannel::AntennaGain(arma::mat angleLCS) // 0 H 1 V
{
//	double antennaGainVertical;
//	double antennaGainHorizontal;angleLCS(0,0)angleLCS(1,0)
//	double antennaGainCombined;

//	antennaGainVertical = -min( 12 * pow( ( ((angleLCS(1, 0)*180.0 / PI) - 90.0) / 65.0), 2)  ,              30.0);
//	antennaGainHorizontal = -min(12 * pow( ( (angleLCS(0, 0)*180.0 / PI) / 65.0)        , 2)  ,              30.0);
//	antennaGainCombined = (8 - min(-(antennaGainVertical + antennaGainHorizontal), 30.0));
//	return antennaGainCombined;
	double antennaGainVertical = -min(12 * pow(((angleLCS(1,0)*180.0 / PI - 90.0) / 65.0), 2), 30.0);
	double antennaGainHorizontal = -min(12 * pow(((angleLCS(0,0)*180.0 / PI) / 65.0), 2), 30.0);
	double antennaGainCombined = (8 - min(-(antennaGainVertical + antennaGainHorizontal), 30.0));
	return antennaGainCombined;
	
}

double SpatialChannel::Modulo(double a, double b) {
	if (b == 0)
	{
		return 0;
	}
	else
	{
		double n = floor(a / b);
		return a - n*b;
	}
}

arma::mat SpatialChannel::ReceiverAntennaGain(int src, int zeta, arma::mat angleGCS, int type) { // 
	arma::mat angleLCS, antennaOrientation;
	if (type == 0)
		antennaOrientation = MS[src]->channel->antennaOrientation;
	else
		antennaOrientation = UMS[src]->channel->antennaOrientation;
	
	angleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(antennaOrientation(0, 0), 0, antennaOrientation(2, 0), angleGCS);

	arma::mat antennaGainLCS2(2, 1); // 0 H 1 V
	arma::mat antennaGainLCS(2, 1); // 0 H 1 V
	arma::mat antennaGainGCS(2, 1); // 0 H 1 V


	antennaGainLCS2(0, 0) = 0;
	antennaGainLCS2(1, 0) = 1.0;

	if (Sim.channel->PolarizedAntennaModel == 0) {
		antennaGainLCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(0.0, 0.0, zeta, angleLCS(1,0), angleLCS(0,0), antennaGainLCS2);
		antennaGainGCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(antennaOrientation(0, 0), 0.0, 0.0, angleGCS(1, 0), angleGCS(0, 0), antennaGainLCS);
	}
	else {
		antennaGainLCS = antennaGainLCS2;
		antennaGainGCS(1,0) = antennaGainLCS(1,0) * cos(zeta);
		antennaGainGCS(0,0) = antennaGainLCS(0,0) * sin(zeta);
	}


	return antennaGainGCS;
}

arma::cx_mat SpatialChannel::TransmitterAntennaGain(int src, double alpha, double beta, double gamma, double zeta, arma::mat angleGCS, int i, int numProcess) // i = BS index
{
	arma::mat angleLCS;
	arma::mat angleLCS2;
	
	arma::mat antennaGainLCS2;
	arma::mat antennaGainLCS;
	arma::mat antennaGainGCS;
	arma::cx_mat F_tx(2, 1);
	arma::vec tiltm(8);
	tiltm << 20 << 40 << 60 << 80 << 100 << 120 << 140 << 160 << arma::endr;

	
	BS[i]->channel->numVerticalAntenna = 8;
	antennaGainLCS2.zeros(2, 1);
	antennaGainLCS.zeros(2, 1);

	angleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(alpha, beta, gamma, angleGCS);
	angleLCS2 = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(0, 0, zeta, angleLCS);
		
	antennaGainLCS2(1, 0) = sqrt(pow(10.0, AntennaGain(angleLCS2) / 10.0));
	antennaGainLCS2(0, 0) = 0.0;
	Sim.channel->PolarizedAntennaModel = 0;
	if (Sim.channel->PolarizedAntennaModel == 0) {
		antennaGainLCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(0, 0, zeta, angleLCS(1,0), angleLCS(0,0), antennaGainLCS2);
		antennaGainGCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(alpha, beta, gamma, angleGCS(1, 0), angleGCS(0, 0), antennaGainLCS);
	}
	else {
		antennaGainLCS = antennaGainLCS2;
		antennaGainGCS(1, 0) = antennaGainLCS(1, 0) * cos(zeta);
		antennaGainGCS(0, 0) = antennaGainLCS(0, 0) * sin(zeta);
	}


	Sim.channel->AntennaTilting = 1;
	if (Sim.channel->AntennaTilting == 1) { // tilt
		double F_tempReal = 0.0;
		double F_tempImag = 0.0;
		double F_temp1Real = 0.0;
		double F_temp1Imag = 0.0; // H real H image endr V real V image endr
		//F_temp(0, 0) = 0;  F_temp1(0, 0) = 0; // real image real image
		for (int p = 0; p < BS[i]->channel->numVerticalAntenna; p++) {
			arma::cx_mat wei(1, 1);
					
			wei(0, 0) = 1i*(-(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave)*p*(Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * 1.6)*cos(tiltm(numProcess) * PI / 180.0));
		
			arma::mat Rd = DistanceAngular(alpha, beta, gamma, 0.0, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * 1.6 * p);
			arma::cx_mat ant_co(1, 1);
			ant_co(0, 0) = 1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
			
			F_tempReal = F_tempReal + (antennaGainGCS(1, 0)* (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * real(exp(wei(0, 0)) * exp(ant_co(0, 0))));
			F_tempImag = F_tempImag + (antennaGainGCS(1, 0)* (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * imag(exp(wei(0, 0)) * exp(ant_co(0, 0))));

			F_temp1Real = F_temp1Real + antennaGainGCS(0, 0)* (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * real(exp(wei(0, 0)) * exp(ant_co(0, 0)));
			F_temp1Imag = F_temp1Imag + antennaGainGCS(0, 0) * (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * imag(exp(wei(0, 0)) * exp(ant_co(0, 0)));
		}
		F_tx(1, 0) = F_tempReal + 1i* F_tempImag;
		F_tx(0, 0) = F_temp1Real + 1i* F_temp1Imag;
	}
	else {
		F_tx(1, 0) = antennaGainGCS(1, 0); 
		F_tx(0, 0) = antennaGainGCS(0, 0); 
	}

	arma::cx_mat txAntennaGainGCS = F_tx;
	return txAntennaGainGCS;
}

arma::mat SpatialChannel::DistanceAngular(double a, double b, double c, double x, double y, double z) {
	arma::mat Rd(3,1);
	
	Rd(0, 0) = cos(a)*cos(b) * x + cos(a)*sin(b)*sin(c) - sin(a)*cos(c) * y + cos(a)*sin(b)*cos(c) + sin(a)*sin(c) * z;
	Rd(1, 0) = sin(a)*cos(b) * x + sin(a)*sin(b)*sin(c) + cos(a)*cos(c) * y + sin(a)*sin(b)*cos(c) - cos(a)*sin(c) * z;
	Rd(2, 0) = -sin(b)		 * x + cos(b)*sin(c)					   * y + cos(b)*cos(c)						* z;

	return Rd;
}

arma::cx_mat SpatialChannel::exp_F_urd(int src, arma::mat A, int numRxAntenna, int type)
{
	arma::mat angleLCS, antennaOrientation;
	if (type == 0)
		antennaOrientation = MS[src]->channel->antennaOrientation;
	else
		antennaOrientation = UMS[src]->channel->antennaOrientation;
	arma::mat Rd(3,1);
	arma::cx_mat Furd;
	Furd.zeros(numRxAntenna, 1);
	for (int u = 0; u < numRxAntenna; u++) {
		if (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray) {
			Rd = DistanceAngular(MS[src]->channel->antennaOrientation(0, 0) , antennaOrientation(1, 0), antennaOrientation(2, 0), 0.0, Sim.channel->WaveLengthOfElectomageneticWave * 0.5 * u, 0.0); //수신 안테나 거리
			Furd(u, 0) = 0.0+ 1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(A(1, 0))*cos(A(0, 0))*Rd(0, 0) + sin(A(1, 0))*sin(A(0, 0))*Rd(1, 0) + cos(A(1, 0))*Rd(2, 0)));
		}
		else {
			Furd(u, 0) = (0.0)+1i*(0.0);
		}
	}
	return Furd;
}

arma::cx_mat SpatialChannel::exp_F_prd(int src, double alpha, double beta, double gamma, arma::mat angleGCS, int numTxHorizontalAntenna, int numTxVerticalAntenna,int numTxPort)
{
	int tx_port = 0;
	double mul_V = 1.6;
	arma::mat Rd(3,1);
	arma::cx_mat F_prd;
	F_prd.zeros(numTxHorizontalAntenna, 1);
	if (Sim.channel->BsAntennaModel== CHANNEL::UniformLinearArray) {
		for (int u = 0; u < numTxHorizontalAntenna; u++) {
			if (numTxPort - numTxHorizontalAntenna != 0) {
				for (int p = 0; p < numTxVerticalAntenna; p++) {
					Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * mul_V* p);
					F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
					tx_port++;
				}
			}
			else {
				Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, 0.0);
				F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
				tx_port++;
			}
		}
	}
	else {
		for (int u = 0; u<numTxHorizontalAntenna / 2; u++) {
			if (numTxPort - numTxHorizontalAntenna != 0) {
				for (int p = 0; p<numTxVerticalAntenna; p++) {
					Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * mul_V* p);
					F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
					F_prd[tx_port + numTxHorizontalAntenna / 2] = F_prd[tx_port];
					tx_port++;
				}
			}
			else {
				Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, 0.0);
				F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0)*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0))));
				F_prd[tx_port + numTxHorizontalAntenna / 2] = F_prd[tx_port];
				tx_port++;
			}
		}
	}

	return F_prd;
}