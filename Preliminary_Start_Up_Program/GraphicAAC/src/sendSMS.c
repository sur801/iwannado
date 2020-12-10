/*
 * sendSMS.c
 *
 *  Created on: Mar 26, 2020
 *      Author: haseungwan
 */

#include "sendSMS.h"
#include <time.h>
#include <dlog.h>
#include <openssl/hmac.h>
#include <string.h>

http_session_h session = NULL;
http_transaction_h transaction = NULL;
static char currentTime[50];

static void
get_current_time() {
	time_t raw_time;
	struct tm* time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);

	sprintf(currentTime, "%d-%s%d-%s%dT%s%d:%s%d:%s%dZ",
			(time_info->tm_year)+1900, time_info->tm_mon<10? "0" : "",(time_info->tm_mon)+1, time_info->tm_mday<10? "0" : "", time_info->tm_mday,
			time_info->tm_hour<10? "0" : "",time_info->tm_hour, time_info->tm_min<10? "0" : "", time_info->tm_min,time_info->tm_sec<10? "0" : "", time_info->tm_sec);

	dlog_print(DLOG_INFO, "SOLAPI", currentTime);
}

static char*
get_HMAC_SHA256(unsigned char* salt)
{
	unsigned char *key = (unsigned char*)"EX47NS7UYFQABVDBVYOR45DFQ4ZN7OTO";
//	unsigned char *data = (unsigned char*) "hoge";
	unsigned char data[64];
	dlog_print(DLOG_INFO, "SOLAPI", data);

//	dlog_print(DLOG_INFO, "SOLAPI", salt);
	strcpy(data,(unsigned char*)currentTime);
	dlog_print(DLOG_INFO, "SOLAPI", data);

	strcat(data,(unsigned char*)salt);
	dlog_print(DLOG_INFO, "SOLAPI", data);
//	unsigned char *expected = (unsigned char*) "4a7bc6c59ebc1a83dc38ec4fd537f98994a9210bf09ad9fc8c60c2ae83746d82";
	unsigned char *result;
	int result_len = 32;
	int i;
	static char res_hexstring[74];

	result = HMAC(EVP_sha256(), key, strlen((char *)key), data, strlen((char *)data), NULL, NULL);

	dlog_print(DLOG_INFO, "SOLAPI", currentTime);
	for (i = 0; i < result_len; i++) {
		sprintf(&(res_hexstring[i * 2]), "%02x", result[i]);
//		dlog_print(DLOG_INFO, "SOLAPI", "33%s",currentTime);
	}

	dlog_print(DLOG_INFO, "SOLAPI", res_hexstring);

	return res_hexstring;
}

static void
initHttp()
{
	int ret = HTTP_ERROR_NONE;
	ret = http_init();
	if (ret != HTTP_ERROR_NONE)
	    printf("http_init failed: %d", ret);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SOLAPI", "HTTP INIT SUCCESS!");
	}
}

static void
deinitHttp()
{
	int ret = HTTP_ERROR_NONE;
	ret = http_deinit();
	if (ret != HTTP_ERROR_NONE)
	    printf("http_deinit failed: %d", ret);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SOLAPI", "HTTP DEINIT SUCCESS!");
	}
}

void
sendSMS(char *phone_check,int randomNum)
{
	char salt[]="jqsba2jxjnrjor";
	char forHeader[256];
	char forBody[256];
//	char *status_text="hehehehehehehehehehehehehehe";
	unsigned char *signature;
	int ret = HTTP_ERROR_NONE;

	initHttp();

	get_current_time();
	signature=get_HMAC_SHA256(&salt);

	sprintf(forHeader, "HMAC-SHA256 apiKey=NCSS2IT45RFETBJO, date=%s, salt=%s, signature=%s", currentTime, salt, signature);
	dlog_print(DLOG_INFO, "SOLAPI", forHeader);
	sprintf(forBody,"{\"message\":{\"to\":\"%s\",\"from\":\"01025761419\",\"text\":\"[Watch AAC] 본인확인 인증번호 %d를 입력해주세요.\"}}", phone_check,randomNum);
//	sprintf(forBody,"2020-99-99");


//	Request URI and data for HTTP POST:
	char uri[1024] = "http://api.solapi.com/messages/v4/send";
//	char uri[1024] = "http://192.168.0.8:8443/status/200";
//	char uri[1024] = "http://watchaac.com/test.php";
	const char* post_header_1=forHeader;
	const char* post_header_2="application/json";
	dlog_print(DLOG_INFO, "SOLAPI", "post header : %s", post_header_1);
	dlog_print(DLOG_INFO, "SOLAPI", "post header : %s", post_header_2);

	const char* post_msg=forBody;
	dlog_print(DLOG_INFO, "SOLAPI", "%s",forBody);
	dlog_print(DLOG_INFO, "SOLAPI", "%s",post_msg);

	ret = http_session_create(HTTP_SESSION_MODE_NORMAL, &session);
	if (ret != HTTP_ERROR_NONE)
	    printf("http_session_create failed: %d", ret);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SOLAPI", "HTTP SESSION CREATE SUCCESS!");
	}

//	Transaction for HTTP POST:
	ret = http_session_open_transaction(session, HTTP_METHOD_POST, &transaction);

	if (ret != HTTP_ERROR_NONE)
	    printf("http_session_open_transaction failed: %d", ret);

	ret = http_transaction_request_set_uri(transaction, uri);
	if (ret != HTTP_ERROR_NONE)
	    printf("http_transaction_request_set_uri failed: %d", ret);

//   Data management for HTTP POST:
//   ret = http_transaction_set_ready_to_write(transaction, 1);
//   if (ret != HTTP_ERROR_NONE)
//	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION SET READY TO WRITE FAIL!");
//   if (ret == HTTP_ERROR_NONE)
//	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION SET READY TO WRITE SUCCESS!");

   http_transaction_header_add_field(transaction, "Authorization", post_header_1);
   if (ret != HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION HEADER ADD FIELD FAIL!");
   if (ret == HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION HEADER ADD FIELD SUCCESS!");

   http_transaction_header_add_field(transaction, "Content-Type", post_header_2);
   if (ret != HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION REQUEST SET HEADER FAIL!");
   if (ret == HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION HEADER ADD FIELD SUCCESS!");

   ret = http_transaction_request_write_body(transaction, post_msg);
   if (ret != HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION REQUEST WRITE BODY FAIL!");
   if (ret == HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION REQUEST WRITE BODY SUCCESS!");

	ret = http_transaction_submit(transaction);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SOLAPI", "HTTP TRANSACTION SUBMIT SUCCESS!");
	}
}
