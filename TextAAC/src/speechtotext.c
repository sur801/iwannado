/*
 * speechtotext.c
 *
 *  Created on: Nov 27, 2019
 *      Author: test
 */

#include "speechtotext.h"
#include <stt.h>
#include <privilege_information.h>
#include <privacy_privilege_manager.h>
#include <string.h>

char *resultText;

Eina_Bool my_func(void *data)
{
    return ECORE_CALLBACK_CANCEL;
}

void _state_changed_cb(stt_h stt, stt_state_e previous, stt_state_e current, void* user_data) {
	int ret;
	dlog_print(DLOG_INFO,"MY_LOG","Your into state_change_cb");
	dlog_print(DLOG_INFO, "TAG", "Your state %d", current);
	if (STT_STATE_CREATED == current){
		dlog_print(DLOG_INFO,"MY_LOG","nnnnnnnnnnnnnnnn");
		dlog_print(DLOG_INFO,"MY_LOG","now is created state");
		dlog_print(DLOG_INFO, "TAG", "Your state %d", current);
	}

	if (STT_STATE_READY == current){
//		Ecore_Timer *timer;
//		timer=ecore_timer_add(8, my_func, ad);

//		ret = stt_start(ad->stt, NULL, STT_RECOGNITION_TYPE_FREE);//언어 설정
		ret = stt_start(stt,"ko_KR",STT_RECOGNITION_TYPE_FREE);//언어 설정
//		ret = stt_start(ad->stt,"en_US",STT_RECOGNITION_TYPE_FREE);
		dlog_print(DLOG_INFO,"MY_LOG","nnnnnnnnnnnnnnnn");
		dlog_print(DLOG_INFO, "TAG", "Your state %d", current);
		if (STT_ERROR_NONE != ret){
			dlog_print(DLOG_INFO,"MY_LOG", "%s  : %s : %d",__func__,__FILE__,ret);
			dlog_print(DLOG_INFO,"MY_LOG","error in starting stt");
		} else{
			dlog_print(DLOG_INFO,"MY_LOG","start success dont forget");
		}
	}
}

void enter_stt(stt_h *stt)
{
	int ret;
	dlog_print(DLOG_INFO,"MY_LOG","into enter_stt");

	resultText = (char *)malloc(256);

	ret=stt_create(stt);
	if (STT_ERROR_NONE != ret)
	{
		dlog_print(DLOG_INFO,"MY_LOG","Error in stt_create");
		dlog_print(DLOG_INFO,"MY_LOG","%d",ret);
	}
	else
	{
		dlog_print(DLOG_INFO,"MY_LOG","Success stt_create");
	}

//	ret = stt_set_state_changed_cb(ad->stt, state_changed_cb, ad);

	ret=stt_prepare(*stt);
	if (STT_ERROR_NONE != ret)
	{
		dlog_print(DLOG_INFO,"MY_LOG","Error in stt_prepare");
		dlog_print(DLOG_INFO,"MY_LOG","%d",ret);
	}
	else
	{
		dlog_print(DLOG_INFO,"MY_LOG","Success stt_prepare");
	}

	ret=stt_set_state_changed_cb(*stt, _state_changed_cb, NULL);
	if (STT_ERROR_NONE != ret)
		dlog_print(DLOG_INFO,"MY_LOG","Your error in setting state changed cb");

//	dlog_print(DLOG_INFO,"MY_LOG","Your pass set_state_change_cb");

//	stt_set_recognition_result_cb(ad->stt, recognition_result_cb,NULL);
//	stt_set_state_changed_cb(ad->stt, state_changed_cb, NULL);
//	stt_set_error_cb(ad->stt, error_cb, NULL);
}

void exit_stt(stt_h *stt)
{
	stt_unprepare(*stt);
	stt_destroy(*stt);
}

void
app_request_response_cb(ppm_call_cause_e cause, ppm_request_result_e result, const char *privilege, void *user_data)
{
	if (cause == PRIVACY_PRIVILEGE_MANAGER_CALL_CAUSE_ERROR) {
		/* Log and handle errors */

		return;
	}

	switch (result) {
	case PRIVACY_PRIVILEGE_MANAGER_REQUEST_RESULT_ALLOW_FOREVER:
		/* Update UI and start accessing protected functionality */
		break;
	case PRIVACY_PRIVILEGE_MANAGER_REQUEST_RESULT_DENY_FOREVER:
		/* Show a message and terminate the application */
		break;
	case PRIVACY_PRIVILEGE_MANAGER_REQUEST_RESULT_DENY_ONCE:
		/* Show a message with explanation */
		break;
	}
}


//for check Privacy-related Permissions
void
app_check_and_request_permission(void)
{
	ppm_check_result_e result;
	const char *privilege = "http://tizen.org/privilege/recorder";

	int ret = ppm_check_permission(privilege, &result);

	if (ret == PRIVACY_PRIVILEGE_MANAGER_ERROR_NONE) {
		switch (result) {
		case PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW:
			/* Update UI and start accessing protected functionality */
			break;
		case PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_DENY:
			/* Show a message and terminate the application */
			break;
		case PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ASK:
			ret = ppm_request_permission(privilege, app_request_response_cb, NULL);
			/* Log and handle errors */
			break;
		}
	}
	else {
		/* ret != PRIVACY_PRIVILEGE_MANAGER_ERROR_NONE */
		/* Handle errors */
	}
}
