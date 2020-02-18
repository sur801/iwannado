
#include <app.h>
#include <Elementary.h>
#include <dlog.h>

#include "data.h"
#include "main.h"
#include "view.h"
#define SETTING_ITEMS 2

/*
 * @brief: Make more option object
 * @param[parent]: Object to which you want to set the more option
 * @param[part_name]: Part name for more option, set part size as large as parent
 * @param[_item_selected]: Function will be operated when more option item is clicked
 * @param[user_data]: Data passed to the '_item_selected' function
 */

char test2[10] = "hellllo";

static void _create_category_list(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;

		switch (index) {
		case 0:
			/*
			 * Greetings
			 */
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
	if(!strcmp(style, "setting.title")){
		item_class->item_style = "title";
		item_class->func.text_get = data_get_setting_title_text;
	} else if (!strcmp(style, "setting.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_setting_text;
	}

	return item_class;
}


void view_create_more_item(Evas_Object *parent, int index, char *name, char *sub_name, char *image_path)
{
	//Evas_Object *image = NULL;
	/* Create the new item */
	Eext_Object_Item *item  = eext_more_option_item_append(parent);

	/* Set the text in item text part */
	if (name != NULL) {
		eext_more_option_item_part_text_set(item, "selector,main_text", name);

	}


	if (sub_name != NULL) {
		eext_more_option_item_part_text_set(item, "selector,sub_text", sub_name);
	}


	//image = elm_image_add(parent);
	/* Set the content in item content part */
	//eext_more_option_item_part_content_set(item, "item,icon", image);
	//elm_image_file_set(image, image_path, NULL);



	return;
}

// Callback function for the "more,option,opened" signal
// This callback is called when the more_option is seen
void
_opened_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object * detail_more = (Evas_Object *)data;
	// set more 버튼 누르면 실행되는 callback 함수
   dlog_print(DLOG_INFO, LOG_TAG, "Open the More Option\n");
   //elm_naviframe_item_push(view_get_naviframe(), NULL, NULL, NULL, detail_more, "empty");

}

Evas_Object *view_set_more_button(Evas_Object *parent, const char *part_name, Evas_Smart_Cb _item_selected, void *user_data)
{
	Evas_Object *more_btn = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	more_btn = eext_more_option_add(parent);
	eext_more_option_direction_set(more_btn, EEXT_MORE_OPTION_DIRECTION_BOTTOM);
	if (more_btn == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "more option is NULL.");
		return NULL;
	}

	/* Add smart callback more 버튼 누를 때 실행 */
	evas_object_smart_callback_add(more_btn,"more,option,opened", _opened_cb, more_btn);
	/* Add smart callback detail_more의 item들 누를 때 실행 */
	evas_object_smart_callback_add(more_btn, "item,clicked", _item_selected, user_data);

	// set_more 버튼의 위치 조정. 오른쪽에 위치시킴
	evas_object_geometry_set(more_btn, 180, 180, NULL, NULL);
	elm_object_part_content_set(parent, part_name, more_btn);


	return more_btn;
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
