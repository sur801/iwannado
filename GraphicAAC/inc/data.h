#if !defined(_DATA_H)
#define _DATA_H


static const int category_count = 4;
static const int greeting_count = 4;
static const int qna_count = 4;
static const int mart_count = 4;
#define BUF_LEN 1024

static char *category_its[] = {
	/*** 1line styles ***/
	"core",
	"buy",
	"class",
	"food",
	"hospital",
	"pe",
	/* do not delete below */
	NULL
};

static char *core_its[] = {
	/*** 1line styles ***/
	"yes",
	"no",
	"good",
	"bad",
	"unaware",
	"okay",
	"something",
	"nothing",
	"this",
	"sick",

	/* do not delete below */
	NULL
};

static char *class_its[] = {
	"study",
	"sit",
	"class",
	"paint",
	"write",
	"pass",
	"glue",
	"scissors",
	"cut",
	NULL
};

static char *buy_its[] = {
	"hello",
	"howmuch",
	"pay",
	"where",
	"card",
	"recipt",
	"hot",
	"chopstick",
	NULL
};

static char *food_its[] = {
	"eat",
	"good",
	"bad",
	"get",
	"more",
	"many",
	"this",
	NULL
};

static char *hospital_its[] = {
	"sick",
	"yes",
	"no",
	"pill",
	"nurse",
	"water",
	"toilet",
	"out",
	NULL
};

static char *pe_its[] = {
	"jump",
	"catch",
	"ball",
	"hall",
	"run",
	"gym",
	"walk",
	NULL
};

static char *setting_its[] = {
	"정보",
	NULL
};


void _file_abs_resource_path_get(char *res_file_path, char *abs_path, int buf_size);
char *data_get_setting_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_setting_text(void *data, Evas_Object *obj, const char *part);
#endif
