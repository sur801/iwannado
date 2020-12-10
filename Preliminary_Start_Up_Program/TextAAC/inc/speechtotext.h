/*
 * speechtotext.h
 *
 *  Created on: Nov 27, 2019
 *      Author: test
 */

#ifndef SPEECHTOTEXT_H_
#define SPEECHTOTEXT_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#include <stt.h>
#include <privilege_information.h>
#include <privacy_privilege_manager.h>
#include <string.h>

Eina_Bool my_func(void *data);
void _state_changed_cb(stt_h stt, stt_state_e previous, stt_state_e current, void* user_data);
void enter_stt(stt_h *stt);
void exit_stt(stt_h *stt);
void app_request_response_cb(ppm_call_cause_e cause, ppm_request_result_e result, const char *privilege, void *user_data);
void app_check_and_request_permission(void);

#endif /* SPEECHTOTEXT_H_ */
