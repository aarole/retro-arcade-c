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

int GetCurl()
{
    CURL *curl;
    CURLcode res;

    

     char *s = (char *) malloc(512);

     curl = curl_easy_init();
     if (curl)
     {
          curl_easy_setopt(curl, CURLOPT_URL, "https://www.fourmilab.ch/cgi-bin/Hotbits.api?nbytes=128&fmt=c&apikey=Pseudorandom");
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
		printf("%s\n", s);
		
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

   for(i=0;i<128;i++)
    printf("%s\n", arrayOfString[i]);

   
	return 0;
}


int main()
{
	GetCurl();
	
}