/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
/* <DESC>
 * Simple HTTPS GET
 * </DESC>
 */ 
//#include <cstdlib>
#include <iostream>
#include <string.h>
#include <curl/curl.h>

#ifndef WIN32 // or something like that...
#define __stdcall
#endif

using namespace std;

bool retrieve = false;

void get_result(char* strDoc){
//https://github.com/cgroza/wx-Youtube/blob/master/tests/xml_curl/xml_curl_test.cxx
}
 
int main(int argc, char* argv[]) {
  CURL *curl;
  CURLcode res;
  std::string responseBody;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
    char url[80]="https://www.nasdaq.com/dividend-stocks/dividend-calendar.aspx?date=";
    cout << url << "\n";
    strcat(url, argv[1]);
    cout << url << "\n";
//  const char* url = "http://kermitproject.org/utf8.html";
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
 
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */ 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
 
#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */ 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

#ifdef VERBOSE
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
 
#ifdef USE_SSL
    curl_easy_setopt(curl, CURLOPT_USE_SSL, 1L);
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_SSLv3);
#endif

    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, (char*)"Dark Secret Ninja/1.0");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, 
//https://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
    static_cast<size_t (__stdcall *)(char*, size_t, size_t, void*)>(
        [](char* ptr, size_t size, size_t nmemb, void* resultBody){
            //*(static_cast<std::string*>(resultBody)) += std::string {ptr, size * nmemb};
            const char* start;
            if (!retrieve) {
                start = strstr(ptr, "<table id=\"Table1");
                if (NULL != start) {
                    retrieve = true;
                } else
                    return nmemb;
            } else
                start = ptr;
            if (retrieve) {
                char *end = strstr((char*)start, "</table>");
                const char *eot = end + 8;
                if (NULL != end) {
                    (static_cast<std::string*>(resultBody))->append(start, eot);
                    retrieve = false;
                } else
                    (static_cast<std::string*>(resultBody))->append(start);
            }
            return nmemb;
        }));

    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  cout << responseBody;
//  char *chrDoc=(char *)responseBody.c_str();
//  get_result(chrDoc);
 
  curl_global_cleanup();
 
  return 0;
} 
