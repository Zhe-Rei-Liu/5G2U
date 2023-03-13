#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "open62541.h"

int loop_switch = 1;
int count = 0;

struct timespec start;
struct timespec end;
struct timespec diff;

UA_WriteValue write_array[9000];
UA_Double DoubleCommand[8000];

double setdouble = 1.0000;

//  產生exponential隨機分佈
int ran_expo(double lambda)
{
    double u,x;
    
    u = rand() / (RAND_MAX + 1.0);
    x = -log(1- u) / lambda;
    return x;
}
// 產生高斯隨機分佈
int ran_norm(int mean, int std)
{
	float u,v,x;
    u = rand() / (double)RAND_MAX;
    v = rand() / (double)RAND_MAX;
    x = sqrt(-2 * log(u)) * cos(2 * M_PI * v) * std + mean;
    
    return x;
}

UA_StatusCode multiWrite(UA_Client *client, int num_Doubles)
{						
	UA_Variant Variant_for_Double;
	UA_Variant_init(&Variant_for_Double);
	UA_Variant_setScalar(&Variant_for_Double, &setdouble, &UA_TYPES[UA_TYPES_DOUBLE]);	
	
	//clock_gettime(CLOCK_MONOTONIC,&start);

	double random = ((double)rand() / RAND_MAX)*1023.0;
	
	// 根據輸入的 num_Doubles 來產生 0-1023 的隨機亂數 
	for(int i = 0; i < num_Doubles; ++i)
	{
		UA_NodeId NodeId = UA_NODEID_NUMERIC(1, 8000+i);
		
		//double random = ((double)rand() / RAND_MAX)*1023.0;
		//DoubleCommand[i-num_Ints] = random;
		
		//printf("Random Double is %lf\n", DoubleCommand[i-num_Ints]);
		
		UA_Variant Variant_for_Double;
		UA_Variant_init(&Variant_for_Double);
		UA_Variant_setScalar(&Variant_for_Double, &random, &UA_TYPES[UA_TYPES_DOUBLE]);
		
		UA_WriteValue_init(&write_array[i]);
		write_array[i].attributeId = UA_ATTRIBUTEID_VALUE;
		write_array[i].nodeId = NodeId;
		write_array[i].value.value = Variant_for_Double;
		write_array[i].value.hasValue = true;
	}

	UA_WriteRequest wReq;
	UA_WriteRequest_init(&wReq);
	wReq.nodesToWrite = &write_array[0];
	wReq.nodesToWriteSize = num_Doubles;
	
	UA_WriteResponse wResp = UA_Client_Service_write(client, wReq);
	
	UA_StatusCode retval = wResp.responseHeader.serviceResult;
	if (retval == UA_STATUSCODE_GOOD) 
	{
		if (wResp.resultsSize == 1)
		{
			retval = wResp.results[0];
		}
		else
		{
			retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
		}
	}

	UA_WriteResponse_clear(&wResp);
	//clock_gettime(CLOCK_MONOTONIC,&end);
	//printf("Start timestamp is %ld.%09ld\n",start.tv_sec, start.tv_nsec);
	//printf("End timestamp is %ld.%09ld\n",end.tv_sec, end.tv_nsec);
}



void generating_double_alarm(UA_Client *client, int num_double)
{
	int num_alarm;
	
	num_alarm = ran_norm(num_double*0.8, num_double*0.1);
	if (num_alarm > num_double)
	{
		num_alarm =	num_alarm*0.9;
	}
	else if (num_alarm < num_double*0.6)
	{
		num_alarm =	num_double*0.7;
	}	
	//printf("%d double type alarming happened!!!\n", num_alarm); 	
	
	// 根據輸入的 num_Doubles 來產生 0.0-1023.0 的隨機亂數並由write request發出 (總共產生 num_Ints*4 個 bytes 的data in write request )
	multiWrite(client, num_alarm);
}



double exetime;

int main(int argc, char *argv[]) 
{	
    if (argc != 3) 
    {
        printf("Usage: <program> <#_of_CreatedDoublesinServer> <#_of_Alarming>\n");
        printf("[Try type]./A-Client 100 2000\n");
        return 1;
    }

    // 將輸入的整數字符串轉換成integer
    int num_Doubles = atoi(argv[1]);
    int msg_num = atoi(argv[2]);  
    
    if(num_Doubles < 0)
    {
    	printf("<#_of_CreatedDoublesinServer> can't be negative !!!\n");
        return 1;
    }     
    else if(num_Doubles > 8000)
	{
    	printf("<#_of_CreatedDoublesinServer> can't be larger than 8000 !!!\n");
        return 1;
    } 
    else if(msg_num < 0 )
	{
    	printf("<#_of_Alarming> can't be negative !!!\n");
        return 1;
    }  	

    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.0.101:4841");
	
    if(retval != UA_STATUSCODE_GOOD) 
    {
        UA_Client_delete(client);
        return (int)retval;
    }    
	
	srand(11);
	clock_gettime(CLOCK_MONOTONIC,&start);
	while(loop_switch)
	{
		usleep(ran_expo(0.03)*1000);
		
		generating_double_alarm(client,num_Doubles);	
		count++;
		
		if(count >= msg_num)
		{
			UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "%d warnings are sent!!", count);
			loop_switch = 0;
		}
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	
    UA_Client_delete(client); /* Disconnects the client internally */


    return EXIT_SUCCESS;
}

