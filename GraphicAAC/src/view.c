
#include <app.h>
#include <Elementary.h>
#include <dlog.h>

#include "data.h"
#include "main.h"
#include "view.h"

/*
 * @brief: Make more option object
 * @param[parent]: Object to which you want to set the more option
 * @param[part_name]: Part name for more option, set part size as large as parent
 * @param[_item_selected]: Function will be operated when more option item is clicked
 * @param[user_data]: Data passed to the '_item_selected' function
 */

char test2[10] = "hellllo";
Evas_Object *check; // check box widjet
Evas_Object * gps_genlist;// for refresh gps setting genlist
Evas_Object *entry; // number input for certificate phone number;

// for genlist, and update items. make global
//Elm_Genlist_Item_Class *item_class;
//Elm_Object_Item *item;

/*
 * @brief: Create check box
 * @param[parent]: Object to which you want to add check
 * @param[event]: Event's name
 * @param[cb_func]: Callback function
 * @param[data]: Data needed in this function
 */
Evas_Object *view_create_checkbox(Evas_Object *parent, const char *event, Evas_Smart_Cb cb_func, void *data)
{


	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	check = elm_check_add(parent);

	elm_object_text_set(check, "Check");
	elm_object_style_set(check, "small popup");

	evas_object_smart_callback_add(check, event, cb_func, data);
	evas_object_show(check);

	return check;
}

/*
 * @brief: Function will be operated when check object is clicked.
 * @param[data]: Data needed in this function
 * @param[obj]: Check
 * @param[event_info]: Information of event
 */
static void _icon_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	state = elm_check_state_get(obj);
	dlog_print(DLOG_INFO, LOG_TAG, "GET CHECK : check state [%d]", state);


	if (state == EINA_TRUE) {
		//dlog_print(DLOG_INFO, LOG_TAG, "True : check state [%d]", state);
		//dlog_print(DLOG_INFO, LOG_TAG, "BEFORE : check state [%d]", gps_its_value[0]);
		elm_check_state_set(obj, EINA_TRUE);
		data_set_gps_int_value((int)data, EINA_TRUE);
	} else {
		//dlog_print(DLOG_INFO, LOG_TAG, "False : check state [%d]", state);
		//dlog_print(DLOG_INFO, LOG_TAG, "AFTER : check state [%d]", gps_its_value[0]);
		elm_check_state_set(obj, EINA_FALSE);
		data_set_gps_int_value((int)data, EINA_FALSE);
	}


	//elm_genlist_item_item_class_update(item, item_class);
	elm_genlist_realized_items_update(gps_genlist);

	/*
	 * @note
	 * Do something when the icon is clicked.
	 */
}


/*
 * @brief: Function will be operated when the item is shown to genlist.
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
static Evas_Object* _get_gps_check(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *content = NULL;

	if (strcmp(part, "elm.icon")) return NULL;


	content = view_create_checkbox(obj, "changed", _icon_clicked_cb, data);

	data_get_gps_int_value((int)data, &state);
	elm_check_state_set(content, !!state);

	return content;
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
	} else if(!strcmp(style, "gps.title")){
		item_class->item_style = "title";
		item_class->func.text_get = data_get_gps_title_text;
	} else if(!strcmp(style, "phone.title")){
		item_class->item_style = "title";
		item_class->func.text_get = data_get_phone_title_text;
	}
	else if (!strcmp(style, "setting.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_setting_text;
	} else if (!strcmp(style, "setting.2text")) {
		item_class->item_style = "2text";
		item_class->func.text_get = data_get_setting_text;
	} else if (!strcmp(style, "gps.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_gps_text;

	} else if(!strcmp(style, "1text.1icon.1")) {
		item_class->item_style = "1text.1icon.1";
		item_class->func.content_get = _get_gps_check;
		item_class->func.text_get = data_get_gps_text;
	} else if (!strcmp(style, "phone.1text")) {
		item_class->item_style = "1text";
		item_class->func.text_get = data_get_phone_text;

	}

	return item_class;
}



static void _app_info_display(void) {
	Evas_Object * layout = elm_layout_add(view_get_naviframe());
	elm_layout_theme_set(layout, "layout", "application", "default");


	// 세팅창 켜져있음.
	setting_on = 2;

	/*app info page scroller 생성 */

	Evas_Object* scroller;
	Evas_Object *circle_scroller;
	scroller = elm_scroller_add(layout);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);


	/*로고 이미지 붙이기*/
	Evas_Object* logo_img = elm_image_add(layout);
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
	Evas_Object * label = elm_label_add(scroller);
	elm_object_text_set(label,
	"<br><br><br><br><br><br><br><br><align=center><font_size=25>개발사 : 하고싶다</font> <br> <font_size=25>이메일 : hswom@naver.com </font> <br> <font_size=15>위치 관리 번호를 등록하셨을 경우 사용자 위치를</font> <br> <font_size=15> www.watchacc.com에서 확인하실 수 있습니다.</font> <br> <font_size = 15>사용법 및 기능에 자세한 내용은 </br> www.watchaac.com에서 확인하실 수 있습니다.</font><br><font_size = 15>본 어플리케이션은 AAC 전문기관<br>'사람과 소통' 의 도움을 받아 제작되었습니다.</font><br><br><br></align> ");

	elm_object_style_set(label, "marker");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(label);


	elm_object_content_set(scroller, label);

	Eext_Circle_Surface *surface = eext_circle_surface_conformant_add(view_get_naviframe());
	circle_scroller = eext_circle_object_scroller_add(scroller, surface);
	eext_circle_object_scroller_policy_set(circle_scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	eext_rotary_object_event_activated_set(circle_scroller, EINA_TRUE);

	evas_object_show(scroller);
	elm_object_part_content_set(layout, "elm.swallow.bg", scroller);


	evas_object_show(layout);

	view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);

}

//callback function for click sending certification number
static void _certifi_clicked(void *data, Evas_Object *obj, void *event_info){
	//char number[100] = (char*)data;
	phone_check = elm_object_text_get(entry);
	dlog_print(DLOG_INFO, LOG_TAG, "sending number : %s\n", phone_check);

}
//layout for add phone number
static void _phone_add_cb(void *data, Evas_Object *obj, void *event_info){
	Evas_Object * layout = elm_layout_add(view_get_naviframe());
	elm_layout_theme_set(layout, "layout", "application", "default");
	setting_on = 4;


	Evas_Object * label = elm_label_add(layout); // 휴대전화 번호 입력
	Evas_Object * label2 = elm_label_add(layout); // 개인정보 동의
	Evas_Object *check = elm_check_add(layout); // 개인정보 동의를 위한 체크 박스
	entry = elm_entry_add(layout); // 전화번호 입력을 위한 text filed
	elm_entry_single_line_set(entry, EINA_TRUE);
	//elm_entry_entry_insert(entry, "전화번호 입력");
	elm_object_part_text_set(entry, "elm.guide", "INPUT PHONE NUMBER");
	elm_entry_input_panel_layout_set(entry,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY);


	elm_object_style_set(check, "small popup");
	elm_object_style_set(label, "marker");
	elm_object_text_set(label,"<align=center><font_size=30><br>휴대전화 번호 입력</font><algin>");
	//evas_object_color_set(label, 0, 92, 230, 255); 칼라 세팅
	elm_object_style_set(label2, "marker");
	elm_object_text_set(label2,"<align=center><font_size=25><br>개인정보 수집 동의</font><algin>");

	evas_object_geometry_set(entry, 50, 140, 300, 30); // 전화번호 입력을 위한 text field 위치 설정
	evas_object_geometry_set(check, 40, 180, 80, 80); // check box 위치 설정
	evas_object_geometry_set(label2, 110, 180, 180, 50); // 개인 정보 동의 텍스트  위치 설정


	// 인증번호 보내는 버튼.
	Evas_Object* btn = elm_button_add(layout);
	evas_object_color_set(btn, 40, 154, 247, 220);
	evas_object_geometry_set(btn, 90, 260, 180, 50);
	elm_object_style_set(btn, "nextdepth");
	elm_object_text_set(btn, "<color=#FFFFFF>인증번호 전송</color>");

	elm_object_content_set(layout, label);
	evas_object_show(check);
	evas_object_show(label2);
	evas_object_show(btn);
	evas_object_show(entry);
	evas_object_show(layout);



	evas_object_smart_callback_add(btn, "clicked", _certifi_clicked, NULL);

	view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);

}


static void _delete_clicked(void *data, Evas_Object *obj, void *event_info) {
	int id = (int)data;
	int i;
	for(i = id ; i<=phone_cnt ; i++){
		phone_its[i] =  phone_its[i+1];
	}
	phone_its[phone_cnt+1] = NULL;
	phone_cnt--;


	elm_genlist_clear(phone_genlist);
	view_append_item_to_genlist(phone_genlist, "phone.title", NULL, NULL, NULL);
	for (i = 0; i < phone_cnt+1 ; i++) {
		// item이 추가 버튼 아니고, 전화번호들 일때,
		if(i!=phone_cnt && phone_cnt)
			view_append_item_to_genlist(phone_genlist, "phone.1text", (void *)i, _phone_delete_cb , (void *)i);
		else
			view_append_item_to_genlist(phone_genlist, "phone.1text", (void *)i, _phone_add_cb , (void *)i);
	}

	view_append_item_to_genlist(phone_genlist, "padding", NULL, NULL, NULL);
	elm_naviframe_item_pop(view_get_naviframe());

}

// layout for delete phone number
static void _phone_delete_cb(void *data, Evas_Object *obj, void *event_info) {

	int id = (int)data;
	Evas_Object * layout = elm_layout_add(view_get_naviframe());
	elm_layout_theme_set(layout, "layout", "application", "default");

	setting_on = 4;

	Evas_Object* label = elm_label_add(layout);
	Evas_Object* btn = elm_button_add(layout);

	char phone_number[100] = {0,};
	snprintf(phone_number, 100, "<align=center><font_size=40><br><br><br> %s </font></align>", phone_its[id]);
	//dlog_print(DLOG_INFO, LOG_TAG, "phone number : %s\n",phone_number);
	elm_object_text_set(label,phone_number);
	elm_object_text_set(btn, "삭제");

	elm_object_style_set(label, "marker");
	elm_object_style_set(btn, "bottom");
	//evas_object_geometry_set(label, 10, 150, 300, 100);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_show(label);

	evas_object_geometry_set(btn, 120,295, 110, 75);
	elm_object_content_set(layout, label);


	evas_object_show(btn);

	evas_object_smart_callback_add(btn, "clicked", _delete_clicked, (void*)id);

	evas_object_show(layout);
	view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);


}


static void _phone_setting(void *data, Evas_Object *obj, void *event_info)
{

	setting_on = 3;

	phone_genlist = NULL;

	/* make genlist and shape genlist circle */
	phone_genlist = view_create_circle_genlist(view_get_naviframe());
	view_push_item_to_naviframe(view_get_naviframe(), phone_genlist,NULL, NULL);
	//append title to genlist.
	view_append_item_to_genlist(phone_genlist, "phone.title", NULL, NULL, NULL);

//	int i;
//	for(i=0;i<2;i++){
//		dlog_print(DLOG_INFO, LOG_TAG, "phone item : %s\n",phone_its[i]);
//	}


	// append items to genlist .
	// 추가 버튼 까지 genlist에 추가.
	int i;
	for (i = 0; i < phone_cnt+1 ; i++) {
		if(i!=phone_cnt && phone_cnt)
			view_append_item_to_genlist(phone_genlist, "phone.1text", (void *)i, _phone_delete_cb , (void *)i);
		else
			view_append_item_to_genlist(phone_genlist, "phone.1text", (void *)i, _phone_add_cb , (void *)i);
	}
	evas_object_show(phone_genlist);
	//evas_object_show(layout);

	view_append_item_to_genlist(phone_genlist, "padding", NULL, NULL, NULL);

}


static void _gps_setting(void){
	// 세팅창 켜져있음.
	setting_on = 2;
	gps_genlist = NULL;

	/* make genlist and shape genlist circle */
	gps_genlist = view_create_circle_genlist(view_get_naviframe());
	view_push_item_to_naviframe(view_get_naviframe(), gps_genlist,NULL, NULL);

	//append title to genlist.
	view_append_item_to_genlist(gps_genlist, "gps.title", NULL, NULL, NULL);

	// append items to genlist .
	int i;
	for (i = 0; i < GPS_ITEM ; i++) {
		if(i==0)
			view_append_item_to_genlist(gps_genlist, "1text.1icon.1", (void *)i,NULL, (void *)i);
		else
			view_append_item_to_genlist(gps_genlist, "gps.1text", (void *)i,_phone_setting, (void *)i);
	}
    evas_object_show(gps_genlist);
	//evas_object_show(layout);

    view_append_item_to_genlist(gps_genlist, "padding", NULL, NULL, NULL);
	//view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);

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
		 * 위치 추적 기능, 전화번호 세팅
		 */
		_gps_setting();

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

	setting_genlist = NULL;

	/* From here, we make genlist for voice memo list */
	/* make genlist and shape genlist circle */
	setting_genlist = view_create_circle_genlist(view_get_naviframe());
	view_push_item_to_naviframe(view_get_naviframe(), setting_genlist,NULL, NULL);

	//append title to genlist.
	view_append_item_to_genlist(setting_genlist, "setting.title", NULL, NULL, NULL);

	// append items to genlist .
	int i;
	for (i = 0; i < SETTING_ITEM; i++) {
		if(i==0)
			view_append_item_to_genlist(setting_genlist, "setting.1text", (void *)i, _create_setting_layout, (void *)i);
		else
			view_append_item_to_genlist(setting_genlist, "setting.2text", (void *)i, _create_setting_layout, (void *)i);
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
