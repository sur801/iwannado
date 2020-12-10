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

#include "systemsettings2.h"
#include "data.h"

int ON_OFF = 0;

static char *func_its[] = {
	/*** 1line styles ***/
	"문자 AAC",
	"상징 추천",
	/* do not delete below */
	NULL
};

static char *category_its[] = {
	/*** 1line styles ***/
	"핵심어휘",
	"구매",
	"교실",
	"밥",
	"병원",
	"체육",
	/* do not delete below */
	NULL
};

static char *core_its[] = {
	/*** 1line styles ***/
	"예",
	"아니오",
	"좋아요",
	"싫어요",
	"몰라요",
	"괜찮아요",
	"있어요",
	"없어요",
	"이것",
	"아파요",
	/* do not delete below */
	NULL
};


static char *mart_its[] = {
	"안녕하세요",
	"얼마에요?",
	"계산해주세요",
	"어디있어요?",
	"카드로 계산해 주세요",
	"영수증 주세요",
	"데워주세요",
	"젓가락주세요",
	NULL
};


static char *class_its[] = {
	"공부해요",
	"앉아요",
	"교실",
	"색칠해요",
	"써요",
	"넘겨요",
	"풀",
	"가위",
	"오려요",
	NULL
};

static char *food_its[] = {
	"먹어요",
	"좋아요",
	"싫어요",
	"받아요",
	"많이",
	"많아요",
	"이것",
	NULL
};

static char *hospital_its[] = {
	"아파요",
	"예",
	"아니오",
	"약",
	"간호사",
	"물 주세요",
	"화장실",
	"나가요",
	NULL
};

static char *pe_its[] = {
	"뛰어요",
	"잡아요",
	"공놀이해요",
	"강당",
	"운동장돌아요",
	"체육관",
	"강당에서 걸어요",
	NULL
};

static char *setting_its[] = {
	"정보",
	NULL
};


/*
 * display items's values.
 * states of check boxes is controlled by these values.
 */
static int category_its_value[] = {
		-1,	/* Watch faces */
		0,	/* Watch always on */
		0,	/* Notification indicator */
		-1,	/* Brightness */
		-1,	/* Screen timeout */
		-1	/* Font */
};

/*
 * @brief: Initialize data that is used in this application.
 */
void data_initialize(void)
{
	/*
	 * If you need to initialize managing data,
	 * please use this function.
	 */
}

/*
 * @brief: Destroy data that is used in this application.
 */
void data_finalize(void)
{
	/*
	 * If you need to finalize managing data,
	 * please use this function.
	 */
}
/*
 * @brief: Get text
 * @param[part]: Name string of one of the existing text parts in the EDJ group
 */
char *data_get_text(const char *part)
{
	/*
	 * You can use this function to retrieve data.
	 */
	return NULL;
}

/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_func_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "자연스레");
	return strdup(buf);
}

/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_category_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "상징 목차");
	return strdup(buf);
}

char *data_get_core_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "핵심어휘");
	return strdup(buf);
}

char *data_get_class_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "교실");
	return strdup(buf);
}

char *data_get_mart_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "구매");
	return strdup(buf);
}

char *data_get_food_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "밥");
	return strdup(buf);
}

char *data_get_hospital_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "병원");
	return strdup(buf);
}

char *data_get_pe_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "체육");
	return strdup(buf);
}

/*
 * @brief: Function will be operated when items are shown on the screen
 * @param[data]: Data passed from 'elm_genlist_item_append' as third parameter
 * @param[obj]: Genlist
 * @param[part]: Name string of one of the existing text parts in the EDJ group implementing the item's theme
 */
char *data_get_func_text(void *data, Evas_Object *obj, const char *part)
{
	int index = (int)data;
	char buf[BUF_LEN];

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", func_its[index]);
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
char *data_get_category_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", category_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_core_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", core_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_class_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", class_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_mart_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", mart_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_food_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", food_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_hospital_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", hospital_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_pe_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", pe_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
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
char *data_get_setting_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		if(index==0){
			snprintf(buf, sizeof(buf), "%s", setting_its[index]);
		} else {
			snprintf(buf, sizeof(buf), "%s", setting_its[index]);
		}

		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
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
 * @brief: Get display item's value that can shows state of check box
 * @param[index]: Index of display item's value
 * @param[value]: The point to which save value of display item
 */
void data_get_category_int_value(int index, int *value)
{
	*value = category_its_value[index];
}

/*
 * @brief: Set display item's value that can shows state of check box
 * @param[index]: Index of display item's value
 * @param[value]: Value of display item
 */
void data_set_category_int_value(int index, int value)
{
	category_its_value[index] = value;
}

/*
 * @brief: Get path of resource.
 * @param[file_in]: File name
 * @param[file_path_out]: The point to which save full path of the resource
 * @param[file_path_max]: Size of file name include path
 */
void data_get_resource_path(const char *file_in, char *file_path_out, int file_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(file_path_out, file_path_max, "%s%s", res_path, file_in);
		free(res_path);
	}
}


/* End of file */
