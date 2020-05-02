#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <curl/curl.h>


size_t static curl_write(void *buffer, size_t size, size_t nmemb, void *userp)
{
	userp += strlen(userp);  // Skipping to first unpopulated char
	memcpy(userp, buffer, nmemb);  // Populating it.
	return nmemb;
}

int get_rand()
{
	CURL *curl;
	CURLcode res;
	char *s = (char *) malloc(512);

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.fourmilab.ch/cgi-bin/Hotbits.api?nbytes=1&fmt=c&apikey=Pseudorandom");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	char *src, *dst;
	for (src = s, dst = s; *src; src++) 
	{
		if ('0' <= *src && *src <= '9' || *src == ',')
		{
			*dst++ = *src;
		}
	}
	*dst = '\0';

	char* arrayOfString[128];
	const char d[2] = ", ";
	char *token;
	int i=0;
	/* get the first token */
	token = strtok(s, d);

	/* walk through other tokens */
	while( token != NULL ) 
	{
		arrayOfString[i] = token;
		token = strtok(NULL, d);
		i++;
	}

	int randint;
	randint = atoi(arrayOfString[0]);

	return randint;
}
/*
void main(){
	printf("%d",get_rand());
}*/