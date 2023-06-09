/****************************************************************************

Performance header (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME : PerformanceURLLCMS_NRuRLLC.h
DATE : 2017.1.31
VERSION : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright(C) 2016, by Korea University, Dongguk University, All Rights Reserved

**************************************************************************** /

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han    	Created

===========================================================================*/

#ifndef PERFORMANCEURLLCMS_H
#define PERFORMANCEURLLCMS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Performance mobile station
class PerformanceURLLCMS
{
public:
	int id; // MS ID
	double uplinkThroghput; // Throughput
	double downlinkThroghput;
	double instantThroughput;
	double receivedSinr;

	void Initialize(int ms); // Initialization
	void Measure(); // Throughput measurement
	double FER(double SINR, int MCS);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif