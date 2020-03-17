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

#include <app.h>
#include <Elementary.h>
#include <dlog.h>
#include "view.h"
#include "data.h"
#include "main.h"


int ON_OFF = 0;

void _file_abs_resource_path_get(char *res_file_path, char *abs_path, int buf_size)
{
   char *res_dir_path = app_get_resource_path();
   snprintf(abs_path, buf_size, "%s%s", res_dir_path, res_file_path);

   //dlog_print(DLOG_INFO, "hello%s", res_dir_path );
   if (res_dir_path)
     {
	    	snprintf(abs_path, buf_size, "%scategory/%s", res_dir_path, res_file_path);
        dlog_print(DLOG_INFO, "hello%s", abs_path );

        free(res_dir_path);
 }
}


/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_setting_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	dlog_print(DLOG_INFO, LOG_TAG, "SETTING TEXT CHECK : check state [%d]", gps_its_value[0]);

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", setting_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		if(gps_its_value[0])
			snprintf(buf, sizeof(buf), "%s", "사용 중");
		else
			snprintf(buf, sizeof(buf), "%s", "사용 안함");
		return strdup(buf);
	}

	return NULL;
}


/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_setting_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "설 정");
	return strdup(buf);
}


/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_gps_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	dlog_print(DLOG_INFO, LOG_TAG, "GPS TEXT CHECK : check state [%d]", gps_its_value[0]);
	if(gps_its_value[0]==1&&index == 0)
		gps_its[index] = "사용 중";
	else if(gps_its_value[0]==0&&index == 0)
		gps_its[index] = "사용 안함";
	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", gps_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "사용 안함");
		return strdup(buf);
	}

	return NULL;
}


/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_gps_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "위치 추적 기능");
	return strdup(buf);
}

/*
 * @brief: Get display item's value that can shows state of check box
 * @param[index]: Index of display item's value
 * @param[value]: The point to which save value of display item
 */
void data_get_gps_int_value(int index, int *value)
{
	dlog_print(DLOG_INFO, LOG_TAG, "GET GPS : check state [%d]", gps_its_value[index] );
	*value = gps_its_value[index];
}

/*
 * @brief: Set display item's value that can shows state of check box
 * @param[index]: Index of display item's value
 * @param[value]: Value of display item
 */
void data_set_gps_int_value(int index, int value)
{

	gps_its_value[index] = value;
	dlog_print(DLOG_INFO, LOG_TAG, "SET GPS : check state [%d]", gps_its_value[index] );

}

char *data_get_phone_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "보호자 전화번호 설정");
	return strdup(buf);
}

char *data_get_phone_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];


	int i;
	for(i=0;i<2;i++){
		dlog_print(DLOG_INFO, LOG_TAG, "phone item : %s\n",phone_its[i]);
	}


	int index = (int)data;
	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", phone_its[index]);
		return strdup(buf);
	}
	return NULL;
}


/* End of file */
