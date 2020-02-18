/*
 * view.h
 *
 *  Created on: Feb 5, 2020
 *      Author: seoyulim
 */

#ifndef VIEW_H_
#define VIEW_H_

#define SETTING_ITEMS 2


Evas_Object *view_set_more_button(Evas_Object *parent, const char *part_name, Evas_Smart_Cb _item_selected, void *user_data);
Evas_Object *view_create_circle_genlist(Evas_Object *parent);
Elm_Object_Item *view_append_item_to_genlist(Evas_Object *genlist, const char *style,
		const void *data, Evas_Smart_Cb _clicked_cb, const void *cb_data);
static void _create_category_list(void *data, Evas_Object *obj, void *event_info);
void view_create_more_item(Evas_Object *parent, int index, char *name, char *sub_name, char *image_path);

#endif /* VIEW_H_ */
