/*
 * view.h
 *
 *  Created on: Feb 5, 2020
 *      Author: seoyulim
 */

#ifndef VIEW_H_
#define VIEW_H_

#define GPS_ITEM 2



Evas_Object *view_create_circle_genlist(Evas_Object *parent);
Elm_Object_Item *view_append_item_to_genlist(Evas_Object *genlist, const char *style,
		const void *data, Evas_Smart_Cb _clicked_cb, const void *cb_data);
static void _create_category_list(void *data, Evas_Object *obj, void *event_info);
void view_create_more_item(Evas_Object *parent, int index, char *name, char *sub_name, char *image_path);
void
_opened_cb(void *data, Evas_Object *obj, void *event_info);

static Evas_Object* _get_gps_check(void *data, Evas_Object *obj, const char *part);
Eina_Bool state; // state variable for gps checkbox
Evas_Object * setting_genlist;// for refresh default setting genlist
Evas_Object * phone_genlist; // for refresh default phone genlist
static void _phone_delete_cb(void *data, Evas_Object *obj, void *event_info);
void _phone_add(void);

#endif /* VIEW_H_ */
