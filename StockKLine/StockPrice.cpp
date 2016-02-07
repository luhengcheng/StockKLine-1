#include "stdafx.h"
#include "StockPrice.h"

//extern "C"
//{

//}
#include <errno.h>
#include <stdlib.h>
#ifndef WIN32
#  include <unistd.h>
#endif


CStockPrice::CStockPrice()
{
}


CStockPrice::~CStockPrice()
{
}

#define MAX_BUF 1024
static char wr_buf[MAX_BUF];
static int  wr_index = 0;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int CStockPrice::DownloadSingleStockPrices(std::string strCode)
{
	CURL *curl;
	FILE *fp;
	CURLcode res;
	std::string strYahooURL = "http://table.finance.yahoo.com/table.csv?s=";
	std::string strStockURL = strYahooURL + strCode;
	std::string strFileName = PRICEFILE_PATH;
	strFileName += strCode;
	strFileName += ".csv";
	curl = curl_easy_init();
	if (curl) {
		if (!fopen_s(&fp, strFileName.c_str(), "wb"))
		{
			curl_easy_setopt(curl, CURLOPT_URL, strStockURL.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			/* always cleanup */
			curl_easy_cleanup(curl);
		}
		fclose(fp);
	}
	return 0;
}