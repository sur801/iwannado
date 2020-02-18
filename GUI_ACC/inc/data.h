#if !defined(_DATA_H)
#define _DATA_H


static const int category_count = 4;
static const int greeting_count = 4;
static const int qna_count = 4;
static const int mart_count = 4;
#define BUF_LEN 1024

static char *category_its[] = {
	/*** 1line styles ***/
	"greet",
	"ask",
	"mart",
	/* do not delete below */
	NULL
};

static char *greeting_its[] = {
	/*** 1line styles ***/
	"hello",
	"okay",
	"sorry",
	"thankyou",
	"sorry",

	/* do not delete below */
	NULL
};

static char *qna_its[] = {
	"good",
	"bad",
	"yes",
	"no",
	NULL
};

static char *mart_its[] = {
	"hello",
	"where",
	"pay",
	"howmuch",
	NULL
};

static char *setting_its[] = {
	"사용중",
	"보호자 전화번호 설정"

};


void _file_abs_resource_path_get(char *res_file_path, char *abs_path, int buf_size);
char *data_get_setting_title_text(void *data, Evas_Object *obj, const char *part);
char *data_get_setting_text(void *data, Evas_Object *obj, const char *part);
#endif
