#ifndef __circle2_H__
#define __circle2_H__

#include <app.h>
#include<tts.h>
#include <sqlite3.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "guiacc"

#if !defined(PACKAGE)
#define PACKAGE "org.example.guiacc"
#endif


#define SETTING_ITEM 2

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *layout;
	Evas_Object *grid;
	Evas_Object *button;
	Evas_Object *scroller;
	Evas_Object *circle_scroller;
	Evas_Object *box;
	Evas_Object *padding_start;
	Evas_Object *padding_end;
	Evas_Object *index;
	Evas_Object *nf;
	Evas_Object *page_layout;
	Eext_Circle_Surface *surface;
	tts_h tts;
	int item_count;
	Evas_Object* label;
	Elm_Gesture_Layer* g_layer; // for long click event
	sqlite3 *phone_db; // PHONE Database handle
	sqlite3 *gps_db; //GPS Database handle
	char *current_key;

} appdata_s;


typedef struct phonedata {
	char key[10]; // 식별 키
	int id; // 이 전화번호의 id number
	char phone[20]; // 전화번호
} phonedata_s;
// phone db에 저장할 record 형태.

typedef struct gpsdata {
	char key[10]; // 식별 키
	int gps;// 위치추적 기능 켰는지 안켰는지
} gpsdata_s;
// gps db에 저장할 record 형태.

Evas_Object* more_image;
typedef struct {
	char *name;
	char *sub_name;
	char *icon;
} more_item_info;





static more_item_info detail_more_item[2] = {
	{"Watch AAC란?", "", "image/more_option_icon_delete.png"},
	{"위치추적 설정", "", "image/more_option_icon_delete.png"},
};

char phone_its[100][20];
int phone_cnt;
char phone_check[20];// 인증번호 발송하기 위해 전화번호를 저장하는 전역 변수




int setting_on;
int app_start;

void sub_view_cb(void *data, Evas_Object *obj, void *event_info);
static void gui_tts(void *user_data, Evas* e,  Evas_Object *obj, void *event_info);
void enter_tts(appdata_s *ad);
void state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data);
static void _layout_create(appdata_s *ad);
static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it);
Elm_Object_Item *view_push_item_to_naviframe(Evas_Object *nf, Evas_Object *item, Elm_Naviframe_Item_Pop_Cb _pop_cb, void *cb_data);
Evas_Object *view_create_circle_genlist(Evas_Object *parent);
Evas_Object *view_get_naviframe(void);
Evas_Object *view_get_layout(void);
Evas_Object *view_get_win(void);
appdata_s *get_ad(void);
Evas_Object *view_create_circle_genlist(Evas_Object *parent);
static void
_scroll_cb(void *data, Evas_Object *scroller, void *event);




#endif /* __circle2_H__ */


