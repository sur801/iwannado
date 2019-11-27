#include "FirstView.h"
#include<tts.h>
#include<http.h>


typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *layout;
	Evas_Object *scroller;
	Evas_Object *circle_scroller;
	Evas_Object *box;
	Evas_Object *padding_start;
	Evas_Object *padding_end;
	Evas_Object *index;
	Evas_Object *nf;
	int depth;
	tts_h tts;


} appdata_s;

appdata_s * global_ad;


int op, tts_num;

int pages_count = 4;
#define PAGE_CHANGED_EVENT "active_page,changed"



// Styles for an even number of pages
static const char *even_style[] = {
   "item/even_1",
   "item/even_2",
   "item/even_3",
   "item/even_4",
   "item/even_5",
   "item/even_6",
   "item/even_7",
   "item/even_8",
   "item/even_9",
   "item/even_10",
   "item/even_11",
   "item/even_12",
   "item/even_13",
   "item/even_14",
   "item/even_15",
   "item/even_16",
   "item/even_17",
   "item/even_18",
   "item/even_19",
   "item/even_20",
};

// Styles for an odd number of pages
static const char *odd_style[] = {
   "item/odd_1",
   "item/odd_2",
   "item/odd_3",
   "item/odd_4",
   "item/odd_5",
   "item/odd_6",
   "item/odd_7",
   "item/odd_8",
   "item/odd_9",
   "item/odd_10",
   "item/odd_11",
   "item/odd_12",
   "item/odd_13",
   "item/odd_14",
   "item/odd_15",
   "item/odd_16",
   "item/odd_17",
   "item/odd_18",
   "item/odd_19",
};


static char *menu_its[] = {
   /*** 1line styles ***/
   "greet",
   "ask",
   "mart",
   "add",
   /* do not delete below */
   NULL
};


static char *greet_its[] = {
   /*** 1line styles ***/
   "hello",
   "thankyou",
   "sorry",
   "okay",
   /* do not delete below */
   NULL
};

static char *question_its[] = {
   "good",
   "bad",
   "yes",
   "no",
   NULL
};

static char *mart_its[] = {
   "hello",
   "where",
   "pay",
   "howmuch",
   NULL
};
static void sub_create(void *user_data, Evas* e,  Evas_Object *obj, void *event_info);
static Evas_Object * create_naviframe(Evas_Object *parent);
Elm_Object_Item *view_push_item_to_naviframe(Evas_Object *nf, Evas_Object *item, Elm_Naviframe_Item_Pop_Cb _pop_cb, void *cb_data);
static void win_delete_request_cb(void *data, Evas_Object *obj, void *event_info);
static void win_back_cb(void *data, Evas_Object *obj, void *event_info);
static void _file_abs_resource_path_get(char *res_file_path, char *abs_path, int buf_size);
static void _page_indicator_selected_set(Evas_Object *index, int page_index);
static Evas_Object *_image_create(Evas_Object *parent, char *image_name);
static Evas_Object *_page_layout_create(Evas_Object *parent, int image_index);
static Evas_Object *_padding_item_create(Evas_Object *parent);
static void _layout_resize_cb(void *data , Evas *e, Evas_Object *page_layout, void *event_info);
static void _box_create(appdata_s *ad);
static void _circle_scroller_create(appdata_s *ad);
static void _scroll_cb(void *data, Evas_Object *scroller, void *event);
static void _scroller_create(appdata_s *ad);
static void _active_page_changed_cb(void *data, Evas_Object *index, void *event);
static Evas_Object * _index_create(appdata_s *ad);
static void _page_indicator_create(appdata_s *ad);
static Evas_Object * _image_create_end(Evas_Object *parent, char *image_name);
static void _layout_create(appdata_s *ad);
static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it);
static void gui_tts(void *user_data, Evas* e,  Evas_Object *obj, void *event_info);
void enter_tts(appdata_s *ad);
void state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data);



//tts

void state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data)
{
	if (TTS_STATE_READY == current && TTS_STATE_CREATED == previous) {
		appdata_s *ad = (appdata_s *) user_data;
		int ret;
		const char* text;

		if(op == 0) {
			if(tts_num==0) {
				text = "안녕하세요";
			} else if (tts_num==1) {
				text = "고마워요";
			} else if (tts_num==2){
				text = "미안해요";
			}
			else if (tts_num==3){
				text = "괜찮아요";
			}
		}
		else if(op == 1) {
			if(tts_num==0) {
				text = "좋아요";
			} else if (tts_num==1) {
				text = "싫어요";
			} else if (tts_num==2){
				text = "네";
			}
			else if (tts_num==3){
				text = "아니요";
			}

		}
		else if(op == 2) {
			if(tts_num==0) {
				text = "안녕하세요";
			} else if (tts_num==1) {
				text = "어디에있나요";
			} else if (tts_num==2){
				text = "계산해주세요";
			}
			else if (tts_num==3){
				text = "얼마에요";
			}

		}

		const char* language = "ko_KR"; // Language
		int voice_type = TTS_VOICE_TYPE_FEMALE; // Voice type
		int speed = TTS_SPEED_AUTO; // Read speed
		int utt_id; // Utterance ID for the requested text

		ret = tts_add_text(ad->tts, text, language, voice_type, speed, &utt_id);

		ret = tts_play(ad->tts);
		dlog_print(DLOG_INFO, LOG_TAG, "Added text and started playing");
	}
}

void enter_tts(appdata_s *ad)
{
	int ret;
	ret = tts_create(&(ad->tts));
	ret = tts_set_state_changed_cb(ad->tts, state_changed_cb, ad);
	ret = tts_prepare(ad->tts);
}



//naviframe
static Evas_Object *
create_naviframe(Evas_Object *parent)
{
	Evas_Object *nf = NULL;

		if (parent == NULL) {
			dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
			return NULL;
		}

		nf = elm_naviframe_add(parent);

		elm_naviframe_prev_btn_auto_pushed_set(nf, EINA_TRUE);

		elm_object_part_content_set(parent, "elm.swallow.content", nf);
		eext_object_event_callback_add(nf, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, NULL);
		eext_object_event_callback_add(nf, EEXT_CALLBACK_MORE, eext_naviframe_more_cb, NULL);

		evas_object_show(nf);

		return nf;
}

Elm_Object_Item *view_push_item_to_naviframe(Evas_Object *nf, Evas_Object *item, Elm_Naviframe_Item_Pop_Cb _pop_cb, void *cb_data)
{
	Elm_Object_Item* nf_it = NULL;

	if (nf == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "naviframe is NULL.");
		return NULL;
	}

	if (item == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "item is NULL.");
		return NULL;
	}

	/*
	 * Sixth parameter
	 * @param[item_style] item style name. "empty" style has no button like prev_button and next_button.
	 */
	nf_it = elm_naviframe_item_push(nf, NULL, NULL, NULL, item, "empty");
	elm_naviframe_item_pop_cb_set(nf_it, _pop_cb, cb_data);

	return nf_it;
}


static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

static void
_file_abs_resource_path_get(char *res_file_path, char *abs_path, int buf_size)
{
   char *res_dir_path = app_get_resource_path();
   snprintf(abs_path, buf_size, "%s%s", res_dir_path, res_file_path);

   dlog_print(DLOG_INFO, "hello%s", res_dir_path );
   if (res_dir_path)
     {
	    	snprintf(abs_path, buf_size, "%scategory/%s", res_dir_path, res_file_path);
        dlog_print(DLOG_INFO, "hello%s", abs_path );

        free(res_dir_path);
     }
}

static void
_page_indicator_selected_set(Evas_Object *index, int page_index)
{
   Elm_Object_Item *item_to_select = elm_index_item_find(index, (void *)page_index);
   elm_index_item_selected_set(item_to_select, EINA_TRUE);
}

static void gui_tts(void *user_data, Evas* e,  Evas_Object *obj, void *event_info){
	enter_tts(global_ad);
}

static void
sub_create(void *user_data, Evas* e,  Evas_Object *obj, void *event_info)
{
	/* add
	if(op==3) {

	}*/
    dlog_print(DLOG_INFO, "MY_LOG", evas_object_name_get(obj));
    global_ad->depth = 1;
    _layout_create(global_ad);
    elm_object_content_set(global_ad->nf, global_ad->layout);
    view_push_item_to_naviframe(global_ad->nf, global_ad->layout, _naviframe_pop_cb, NULL);

}



static Evas_Object *
_image_create_end(Evas_Object *parent, char *image_name)
{
   Evas_Object *image = elm_image_add(parent);

   char abs_path_to_image[PATH_MAX] = {0,};
   _file_abs_resource_path_get(image_name, abs_path_to_image, PATH_MAX);
   elm_image_file_set(image, abs_path_to_image, NULL);

   evas_object_size_hint_weight_set(image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(image, EVAS_HINT_FILL, EVAS_HINT_FILL);

   evas_object_event_callback_add (image, EVAS_CALLBACK_MOUSE_DOWN, gui_tts, NULL);

   evas_object_show(image);

   return image;
}

static Evas_Object *
_image_create(Evas_Object *parent, char *image_name)
{
   Evas_Object *image = elm_image_add(parent);
   dlog_print(DLOG_INFO, "MY_LOG",NULL);

   char abs_path_to_image[PATH_MAX] = {0,};
   _file_abs_resource_path_get(image_name, abs_path_to_image, PATH_MAX);
   elm_image_file_set(image, abs_path_to_image, NULL);

   evas_object_size_hint_weight_set(image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(image, EVAS_HINT_FILL, EVAS_HINT_FILL);

   evas_object_event_callback_add (image, EVAS_CALLBACK_MOUSE_DOWN, sub_create, NULL);



   evas_object_show(image);

   return image;
}


static Evas_Object *
_page_layout_create(Evas_Object *parent, int image_index)
{
   Evas_Object *page_layout = elm_layout_add(parent);
   elm_layout_theme_set(page_layout, "layout", "body_thumbnail", "default");
   evas_object_size_hint_weight_set(page_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(page_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(page_layout);

   const int MAX_NAME_LENGTH = 40;
   char image_name[MAX_NAME_LENGTH] = {0,};
   if(!(global_ad->depth)){
	   snprintf(image_name, MAX_NAME_LENGTH, "%s.jpg", menu_its[image_index]);
	   dlog_print(DLOG_INFO, "hehe%s", menu_its[image_index] );
	  // op = global_ad->index;
   }
   else {
	   if(op==0)
		   snprintf(image_name, MAX_NAME_LENGTH, "greet/%s.jpg", greet_its[image_index]);
	   else if(op==1)
		   snprintf(image_name, MAX_NAME_LENGTH, "question/%s.jpg", question_its[image_index]);
	   else if(op==2)
	   	   snprintf(image_name, MAX_NAME_LENGTH, "mart/%s.jpg", mart_its[image_index]);

   }
   Evas_Object *image;

   if(!(global_ad->depth))
	   image = _image_create(page_layout, image_name);
   else
	   image = _image_create_end(page_layout, image_name);
   elm_object_part_content_set(page_layout, "elm.icon", image);

   return page_layout;
}

static Evas_Object *
_padding_item_create(Evas_Object *parent)
{
   Evas_Object *padding = evas_object_rectangle_add(evas_object_evas_get(parent));

   evas_object_size_hint_weight_set(padding, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(padding, EVAS_HINT_FILL, EVAS_HINT_FILL);

   return padding;
}

static void
_layout_resize_cb(void *data , Evas *e, Evas_Object *page_layout, void *event_info)
{
   int page_width;
   int page_height;
   int container_width;
   int container_height;
   appdata_s *ad = data;

   evas_object_geometry_get(page_layout, NULL, NULL, &page_width, &page_height);
   evas_object_geometry_get(ad->scroller, NULL, NULL, &container_width, &container_height);

   int padding_size = (container_width - page_width) / 2;
   //int padding_size = 0;

   evas_object_size_hint_min_set(ad->padding_start, padding_size, container_height);
   evas_object_size_hint_min_set(ad->padding_end, padding_size, container_height);

   elm_scroller_page_size_set(ad->scroller, page_width, page_height);
}


static void
_box_create(appdata_s *ad)
{
   ad->box = elm_box_add(ad->scroller);

   int IMAGES_COUNT = 5;
   Evas_Object *page_layout;
   for (int i = 0; i < pages_count; ++i)
     {
        page_layout = _page_layout_create(ad->box, i % IMAGES_COUNT);
        elm_box_pack_end(ad->box, page_layout);
     }

   evas_object_event_callback_add(page_layout, EVAS_CALLBACK_RESIZE, _layout_resize_cb, ad);

   ad->padding_start = _padding_item_create(ad->box);
   elm_box_pack_start(ad->box, ad->padding_start);

   ad->padding_end = _padding_item_create(ad->box);
   elm_box_pack_end(ad->box, ad->padding_end);

   elm_box_horizontal_set(ad->box, EINA_TRUE);
   evas_object_size_hint_weight_set(ad->box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

   evas_object_show(ad->box);
}

static void
_circle_scroller_create(appdata_s *ad)
{
   Eext_Circle_Surface *surface = eext_circle_surface_conformant_add(ad->nf);

   ad->circle_scroller = eext_circle_object_scroller_add(ad->scroller, surface);

   eext_circle_object_scroller_policy_set(ad->circle_scroller,
                                          ELM_SCROLLER_POLICY_ON,
                                          ELM_SCROLLER_POLICY_OFF);

   eext_rotary_object_event_activated_set(ad->circle_scroller, EINA_TRUE);
}

static void
_scroll_cb(void *data, Evas_Object *scroller, void *event)
{
   static int prev_h_page = 0;
   int cur_h_page         = 0;

   elm_scroller_current_page_get(scroller, &cur_h_page, NULL);
   if (cur_h_page != prev_h_page)
     {
        appdata_s *ad = data;
        evas_object_smart_callback_call(ad->index, PAGE_CHANGED_EVENT, NULL);

        prev_h_page = cur_h_page;
     }
}

static void
_scroller_create(appdata_s *ad)
{
   ad->scroller = elm_scroller_add(ad->layout);

   elm_scroller_policy_set(ad->scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);

   _box_create(ad);
   elm_object_content_set(ad->scroller, ad->box);

   evas_object_smart_callback_add(ad->scroller, "scroll", _scroll_cb, ad);

   _circle_scroller_create(ad);

   evas_object_show(ad->scroller);
}

static void
_active_page_changed_cb(void *data, Evas_Object *index, void *event)
{
   appdata_s *ad     = data;
   int cur_h_page = 0;

   elm_scroller_current_page_get(ad->scroller, &cur_h_page, NULL);
   if(!(global_ad->depth))
	   op = cur_h_page;
   else
	   tts_num = cur_h_page;
   _page_indicator_selected_set(ad->index, cur_h_page);
}

static Evas_Object *
_index_create(appdata_s *ad)
{
   Evas_Object *index = elm_index_add(ad->layout);

   elm_object_style_set(index, "circle");
   elm_index_horizontal_set(index, EINA_TRUE);
   elm_index_autohide_disabled_set(index, EINA_TRUE);

   Eina_Bool is_even_count = pages_count % 2 == 0;
   const int CENTER_INDEX = is_even_count ? 10 : 9;
   int start_index = CENTER_INDEX - pages_count / 2;

   const char **style = is_even_count ? even_style : odd_style;

   for (int i = 0; i < pages_count; ++i)
     {
        Elm_Object_Item *it = elm_index_item_append(index, NULL, NULL, (void *)i);
        elm_object_item_style_set(it, style[start_index + i]);
     }

   elm_index_level_go(index, 0);

   _page_indicator_selected_set(index, 0);

   evas_object_smart_callback_add(index, PAGE_CHANGED_EVENT, _active_page_changed_cb, ad);

   evas_object_show(index);

   return index;
}

static void
_page_indicator_create(appdata_s *ad)
{
   const int MAX_INDEX_STYLE_ITEM = 20;

   if (pages_count > MAX_INDEX_STYLE_ITEM)
     {
        eext_circle_object_scroller_policy_set(ad->circle_scroller,
                                               ELM_SCROLLER_POLICY_ON,
                                               ELM_SCROLLER_POLICY_OFF);
     }
   else
     {
        ad->index = _index_create(ad);
        elm_object_part_content_set(ad->layout, "elm.swallow.content", ad->index);
        eext_circle_object_scroller_policy_set(ad->circle_scroller,
                                               ELM_SCROLLER_POLICY_OFF,
                                               ELM_SCROLLER_POLICY_OFF);
     }
}




static void
_layout_create(appdata_s *ad)
{
   ad->layout = elm_layout_add(ad->nf);


   elm_layout_theme_set(ad->layout, "layout", "application", "default");

   _scroller_create(ad);
   elm_object_part_content_set(ad->layout, "elm.swallow.bg", ad->scroller);

   _page_indicator_create(ad);

   evas_object_show(ad->layout);
}

static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	if(!(global_ad->depth))
		ui_app_exit();
	else{
		global_ad->depth = 0;

	}

	return EINA_FALSE;
}



static void
create_base_gui(appdata_s *ad)
{
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	ad->conform = elm_conformant_add(ad->win);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);


	// naviframe 만들
	ad->nf = create_naviframe(ad->conform);
	elm_object_content_set(ad->conform, ad->nf);

	//layout 만들
	global_ad->depth = 0;
	_layout_create(ad);


	elm_object_content_set(ad->nf, ad->layout);
	view_push_item_to_naviframe(ad->nf, ad->layout, _naviframe_pop_cb, NULL);
	evas_object_show(ad->conform);


	/* Show window after base gui is set up */
	evas_object_show(ad->win);
}




static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;
	global_ad = data;
	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
