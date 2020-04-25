#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "cJSON.c"
#include <curl/curl.h>

char* get_current_time(){
	char URL[100] = "http://worldclockapi.com/api/json/utc/now";
	
	FILE* output_file;
	output_file = fopen("start_time.json","wb");
	
	CURL* curl;
	int ret_code;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
	curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

	ret_code = curl_easy_perform(curl);

	if(ret_code == CURLE_OK){
		//Download complete
	}
	else{
		printf("Error: %s\n", curl_easy_strerror(ret_code));
	}

	fclose(output_file);
	curl_easy_cleanup(curl);
	
	FILE* json_file = fopen("start_time.json","r");
	
	char json_string[255];
	fgets(json_string,255,json_file);
	
	const cJSON* json_root = cJSON_Parse(json_string);

	const cJSON* time_stamp = cJSON_GetObjectItem(json_root, "currentDateTime");
	const cJSON* time_zone = cJSON_GetObjectItem(json_root, "timeZoneName");
	char* current_time = malloc(5);
	strncpy(current_time,time_stamp->valuestring+11,5);
	
	return current_time;
}