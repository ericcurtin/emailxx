#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#include <vector>
#include <sstream>
#include <iostream>

using std::string;
using std::vector;
using std::ostringstream;
using std::cout;

size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  time_t t = time(0);
  const struct tm* now = localtime(&t);
  char date[32];
  strftime(date, sizeof(date), "%a, %d %b %G %T %z", now);

  ostringstream payload;
  payload << "Date: " << date << "\r\n"
          << "To: " << to << "\r\n"
          << "From: " << from << "\r\n"
          << "Subject: " << subject << "\r\n\r\n"
          << body << "\r\n";
  const string payload_str = payload.str();
  cout << payload_str;

  const size_t len = payload_str.size();
  memcpy(ptr, payload_str.c_str(), len);
  upload_ctx->lines_read++;

  return len;
}

void send_email(const string& from, const string& to, const string& subject,
                const string& body) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, "smtp://mail.example.com");

      curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());

      recipients = curl_slist_append(recipients, to.c_str())
      curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

      curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
      curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
      curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);





}

int main() {
  send_email("", "", "", "");
}
