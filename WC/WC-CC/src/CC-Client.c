#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "open62541.h"

UA_Boolean running = true;
int loop_switch = 1;
int count = 0;
int msg_num;
//struct timespec start;
//struct timespec end;

UA_ReadValueId read_array[9000];
UA_Double DoubleCommand[8000];


void stopHandler(int sign) 
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
    loop_switch = 0;
}

UA_StatusCode multiRead(UA_Client *client, int num_Doubles)
{	
	//clock_gettime(CLOCK_MONOTONIC,&start);
	
	// 根據輸入的 num_Ints 來產生 0-1023 的隨機亂數 (總共產生 num_Ints*4 個 bytes 的data in write request )
	for(int i = 0; i < num_Doubles; ++i)
	{
		
	// 根據輸入的 num_Doubles 來產生 0.0-1023.0 的隨機亂數 (總共產生 num_Ints*4 個 bytes 的data in write request )
		UA_NodeId NodeId = UA_NODEID_NUMERIC(1, 8000+i);
		UA_ReadValueId_init(&read_array[i]);
		read_array[i].nodeId = NodeId;
		read_array[i].attributeId = UA_ATTRIBUTEID_VALUE;
		//read_array[i].value.value = Variant_for_Double;
		//read_array[i].value.hasValue = true;
	}

	UA_ReadRequest rReq;
	UA_ReadRequest_init(&rReq);
	rReq.nodesToRead = &read_array[0];
	rReq.nodesToReadSize = num_Doubles;
	
	UA_ReadResponse rResp = UA_Client_Service_read(client, rReq);
	
	UA_StatusCode retStatusArray[num_Doubles];
	UA_StatusCode retval = rResp.responseHeader.serviceResult;
	if (retval == UA_STATUSCODE_GOOD) 
	{
		if (rResp.resultsSize == num_Doubles)
		{
			for (int i = 0; i < num_Doubles; i++)
			{
				retStatusArray[i] = rResp.results[i].status;
			}
		}
		else
		{
			UA_ReadResponse_clear(&rResp);
			retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
		}
	}

	UA_ReadResponse_clear(&rResp);
	
	//clock_gettime(CLOCK_MONOTONIC,&end);
	//printf("Start timestamp is %ld.%09ld\n",start.tv_sec, start.tv_nsec);
	//printf("End timestamp is %ld.%09ld\n",end.tv_sec, end.tv_nsec);
	
	return UA_STATUSCODE_GOOD;
}



double exetime;

int main(int argc, char *argv[]) 
{	
    if (argc != 3) 
    {
        printf("Usage: <program> <#_of_CreatedDoublesinServer> <#_of_ControlCommand>\n");
        printf("[Try type]./CC-Client 100 2000\n");
        return 1;
    }
    // 將輸入的整數字符串轉換成integer
    int num_Doubles = atoi(argv[1]);
    msg_num = atoi(argv[2]);
    
    if(num_Doubles < 0)
    {
    	printf("<#_of_CreatedDoublesinServer> can't be negative !!!\n");
        return 1;
    }  
    else if(num_Doubles > 8000)
	{
    	printf("<#_of_Doubles> can't be larger than 8000 !!!\n");
        return 1;
    } 

    signal(SIGTERM, stopHandler);
	
    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.0.101:4840");
	
   
    if(retval != UA_STATUSCODE_GOOD) 
    {
        UA_Client_delete(client);
        return (int)retval;
    }    
	
	srand(time(NULL));
	
	while(loop_switch)
	{
		usleep(4000);
		multiRead(client, num_Doubles);	
		count++;
		
		if(count >= msg_num)
		{
			UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "%d control commands are sent!!", count);
			running = false;
			loop_switch = 0;
		}
	}

    UA_Client_delete(client); /* Disconnects the client internally */


    return EXIT_SUCCESS;
}
