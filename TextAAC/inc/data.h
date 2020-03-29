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

#if !defined(_DATA_H)
#define _DATA_H

#define BUF_LEN 1024



/*
 * Initialize the data component
 */
void data_initialize(void);
/*
 * Finalize the data component
 */
void data_finalize(void);

char *data_get_text(const char *part);

char *data_get_func_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_category_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_func_text(void *data, Evas_Object *obj, const char *part);
char *data_get_category_text(void *data, Evas_Object *obj, const char *part);
void data_get_category_int_value(int index, int *value);
void data_set_category_int_value(int index, int value);

void data_get_resource_path(const char *edj_file_in, char *file_path_out, int file_path_max);

char *data_get_core_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_corona_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_class_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_mart_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_food_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_hospital_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_pe_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_setting_title_text(void *data, Evas_Object *obj, const char *part);


char *data_get_core_text(void *data, Evas_Object *obj, const char *part);
char *data_get_class_text(void *data, Evas_Object *obj, const char *part);
char *data_get_corona_text(void *data, Evas_Object *obj, const char *part);
char *data_get_corona_content(void *data, Evas_Object *obj, const char *part);
char *data_get_mart_text(void *data, Evas_Object *obj, const char *part);
char *data_get_food_text(void *data, Evas_Object *obj, const char *part);
char *data_get_hospital_text(void *data, Evas_Object *obj, const char *part);
char *data_get_pe_text(void *data, Evas_Object *obj, const char *part);
char *data_get_setting_text(void *data, Evas_Object *obj, const char *part);

#endif
