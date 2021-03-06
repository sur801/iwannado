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

#if !defined(_MAIN_H)
#define _MAIN_H

#if !defined(PACKAGE)
#define PACKAGE "org.example.systemsettings2"
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "systemsettings2"


int setting_on;
//카테고리 리스트
Evas_Object *category_genlist;
//더보기 버튼
Evas_Object * more_image;

static void _create_category_list(void *data, Evas_Object *obj, void *event_info);
void _opened_cb(void *data, Evas_Object *obj, void *event_info);

/*long click timer*/
static const char* _klongtimer = "_long_timer";
static long _long_click_time = 1; // 1 sec default
static Eina_Bool _long_press_cb(void *data);
static void _mouse_down(void *data, Evas *e, Evas_Object *obj, void *event_info);
static void _mouse_up(void *data, Evas *e, Evas_Object *obj, void *event_info);
static void _mouse_move(void *data, Evas *e, Evas_Object *obj, void *event_info);
void pius_object_longclick_time_set(double time);
double pius_object_longclick_time_get();
void pius_object_longclick_add(Evas_Object *obj, Evas_Smart_Cb func, const void *data);







#endif
