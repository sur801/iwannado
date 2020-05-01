/*
 * view.h
 *
 *  Created on: Feb 5, 2020
 *      Author: seoyulim
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "main.h"
#define GPS_ITEM 2

int gps_state;
Evas_Object * gps_genlist;// for refresh gps setting genlist

Evas_Object *view_create_circle_genlist(Evas_Object *parent);
Elm_Object_Item *view_append_item_to_genlist(Evas_Object *genlist, const char *style,
		const void *data, Evas_Smart_Cb _clicked_cb, const void *cb_data);
static void _create_category_list(void *data, Evas_Object *obj, void *event_info);
void view_create_more_item(Evas_Object *parent, int index, char *name, char *sub_name, char *image_path);
static void _popup_timeout(void *data, Evas_Object *obj, void *event_info);
void _to_longclick_popup_cb(void *data, Evas_Object *obj, void *event_info);
static void _to_popup(int flag);
void
_opened_cb(void *data, Evas_Object *obj, void *event_info);

Evas_Object *popup;//popup for announce longclick
static Evas_Object* _get_gps_check(void *data, Evas_Object *obj, const char *part);
Eina_Bool state; // state variable for gps checkbox
Evas_Object * setting_genlist;// for refresh default setting genlist
Evas_Object * phone_genlist; // for refresh default phone genlist
static void _phone_delete_cb(void *data, Evas_Object *obj, void *event_info);
static void _phone_add_cb(void *data, Evas_Object *obj, void *event_info);

/*db 관리 함수들*/
int CreatePhoneTable(appdata_s *ad);
void init_phonedb(appdata_s *ad);
void my_phonetable_pack(Evas_Object *table, Evas_Object *child, int x, int y, int w, int h);
int InsertRecordPhone(appdata_s *ad, int id, unsigned char *phone);
int read_db(appdata_s *ad);
int CreateGpsTable(appdata_s *ad);
void my_gpstable_pack(Evas_Object *table, Evas_Object *child, int x, int y, int w, int h);
int InsertRecordGps(appdata_s *ad, int gps);
#endif /* VIEW_H_ */
