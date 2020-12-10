/*
 * sendGPS.c
 *
 *  Created on: Mar 26, 2020
 *      Author: haseungwan
 */
#include "sendGPS.h"

static char currentTime[50];

char *_accuracy_level_to_string(location_accuracy_level_e level)
{
    switch (level) {
    case LOCATIONS_ACCURACY_NONE:
        return "LOCATIONS_ACCURACY_NONE";

    case LOCATIONS_ACCURACY_COUNTRY:
        return "LOCATIONS_ACCURACY_COUNTRY";

    case LOCATIONS_ACCURACY_REGION:
        return "LOCATIONS_ACCURACY_REGION";

    case LOCATIONS_ACCURACY_LOCALITY:
        return "LOCATIONS_ACCURACY_LOCALITY";

    case LOCATIONS_ACCURACY_POSTALCODE:
        return "LOCATIONS_ACCURACY_POSTALCODE";

    case LOCATIONS_ACCURACY_STREET:
        return "LOCATIONS_ACCURACY_STREET";

    case LOCATIONS_ACCURACY_DETAILED:
        return "LOCATIONS_ACCURACY_DETAILED";

    default:
        return "Unknown";
    }
}

static void get_current_time()
{
	time_t raw_time;
	struct tm* time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);

	sprintf(currentTime, "%d-%s%d-%s%d %s%d:%s%d:%s%d",
			(time_info->tm_year)+1900, time_info->tm_mon<10? "0" : "",(time_info->tm_mon)+1, time_info->tm_mday<10? "0" : "", time_info->tm_mday,
			time_info->tm_hour<10? "0" : "",time_info->tm_hour, time_info->tm_min<10? "0" : "", time_info->tm_min,time_info->tm_sec<10? "0" : "", time_info->tm_sec);

	dlog_print(DLOG_INFO, "SOLAPI", currentTime);
}

/* Get the Last Known Location */
void _get_last_location(char *phone)
{
    if (state_ != LOCATIONS_SERVICE_ENABLED) {
        dlog_print(DLOG_ERROR, "SENDGPS", "state is not LOCATIONS_SERVICE_ENABLED");
        return;
    }

    int ret = 0;
    dlog_print(DLOG_DEBUG, "SENDGPS", "_get_last_location_cb");

    double altitude = 0, latitude = 0, longitude = 0, climb = 0, direction = 0, speed = 0;
    double horizontal = 0, vertical = 0;
    location_accuracy_level_e level;
    time_t timestamp;

    ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude,
            &climb, &direction, &speed, &level,
            &horizontal, &vertical, &timestamp);
    if (LOCATIONS_ERROR_NONE != ret) {
        dlog_print(DLOG_ERROR, "SENDGPS", "location_manager_get_last_location failed : %d", ret);
    }
    else {
        dlog_print(DLOG_DEBUG, "SENDGPS", "Last location: La:%f Lo:%f", latitude, longitude);
        dlog_print(DLOG_INFO, "SENDGPS", "phone in not CB : %s", phone);
        sendGPS(phone,latitude,longitude);
    }
}

//callback for timer
/* Get the Last Known Location */
void _get_last_location_cb(char *phone, Evas_Object *obj, void *event_info)
{
	dlog_print(DLOG_INFO, "SENDGPS", "phone in CB : %s", phone);
    if (state_ != LOCATIONS_SERVICE_ENABLED) {
        dlog_print(DLOG_ERROR, "SENDGPS", "state is not LOCATIONS_SERVICE_ENABLED");
        return;
    }

    int ret = 0;
    dlog_print(DLOG_DEBUG, "SENDGPS", "_get_last_location_cb");

    double altitude = 0, latitude = 0, longitude = 0, climb = 0, direction = 0, speed = 0;
    double horizontal = 0, vertical = 0;
    location_accuracy_level_e level;
    time_t timestamp;

    ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude,
            &climb, &direction, &speed, &level,
            &horizontal, &vertical, &timestamp);
    if (LOCATIONS_ERROR_NONE != ret) {
        dlog_print(DLOG_ERROR, "SENDGPS", "location_manager_get_last_location failed : %d", ret);
    }
    else {
        dlog_print(DLOG_DEBUG, "SENDGPS", "Last location: La:%f Lo:%f", latitude, longitude);
        sendGPS(phone,latitude,longitude);
    }
}


void location_init(char * phone)
{
    bool is_enabled = false;
    int ret = location_manager_is_enabled_method(LOCATIONS_METHOD_HYBRID, &is_enabled);
    if (LOCATIONS_ERROR_NONE != ret) {
        dlog_print(DLOG_ERROR, "SENDGPS", "location_manager_is_enabled_method failed : %d", ret);
        return;
    }

    if (true != is_enabled) {
        state_ = LOCATIONS_SERVICE_DISABLED;
        return;
    }

    state_ = LOCATIONS_SERVICE_ENABLED;
    /* Create a location manager handle */
    ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
    if (LOCATIONS_ERROR_NONE != ret) {
        dlog_print(DLOG_ERROR, "SENDGPS", "location_manager_create failed : %d", ret);
        return;
    }

    /* Start the location service */
    ret = location_manager_start(manager);
    if (LOCATIONS_ERROR_NONE != ret) {
        dlog_print(DLOG_ERROR, "SENDGPS", "location_manager_start failed : %d", ret);
        return;
    }

    dlog_print(DLOG_ERROR, "SENDGPS", "location_manager_start success");
//    _get_last_location(phone);
//    dlog_print(DLOG_INFO, "SENDGPS", "phone in init : %s", phone);
    timer=ecore_timer_add(1800, _get_last_location_cb, phone);
}

//void _location_deinitialize(void)
//{
//	ecore_timer_freeze(timer1);
//	ecore_timer_del(timer1);
//	dlog_print(DLOG_DEBUG, LOG_TAG, "Stop getting location");
//
//    if (elm_object_disabled_get(start)) {
//        /* Destroy the polygon bounds */
//        int ret = location_bounds_destroy(bounds_poly);
//        bounds_poly = NULL;
//
//        /* Unset all connected callback functions */
//
//        ret = gps_status_unset_satellite_updated_cb(manager);
//        dlog_print(DLOG_DEBUG, LOG_TAG, "gps_status_set_satellite_updated_cb: %d", ret);
//
//        ret = location_manager_unset_service_state_changed_cb(manager);
//        dlog_print(DLOG_DEBUG, LOG_TAG, "location_manager_unset_service_state_changed_cb: %d", ret);
//
//        /* Stop the Location Manager */
//        ret = location_manager_stop(manager);
//        dlog_print(DLOG_DEBUG, LOG_TAG, "location_manager_stop: %d", ret);
//        PRINT_MSG("location_manager_stop success");
//
//        /* Destroy the Location Manager */
//        ret = location_manager_destroy(manager);
//        manager = NULL;
//        dlog_print(DLOG_DEBUG, LOG_TAG, "location_manager_destroy: %d", ret);
////        elm_object_disabled_set(start, EINA_FALSE);
////        elm_object_disabled_set(stop, EINA_TRUE);
//    }
//}

static void
initHttp()
{
	int ret = HTTP_ERROR_NONE;
	ret = http_init();
	if (ret != HTTP_ERROR_NONE)
	    printf("http_init failed: %d", ret);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SENDGPS", "HTTP INIT SUCCESS!");
	}

}

void
sendGPS(char *phone, double lat, double lon)
{
	char forBody[256];
	int ret = HTTP_ERROR_NONE;

	initHttp();

	get_current_time();

//	Request URI and data for HTTP POST:
	char uri[1024] = "http://watchaac.com/send_gps.php";

	const char* post_header="application/json";
	dlog_print(DLOG_INFO, "SENDGPS", "post header : %s", post_header);
	sprintf(forBody,"%s,%s,%lf,%lf", phone,currentTime,lat,lon);
//	sprintf(forBody,"01072027518,%s,%lf,%lf",currentTime,lat,lon);

	const char* post_msg=forBody;
	dlog_print(DLOG_INFO, "SENDGPS", "%s",forBody);
	dlog_print(DLOG_INFO, "SENDGPS", "%s",post_msg);

	ret = http_session_create(HTTP_SESSION_MODE_NORMAL, &session);
	if (ret != HTTP_ERROR_NONE)
	    printf("http_session_create failed: %d", ret);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SENDGPS", "HTTP SESSION CREATE SUCCESS!");
	}

//	Transaction for HTTP POST:
	ret = http_session_open_transaction(session, HTTP_METHOD_POST, &transaction);

	if (ret != HTTP_ERROR_NONE)
	    printf("http_session_open_transaction failed: %d", ret);

	ret = http_transaction_request_set_uri(transaction, uri);
	if (ret != HTTP_ERROR_NONE)
	    printf("http_transaction_request_set_uri failed: %d", ret);

   http_transaction_header_add_field(transaction, "Content-Type", post_header);
   if (ret != HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SENDGPS", "HTTP TRANSACTION REQUEST SET HEADER FAIL!");
   if (ret == HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SENDGPS", "HTTP TRANSACTION HEADER ADD FIELD SUCCESS!");

   ret = http_transaction_request_write_body(transaction, post_msg);
   if (ret != HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SENDGPS", "HTTP TRANSACTION REQUEST WRITE BODY FAIL!");
   if (ret == HTTP_ERROR_NONE)
	   dlog_print(DLOG_INFO, "SENDGPS", "HTTP TRANSACTION REQUEST WRITE BODY SUCCESS!");

	ret = http_transaction_submit(transaction);
	if (ret == HTTP_ERROR_NONE){
		dlog_print(DLOG_INFO, "SENDGPS", "HTTP TRANSACTION SUBMIT SUCCESS!");
	}
}

