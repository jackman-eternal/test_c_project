//#include <stdio.h>
#include <string.h>
// 
// 
//int main()
//{
//   const char haystack[] = "+MQTTSUBRECV:0,\"/sys/ibbkznChKyz/wechat/thing/service/property/set\",230,{\"deviceType\":\"CustomCategory\",\"iotId\":\"20V9wmZGFa8a0pYDjrqPibbk00\",\"requestId\":\"null\",\"checkFailedData\":{},\"productKey\":\"ibbkznChKyz\",\"gmtCreate\":1680615566618,\"deviceName\":\"apps\",\"items\":{\"Led\":{\"time\":1680615566610,\"value\":0}}}";
//   const char needle[] = "{";
//   char *ret;
// 
//   ret = strstr(haystack, needle);
// 
//   printf("子字符串是： %s\n", ret);
//   
//   return(0);
//}

#include <stdio.h>
#include "cJSON.h"

char *message = 
"{                              \
    \"name\":\"mculover666\",   \
    \"age\": 22,                \
    \"weight\": 55.5,           \
    \"address\":                \
        {                       \
            \"country\": \"China\",\
            \"zip-code\": 111111\
        },                      \
    \"skill\": [\"c\", \"Java\", \"Python\"],\
    \"student\": false          \
}";

char* str = 
"{                                              \
     \"deviceType\":\"CustomCategory\",         \
	 \"iotId\":\"20V9wmZGFa8a0pYDjrqPibbk00\",  \
	 \"requestId\":\"null\",                    \
	 \"checkFailedData\":{},                    \
	 \"productKey\":\"ibbkznChKyz\",            \
	 \"gmtCreate\":1680670993632,               \
	 \"deviceName\":\"apps\",                   \
	 \"items\":                                 \
			    {\"Led\":						 \
				  { \"time\":1680670993630, \
			        \"value\":1             \
				  }                         \
				}}";
int main(void)
{
   const char haystack[] = "+MQTTSUBRECV:0,\"/sys/ibbkznChKyz/wechat/thing/service/property/set\",230,{\"deviceType\":\"CustomCategory\",\"iotId\":\"20V9wmZGFa8a0pYDjrqPibbk00\",\"requestId\":\"null\",\"checkFailedData\":{},\"productKey\":\"ibbkznChKyz\",\"gmtCreate\":1680615566618,\"deviceName\":\"apps\",\"items\":{\"Led\":{\"time\":1680615566610,\"value\":0}}}";
   const char needle[] = "{";
   char *ret;
   char *string1; 
    ret = strstr(haystack, needle);
    cJSON* cjson_test = NULL;
    cJSON* cjson_name = NULL;
    cJSON* cjson_age = NULL;
    cJSON* cjson_weight = NULL;
    cJSON* cjson_address = NULL;
    cJSON* cjson_address_country = NULL;
    cJSON* cjson_address_zipcode = NULL;
    cJSON* cjson_skill = NULL;
    cJSON* cjson_student = NULL;
    int    skill_array_size = 0, i = 0;
    cJSON* cjson_skill_item = NULL;
    
    cJSON* cjson_all = NULL;
    cJSON* cjson_item = NULL;
    cJSON* cjson_Led = NULL;
    cJSON* cjson_val = NULL;
    
    /* 解析整段JSO数据 */
    cjson_test = cJSON_Parse(message);
    cjson_all = cJSON_Parse(ret);
    if(cjson_test == NULL)
    {
        printf("parse fail.\n");
        return -1;
    }
    if(cjson_all == NULL)
    {
        printf("parse fail.\n");
        return -1;	
	}

    /* 依次根据名称提取JSON数据（键值对） */
    cjson_name = cJSON_GetObjectItem(cjson_test, "name");
    cjson_age = cJSON_GetObjectItem(cjson_test, "age");
    cjson_weight = cJSON_GetObjectItem(cjson_test, "weight");

    printf("name: %s\n", cjson_name->valuestring);
    printf("age:%d\n", cjson_age->valueint);
    printf("weight:%.1f\n", cjson_weight->valuedouble);
    //提取数据 
    cjson_item = cJSON_GetObjectItem(cjson_all,"items");
    cjson_Led =  cJSON_GetObjectItem(cjson_item,"Led"); 
    cjson_val = cJSON_GetObjectItem(cjson_Led,"value");
    string1 = cJSON_Print(cjson_item);
    printf("%s\r\n",string1);
    
    printf("value : %d \r\n",cjson_val->valueint);
    /* 解析嵌套json数据 */
    cjson_address = cJSON_GetObjectItem(cjson_test, "address");
    cjson_address_country = cJSON_GetObjectItem(cjson_address, "country");
    cjson_address_zipcode = cJSON_GetObjectItem(cjson_address, "zip-code");
    printf("address-country:%s\naddress-zipcode:%d\n", cjson_address_country->valuestring, cjson_address_zipcode->valueint);

    /* 解析数组 */
    cjson_skill = cJSON_GetObjectItem(cjson_test, "skill");
    skill_array_size = cJSON_GetArraySize(cjson_skill);
    printf("skill:[");
    for(i = 0; i < skill_array_size; i++)
    {
        cjson_skill_item = cJSON_GetArrayItem(cjson_skill, i);
        printf("%s,", cjson_skill_item->valuestring);
    }
    printf("\b]\n");

    /* 解析布尔型数据 */
    cjson_student = cJSON_GetObjectItem(cjson_test, "student");
    if(cjson_student->valueint == 0)
    {
        printf("student: false\n");
    }
    else
    {
        printf("student:error\n");
    }
    
    return 0;
}



