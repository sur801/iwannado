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
	"자주 쓰는 말",
	"코로나",
	"음식",
	"병원",
	"마트",
	"체육",
	/* do not delete below */
	NULL
};

static char *class_its[];
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


static char *corona_its[] = {
	"코로나란",
	"원인",
	"증상",
	"치료법",
	"현황",
	"첫번째 예방법",
	"두번째 예방법은?",
	"선별진료소란?",
	"검사 방법은?",
	"추가 질문 있나요?",
	NULL
};

static char *corona_its_value[] = {
	"중국 우한에서 발생한 폐렴은 신종 코로나 바이러스인 2019년 12월 처음 인체 감염이 확인됐다는 의미에서 '코로나19'로 불리웁니다. 중국 우한에서 발생한 바이러스는 기존 코로나 바이러스와는 성질이 달라 신종 코로나 바이러스로 분류됐습니다.",
	"국제보건기구(WHO)에 따르면 우한에서 발생한 새로운 코로나 바이러스의 확산은 동물에서 비롯된 것으로 보고 있습니다. 신종 코로나 바이러스는 새로운 바이러스이기 때문에 감염 경로는 아직 명확하게 밝혀지지 않은 상태입니다.",
	"코로나19에 감염되면 2~3일에서 최장 2주 정도 잠복기를 거쳤다가 다양한 증상이 나타납니다. 37.5도 이상의 고열, 기침, 인후통, 가래, 근육통, 두통, 호흡곤란, 폐렴 등의 증상이 발생합니다. 폐 손상에 따른 호흡부전으로 심하면 사망에 이를 수도 있습니다.",
	"현재까지 코로나19 치료법은 없습니다. 증상에 따른 약제를 사용하고 에이즈 치료제나 항말라리아 제제를 이용하여 치료한 사례가 있으며 호흡곤란을 호소하는 경우 산소 마스크를 적용할 수 있습니다.",
	"어제 기준으로 국내 코로나 확진자는 9478명, 서울은 390명, 마포구는 14명 확진받았습니다.",
	"철저한 손씻기가 가장 중요한 감염병 예방법입니다. 사람의 분비물은 직접 튀는 경우보다, 그 분비물이 어딘가에 묻었는데 손으로 만져서 몸으로 들어올 확률이 더 높다고 알려져 있습니다. 흐르는 물에 비누를 이용하여 30초 이상 손을 씻으면 바이러스는 거의 다 죽거나 힘이 약해져 감염을 일으키기 힘들다고 합니다.",
	"마스크는 감염자의 분비물이 공기 중으로 날아가지 않게하고, 공기 중의 바이러스가 호흡기를 통해 들어오지 못하도록 막아주는 역할을 합니다. 기침 시에는 분비물이 손이나 공기 중에 뿌려지지 않도록 옷소매에 하는 것이 좋습니다. 또 호흡기 증상이 있는 사람과의 밀접한 접촉을 피하고 사람 많이 모인 곳에는 가지 않아야 하겠습니다.",
	"만약 코로나19에 걸린것 같으면 마포구 보건소 선별진료소에 가서 검사 받아야합니다.ß",
	"선별진료소에 가면 상담과 열을 측정하고 가래검사, 입 면봉검사,  코면봉검사를 하게됩니다, 결과는 다음날 나옵니다.",
	"코로나19 설명은 끝났습니다. 혹시 질문있는 사람 있어요?",
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

char *data_get_corona_title_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];

	snprintf(buf, sizeof(buf), "%s", "코로나");
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

char *data_get_corona_text(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", corona_its[index]);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.1")) {
		snprintf(buf, sizeof(buf), "%s", "30 seconds");
		return strdup(buf);
	}

	return NULL;
}

char *data_get_corona_content(void *data, Evas_Object *obj, const char *part)
{
	char buf[BUF_LEN];
	int index = (int)data;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, sizeof(buf), "%s", corona_its_value[index]);
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
