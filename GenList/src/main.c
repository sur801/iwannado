/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd
 *
 * Licensed under the Flora License, Version 1.1 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://floralicense.org/license/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Elementary.h>
#include <app.h>
#include <dlog.h>
#include <system_settings.h>
#include <efl_extension.h>

#include "systemsettings2.h"
#include "view.h"
#include "data.h"
#include "texttospeech.h"
#include "speechtotext.h"

#define FUNC_ITEMS 2
#define CATEGORY_ITEMS 3
#define GREETING_ITEMS 8
#define QANDA_ITEMS 6
#define MART_ITEMS 19

static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it);

static void _gl_display(void);
static void _create_sub_list(void *data, Evas_Object *obj, void *event_info);
static void symbol_recommend(void);

static void _gl_sub_display(int index);
static void _create_category_list(void *data, Evas_Object *obj, void *event_info);

static void _create_greeting_list(void *data, Evas_Object *obj, void *event_info);
static void _create_qanda_list(void *data, Evas_Object *obj, void *event_info);
static void _create_mart_list(void *data, Evas_Object *obj, void *event_info);

void recognition_result_cb(stt_h stt, stt_result_event_e event, const char** data, int data_count, const char* msg, void* user_data);
bool result_time_cb(stt_h stt, int index, stt_result_time_event_e event, const char* text, long start_time, long end_time, void* user_data);


/*
 * @brief: Hook to take necessary actions before main event loop starts
 * Initialize UI resources and application's data
 * If this function returns true, the main loop of application starts
 * If this function returns false, the application is terminated
 */
static bool app_create(void *user_data)
{
	/* Hook to take necessary actions before main event loop starts
	   Initialize UI resources and application's data
	   If this function returns true, the main loop of application starts
	   If this function returns false, the application is terminated */

	app_check_and_request_permission();

	Evas_Object *nf = NULL;
	Evas_Object *genlist = NULL;
	int i = 0;

	/*
	 * Create essential objects.
	 */
	view_create();

	/*
	 * Create a genlist.
	 */
	nf = view_get_naviframe();
	genlist = view_create_circle_genlist(nf);

	/*
	 * Append a genlist's item as a title.
	 */
	view_append_item_to_genlist(genlist, "func.title", NULL, NULL, NULL);

	/*
	 * Append menu items to genlist.
	 */
	for (i = 0; i < FUNC_ITEMS; i++) {
		view_append_item_to_genlist(genlist, "func.1text", (void *)i, _create_sub_list, (void *)i);
	}

	/*
	 * Create a genlist's item as a padding item.
	 * Padding item makes genlist's items is located at the middle of the screen.
	 */
	view_append_item_to_genlist(genlist, "padding", NULL, NULL, NULL);

	/*
	 * Push the genlist at naviframe.
	 */
	view_push_item_to_naviframe(nf, genlist, _naviframe_pop_cb, NULL);

	view_set_genlist(genlist);

	return true;
}

/*
 * @brief: This callback function is called when another application
 * sends the launch request to the application
 */
static void app_control(app_control_h app_control, void *user_data)
{
	/* Handle the launch request. */
}

/*
 * @brief: This callback function is called each time
 * the application is completely obscured by another application
 * and becomes invisible to the user
 */
static void app_pause(void *user_data)
{
	/* Take necessary actions when application becomes invisible. */
}

/*
 * @brief: This callback function is called each time
 * the application becomes visible to the user
 */
static void app_resume(void *user_data)
{
	/* Take necessary actions when application becomes visible. */
}

/*
 * @brief: This callback function is called once after the main loop of the application exits
 */
static void app_terminate(void *user_data)
{
	/* Release all resources. */

	view_destroy();
}

/*
 * @brief: This function will be called when the language is changed
 */
static void ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;

	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);

	if (locale != NULL) {
		elm_language_set(locale);
		free(locale);
	}
	return;
}

/*
 * @brief: main function of the application
 */
int main(int argc, char *argv[])
{
	int ret;

	ui_app_lifecycle_callback_s event_callback = {0, };
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	/*
	 * If you want to handling more events,
	 * Please check the application lifecycle guide
	 */
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, NULL);

	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}

/*
 * @note
 * Below functions are static functions.
 */

/*
 * @brief: This function will be operated when the first item of the naviframe is going to popped.
 * @param[data]: Data needed in this function
 * @param[it]: Item of naviframe
 */
static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	ui_app_exit();

	return EINA_FALSE;
}

/*
 * @brief: This function will be operated when the first genlist's item is clicked
 */
static void _gl_display(void)
{
	Evas_Object *nf = NULL;
	Evas_Object *category_genlist = NULL;
	int i = 0;

	/*
	 * Create a genlist of display menu.
	 */
	nf = view_get_naviframe();
	category_genlist = view_create_circle_genlist(nf);

	view_append_item_to_genlist(category_genlist, "category.title", NULL, NULL, NULL);
	for (i = 0; i < CATEGORY_ITEMS; i++)
		view_append_item_to_genlist(category_genlist, "category.1text", (void *)i, _create_category_list, (void *)i);


	view_append_item_to_genlist(category_genlist, "padding", NULL, NULL, NULL);

	view_push_item_to_naviframe(nf, category_genlist, NULL, NULL);
}

/*
 * @brief: This function will be operated when the second genlist's item is clicked
 */
static void _gl_sub_display(int index)
{
	Evas_Object *nf = NULL;
	Evas_Object *symbol_genlist = NULL;
	int i = 0;

	/*
	 * Create a genlist of display menu.
	 */
	nf = view_get_naviframe();
	symbol_genlist = view_create_circle_genlist(nf);

	switch (index) {
	case 0:
		view_append_item_to_genlist(symbol_genlist, "greeting.title", NULL, NULL, NULL);
		for (i = 0; i < GREETING_ITEMS; i++)
			view_append_item_to_genlist(symbol_genlist, "greeting.1text", (void *)i, _create_greeting_list, (void *)i);
		break;
	case 1:
		view_append_item_to_genlist(symbol_genlist, "qanda.title", NULL, NULL, NULL);
		for (i = 0; i < QANDA_ITEMS; i++)
			view_append_item_to_genlist(symbol_genlist, "qanda.1text", (void *)i, _create_qanda_list, (void *)i);
		break;
	case 2:
		view_append_item_to_genlist(symbol_genlist, "mart.title", NULL, NULL, NULL);
		for (i = 0; i < MART_ITEMS; i++)
			view_append_item_to_genlist(symbol_genlist, "mart.1text", (void *)i, _create_mart_list, (void *)i);
		break;
	default:
		break;
	}

	view_append_item_to_genlist(symbol_genlist, "padding", NULL, NULL, NULL);

	view_push_item_to_naviframe(nf, symbol_genlist, NULL, NULL);
}

static void symbol_recommend(void)
{
	Evas_Object *nf = NULL;
	Evas_Object *label = NULL;
	stt_h *stt = view_get_stt();
	Ecore_Timer *timer;

	nf = view_get_naviframe();
	//layout = view_create_layout(nf, NULL, NULL, NULL, NULL);
	label = elm_label_add(nf);
	elm_object_style_set(label, "slide_roll");
	elm_object_text_set(label, "Recording your speech. Please wait a moment :)");
	elm_label_slide_mode_set(label, ELM_LABEL_SLIDE_MODE_ALWAYS);
	//elm_label_slide_duration_set(label, 10);
	elm_label_slide_go(label);

	elm_object_content_set(nf, label);
	evas_object_show(nf);


	view_push_item_to_naviframe(nf, label, NULL, NULL);

	timer = ecore_timer_add(8, my_func, NULL);
	enter_stt(stt);

	stt_set_recognition_result_cb(*stt, recognition_result_cb, NULL);
	stt_stop(*stt);

}

/* Result time callback */
bool result_time_cb(stt_h stt, int index, stt_result_time_event_e event, const char* text, long start_time, long end_time, void* user_data) {
	dlog_print(DLOG_INFO, "TAG", "Your result: %s", text);
	Evas_Object *nf = NULL;
	Evas_Object *label = NULL;

	nf = view_get_naviframe();
	//layout = view_create_layout(nf, NULL, NULL, NULL, NULL);
	label = elm_label_add(nf);
	elm_object_text_set(label, text);
	elm_label_slide_mode_set(label, ELM_LABEL_SLIDE_MODE_ALWAYS);

	elm_object_content_set(nf, label);
	evas_object_show(nf);

	view_push_item_to_naviframe(nf, label, NULL, NULL);
	return true;
}

/* Recognition result callback */
void recognition_result_cb(stt_h stt, stt_result_event_e event, const char** data, int data_count, const char* msg, void* user_data)
{
	dlog_print(DLOG_INFO,"MY_LOG","into recognition_result_cb");
    /* If you want to get time info of result */
    int ret;
    ret = stt_foreach_detailed_result(stt, result_time_cb, NULL);
	if (STT_ERROR_NONE != ret)
		dlog_print(DLOG_INFO,"MY_LOG","error in stt_foreach_detailed_result");
//	stt_foreach_detailed_result(stt, result_time_cb, user_data);
}

/*
 * @brief: This function will be operated when one of genlist's items is clicked
 * @param[data]: Data passed from 'elm_genlist_item_append' as seventh parameter
 * @param[obj]: Genlist
 * @param[event_info]: A pointer to data which is totally dependent on the smart object's implementation and semantic for the given event
 */
static void _create_sub_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;

	switch (index) {
	case 0:
		/*
		 * String AAC
		 */
		_gl_display();
		break;
	case 1:
		/*
		 * Symbol Recommendation
		 */
		symbol_recommend();
		break;
	default:
		dlog_print(DLOG_ERROR, LOG_TAG, "wrong approach");
		break;
	}
}

static void _create_category_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;

		switch (index) {
		case 0:
			/*
			 * Greetings
			 */
			_gl_sub_display(0);
			break;
		case 1:
			/*
			 * Question & Answer
			 */
			_gl_sub_display(1);
			break;
		case 2:
			/*
			 * Mart
			 */
			_gl_sub_display(2);
			break;
		default:
			dlog_print(DLOG_ERROR, LOG_TAG, "wrong approach");
			break;
		}
}

static void _create_greeting_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "greeting");
}

static void _create_qanda_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "qanda");
}

static void _create_mart_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "mart");
}

/* End of file */
