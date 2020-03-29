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

#include <tizen.h>
#include <dlog.h>
#include <efl_extension.h>
#include <Elementary.h>
#include <app.h>
#include <tts.h>

#include "systemsettings2.h"
#include "view.h"
#include "data.h"
#define SETTING_ITEMS 3
static struct view_info {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *layout;
	Evas_Object *nf;
	Evas_Object *genlist;
	Evas_Object *circle_genlist;
	Evas_Object *label;
	Eext_Circle_Surface *circle_surface;
	tts_h tts;
	stt_h stt;

} s_info = {
	.win = NULL,
	.conform = NULL,
	.layout = NULL,
	.nf = NULL,
	.genlist = NULL,
	.circle_genlist = NULL,
	.label = NULL,
	.circle_surface = NULL,
	.tts = NULL,
	.stt = NULL,
};

static Elm_Genlist_Item_Class *_set_genlist_item_class(const char *style);
static void _win_delete_request_cb(void *data, Evas_Object *obj, void *event_info);
static void _gl_selected_cb(void *data, Evas_Object *obj, void *event_info);


tts_h *view_get_tts(void)
{
	return &(s_info.tts);
}

stt_h *view_get_stt(void)
{
	return &(s_info.stt);
}

/*
 * @brief: Get naviframe
 */
Evas_Object *view_get_naviframe(void)
{
	return s_info.nf;
}

/*
 * @brief: Get genlist
 */
Evas_Object *view_get_genlist(void)
{
	return s_info.genlist;
}

/*
 * @brief: Set genlist
 * @param[genlist]: Genlist will be stored in view_info
 */
void view_set_genlist(Evas_Object *genlist)
{
	s_info.genlist = genlist;
}

/*
 * MORE 버튼 만들어주기
 */
Evas_Object *view_set_more_button(Evas_Object *parent, const char *part_name, Evas_Smart_Cb _item_selected, void *user_data)
{
	Evas_Object *more_btn = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	more_btn = eext_more_option_add(parent);
	if (more_btn == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "more option is NULL.");
		return NULL;
	}

	/* Add smart callback */
	//evas_object_smart_callback_add(more_btn, "item,clicked", _item_selected, user_data);

	// set_more 버튼의 위치 조정. 하단에 위치시킴.
	//evas_object_geometry_set(more_btn, 15, 340, NULL, NULL);

	// set_more 버튼의 위치 조정. 오른쪽에 위치시킴
	evas_object_geometry_set(more_btn, 180, 180, NULL, NULL);
	elm_object_part_content_set(parent, part_name, more_btn);


	return more_btn;
}


static void _create_category_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;

		switch (index) {
		case 0:
			/*
			 * Greetings
			 */
			//_gl_sub_display(0);
			break;
		case 1:
			/*
			 * Question & Answer
			 */
			//_gl_sub_display(1);
			break;
		case 2:
			/*
			 * Mart
			 */
			//_gl_sub_display(2);
			break;
		default:
			dlog_print(DLOG_ERROR, LOG_TAG, "wrong approach");
			break;
		}
}


Evas_Object* view_get_layout(){
	return s_info.layout;
}

Evas_Object* view_get_conform(){
	return s_info.conform;
}

/*
 * @brief: Create Essential Object window, conformant and layout
 */
void view_create(void)
{
	/* Create window */
	s_info.win = view_create_win(PACKAGE);
	if (s_info.win == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a window.");
		return;
	}

	/* Create conformant */
	s_info.conform = view_create_conformant_without_indicator(s_info.win);
	if (s_info.conform == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a conformant");
		evas_object_del(s_info.win);
		return;
	}

	/*
	 * Eext Circle Surface Creation
	 */
	s_info.circle_surface = eext_circle_surface_conformant_add(s_info.conform);

	s_info.layout = view_create_layout_for_conformant(s_info.conform, NULL, NULL, NULL, NULL);





	s_info.nf = view_create_naviframe(s_info.layout);
	if (s_info.nf == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a naviframe.");
		evas_object_del(s_info.win);
		return;
	}


	/* Show window after main view is set up */
	evas_object_show(s_info.win);
}

/*
 * @brief: Make a basic window named package name.
 * @param[pkg_name]: Name of the window
 */
Evas_Object *view_create_win(const char *pkg_name)
{
	Evas_Object *win = NULL;

	/*
	 * Window
	 * Create and initialize elm_win.
	 * elm_win is mandatory to manipulate window.
	 */

	win = elm_win_util_standard_add(pkg_name, pkg_name);
	elm_win_conformant_set(win, EINA_TRUE);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(win, "delete,request", _win_delete_request_cb, NULL);

	return win;
}

/*
 * @brief: Make conformant without indicator for wearable app.
 * @param[win]: Window to which you want to set this conformant
 */
Evas_Object *view_create_conformant_without_indicator(Evas_Object *win)
{
	Evas_Object *conform = NULL;

	/* Conformant
	 * Create and initialize elm_conformant.
	 * elm_conformant is mandatory for base GUI to have proper size
	 * when indicator or virtual keypad is visible.
	 */

	if (win == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "window is NULL.");
		return NULL;
	}

	conform = elm_conformant_add(win);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	evas_object_show(conform);

	return conform;
}

/*
 * @brief: Make a layout to target parent object with edje file
 * @param[parent]: The object to which you want to add this layout
 * @param[file_path]: File path of EDJ file will be used
 * @param[group_name]: Name of group in EDJ you want to set to
 * @param[cb_function]: The function will be called when back event is detected
 * @param[user_data]: The user data to be passed to the callback functions
 */
Evas_Object *view_create_layout(Evas_Object *parent, const char *file_path, const char *group_name, Eext_Event_Cb cb_function, void *user_data)
{
	Evas_Object *layout = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, file_path, group_name);

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	if (cb_function)
		eext_object_event_callback_add(layout, EEXT_CALLBACK_BACK, cb_function, user_data);

	evas_object_show(layout);

	return layout;
}

/*
 * @brief: Make a layout with theme.
 * @param[parent]: Object to which you want to add this layout
 * @param[classname]: The class of the group
 * @param[group]: Group name in EDJ you want to set to layout
 * @param[style]: The style to use
 */
Evas_Object *view_create_layout_by_theme(Evas_Object *parent, const char *classname, const char *group, const char *style)
{
	Evas_Object *layout = NULL;

	/*
	 * Layout
	 * Create and initialize elm_layout.
	 * view_create_layout_by_theme() is used to create layout by using pre-made edje file.
	 */

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	layout = elm_layout_add(parent);
	elm_layout_theme_set(layout, classname, group, style);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_show(layout);

	return layout;
}

/*
 * @brief: Make and set a layout to conformant
 * @param[parent]: Target conformant object
 * @param[file_name]: File path of EDJ used
 * @param[group_name]: Group name in EDJ you want to set to layout
 * @param[cb_function]: Callback for back event handling
 * @param[user_data]: The user data to be passed to the callback functions
 */
Evas_Object *view_create_layout_for_conformant(Evas_Object *parent, const char *file_name, const char *group_name, Eext_Event_Cb cb_function, void *user_data)
{
	Evas_Object *layout = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	if (file_name == NULL) {
		layout = view_create_layout_by_theme(parent, "layout", "application", "default");
	} else {
		layout = view_create_layout(parent, file_name, group_name, cb_function, user_data);
	}

	if (layout == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "layout is NULL.");
		return NULL;
	}

	elm_object_content_set(parent, layout);

	return layout;
}

/*
 * @brief: Destroy window and free important data to finish this application
 */
void view_destroy(void)
{
	if (s_info.win == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "window is NULL.");
		return;
	}

	evas_object_del(s_info.win);
}

/*
 * @brief: Set image to given part
 * @param[parent]: Object has part to which you want to set this image
 * @param[part_name]: Part name to which you want to set this image
 * @param[image_path]: Path of the image file
 */
void view_set_image(Evas_Object *parent, const char *part_name, const char *image_path)
{
	Evas_Object *image = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return;
	}

	image = elm_object_part_content_get(parent, part_name);
	if (image == NULL) {
		image = elm_image_add(parent);
		if (image == NULL) {
			dlog_print(DLOG_ERROR, LOG_TAG, "failed to create an image object.");
			return;
		}

		elm_object_part_content_set(parent, part_name, image);
	}

	if (EINA_FALSE == elm_image_file_set(image, image_path, NULL)) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to set image.");
		return;
	}

	evas_object_show(image);

	return;
}

/*
 * @brief: Set color of the part
 * @param[parent]: Object has part to which you want to set color
 * @param[part_name]: Name of part to which you want to set color
 * @param[r]: R of RGBA you want to set to the part
 * @param[g]: G of RGBA you want to set to the part
 * @param[b]: B of RGBA you want to set to the part
 * @param[a]: A of RGBA you want to set to the part
 */
void view_set_color(Evas_Object *parent, const char *part_name, int r, int g, int b, int a)
{
	Evas_Object *obj = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return;
	}

	obj = elm_object_part_content_get(parent, part_name);
	if (obj == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get parent.");
		return;
	}

	/* Set color of target part object */
	evas_object_color_set(obj, r, g, b, a);
}

/*
 * @brief: Make a label and set label options.
 * @param[parent]: The object to which you want to add this label
 */
Evas_Object *view_create_label(Evas_Object *parent)
{
	Evas_Object *label = elm_label_add(parent);

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	elm_object_style_set(label, "slide_short");
	elm_label_wrap_width_set(label, 230);
	elm_label_ellipsis_set(label, EINA_TRUE);
	elm_label_slide_duration_set(label, 2);
	elm_label_slide_mode_set(label, ELM_LABEL_SLIDE_MODE_NONE);
	elm_label_slide_go(label);
	evas_object_show(label);

	return label;
}




/*
 * @brief: Make a naviframe and set to parent
 * @param[parent]: Object to which you want to set naviframe
 */
static void
_naviframe_back_cb(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   dlog_print(DLOG_INFO, LOG_TAG, "back button setting:on : %d\n",setting_on);
   elm_naviframe_item_pop(obj);
   if(category_genlist == NULL)
	   dlog_print(DLOG_INFO, LOG_TAG, "NULL\n");
   if(setting_on > 1){
	   setting_on--;
	   //더보기 버튼
   } else if(setting_on <= 1 && setting_on >= 0){
	   setting_on --;
	   dlog_print(DLOG_INFO, LOG_TAG, "OUT OF SETTING\n");

		char abs_path_to_image[PATH_MAX] = {0,};
		char *res_dir_path = app_get_resource_path();
		snprintf(abs_path_to_image,PATH_MAX, "%s%s", res_dir_path, "vertical_more_ic.png");

		evas_object_image_file_set(more_image, abs_path_to_image, NULL);
		evas_object_geometry_set(more_image, 310, 150, 60, 60);
		dlog_print(DLOG_INFO, LOG_TAG, "image_path : %s",abs_path_to_image);
		evas_object_size_hint_weight_set(more_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(more_image, EVAS_HINT_FILL, EVAS_HINT_FILL);


		evas_object_show(more_image);
   }
   eext_rotary_object_event_activated_set(category_genlist, EINA_TRUE);
}


Evas_Object *view_create_naviframe(Evas_Object *parent)
{
	Evas_Object *nf = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	nf = elm_naviframe_add(parent);
	elm_naviframe_prev_btn_auto_pushed_set(nf, EINA_TRUE);

	elm_object_part_content_set(parent, "elm.swallow.content", nf);
	eext_object_event_callback_add(nf, EEXT_CALLBACK_BACK, _naviframe_back_cb, NULL);;
	eext_object_event_callback_add(nf, EEXT_CALLBACK_MORE, eext_naviframe_more_cb, NULL);

	evas_object_show(nf);

	return nf;
}

/*
 * @brief: Push item to naviframe
 * @param[nf]: Naviframe that item will be added to
 * @param[item]: Object will be added to naviframe
 * @param[_pop_cb]: Function will be operated when this item is popped from naviframe
 * @param[cb_data]: Data needed to operate '_pop_cb' function
 */
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

/*
 * @brief: Make genlist for circular shape.
 * @param[parent]: Object to which you want to set genlist
 */
Evas_Object *view_create_circle_genlist(Evas_Object *parent)
{
	Evas_Object *genlist = NULL;
	Evas_Object *circle_genlist = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	if (s_info.circle_surface == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "circle surface is NULL.");
		return NULL;
	}

	genlist = elm_genlist_add(parent);
	/*
	 * This make selected list item is shown compressed.
	 */
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(genlist, "selected", _gl_selected_cb, NULL);

	/*
	 * This make genlist style circular.
	 */
	circle_genlist = eext_circle_object_genlist_add(genlist, s_info.circle_surface);
	s_info.circle_genlist = circle_genlist;
	eext_circle_object_genlist_scroller_policy_set(s_info.circle_genlist, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	eext_rotary_object_event_activated_set(s_info.circle_genlist, EINA_TRUE);


	evas_object_show(genlist);

	return genlist;
}

/*
 * @brief: Add item to genlist.
 * @param[genlist]: Genlist that item will be added to
 * @param[style]: Style of item determine how to show this item, such as "1text", "1text1icon" and so on
 * @param[data]: Item data that use item's callback function
 * @param[_clicked_cb]: Function will be operated when the item is clicked
 * @param[cb_data]: Data needed in '_clicked_cb' function
 */
Elm_Object_Item *view_append_item_to_genlist(Evas_Object *genlist, const char *style,
		const void *data, Evas_Smart_Cb _clicked_cb, const void *cb_data)
{
	Elm_Genlist_Item_Class *item_class;
	Elm_Object_Item *item;

	if (genlist == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "genlist is NULL.");
		return NULL;
	}

	if (style == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "item style is NULL.");
		return NULL;
	}

	item_class = _set_genlist_item_class(style);

	item = elm_genlist_item_append(genlist, item_class, data, NULL, ELM_GENLIST_ITEM_NONE, _clicked_cb, cb_data);

	elm_genlist_item_class_free(item_class);

	return item;
}

/*
 * @brief: Create check box
 * @param[parent]: Object to which you want to add check
 * @param[event]: Event's name
 * @param[cb_func]: Callback function
 * @param[data]: Data needed in this function
 */
Evas_Object *view_create_checkbox(Evas_Object *parent, const char *event, Evas_Smart_Cb cb_func, void *data)
{
	Evas_Object *check;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	check = elm_check_add(parent);

	evas_object_smart_callback_add(check, event, cb_func, data);
	evas_object_show(check);

	return check;
}

/*
 * @note
 * Below functions are static functions.
 */

/*
 * @brief: Set functions will be operated when this item is shown on the screen according to the style.
 * @param[style]: Style of item.
 */
static Elm_Genlist_Item_Class *_set_genlist_item_class(const char *style)
{
	Elm_Genlist_Item_Class *item_class = NULL;

	if (style == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "style is NULL.");
		return NULL;
	}

	item_class = elm_genlist_item_class_new();

	/*
	 * If you want to add the item class of genlist, you should be add below.
	 * To see more genlist's styles click on the link below.
	 * https://developer.tizen.org/development/ui-practices/native-application/efl/ui-components/wearable-ui-components
	 */
	if (!strcmp(style, "func.title")) {
		/*
		 * This function will be operated when this item is shown on the screen to get the title.
		 */
		item_class->item_style = "title";
		item_class->func.text_get = data_get_func_title_text;
	} else if (!strcmp(style, "category.title")) {
		item_class->item_style = "title";
		item_class->func.text_get = data_get_category_title_text;
	} else if (!strcmp(style, "core.title")) {
		item_class->item_style = "title";
		item_class->func.text_get = data_get_core_title_text;
	} else if (!strcmp(style, "corona.title")) {						//qanda
		item_class->item_style = "title";
		item_class->func.text_get = data_get_corona_title_text;
	} else if (!strcmp(style, "mart.title")) {						//mart
		item_class->item_style = "title";
		item_class->func.text_get = data_get_mart_title_text;
	} else if (!strcmp(style, "food.title")) {						//mart
		item_class->item_style = "title";
		item_class->func.text_get = data_get_food_title_text;
	} else if (!strcmp(style, "hospital.title")) {
		item_class->item_style = "title";
		item_class->func.text_get = data_get_hospital_title_text;
	} else if (!strcmp(style, "pe.title")) {
		item_class->item_style = "title";
		item_class->func.text_get = data_get_pe_title_text;
	} else if (!strcmp(style, "setting.title")) {						//mart
		item_class->item_style = "title";
		item_class->func.text_get = data_get_setting_title_text;
	}

	else if (!strcmp(style, "func.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_func_text;
	} else if (!strcmp(style, "category.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_category_text;
	} else if (!strcmp(style, "core.1text")) {					//qanda
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_core_text;
	} else if (!strcmp(style, "corona.1text")) {						//mart
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_corona_text;
	} else if (!strcmp(style, "mart.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_mart_text;
	} else if (!strcmp(style, "food.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_food_text;
	} else if (!strcmp(style, "hospital.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_hospital_text;
	} else if (!strcmp(style, "pe.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_pe_text;
	} else if (!strcmp(style, "setting.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_setting_text;
	} else if (!strcmp(style, "padding")) {
		/*
		 * "padding" style does nothing.
		 * But it makes genlist's item placed in the middle of the screen.
		 */
	}

	return item_class;
}

/*
 * @brief: Function will be operated when window is deleted.
 * @param[data]: Data needed in this function
 * @param[obj]: Smart object
 * @param[event_info]: Information of event
 */
static void _win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

/*
 * @brief: Function will be operated when genlist's item is selected.
 * @param[data]: Data needed in this function
 * @param[obj]: Genlist
 * @param[event_info]: Selected item
 */
static void _gl_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = (Elm_Object_Item *)event_info;

	elm_genlist_item_selected_set(it, EINA_FALSE);
}


/* End of file */
