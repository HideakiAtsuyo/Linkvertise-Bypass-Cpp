#define CURL_STATICLIB
#define api "https://online-coding.eu/api/LinkvertiseBypass.php?url="
#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include "curl/curl.h"

static size_t writefunciton(void* buffer, size_t size, size_t nmemb, void* param)
{
    std::string& text = *static_cast<std::string*>(param);
    size_t totalsize = size * nmemb;
    text.append(static_cast<char*>(buffer), totalsize);
    return totalsize;
}

 int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::wcout << "Linkvertise link:" << std::endl;
    std::string link;
    std::getline(std::cin, link);
    std::string finallink = api;

    finallink = finallink += link;

    std::string result;
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    std::string response;
    std::string header_string;
    char* url;
    double time;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, finallink.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "1337");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunciton);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &time);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        res = curl_easy_perform(curl);
        if (!response._Equal("Error")) {
            std::cout << std::endl << "Result: (" << time << " ms) " << std::endl << response << std::endl; //<< "Launching browser.." << std::endl;
        }
        else {
            std::cout << "Error. (" << time << " ms)" << std::endl; system("pause"); return -1;
        }
        //Fuck browsers in c++ :(
        if (CURLE_OK != res) {
            std::cerr << "CURL error: " << res << '\n';
        }
        curl_global_cleanup();
        curl = NULL;
    }
    system("pause");
}
