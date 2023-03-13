//#include <open62541/plugin/log_stdout.h>
//#include <open62541/plugin/pubsub_ethernet.h>
//#include <open62541/plugin/pubsub_udp.h>
//#include <open62541/server.h>
//#include <open62541/server_config_default.h>

#include <open62541.h>
#include <pthread.h>
#include <signal.h>

struct timespec start;
struct timespec now;
double current_time;
double  howlong;

UA_NodeId connectionIdent, publishedDataSetIdent, writerGroupIdent;
UA_Boolean running = true;
int loop_switch = 1;
double msg_num;	
int num_Doubles;

typedef struct container 
{
	UA_Server * ptr1;
	double * ptr2;
	double   * ptr3;
} container_t;
 
static void addDoubles(UA_Server *server, UA_NodeId nodeid)
{	
    UA_Double initvalue = 1.0;
    UA_VariableAttributes pubattr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&pubattr.value, &initvalue, &UA_TYPES[UA_TYPES_DOUBLE]);
    pubattr.displayName = UA_LOCALIZEDTEXT("en-US", "published_Double");
    pubattr.accessLevel |= UA_ACCESSLEVELMASK_WRITE; 
    UA_Server_addVariableNode(server, nodeid ,UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),UA_QUALIFIEDNAME(1, "Published_Double"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), pubattr, NULL, NULL);
}

static void addPubSubConnection(UA_Server *server, UA_String *transportProfile, UA_NetworkAddressUrlDataType *networkAddressUrl)
{
    /* Details about the connection configuration and handling are located in the pubsub connection tutorial */
    UA_PubSubConnectionConfig connectionConfig;
    // 將connectioConfig 變為 00000000000...
    memset(&connectionConfig, 0, sizeof(connectionConfig));
    connectionConfig.name = UA_STRING("UADP Connection 1");
    connectionConfig.transportProfileUri = *transportProfile;
    connectionConfig.enabled = UA_TRUE;
    UA_Variant_setScalar(&connectionConfig.address, networkAddressUrl, &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);
    /* Changed to static publisherId from random generation to identify the publisher on Subscriber side */
    connectionConfig.publisherId.numeric = 2234;
    UA_Server_addPubSubConnection(server, &connectionConfig, &connectionIdent);
}

/**
 * **PublishedDataSet handling**
 *
 * The PublishedDataSet (PDS) and PubSubConnection are the toplevel entities and
 * can exist alone. The PDS contains the collection of the published fields. All
 * other PubSub elements are directly or indirectly linked with the PDS or
 * connection. */
static void
addPublishedDataSet(UA_Server *server) 
{
    /* The PublishedDataSetConfig contains all necessary public informations for the creation of a new PublishedDataSet */
    UA_PublishedDataSetConfig publishedDataSetConfig;
    memset(&publishedDataSetConfig, 0, sizeof(UA_PublishedDataSetConfig));
    publishedDataSetConfig.publishedDataSetType = UA_PUBSUB_DATASET_PUBLISHEDITEMS;
    publishedDataSetConfig.name = UA_STRING("MY PDS");
    /* Create new PublishedDataSet based on the PublishedDataSetConfig. */
    UA_Server_addPublishedDataSet(server, &publishedDataSetConfig, &publishedDataSetIdent);
}

/**
 * **DataSetField handling**
 *
 * The DataSetField (DSF) is part of the PDS and describes exactly one published
 * field. */
static void addDataSetField(UA_Server *server, int num_Doubles) 
{
    /* Add a field to the previous created PublishedDataSet */
    
    //加入自己創建的node 在 published Dataset
    UA_NodeId dataSetFieldIdent[num_Doubles];
    UA_DataSetFieldConfig dataSetFieldConfig[num_Doubles];
    for(int i=0; i < num_Doubles; i++)
	{	
		memset(&dataSetFieldConfig[i], 0, sizeof(UA_DataSetFieldConfig));
		dataSetFieldConfig[i].dataSetFieldType = UA_PUBSUB_DATASETFIELD_VARIABLE;
		dataSetFieldConfig[i].field.variable.fieldNameAlias = UA_STRING("MY_Doubles");
		dataSetFieldConfig[i].field.variable.promotedField = UA_FALSE;
		dataSetFieldConfig[i].field.variable.publishParameters.publishedVariable = UA_NODEID_NUMERIC(1,8000 + i);    //we need to configure dataset with same node ID
		dataSetFieldConfig[i].field.variable.publishParameters.attributeId = UA_ATTRIBUTEID_VALUE;
		UA_Server_addDataSetField(server, publishedDataSetIdent, &dataSetFieldConfig[i], &dataSetFieldIdent[i]);
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Nodes have been put into the published data set.");
    
}


/**
 * **WriterGroup handling**
 *
 * The WriterGroup (WG) is part of the connection and contains the primary
 * configuration parameters for the message creation. */
static void addWriterGroup(UA_Server *server) 
{
    /* Now we create a new WriterGroupConfig and add the group to the existing PubSubConnection. */
    UA_WriterGroupConfig writerGroupConfig;
    memset(&writerGroupConfig, 0, sizeof(UA_WriterGroupConfig));
    writerGroupConfig.name = UA_STRING("Demo WriterGroup");
    writerGroupConfig.publishingInterval = 100;  // ms
    writerGroupConfig.enabled = UA_FALSE;
    writerGroupConfig.writerGroupId = 100;
    writerGroupConfig.encodingMimeType = UA_PUBSUB_ENCODING_UADP;
    writerGroupConfig.messageSettings.encoding             = UA_EXTENSIONOBJECT_DECODED;
    writerGroupConfig.messageSettings.content.decoded.type = &UA_TYPES[UA_TYPES_UADPWRITERGROUPMESSAGEDATATYPE];
    /* The configuration flags for the messages are encapsulated inside the
     * message- and transport settings extension objects. These extension
     * objects are defined by the standard. e.g. UadpWriterGroupMessageDataType */
    UA_UadpWriterGroupMessageDataType *writerGroupMessage  = UA_UadpWriterGroupMessageDataType_new();
    /* Change message settings of writerGroup to send PublisherId,
     * WriterGroupId in GroupHeader and DataSetWriterId in PayloadHeader
     * of NetworkMessage */
    writerGroupMessage->networkMessageContentMask          = (UA_UadpNetworkMessageContentMask)(UA_UADPNETWORKMESSAGECONTENTMASK_PUBLISHERID |
                                                              (UA_UadpNetworkMessageContentMask) UA_UADPNETWORKMESSAGECONTENTMASK_GROUPHEADER |
                                                              (UA_UadpNetworkMessageContentMask) UA_UADPNETWORKMESSAGECONTENTMASK_WRITERGROUPID |
                                                              (UA_UadpNetworkMessageContentMask) UA_UADPNETWORKMESSAGECONTENTMASK_PAYLOADHEADER);
    writerGroupConfig.messageSettings.content.decoded.data = writerGroupMessage;
    UA_Server_addWriterGroup(server, connectionIdent, &writerGroupConfig, &writerGroupIdent);
    UA_Server_setWriterGroupOperational(server, writerGroupIdent);
    UA_UadpWriterGroupMessageDataType_delete(writerGroupMessage);
}

/**
 * **DataSetWriter handling**
 *
 * A DataSetWriter (DSW) is the glue between the WG and the PDS. The DSW is
 * linked to exactly one PDS and contains additional informations for the
 * message generation. */
static void addDataSetWriter(UA_Server *server) 
{
    /* We need now a DataSetWriter within the WriterGroup. This means we must
     * create a new DataSetWriterConfig and add call the addWriterGroup function. */
    UA_NodeId dataSetWriterIdent;
    UA_DataSetWriterConfig dataSetWriterConfig;
    memset(&dataSetWriterConfig, 0, sizeof(UA_DataSetWriterConfig));
    dataSetWriterConfig.name = UA_STRING("Demo DataSetWriter");
    dataSetWriterConfig.dataSetWriterId = 62541;
    dataSetWriterConfig.keyFrameCount = 10;
    UA_Server_addDataSetWriter(server, writerGroupIdent, publishedDataSetIdent, &dataSetWriterConfig, &dataSetWriterIdent);
}

void varying_doublevalues(UA_Server *server, int num_D)
{
	double random = ((double)rand() / RAND_MAX)*1023.0;
	// 根據輸入的 num_Ints 來產生 0-1023 的隨機亂數 (總共產生 num_Ints*8 個 bytes 的data in publish )
	for(int i = 0; i < num_D; i++)
	{	

		UA_NodeId DoubleId = UA_NODEID_NUMERIC(1, 8000+i);
		
		UA_Double Double_var;

		Double_var = random;
		
		UA_Variant Variant_for_Double;
		UA_Variant_init(&Variant_for_Double);
		UA_Variant_setScalar(&Variant_for_Double, &Double_var, &UA_TYPES[UA_TYPES_DOUBLE]);
		
		UA_StatusCode ret = UA_Server_writeValue(server, DoubleId, Variant_for_Double);	
	}   

}

void *thr_fn(void *arg)
{
	
    container_t *pContainer = (container_t*)arg;
    UA_Server *server = pContainer->ptr1;
    double *num_msg = pContainer->ptr2;
    double  *start_time = pContainer->ptr3;
    
    while(loop_switch)
    {
    	usleep(10000);
    	clock_gettime(CLOCK_MONOTONIC,&now);
    	howlong = now.tv_sec + now.tv_nsec*0.000000001 - *start_time;
    	//printf("Now is %lf \n",howlong);
    	
    	if(howlong*10.0 >= *num_msg)
    	{	    		
    		double integer = *num_msg; 
			UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%d sensor datas are published!!", (int)integer);    	
    		running = false;
			loop_switch = 0;			
    	}
    }
    
    return NULL;
}

/**
 * That's it! You're now publishing the selected fields. Open a packet
 * inspection tool of trust e.g. wireshark and take a look on the outgoing
 * packages. The following graphic figures out the packages created by this
 * tutorial.
 *
 * .. figure:: ua-wireshark-pubsub.png
 *     :figwidth: 100 %
 *     :alt: OPC UA PubSub communication in wireshark
 *
 * The open62541 subscriber API will be released later. If you want to process
 * the the datagrams, take a look on the ua_network_pubsub_networkmessage.c
 * which already contains the decoding code for UADP messages.
 *
 * It follows the main server code, making use of the above definitions. */

static void stopHandler(int sign) 
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
    loop_switch = 0;
}

static int run(UA_String *transportProfile, UA_NetworkAddressUrlDataType *networkAddressUrl, int num_Ds, double msg_num) 
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);
    

    UA_Server *server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, 5566, NULL);

    /* Details about the connection configuration and handling are located in the pubsub connection tutorial */
    UA_ServerConfig_addPubSubTransportLayer(config, UA_PubSubTransportLayerUDPMP());
#ifdef UA_ENABLE_PUBSUB_ETH_UADP
    UA_ServerConfig_addPubSubTransportLayer(config, UA_PubSubTransportLayerEthernet());
#endif

	UA_NodeId pubnode[num_Ds];

	for(int i=0; i < num_Ds; i++)
	{	
		pubnode[i] = UA_NODEID_NUMERIC(1,8000 + i);
		addDoubles(server, pubnode[i]);
	}
	
	varying_doublevalues(server, num_Ds);
	
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "My published node has been created.");

    addPubSubConnection(server, transportProfile, networkAddressUrl);
    addPublishedDataSet(server);
    addDataSetField(server, num_Ds);
    addWriterGroup(server);
    addDataSetWriter(server);
    
    clock_gettime(CLOCK_MONOTONIC,&start);
    
    current_time = start.tv_sec + start.tv_nsec*0.000000001;
	
	container_t cont = {server, &msg_num, &current_time};
    pthread_t t1;
    int err = pthread_create(&t1, NULL, thr_fn, &cont);
    if (err != 0)
    {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Create thread Fail.");
        return -1;
    }
    
    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(int argc, char **argv) 
{
    UA_String transportProfile = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-udp-uadp");
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , UA_STRING("opc.udp://224.0.0.22:4840/")};
	
	srand(911);
		
	if (argc != 4) 
    {
        printf("Usage: <program> <uri> <#_of_CreatedDoublesinServer> <#_of_Monitoring>\n");
        printf("[Try type]./M-Publisher opc.udp://224.0.5.1:4840 100 1000\n");
        return 1;
    }
    else if (strncmp(argv[1], "opc.udp://", 10) == 0) 
    {
        networkAddressUrl.url = UA_STRING(argv[1]);
        num_Doubles = atoi(argv[2]);
        msg_num = atof(argv[3]);
    } 
    else 
    {
        printf("Error: unknown URI\n");
        return EXIT_FAILURE;
    }

    return run(&transportProfile, &networkAddressUrl, num_Doubles, msg_num);
}

