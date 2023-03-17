#include <iostream>
#include <fstream>
#include <clocale>
#include <map>
#include <vector>
#include <winsock2.h>
#include <ctime>
#include <windows.h>
#include <curl/curl.h>
#include <nlohmann\json.hpp>
using namespace nlohmann;

size_t write_function(char *ptr,size_t size,size_t nmemb, void *data)
{
    size_t r = fwrite(ptr,size,nmemb,(FILE*)data);
    return r;
}

void quick(std::vector <float> &arr, int k, int left, int right) {
    int i = left;
    int j = right;
    float x = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < x)
            i++;

        while (arr[j] > x)
            j--;

        if (i <= j)
            std::swap(arr[i++], arr[j--]);
    }

    if (left < j && k <= j)
        quick(arr, k, left, j);

    if (i < right && k >= i)
        quick(arr, k, i, right);
}

struct val {
    std::vector<float> collect;
    float sum = 0;

    float median() {
        int m = collect.size() / 2;
        float res;
        quick(collect, m, 0, collect.size());

        if (collect.size() % 2 == 1)
            res = collect[m];
        else {
            quick(collect, m - 1, 0, collect.size());
            res = (collect[m] + collect[m - 1]) / 2;
        }
        return res;
    }
    float average() {
        float res = sum / collect.size();
        return res;
    }

    void clear() {
        collect.clear();
        sum = 0;
    }
};


int main(int argc, char *argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int sec = 0;
    std::cout << "введите количество секунд\n";
    std::cin >> sec;
    sec *= 1000;
    FILE *f;
    json j;
    val ex;

    bool flag = true, flag_new = false;
    int i = 0, count_of_valute = 0, count_of_valute_new = 0;
    std::map<std::string, val> all;
    auto it_find = all.begin();

    while ((GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0) {

            f = fopen("currency.json","wb");
            CURL *  curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
                curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_function);
                curl_easy_setopt(curl,CURLOPT_WRITEDATA,f);
                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }
            fclose(f);
            std::fstream file("currency.json");
            file >> j;
            json::iterator it = j["Valute"].begin();
            while (it != j["Valute"].end()) {
                it_find = all.begin();
                it_find = all.find(it.value()["CharCode"]);
                if (it_find == all.end()) {
                    ex.collect.push_back((float)it.value()["Value"]);
                    ex.sum += (float)it.value()["Value"];
                    all.insert(std::make_pair(it.value()["CharCode"], ex));
                }
                else {
                    it_find->second.collect.push_back((float)it.value()["Value"]);
                    it_find->second.sum += (float)it.value()["Value"];
                }
                std::cout << it.value()["Name"] << " (" << it.key() << ") --- "<< it.value()["Value"] << std::endl;
                it++;
            }
            ex.clear();
            Sleep(sec);
            system("cls");
    }
    std::cout << "\nсреднее значение валют и их МеДиАнА ^-^ !!!!!!!: \n";
    it_find = all.begin();
    while (it_find != all.end()) {
        std::cout << it_find->first << " - " << it_find->second.average() << " - "
                  << it_find->second.median() << std::endl;
        it_find++;
    }

    return 0;
}
