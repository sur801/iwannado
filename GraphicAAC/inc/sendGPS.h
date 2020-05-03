/*
 * sendGPS.h
 *
 *  Created on: Mar 26, 2020
 *      Author: haseungwan
 */

#ifndef SENDGPS_H_
#define SENDGPS_H_

#include <dlog.h>
#include <locations.h>
#include <time.h>
#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <http.h>

http_session_h session;
http_transaction_h transaction;

location_manager_h manager;
location_bounds_h bounds_poly;
//Evas_Object *start, *stop;
Ecore_Timer *timer;
int timer_cnt;//timer 발생 횟수
location_service_state_e state_;
static char currentTime[50];

char *_accuracy_level_to_string(location_accuracy_level_e level);
static void get_current_time();
void _get_last_location(char *phone);
void location_init(char *phone);
//void _location_deinitialize(void);
static void initHttp();
void sendGPS(char *phone, double lat, double lon);

#endif /* SENDGPS_H_ */
