#include <signal.h>
#include "open62541.h"

UA_Boolean running = true;

static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
    //loop_switch = 0;
}

// 創建複數個被監控的變數節點(double)並設置其初始值及回傳其node id
UA_NodeId addDoubles(UA_Server *server, const char * name, UA_NodeId nodeId, UA_Double initValue) 
{
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Double doubles = initValue;
    UA_Variant_setScalar(&attr.value, &doubles, &UA_TYPES[UA_TYPES_DOUBLE]);
    attr.description = UA_LOCALIZEDTEXT("en-US", (char*)name);
    attr.displayName = UA_LOCALIZEDTEXT("en-US", (char*)name);
    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_QualifiedName Name = UA_QUALIFIEDNAME(1, (char*)name);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, nodeId, parentNodeId,
                              parentReferenceNodeId, Name,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, NULL);
    
}

int main(int argc, char *argv[]) 
{

	if (argc != 2) 
	{
        printf("Usage: program <#_of_CreatedDoubles>\n");
        return 1;
    }
    
    int num_Doubles = atoi(argv[1]);
    
    if(num_Doubles < 0)
    {
    	printf("<#_of_CreatedDoubles> can't be negative!!!\n");
        return 1;
    }
        
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setMinimal(UA_Server_getConfig(server), 4841, NULL);   
    
    for (int i = 0; i < num_Doubles; ++i)
    {
        char varName[20];
        
        UA_NodeId nodeId = UA_NODEID_NUMERIC(1, 8000+i);
        
        snprintf(varName, 20, "double_%d", i);
        UA_Double initValue = 0.0;
        addDoubles(server, varName, nodeId, initValue);
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "node id: %d, init value: %lf\n", 8000+i, initValue);
    }

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
 
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE; 
}
