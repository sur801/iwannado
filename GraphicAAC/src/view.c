
#include <app.h>
#include <Elementary.h>
#include <dlog.h>
#include "data.h"
#include "main.h"
#include "view.h"
#include "sendSMS.h"
#include "sendGPS.h"
#include <sqlite3.h>

#include<string.h>
#include<stdlib.h>
#include<time.h>



/*
 * @brief: Make more option object
 * @param[parent]: Object to which you want to set the more option
 * @param[part_name]: Part name for more option, set part size as large as parent
 * @param[_item_selected]: Function will be operated when more option item is clicked
 * @param[user_data]: Data passed to the '_item_selected' function
 */

Evas_Object *check; // check box widjet
Evas_Object *entry; // number input for phone number;
Evas_Object * entry2; // number input for certification number;

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


	if (state == EINA_TRUE) {

		//location 권한 획득
		app_check_and_request_permission();

		elm_check_state_set(obj, EINA_TRUE);

		// local gps state 업데이트
		data_set_gps_int_value((int)data, EINA_TRUE);

		char sql[256];
		char *ErrMsg;
		char * key = "1";
		int id=0;

		//snprintf(sql, 256, "UPDATE ReportCard SET NAME=\'%s\', ENGLISH=\'%s\',MATH=\'%s\' WHERE KEY=\'%s\';",name, english, math, ad->current_key);
		snprintf(sql, 256, "UPDATE GpsData SET ID=%d, GPS=1 WHERE KEY=\'%s\';",id,key );
		int ret = sqlite3_exec(get_ad()->phone_db, sql, NULL, 0, &ErrMsg);
		dlog_print(DLOG_INFO, LOG_TAG, "update ret : %d\n",ret);


	} else {
		// 만약에 db에 gps state값 없으면 0로 초기화, 아니면 0로 업데이트

		elm_check_state_set(obj, EINA_FALSE);

		char sql[256];
		char *ErrMsg;
		char * key = "1";
		int id=0;

		//snprintf(sql, 256, "UPDATE ReportCard SET NAME=\'%s\', ENGLISH=\'%s\',MATH=\'%s\' WHERE KEY=\'%s\';",name, english, math, ad->current_key);
		snprintf(sql, 256, "UPDATE GpsData SET ID=%d, GPS=0 WHERE KEY=\'%s\';",id,key );
		int ret = sqlite3_exec(get_ad()->phone_db, sql, NULL, 0, &ErrMsg);
		dlog_print(DLOG_INFO, LOG_TAG, "update ret : %d\n",ret);

		//local gps state 업데이트
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

static int db_gps_cb(void *counter, int argc, char **argv, char **azColName){
	char buf[255];
	gpsdata_s* pd = malloc(sizeof(gpsdata_s));
	strcpy(pd->key, argv[0]);
	pd->id = atoi(argv[1]);
	pd->gps = atoi(argv[2]);

	sprintf(buf, "%s / %s / %s ", argv[0], argv[1], argv[2]);
	dlog_print(DLOG_INFO, LOG_TAG, "buffer : %s\n", buf);

	if(atoi(pd->key) == 1){
		gps_its_value[0] = pd->gps;
		gps_state=pd->gps;
		dlog_print(DLOG_INFO, LOG_TAG, "gps update : %d !!!!\n", gps_its_value[0]);
	}
	return 0;

}

static int db_read_cb(void *counter, int argc, char **argv, char **azColName){
	// read sql에 문제가 있어서 이 call back 함수 안들ㅇ옴.
	char buf[255];
	phonedata_s* pd = malloc(sizeof(phonedata_s));
	strcpy(pd->key, argv[0]);
	pd->id = atoi(argv[1]);
	//strcpy(pd->id, atoi(argv[1]));
	strcpy(pd->phone, argv[2]);

	//strcpy(pd->count, atoi(argv[3]));
	sprintf(buf, "%s / %s / %s ", argv[0], argv[1], argv[2]);
	dlog_print(DLOG_INFO, LOG_TAG, "buffer : %s\n", buf);


	//이 부분 부터 문제 발생.

	int i;
	if(app_start){
		for(i=phone_cnt ; i>=phone_cnt; i--){
				strcpy(phone_its[i+1], phone_its[i]);// 새로운 아이템 넣을 자리 만들기
			dlog_print(DLOG_INFO, LOG_TAG, "index : %d\n",i );
		}
		strcpy(phone_its[phone_cnt], argv[2]);
	} else {
		for(i=phone_cnt+1 ; i>=phone_cnt; i--){
				strcpy(phone_its[i+1], phone_its[i]);// 새로운 아이템 넣을 자리 만들기
			dlog_print(DLOG_INFO, LOG_TAG, "index : %d\n",i );
		}
		strcpy(phone_its[phone_cnt], argv[2]);
	}
	phone_cnt = atoi(argv[0]);

	for(i=0 ; i<phone_cnt+1; i ++){
		dlog_print(DLOG_INFO, LOG_TAG, "phone item : %s\n", phone_its[i]);
	}
	//elm_list_item_append(m_ad->list, buf, NULL, NULL, NULL, (void*)rd);
	//elm_list_go(m_ad->list);
	return 0;
}


int read_db(appdata_s *ad){
	char *sql = "select * from UserData";
	char *sql2 = "select * from GpsData";
	int counter=0;
	char *ErrMsg;
	//elm_genlist_clear(phone_genlist);

	// read를 못함. insert까지는 됐을 텐데
	int ret = sqlite3_exec(ad->phone_db, sql, db_read_cb, &counter, &ErrMsg);
	int ret2 = sqlite3_exec(ad->phone_db, sql2, db_gps_cb, &counter, &ErrMsg);
	//int ret = sqlite3_exec(ad->phone_db, sql, NULL, 0, &ErrMsg);
	dlog_print(DLOG_INFO, LOG_TAG, "read error : %d", ret);
	dlog_print(DLOG_INFO, LOG_TAG, "read error : %d", ret2);
	return ret;
}

static void _enter_clicked_cb(void *data, Evas_Object *obj, void *event_info) {
	dlog_print(DLOG_INFO, LOG_TAG, "activate!");
	int i = (int)data;
	if(i == 0)
		elm_entry_input_panel_hide(entry);
	else
		elm_entry_input_panel_hide(entry2);
}

// callback function for check whether input number and certification number are same.
static void _certifi_check(void *data, Evas_Object *obj, void *event_info){
	int certifi_number = (int)data;
	char * input = elm_object_text_get(entry2);
	char * phone = elm_object_text_get(entry);

	int input_num = atoi(input);
	if(certifi_number == input_num){
		dlog_print(DLOG_INFO, LOG_TAG, "same! : %d %d\n",certifi_number, input_num);
		// 인증번호 맞음.
		int i;

		//strcpy에 문제가 있네.
		for(i=phone_cnt+1 ; i>=phone_cnt; i--){
			strcpy(phone_its[i+1], phone_its[i]);// 새로운 아이템 넣을 자리 만들기
		}
		strcpy(phone_its[phone_cnt], phone_check);

		dlog_print(DLOG_INFO, "SOLAPI", "START TO GET LOCATION");
		location_init(phone);

		//db에 휴대폰 데이터 추가. id, phone, count, gps
		int id = phone_cnt;// id for phone number. starts to 0
		phone_cnt++; // increase number of phone number;
		InsertRecordPhone(get_ad(), id, phone);

		elm_genlist_clear(phone_genlist);
		//read_db(get_ad());
		view_append_item_to_genlist(phone_genlist, "phone.title", NULL, NULL, NULL);

		for (i = 0; i < phone_cnt+1 ; i++) {
			// item이 추가 버튼 아니고, 전화번호들 일때,
			if(i!=phone_cnt && phone_cnt)
				view_append_item_to_genlist(phone_genlist, "phone.1text", (void *)i, _phone_delete_cb , (void *)i);
			else
				view_append_item_to_genlist(phone_genlist, "phone.1text", (void *)i, _phone_add_cb , (void *)i);
		}

		view_append_item_to_genlist(phone_genlist, "padding", NULL, NULL, NULL);


	}
	else{
		// 인증번호 틀림.
		dlog_print(DLOG_INFO, LOG_TAG, "not same! : %d %d\n", certifi_number,input_num);
	}
	setting_on = 4;
	elm_naviframe_item_pop(view_get_naviframe());

}



//callback function for click sending certification number
static void _certifi_clicked(void *data, Evas_Object *obj, void *event_info){

	setting_on = 5;
	strcpy(phone_check, elm_object_text_get(entry));
	// 인증번호 전송할 전화번호
	dlog_print(DLOG_INFO, LOG_TAG, "sending number : %s\n", phone_check);

	// 인증번호 난수로 생성.
	srand(time(NULL));
	int lower_random = rand()%1000; // 0~999 중 난수 생성
	int upper_random = rand()%9+1; // 1~9중 난수 생성

	int random = upper_random*1000 + lower_random;


	dlog_print(DLOG_INFO, LOG_TAG, "random number : %d\n", random );

	// 폰으로 인증번호 전송하기
	sendSMS(phone_check,random);

	Evas_Object * layout = elm_layout_add(view_get_naviframe());
	elm_layout_theme_set(layout, "layout", "application", "default");

	Evas_Object * box = elm_box_add(layout);
	elm_box_horizontal_set(box, EINA_FALSE);
	elm_box_padding_set(box, 0, 5);
	evas_object_show(box);

	// 인증 번호 입력
	Evas_Object * label = elm_label_add(box);
	elm_object_text_set(label,"<align=center><font_size=30><br>인증 번호 입력</font><algin>");
	evas_object_show(label);
    elm_box_pack_end(box,label);

    // 인증번호 입력을 위한 text field
    entry2 = elm_entry_add(box);
	elm_entry_single_line_set(entry2, EINA_TRUE);
	elm_object_part_text_set(entry2, "elm.guide", "발송된 인증번호를 입력하세요.");
	elm_entry_input_panel_layout_set(entry2,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY); // 숫자만 입력.
	evas_object_size_hint_min_set(entry2, 330, 30);
	evas_object_size_hint_weight_set(entry2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(entry2);
	elm_box_pack_end(box,entry2);

	// enter 버튼이 눌리면 panel이 없어지게 하는 함수 달아줌.
	int i = 1;
	evas_object_smart_callback_add(entry2, "activated", _enter_clicked_cb, (void*)i);


	// 인증번호 확인 버튼.
	Evas_Object* btn = elm_button_add(box);
	evas_object_color_set(btn, 40, 154, 247, 220);
	elm_object_style_set(btn, "nextdepth");
	elm_object_text_set(btn, "<color=#FFFFFF>확인</color>");
	evas_object_smart_callback_add(btn, "clicked", _certifi_check, (void*)random);
	evas_object_size_hint_min_set(btn, 150, 50);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(layout, box);

	elm_naviframe_item_pop(view_get_naviframe());
	evas_object_show(layout);
	view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);



}
//layout for add phone number
static void _phone_add_cb(void *data, Evas_Object *obj, void *event_info){
	Evas_Object * layout = elm_layout_add(view_get_naviframe());
	elm_layout_theme_set(layout, "layout", "application", "default");

	setting_on = 4;
	// object들을 한 레이아웃에 묶어줄 box;
	Evas_Object * box = elm_box_add(layout);
	elm_box_horizontal_set(box, EINA_FALSE);
	elm_box_padding_set(box, 0, 5);
    evas_object_show(box);

    // 휴대전화 번호 입력
	Evas_Object * label = elm_label_add(box);
	elm_object_style_set(label, "marker");
	elm_object_text_set(label,"<align=center><font_size=30><br>휴대전화 번호 입력</font><algin>");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	//evas_object_color_set(label, 0, 92, 230, 255); 칼라 세팅
	evas_object_show(label);
    elm_box_pack_end(box,label);


    // check box와 개인정보 동의 글을 가로로 묶기 위한 box
    Evas_Object * sub_box = elm_box_add(box);
    elm_box_horizontal_set(sub_box, EINA_TRUE);
    elm_box_padding_set(sub_box, 5, 0);
    evas_object_show(sub_box);

    // 개인정보 동의를 위한 체크 박스
    Evas_Object *check = elm_check_add(sub_box);
	elm_object_style_set(check, "small popup");
	evas_object_show(check);
	elm_box_pack_end(sub_box, check);//sub box에 check box 집어넣기.

	elm_box_pack_end(box, sub_box); //main box에 sub box 집어넣기

	Evas_Object * label2 = elm_label_add(sub_box); // 개인정보 동의
	elm_object_style_set(label2, "marker");
	elm_object_text_set(label2,"<align=center><font_size=30><br>   개인정보 수집 동의</font><algin>");
	evas_object_show(label2);
	elm_box_pack_end(sub_box, label2); //sub box에 check box 집어넣기.


	// 전화번호 입력을 위한 text filed
	entry = elm_entry_add(box);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_object_part_text_set(entry, "elm.guide", "보호자 전화번호를 입력하세요.");
	elm_entry_input_panel_layout_set(entry,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY);
	evas_object_size_hint_min_set(entry, 330, 30);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(entry);
	elm_box_pack_end(box, entry);

	// enter 버튼이 눌리면 panel이 없어지게 하는 함수 달아줌.
	int i = 0;
	evas_object_smart_callback_add(entry, "activated", _enter_clicked_cb, (void*)i);

	// 인증번호 보내는 버튼.
	Evas_Object* btn = elm_button_add(box);
	evas_object_color_set(btn, 40, 154, 247, 220);
	elm_object_style_set(btn, "nextdepth");
	elm_object_text_set(btn, "<color=#FFFFFF>인증번호 전송</color>");
	evas_object_smart_callback_add(btn, "clicked", _certifi_clicked, NULL);
	evas_object_size_hint_min_set(btn, 200, 50);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(layout, box);



	evas_object_show(layout);
	view_push_item_to_naviframe(view_get_naviframe(), layout, NULL, NULL);

}


static void _delete_clicked(void *data, Evas_Object *obj, void *event_info) {
	int id = (int)data;
	/*db에서 삭제하기*/

	char delete_key[10];

	sprintf(delete_key,"%d",id+1);

	dlog_print(DLOG_INFO, LOG_TAG, "delete key : %s\n", delete_key);

	/*db에서도 전화번호 삭제하기*/
	char sql[256];
	char *ErrMsg;
	snprintf(sql, 256, "DELETE FROM UserData WHERE KEY=\'%s\';", delete_key);
	int ret = sqlite3_exec(get_ad()->phone_db, sql, NULL, 0, &ErrMsg);


	int i;
	for(i = id ; i<=phone_cnt ; i++){
		strcpy(phone_its[i],phone_its[i+1]);
	}
	strcpy(phone_its[phone_cnt+1], "");
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
	setting_on = 3;

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

//	if(!app_start){
//		//세팅 창 처음 킬때만 read함.
//		read_db(get_ad());
//		app_start=1;
//	}

	/* make genlist and shape genlist circle */
	phone_genlist = view_create_circle_genlist(view_get_naviframe());
	view_push_item_to_naviframe(view_get_naviframe(), phone_genlist,NULL, NULL);
	//append title to genlist.
	view_append_item_to_genlist(phone_genlist, "phone.title", NULL, NULL, NULL);


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

	for(i=0 ; i<phone_cnt+1; i ++){
		dlog_print(DLOG_INFO, LOG_TAG, "phone item : %s\n", phone_its[i]);
	}
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

void
_to_longclick_popup_cb(void *data, Evas_Object *obj, void *event_info){
	dlog_print(DLOG_INFO, LOG_TAG, "more image short clicked\n");
	//옵션 클릭, 관리자 모드로 들어가려면 3초 long click 안내
	//s_info.layout 위에 popup 얹기.

	dlog_print(DLOG_INFO, LOG_TAG, "address of data : %d", data);
	popup=elm_popup_add((Elm_Gesture_Layer*)data);
	elm_object_style_set(popup, "toast/circle");
	elm_object_text_set(popup, "설정에 들어가려면,<br> 3초 동안 누르세요.");
	evas_object_show(popup);
	elm_popup_timeout_set(popup, 3.0);
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


	InsertRecordGps(get_ad(), gps_its_value[0]);


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

/* DB 관련 함수들 */
int CreatePhoneTable(appdata_s *ad){
	char *ErrMsg;
	char  *sql  =  "CREATE  TABLE  IF  NOT  EXISTS  UserData(KEY  INTEGER  PRIMARY  KEY, ID INT NOT NULL, PHONE TEXT NOT NULL);";
	int ret = sqlite3_exec(ad->phone_db, sql, NULL, 0, &ErrMsg);
	dlog_print(DLOG_INFO, LOG_TAG, "phone table create ret : %d", ret);
	return ret;
}

int CreateGpsTable(appdata_s *ad){
	char *ErrMsg;
	char  *sql  =  "CREATE  TABLE  IF  NOT  EXISTS  GpsData(KEY  INTEGER  PRIMARY  KEY, ID INT NOT NULL, GPS INT NOT NULL);";
	int ret = sqlite3_exec(ad->phone_db, sql, NULL, 0, &ErrMsg);
	dlog_print(DLOG_INFO, LOG_TAG, "gps table create ret : %d", ret);
	return ret;
}

void init_phonedb(appdata_s *ad){
	int err = sqlite3_shutdown();
	int err2 = sqlite3_config(SQLITE_CONFIG_URI, 1);
	int err3 = sqlite3_initialize();

	char abs_path_to_db[PATH_MAX] = {0,};
	char *data_dir_path = app_get_data_path();

	snprintf(abs_path_to_db, PATH_MAX, "%s%s", data_dir_path, "test.db");
	dlog_print(DLOG_INFO, LOG_TAG, "db path : %s", abs_path_to_db);
	int ret = sqlite3_open(abs_path_to_db, &ad->phone_db);
	dlog_print(DLOG_INFO, LOG_TAG, "open ret : %d", ret);

	CreatePhoneTable(ad);
	CreateGpsTable(ad);
}


void my_phonetable_pack(Evas_Object *table, Evas_Object *child, int x, int y, int w, int h){
	evas_object_size_hint_align_set(child, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(child, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_table_pack(table, child, x, y, w, h);
	evas_object_show(child);
}

int InsertRecordPhone(appdata_s *ad, int id ,unsigned char *phone){
	char sql[256];
	char *ErrMsg;

	snprintf(sql,  256,  "INSERT  INTO  UserData  VALUES(NULL,%d,\'%s\');",  id, phone);
	int ret = sqlite3_exec(ad->phone_db, sql, NULL, 0, &ErrMsg);
	dlog_print(DLOG_INFO, LOG_TAG, "phone insert ret : %d", ret);
	return ret;
}

int InsertRecordGps(appdata_s *ad, int gps){
	char sql[256];
	char *ErrMsg;

	//INSERT INTO users (NAME, email) VALUES ('tez', 'tez@tez.kr') ON DUPLICATE KEY UPDATE name='tez', email='tezpark@tez.kr';
	int id = 0;
	char* key = "1";

	//INSERT OR REPLACE INTO MINE (id, name, age, salary)VALUES ("CD3", "HO", "37", 5245);
	snprintf(sql,  256,  "INSERT OR REPLACE INTO GpsData(KEY, ID, GPS) VALUES(\'%s\',%d,%d);",  key, id, gps);


	int ret = sqlite3_exec(ad->phone_db, sql, NULL, 0, &ErrMsg);
	dlog_print(DLOG_INFO, LOG_TAG, "gps insert ret : %d", ret);
	return ret;
}
