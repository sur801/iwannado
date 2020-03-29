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
#include <sqlite3.h>

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


	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", setting_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		if(gps_state)
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

	if(gps_state==1&&index == 0)
		gps_its[index] = "사용 중";
	else if(gps_state==0&&index == 0)
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
	*value = gps_state;

}

//// db에서 gps column값 읽어오는 컬백함수
//static int db_read_cb(void *counter, int argc, char **argv, char **azColName){
//
//
//	// 이 함수에서 db에서 읽어온 값을 세팅하는데, 이 함수를 들어오지를 않음.
//	dlog_print(DLOG_INFO, LOG_TAG, "DB READ CALL BACK FUNCTION" );
//
//	// db에서 읽어온 gps값이 string이랑 int로 바꿔줌.
//	int gps_state = atoi(argv[1]);
//	dlog_print(DLOG_INFO, LOG_TAG, "gps state :  [%d]", gps_state );
//	// 그리고 그걸 local state 값에 집어넣음.
//	gps_its_value[0] = gps_state;
//	return 0;
//}


/*
 * @brief: Set display item's value that can shows state of check box
 * @param[index]: Index of display item's value
 * @param[value]: Value of display item
 */
void data_set_gps_int_value(int index, int value)
{

	// 여기서 디비에서 gps 값 읽어와서 set 해야 함.
	// gps value 가져옴.
//	char *sql = "SELECT * FROM GpsData";
//	int counter=0;
//	char *ErrMsg;
	//sqlite3_exec(get_ad()->gps_db, sql, db_read_cb, &counter, &ErrMsg);

	//sql lite에 있는 값을 읽어와서 gps_its_value[index] 값을 세팅 해줘야 해!!!!!!!
	gps_state = value;
	dlog_print(DLOG_INFO, LOG_TAG, "SET GPS : check state [%d]", gps_state );

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

	int index = (int)data;
	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", phone_its[index]);
		return strdup(buf);
	}
	return NULL;
}


/* End of file */
