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
#define CATEGORY_ITEMS 6
#define CORE_ITEMS 10
#define MART_ITEMS 8
#define CLASS_ITEMS 9
#define FOOD_ITEMS 7
#define HOSPITAL_ITEMS 8
#define PE_ITEMS 7

#define SETTING_ITEM 1




static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it);

static void _gl_display(void);


static void _gl_sub_display(int index);
static void _create_category_list(void *data, Evas_Object *obj, void *event_info);

static void _create_core_list(void *data, Evas_Object *obj, void *event_info);
static void _create_class_list(void *data, Evas_Object *obj, void *event_info);
static void _create_mart_list(void *data, Evas_Object *obj, void *event_info);
static void _create_food_list(void *data, Evas_Object *obj, void *event_info);
static void _create_hospital_list(void *data, Evas_Object *obj, void *event_info);
static void _create_pe_list(void *data, Evas_Object *obj, void *event_info);


void recognition_result_cb(stt_h stt, stt_result_event_e event, const char** data, int data_count, const char* msg, void* user_data);
bool result_time_cb(stt_h stt, int index, stt_result_time_event_e event, const char* text, long start_time, long end_time, void* user_data);



/*
 *기본 앱 정보를 display해주는 함수
 */

static void _app_info_display(void) {
	Evas_Object * layout = elm_layout_add(view_get_naviframe());
	elm_layout_theme_set(layout, "layout", "application", "default");

	Evas_Object* logo_img = elm_image_add(layout);

	// 세팅창 켜져있음.
	setting_on = 2;
	/*로고 이미지 붙이기*/
	char abs_path_to_image[PATH_MAX] = {0,};
	char *res_dir_path = app_get_resource_path();
	snprintf(abs_path_to_image,PATH_MAX, "%s%s", res_dir_path, "logo.png");


	evas_object_image_file_set(logo_img, abs_path_to_image, NULL);
	evas_object_geometry_set(logo_img, 121, 10, 120,120);
	dlog_print(DLOG_INFO, LOG_TAG, "image_path : %s",abs_path_to_image);
	evas_object_size_hint_weight_set(logo_img, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(logo_img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(logo_img);

	/*앱 info label붙이기*/
	Evas_Object * label = elm_label_add(layout);
	elm_object_text_set(label,
	"<br><br><br><br><br><br><align=center><font_size=25>개발사 : 하고싶다</font> <br> <font_size=25>이메일 : hswom@naver.com </font> <br> <font_size=15>위치 관리 번호를 등록하셨을 경우 </font> <br> <font_size=15>사용자 위치를 www.watchacc.com에서 확인하실 수 있습니다.</font> <br> <font_size = 15>사용법 및 기능에 자세한 내용은 </br> www.watchaac.com에서 확인하실 수 있습니다.</font><br><font_size = 15>본 어플리케이션은 <br>AAC 전문기관 '사람과 소통' 의 도움을 받아 제작되었습니다.</font></align> ");

	elm_object_style_set(label, "marker");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(label);
	elm_object_content_set(layout,label);





//	/*app info page scroller 생성 */
//	Evas_Object* scroller;
//	scroller = elm_scroller_add(layout);
//	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);
//	evas_object_geometry_set(scroller, 121, 20, 120,120);
//	//elm_object_content_set(layout, scroller);
//	evas_object_show(scroller);


	evas_object_show(layout);

	 view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);

}


/*
 * 세팅 뷰를 만드는 함수
 */
static void _create_setting_layout(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;

	switch (index) {
	case 0:
		/*
		 * String AAC
		 */
		_app_info_display();
		break;
	case 1:
		/*
		 * Symbol Recommendation
		 */
		break;
	default:
		dlog_print(DLOG_ERROR, LOG_TAG, "wrong approach");
		break;
	}
}


// Callback function for the "more,option,opened" signal
// This callback is called when the more_option is seen
void
_opened_cb(void *data, Evas_Object *obj, void *event_info)
{

	// 더보기 버튼 이미지 주소받아와서 call back함수 삭제해주기. 설정창 한번 키면 또 눌러도 켜지지 않도록.
	//evas_object_event_callback_del(more_btn, EVAS_CALLBACK_MOUSE_DOWN, _opened_cb);
	//evas_object_event_callback_del_full(more_btn, EVAS_CALLBACK_MOUSE_DOWN, _opened_cb, NULL);
	//evas_object_freeze_events_set(more_btn, EINA_TRUE);
	evas_object_image_file_set(more_image, NULL, NULL);
	evas_object_geometry_set(more_image, 0, 0, 10, 10);
	//evas_object_geometry_set(more_image, 0, 0, 35, 35);

	// setting창 들어간 것 표시
		setting_on = 1;
		dlog_print(DLOG_INFO, LOG_TAG, "Open the More Option\n");

		Evas_Object *setting_genlist = NULL;

		/* From here, we make genlist for voice memo list */
		/* make genlist and shape genlist circle */
		setting_genlist = view_create_circle_genlist(view_get_naviframe());
		view_push_item_to_naviframe(view_get_naviframe(), setting_genlist,NULL, NULL);

		//append title to genlist.
		view_append_item_to_genlist(setting_genlist, "setting.title", NULL, NULL, NULL);

		// append items to genlist .
		int i;
		for (i = 0; i < SETTING_ITEM; i++) {
			view_append_item_to_genlist(setting_genlist, "setting.1text", (void *)i, _create_setting_layout, (void *)i);
		}
		evas_object_show(setting_genlist);
		/*
		 * Create a genlist's item as a padding item.
		 * Padding item makes genlist's items is located at the middle of the screen.
		 */
		view_append_item_to_genlist(setting_genlist, "padding", NULL, NULL, NULL);

		/*
		 * Push the genlist at naviframe.
		 */


}





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

	setting_on = 0;
	app_check_and_request_permission();

	Evas_Object *nf = NULL;
	int i = 0;

	/*
	 * Create essential objects.
	 */
	view_create();

	_gl_display();


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
	category_genlist = NULL;
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

	view_push_item_to_naviframe(nf, category_genlist, _naviframe_pop_cb, NULL);

//더보기 버튼 이미지 삽입
	more_image = elm_image_add(category_genlist);

	char abs_path_to_image[PATH_MAX] = {0,};
	char *res_dir_path = app_get_resource_path();
	snprintf(abs_path_to_image,PATH_MAX, "%s%s", res_dir_path, "vertical_more_ic.png");

	evas_object_image_file_set(more_image, abs_path_to_image, NULL);
	evas_object_geometry_set(more_image, 330, 162, 35, 35);
	dlog_print(DLOG_INFO, LOG_TAG, "image_path : %s",abs_path_to_image);
	evas_object_size_hint_weight_set(more_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(more_image, EVAS_HINT_FILL, EVAS_HINT_FILL);

	// 더보기 버튼에 open callback 함수 달아줌
	evas_object_event_callback_add (more_image, EVAS_CALLBACK_MOUSE_DOWN, _opened_cb, (void*)more_image);
	evas_object_show(more_image);



}

/*
 * @brief: This function will be operated when the second genlist's item is clicked
 */
static void _gl_sub_display(int index)
{
	Evas_Object *nf = NULL;
	Evas_Object *symbol_genlist = NULL;
	int i = 0;

	//setting 버튼 없애기.
	//evas_object_event_callback_del(more_image, EVAS_CALLBACK_MOUSE_DOWN, _opened_cb);
	evas_object_geometry_set(more_image, 0, 0, 10, 10);
	evas_object_image_file_set(more_image, NULL, NULL);
	setting_on = 0;

	/*
	 * Create a genlist of display menu.
	 */
	nf = view_get_naviframe();
	symbol_genlist = view_create_circle_genlist(nf);

	switch (index) {
	case 0:
		view_append_item_to_genlist(symbol_genlist, "core.title", NULL, NULL, NULL);
		for (i = 0; i < CORE_ITEMS; i++)
			view_append_item_to_genlist(symbol_genlist, "core.1text", (void *)i, _create_core_list, (void *)i);
		break;
	case 1:
		view_append_item_to_genlist(symbol_genlist, "mart.title", NULL, NULL, NULL);
			for (i = 0; i < MART_ITEMS; i++)
				view_append_item_to_genlist(symbol_genlist, "mart.1text", (void *)i, _create_mart_list, (void *)i);
			break;
	case 2:
		view_append_item_to_genlist(symbol_genlist, "class.title", NULL, NULL, NULL);
			for (i = 0; i < CLASS_ITEMS; i++)
				view_append_item_to_genlist(symbol_genlist, "class.1text", (void *)i, _create_class_list, (void *)i);
			break;
	case 3:
		view_append_item_to_genlist(symbol_genlist, "food.title", NULL, NULL, NULL);
			for (i = 0; i < FOOD_ITEMS; i++)
				view_append_item_to_genlist(symbol_genlist, "food.1text", (void *)i, _create_food_list, (void *)i);
			break;
	case 4:
		view_append_item_to_genlist(symbol_genlist, "hospital.title", NULL, NULL, NULL);
			for (i = 0; i < HOSPITAL_ITEMS; i++)
				view_append_item_to_genlist(symbol_genlist, "hospital.1text", (void *)i, _create_hospital_list, (void *)i);
			break;
	case 5:
		view_append_item_to_genlist(symbol_genlist, "pe.title", NULL, NULL, NULL);
			for (i = 0; i < PE_ITEMS; i++)
				view_append_item_to_genlist(symbol_genlist, "pe.1text", (void *)i, _create_pe_list, (void *)i);
			break;

	default:
		break;
	}

	view_append_item_to_genlist(symbol_genlist, "padding", NULL, NULL, NULL);

	view_push_item_to_naviframe(nf, symbol_genlist, NULL, NULL);
}


/* Result time callback */
bool result_time_cb(stt_h stt, int index, stt_result_time_event_e event, const char* text, long start_time, long end_time, void* user_data) {
	dlog_print(DLOG_INFO, "TAG", "Your result: %s", text);
	Evas_Object *nf = NULL;
	Evas_Object *label = NULL;

	nf = view_get_naviframe();
	label = elm_label_add(nf);
	elm_object_style_set(label, "slide_roll");
	elm_object_text_set(label, text);
	elm_label_slide_mode_set(label, ELM_LABEL_SLIDE_MODE_ALWAYS);
	elm_label_slide_duration_set(label, 10);
	elm_label_slide_go(label);

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

static void _create_category_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;

		switch (index) {
		case 0:
			/*
			 * core words
			 */
			_gl_sub_display(0);
			break;
		case 1:
			/*
			 * buy
			 */
			_gl_sub_display(1);
			break;
		case 2:
			/*
			 * class
			 */
			_gl_sub_display(2);
			break;
		case 3:
			/*
			 * food
			 */
			_gl_sub_display(3);
			break;
		case 4:
			/*
			 * hospital
			 */
			_gl_sub_display(4);
			break;
		case 5:
			/*
			 * Physical education
			 */
			_gl_sub_display(5);
			break;
		default:
			dlog_print(DLOG_ERROR, LOG_TAG, "wrong approach");
			break;
		}
}

static void _create_core_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "core");
}

static void _create_class_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "class");
}

static void _create_mart_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "mart");
}

static void _create_food_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "food");
}

static void _create_hospital_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "hospital");
}

static void _create_pe_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
	tts_h *tts = view_get_tts();
	enter_tts(tts, index, "pe");
}

/* End of file */
