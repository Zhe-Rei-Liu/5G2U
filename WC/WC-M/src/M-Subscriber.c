//#include <open62541/plugin/log_stdout.h>
//#include <open62541/plugin/pubsub_udp.h>
//#include <open62541/server.h>
//#include <open62541/server_config_default.h>
//#include <open62541/types_generated.h>

#include <open62541.h>
//#include <ua_pubsub.h>

#ifdef UA_ENABLE_PUBSUB_ETH_UADP
#include <open62541/plugin/pubsub_ethernet.h>
#endif

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

UA_NodeId connectionIdentifier;
UA_NodeId readerGroupIdentifier;
UA_NodeId readerIdentifier;

UA_DataSetReaderConfig readerConfig;

int num_Doubles;

static void fillTestDataSetMetaData(UA_DataSetMetaDataType *pMetaData);

/* Add new connection to the server */
static UA_StatusCode addPubSubConnection(UA_Server *server, UA_String *transportProfile, UA_NetworkAddressUrlDataType *networkAddressUrl) 
{
    if((server == NULL) || (transportProfile == NULL) || (networkAddressUrl == NULL)) 
    {
        return UA_STATUSCODE_BADINTERNALERROR;
    }

    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    /* Configuration creation for the connection */
    UA_PubSubConnectionConfig connectionConfig;
    memset (&connectionConfig, 0, sizeof(UA_PubSubConnectionConfig));
    connectionConfig.name = UA_STRING("UAPMC Connection 1");
    connectionConfig.transportProfileUri = *transportProfile;
    connectionConfig.enabled = UA_TRUE;
    UA_Variant_setScalar(&connectionConfig.address, networkAddressUrl, &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);
    connectionConfig.publisherId.numeric = UA_UInt32_random ();
    retval |= UA_Server_addPubSubConnection (server, &connectionConfig, &connectionIdentifier);
    if (retval != UA_STATUSCODE_GOOD) 
    {
        return retval;
    }
//****************************************************************//
    //retval |= UA_PubSubConnection_regist(server, &connectionIdentifier);
//****************************************************************//
    return retval;
}

/* Add ReaderGroup to the created connection */
static UA_StatusCode addReaderGroup(UA_Server *server) 
{
    if(server == NULL) 
    {
        return UA_STATUSCODE_BADINTERNALERROR;
    }

    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    UA_ReaderGroupConfig readerGroupConfig;
    memset (&readerGroupConfig, 0, sizeof(UA_ReaderGroupConfig));
    readerGroupConfig.name = UA_STRING("ReaderGroup1");
    retval |= UA_Server_addReaderGroup(server, connectionIdentifier, &readerGroupConfig, &readerGroupIdentifier);
//************************************************************************//    
    UA_Server_setReaderGroupOperational(server, readerGroupIdentifier);
//************************************************************************//    
    return retval;
}

/* Add DataSetReader to the ReaderGroup */
static UA_StatusCode addDataSetReader(UA_Server *server) 
{
    if(server == NULL) 
    {
        return UA_STATUSCODE_BADINTERNALERROR;
    }

    UA_StatusCode retval = UA_STATUSCODE_GOOD; 
    memset (&readerConfig, 0, sizeof(UA_DataSetReaderConfig));
    readerConfig.name = UA_STRING("DataSet Reader 1");
    /* Parameters to filter which DataSetMessage has to be processed by the DataSetReader */
    /* The following parameters are used to show that the data published by tutorial_pubsub_publish.c is being subscribed and is being updated in the information model */
    UA_UInt16 publisherIdentifier = 2234;
    readerConfig.publisherId.type = &UA_TYPES[UA_TYPES_UINT16];
    readerConfig.publisherId.data = &publisherIdentifier;
    readerConfig.writerGroupId    = 100;
    readerConfig.dataSetWriterId  = 62541;

    /* Setting up Meta data configuration in DataSetReader */
    fillTestDataSetMetaData(&readerConfig.dataSetMetaData);
    retval |= UA_Server_addDataSetReader(server, readerGroupIdentifier, &readerConfig, &readerIdentifier);
    return retval;
}

/* Set SubscribedDataSet type to TargetVariables data type, add subscribedvariables to the DataSetReader */
static UA_StatusCode addSubscribedVariables (UA_Server *server, UA_NodeId dataSetReaderId) 
{
    if(server == NULL) 
    {
        return UA_STATUSCODE_BADINTERNALERROR;
    }

    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    UA_NodeId folderId;
    UA_String folderName = readerConfig.dataSetMetaData.name;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    UA_QualifiedName folderBrowseName;
    if(folderName.length > 0) 
    {
        oAttr.displayName.locale = UA_STRING ("en-US");
        oAttr.displayName.text = folderName;
        folderBrowseName.namespaceIndex = 1;
        folderBrowseName.name = folderName;
    }
    else 
    {
        oAttr.displayName = UA_LOCALIZEDTEXT ("en-US", "Subscribed Variables");
        folderBrowseName = UA_QUALIFIEDNAME (1, "Subscribed Variables");
    }

    UA_Server_addObjectNode (server, UA_NODEID_NULL, UA_NODEID_NUMERIC (0, UA_NS0ID_OBJECTSFOLDER), UA_NODEID_NUMERIC (0, UA_NS0ID_ORGANIZES), folderBrowseName, UA_NODEID_NUMERIC (0, UA_NS0ID_BASEOBJECTTYPE), oAttr, NULL, &folderId);
	
	
//*************************************************************************************************************//
/**
 * **TargetVariables**
 *
 * The SubscribedDataSet option TargetVariables defines a list of Variable mappings between
 * received DataSet fields and target Variables in the Subscriber AddressSpace.
 * The values subscribed from the Publisher are updated in the value field of these variables */
    /* Create the TargetVariables with respect to DataSetMetaData fields */
    
    UA_FieldTargetVariable *targetVars = (UA_FieldTargetVariable *) UA_calloc(readerConfig.dataSetMetaData.fieldsSize, sizeof(UA_FieldTargetVariable));
    for(size_t i = 0; i < readerConfig.dataSetMetaData.fieldsSize; i++) 
    {
        /* Variable to subscribe data */
        UA_VariableAttributes vAttr = UA_VariableAttributes_default;
        UA_LocalizedText_copy(&readerConfig.dataSetMetaData.fields[i].description, &vAttr.description);
        vAttr.displayName.locale = UA_STRING("en-US");
        vAttr.displayName.text = readerConfig.dataSetMetaData.fields[i].name;
        vAttr.dataType = readerConfig.dataSetMetaData.fields[i].dataType;
        vAttr.accessLevel |= UA_ACCESSLEVELMASK_WRITE;

        UA_NodeId newNode;
        retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1, i + 8000), folderId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(1, (char *)readerConfig.dataSetMetaData.fields[i].name.data), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), vAttr, NULL, &newNode);

        /* For creating Targetvariables */
        UA_FieldTargetDataType_init(&targetVars[i].targetVariable);
        targetVars[i].targetVariable.attributeId  = UA_ATTRIBUTEID_VALUE;
        targetVars[i].targetVariable.targetNodeId = newNode;
    }

    retval = UA_Server_DataSetReader_createTargetVariables(server, dataSetReaderId, readerConfig.dataSetMetaData.fieldsSize, targetVars);
    for(size_t i = 0; i < readerConfig.dataSetMetaData.fieldsSize; i++)
        UA_FieldTargetDataType_clear(&targetVars[i].targetVariable);

    UA_free(targetVars);
    UA_free(readerConfig.dataSetMetaData.fields);
    return retval;
//******************************************************************************************************************//

}

/* Define MetaData for TargetVariables */
static void fillTestDataSetMetaData(UA_DataSetMetaDataType *pMetaData) 
{
    if(pMetaData == NULL) 
    {
    	printf("no message!!\n");
        return;
    }

    UA_DataSetMetaDataType_init (pMetaData);
    pMetaData->name = UA_STRING ("DataSet 1");

    /* Static definition of number of fields size to 4 to create four different targetVariables of distinct datatype
     * Currently the publisher sends only DateTime data type */
    pMetaData->fieldsSize = num_Doubles;
    pMetaData->fields = (UA_FieldMetaData*)UA_Array_new (pMetaData->fieldsSize, &UA_TYPES[UA_TYPES_FIELDMETADATA]);

	for(int i = 0; i < num_Doubles; i++)
	{
		/* double DataType */
		UA_FieldMetaData_init (&pMetaData->fields[i]);
    	UA_NodeId_copy(&UA_TYPES[UA_TYPES_DOUBLE].typeId, &pMetaData->fields[i].dataType);
    	pMetaData->fields[i].builtInType = UA_NS0ID_DOUBLE;
    	pMetaData->fields[i].name =  UA_STRING ("Published_Doubles");
    	pMetaData->fields[i].valueRank = -1; /* scalar */
	}
}

UA_Boolean running = true;
static void stopHandler(int sign) 
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

static int
run(UA_String *transportProfile, UA_NetworkAddressUrlDataType *networkAddressUrl, int num_Is) 
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);
    
    /* Return value initialized to Status Good */
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    UA_Server *server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, 7788, NULL);

    /* Add the PubSub network layer implementation to the server config.
     * The TransportLayer is acting as factory to create new connections
     * on runtime. Details about the PubSubTransportLayer can be found inside the
     * tutorial_pubsub_connection */
    UA_ServerConfig_addPubSubTransportLayer(config, UA_PubSubTransportLayerUDPMP());
#ifdef UA_ENABLE_PUBSUB_ETH_UADP
    UA_ServerConfig_addPubSubTransportLayer(config, UA_PubSubTransportLayerEthernet());
#endif


    /* API calls */
    
    /* Add PubSubConnection */
    retval |= addPubSubConnection(server, transportProfile, networkAddressUrl);
    if (retval != UA_STATUSCODE_GOOD)
        return EXIT_FAILURE;

    /* Add ReaderGroup to the created PubSubConnection */
    retval |= addReaderGroup(server);
    if (retval != UA_STATUSCODE_GOOD)
        return EXIT_FAILURE;

    /* Add DataSetReader to the created ReaderGroup */
    retval |= addDataSetReader(server);
    if (retval != UA_STATUSCODE_GOOD)
        return EXIT_FAILURE;

    /* Add SubscribedVariables to the created DataSetReader */
    retval |= addSubscribedVariables(server, readerIdentifier);
    if (retval != UA_STATUSCODE_GOOD)
        return EXIT_FAILURE;

    retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}

static void usage(char *progname) 
{
    printf("usage: %s <uri> <num_Doubles>\n", progname);
}

int main(int argc, char **argv) {
    UA_String transportProfile = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-udp-uadp");
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , UA_STRING("opc.udp://224.0.0.22:4840/")};

    if(argc > 1) {
        if(strcmp(argv[1], "-h") == 0) 
        {
            usage(argv[0]);
            return EXIT_SUCCESS;
        } 
        else if(strncmp(argv[1], "opc.udp://", 10) == 0) 
        {
            networkAddressUrl.url = UA_STRING(argv[1]);
            num_Doubles = atoi(argv[2]);
        } 
        else 
        {
            printf ("Error: unknown URI\n");
            return EXIT_FAILURE;
        }
    }

    return run(&transportProfile, &networkAddressUrl, num_Doubles);
}
