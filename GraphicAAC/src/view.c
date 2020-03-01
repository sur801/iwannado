
#include <app.h>
#include <Elementary.h>
#include <dlog.h>

#include "data.h"
#include "main.h"
#include "view.h"
#define SETTING_ITEMS 1

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
	evas_object_image_file_set(more_image, NULL, NULL);
	evas_object_geometry_set(more_image, 0, 0, 10, 10);

	//setting 창 들어간것 표시
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
	evas_object_smart_callback_add(more_btn, "item,clicked",NULL, user_data);


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
