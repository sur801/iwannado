/*
 * sendSMS.h
 *
 *  Created on: Mar 26, 2020
 *      Author: haseungwan
 */

#ifndef SENDSMS_H_
#define SENDSMS_H_

#include <http.h>


http_session_h session;
http_transaction_h transaction;
static char currentTime[50];

static void get_current_time();
static char* get_HMAC_SHA256(unsigned char* salt);
static void initHttp();
static void deinitHttp();
void sendSMS(char* phone_check,int randomNum);


#endif /* SENDSMS_H_ */
