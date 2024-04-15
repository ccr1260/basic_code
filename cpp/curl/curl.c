#include <curl/curl.h>
#include <string>
#include <iostream>

int main()
{
    CURL *curl;
    CURLcode res;
    long rsl_code;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        std::string url = "http://192.168.20.131:8000/room/v0/process";
        std::string data = "{\"roomId\":1, \"username\":\"wanh\", \"audioData\":\"hello\"}"; 
        // 设置url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // 设置post的数据内容
        // curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        // 发送请求
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // 处理响应数据（这里简单打印出来）
            std::cout << "Response: " << curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rsl_code) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}