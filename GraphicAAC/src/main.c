//제일 나은 최종본

#include "main.h"
#include "data.h"
#include "view.h"
#include<tts.h>
#include<string.h>


int depth, tts_num, op;
//naviframe 의 깊이, 몇번째 아이템의 tts를 실행시킬지, 몇번째 카테고리의 아이템들인지

//static const int ad->item_count = 3;
#define PAGE_CHANGED_EVENT "active_page,changed"

appdata_s s_info = {
		.win = NULL,
		.conform = NULL,
		.layout = NULL,
		.button = NULL,
		.grid = NULL,
		.scroller = NULL,
		.circle_scroller = NULL,
		.box = NULL,
		.padding_start = NULL,
		.padding_end = NULL,
		.index = NULL,
		.nf = NULL,
		.page_layout = NULL,
		.surface = NULL,
		.item_count = 6,
		.label = NULL,
		.g_layer = NULL,
		.phone_db = NULL,
		.current_key = NULL,
};

appdata_s v_info = {
		.layout = NULL,
		.button = NULL,
		.scroller = NULL,
		.circle_scroller = NULL,
		.box = NULL,
		.padding_start = NULL,
		.padding_end = NULL,
		.index = NULL,
		.nf = NULL,
		.page_layout = NULL,
		.surface = NULL,
		.item_count = 4,
		.label = NULL,
};

char test[10] = "helllo";


// Styles for an even number of pages
static const char *even_style[] = {
   "item/even_1",
   "item/even_2",
   "item/even_3",
   "item/even_4",
   "item/even_5",
   "item/even_6",
   "item/even_7",
   "item/even_8",
   "item/even_9",
   "item/even_10",
   "item/even_11",
   "item/even_12",
   "item/even_13",
   "item/even_14",
   "item/even_15",
   "item/even_16",
   "item/even_17",
   "item/even_18",
   "item/even_19",
   "item/even_20",
};

// Styles for an odd number of pages
static const char *odd_style[] = {
   "item/odd_1",
   "item/odd_2",
   "item/odd_3",
   "item/odd_4",
   "item/odd_5",
   "item/odd_6",
   "item/odd_7",
   "item/odd_8",
   "item/odd_9",
   "item/odd_10",
   "item/odd_11",
   "item/odd_12",
   "item/odd_13",
   "item/odd_14",
   "item/odd_15",
   "item/odd_16",
   "item/odd_17",
   "item/odd_18",
   "item/odd_19",
};




Evas_Object *view_create_circle_genlist(Evas_Object *parent)
{
	Evas_Object *genlist = NULL;
	Evas_Object *circle_genlist = NULL;

	if (parent == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

//	s_info.surface = eext_circle_surface_conformant_add(s_info.nf);
	if (s_info.surface) {
		dlog_print(DLOG_ERROR, LOG_TAG, "circle surface is NULL.");
		return NULL;
	}

	genlist = elm_genlist_add(parent);
	/*
	 * This make selected list item is shown compressed.
	 */
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(genlist, "selected", NULL, NULL);

	/*
	 * This make genlist style circular.
	 */
	circle_genlist = eext_circle_object_genlist_add(genlist, s_info.surface);
	eext_circle_object_genlist_scroller_policy_set(circle_genlist, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	eext_rotary_object_event_activated_set(circle_genlist, EINA_TRUE);

	evas_object_show(genlist);

	return genlist;
}

/*
static void _gl_display(void)
{

	settings_genlist = view_create_circle_genlist(s_info.nf);
	int i;
	view_append_item_to_genlist(settings_genlist, "category.title", NULL, NULL, NULL);
	for (i = 0; i < CATEGORY_ITEMS; i++)
		view_append_item_to_genlist(settings_genlist, "category.1text", (void *)i, _create_category_list, (void *)i);


	view_append_item_to_genlist(settings_genlist, "padding", NULL, NULL, NULL);

	view_push_item_to_naviframe(s_info.nf, settings_genlist, NULL, NULL);
}
*/



void state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data)
{
	if (TTS_STATE_READY == current && TTS_STATE_CREATED == previous) {
		appdata_s *ad = (appdata_s *) user_data;
		int ret;
		const char* text;

		if(op == 0) {
			if(tts_num==0) {
				text = "예";
			} else if (tts_num==1) {
				text = "아니오";
			} else if (tts_num==2){
				text = "좋아요";
			} else if (tts_num==3){
				text = "싫어요";
			} else if (tts_num==4){
				text = "몰라요";
			} else if (tts_num==5){
				text = "괜찮아요";
			} else if (tts_num==6){
				text = "있어요";
			} else if (tts_num==7){
				text = "없어요";
			} else if (tts_num==8){
				text = "이것";
			} else if (tts_num==9){
				text = "아파요";
			}
		}
		else if(op == 1) {
			if(tts_num==0) {
				text = "안녕하세요";
			} else if (tts_num==1) {
				text = "얼마에요";
			} else if (tts_num==2){
				text = "계산해주세요";
			} else if (tts_num==3){
				text = "어디에있나요";
			} else if (tts_num==4){
				text = "카드로결제해주세요";
			} else if (tts_num==5){
				text = "영수증주세요";
			} else if (tts_num==6){
				text = "데워주세요";
			} else if (tts_num==7){
				text = "젓가락주세요";
			}

		}
		else if(op == 2) {
			if(tts_num==0) {
				text = "공부해요";
			} else if (tts_num==1) {
				text = "앉아요";
			} else if (tts_num==2){
				text = "교실";
			} else if (tts_num==3){
				text = "색칠해요";
			} else if (tts_num==4){
				text = "써요";
			} else if (tts_num==5){
				text = "넘겨요";
			} else if (tts_num==6){
				text = "풀";
			} else if (tts_num==7){
				text = "가위";
			} else if (tts_num==8){
				text = "오려요";
			}

		}
		else if(op == 3) {
			if(tts_num==0) {
				text = "먹어요";
			} else if (tts_num==1) {
				text = "좋아요";
			} else if (tts_num==2){
				text = "싫어요";
			} else if (tts_num==3){
				text = "받아요";
			} else if (tts_num==4){
				text = "많이";
			} else if (tts_num==5){
				text = "많아요";
			} else if (tts_num==6){
				text = "이것";
			}
		}
		else if(op == 4) {
			if(tts_num==0) {
				text = "아파요";
			} else if (tts_num==1) {
				text = "예";
			} else if (tts_num==2){
				text = "아니오";
			} else if (tts_num==3){
				text = "약";
			} else if (tts_num==4){
				text = "간호사";
			} else if (tts_num==5){
				text = "물 주세요";
			} else if (tts_num==6){
				text = "화장실";
			} else if (tts_num==7){
				text = "나가요";
			}

		}
		else if(op == 5) {
			if(tts_num==0) {
				text = "뛰어요";
			} else if (tts_num==1) {
				text = "잡아요";
			} else if (tts_num==2){
				text = "공놀이해요";
			} else if (tts_num==3){
				text = "강당";
			} else if (tts_num==4){
				text = "운동장 돌아요";
			} else if (tts_num==5){
				text = "체육관";
			} else if (tts_num==6){
				text = "강당에서 걸어요";
			}

		}

		const char* language = "ko_KR"; // Language
		int voice_type = TTS_VOICE_TYPE_FEMALE; // Voice type
		int speed = TTS_SPEED_AUTO; // Read speed
		int utt_id; // Utterance ID for the requested text

		ret = tts_add_text(ad->tts, text, language, voice_type, speed, &utt_id);

		ret = tts_play(ad->tts);
		dlog_print(DLOG_INFO, LOG_TAG, "Added text and started playing");
	}
}

void enter_tts(appdata_s *ad)
{
	int ret;
	ret = tts_create(&(ad->tts));
	ret = tts_set_state_changed_cb(ad->tts, state_changed_cb, ad);
	ret = tts_prepare(ad->tts);
}

static void gui_tts(void *user_data, Evas* e,  Evas_Object *obj, void *event_info){
	enter_tts(user_data);
}


//naviframe item들 back 버튼 눌러서 pop될때 실행되는 callback 함수
static void _naviframe_back_cb(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   dlog_print(DLOG_INFO, LOG_TAG, "back button setting:on : %d\n",setting_on);
   elm_naviframe_item_pop(obj);


   eext_rotary_object_event_activated_set(s_info.circle_scroller, EINA_TRUE);

   if(setting_on > 1){
	   // gps setting 창에서 back버튼 눌렀을때, setting 창 아이템들 리프레시
	   if(setting_on==2){
		   dlog_print(DLOG_INFO, LOG_TAG, "update setting_genlist\n");
		   elm_genlist_realized_items_update(setting_genlist);
		   eext_rotary_object_event_activated_set(setting_genlist, EINA_TRUE);
	   } else if(setting_on==4){
		   eext_rotary_object_event_activated_set(phone_genlist, EINA_TRUE);
	   } else if(setting_on==3) {
		   eext_rotary_object_event_activated_set(gps_genlist, EINA_TRUE);
	   }
	   setting_on--;


	   //더보기 버튼
   } else if(setting_on <= 1 && setting_on >= 0){
	   setting_on --;
	   dlog_print(DLOG_INFO, LOG_TAG, "OUT OF SETTING\n");

		//more_image = elm_image_add(s_info.layout);
		char abs_path_to_image[PATH_MAX] = {0,};
		char *res_dir_path = app_get_resource_path();
		snprintf(abs_path_to_image,PATH_MAX, "%s%s", res_dir_path, "horizontal_more_ic.png");

		evas_object_image_file_set(more_image, abs_path_to_image, NULL);
		evas_object_geometry_set(more_image, 150, 310, 60, 60);
		dlog_print(DLOG_INFO, LOG_TAG, "image_path : %s",abs_path_to_image);
		evas_object_size_hint_weight_set(more_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(more_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(more_image);
   }
   // 상부 메뉴가 됐다는 표시로 depth를 0으로 표시
   depth = 0;
}


Evas_Object *view_get_naviframe(void)
{
	return s_info.nf;
}

Evas_Object *view_get_layout(void)
{
	return v_info.layout;
}

Evas_Object *view_get_win(void)
{
	return s_info.win;
}
appdata_s *get_ad(void){
	return &s_info;
}


//naviframe
static Evas_Object *
create_naviframe(Evas_Object *parent)
{
	Evas_Object *nf = NULL;
		if (parent == NULL) {
			dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
			return NULL;
		}

		nf = elm_naviframe_add(parent);

		elm_naviframe_prev_btn_auto_pushed_set(nf, EINA_TRUE);

		elm_object_part_content_set(parent, "elm.swallow.content", nf);
		eext_object_event_callback_add(nf, EEXT_CALLBACK_BACK, _naviframe_back_cb, NULL);
		eext_object_event_callback_add(nf, EEXT_CALLBACK_MORE, eext_naviframe_more_cb, NULL);


		return nf;
}

Elm_Object_Item *view_push_item_to_naviframe(Evas_Object *nf, Evas_Object *item, Elm_Naviframe_Item_Pop_Cb _pop_cb, void *cb_data)
{
	Elm_Object_Item* nf_it = NULL;

	if (nf == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "naviframe is NULL.");
		return NULL;
	}

	if (item == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "item is NULL.");
		return NULL;
	}

	/*
	 * Sixth parameter
	 * @param[item_style] item style name. "empty" style has no button like prev_button and next_button.
	 */
	nf_it = elm_naviframe_item_push(nf, NULL, NULL, NULL, item, "empty");
	if (_pop_cb != NULL)
			elm_naviframe_item_pop_cb_set(nf_it, _pop_cb, cb_data);

	return nf_it;
}


static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}


static void
_page_indicator_selected_set(Evas_Object *index, int page_index)
{
   Elm_Object_Item *item_to_select = elm_index_item_find(index, (void *)page_index);
   elm_index_item_selected_set(item_to_select, EINA_TRUE);
}


static void
_view_create(void *user_data, Evas* e,  Evas_Object *obj, void *event_info)
{

    dlog_print(DLOG_INFO, "MY_LOG", evas_object_name_get(obj));
    depth = 1;
    // 일단 tts num 기본으로 0 세팅.
    tts_num=0;

    evas_object_geometry_set(more_image, 0, 0, 10, 10);
    evas_object_image_file_set(more_image, NULL, NULL);
    setting_on = 0;

    _layout_create(&v_info);


    //요게 문제 이것때문에 팝하면 그전 뷰가 안보임.
    //elm_object_content_set(v_info.nf, v_info.layout);
    view_push_item_to_naviframe(v_info.nf, v_info.layout, NULL, NULL);

}


static Evas_Object *
_image_create(Evas_Object *parent, char *image_name)
{
   Evas_Object *image = elm_image_add(parent);

   char abs_path_to_image[PATH_MAX] = {0,};
   _file_abs_resource_path_get(image_name, abs_path_to_image, PATH_MAX);
   elm_image_file_set(image, abs_path_to_image, NULL);

   evas_object_size_hint_weight_set(image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(image, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add (image, "clicked", _view_create, NULL);

   evas_object_show(image);

   return image;
}

static Evas_Object *
_image_create_end(Evas_Object *parent, char *image_name)
{
   Evas_Object *image = elm_image_add(parent);

   char abs_path_to_image[PATH_MAX] = {0,};
   _file_abs_resource_path_get(image_name, abs_path_to_image, PATH_MAX);
   elm_image_file_set(image, abs_path_to_image, NULL);

   evas_object_size_hint_weight_set(image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(image, EVAS_HINT_FILL, EVAS_HINT_FILL);

   // 이미지 클릭시 tts 함수 달아줌.
   evas_object_smart_callback_add (image, "clicked", gui_tts, &v_info);
   evas_object_show(image);

   return image;
}



static Evas_Object *
_page_layout_create(Evas_Object *parent, int image_index)
{
   Evas_Object *page_layout = elm_layout_add(parent);
   elm_layout_theme_set(page_layout, "layout", "body_thumbnail", "default");
   evas_object_size_hint_weight_set(page_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(page_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(page_layout);

   //이미지 경로 가져오기
   const int MAX_NAME_LENGTH = 40;
      char image_name[MAX_NAME_LENGTH] = {0,};
      if(!(depth)){
   	   snprintf(image_name, MAX_NAME_LENGTH, "%s.jpg",category_its[image_index]);
   	   dlog_print(DLOG_INFO, "hehe%s", category_its[image_index] );
   	   //op = global_ad->index;
      }
      else {
    	  if(op==0){
    	  	snprintf(image_name, MAX_NAME_LENGTH, "%s/%s.jpg", category_its[op] ,core_its[image_index]);
    	  	v_info.item_count = 10;
    	  }
    	  else if(op==1){
    	  	snprintf(image_name, MAX_NAME_LENGTH, "%s/%s.jpg", category_its[op] ,buy_its[image_index]);
    	  	v_info.item_count = 8;
    	  }
    	  else if(op==2){
    	  	snprintf(image_name, MAX_NAME_LENGTH, "%s/%s.jpg", category_its[op] ,class_its[image_index]);
    	  	v_info.item_count = 9;
    	  }
    	  else if(op==3){
    	    snprintf(image_name, MAX_NAME_LENGTH, "%s/%s.jpg", category_its[op] ,food_its[image_index]);
    	    v_info.item_count = 7;
    	  }
    	  else if(op==4){
    	    snprintf(image_name, MAX_NAME_LENGTH, "%s/%s.jpg", category_its[op] ,hospital_its[image_index]);
    	    v_info.item_count = 8;
    	  }
    	  else if(op==5){
    	    snprintf(image_name, MAX_NAME_LENGTH, "%s/%s.jpg", category_its[op] ,pe_its[image_index]);
    	    v_info.item_count = 7;
    	  }


    	  dlog_print(DLOG_INFO, "hehe%s", image_name );
      }

   Evas_Object *image;

   if(!(depth))
   	   image = _image_create(page_layout, image_name); // 첫번째 화면 이미지 생성할
      else
   	   image = _image_create_end(page_layout, image_name); // 두번째 화면 이미지 생성할때

   elm_object_part_content_set(page_layout, "elm.icon", image);

   return page_layout;
}

static Evas_Object *
_padding_item_create(Evas_Object *parent)
{
   Evas_Object *padding = evas_object_rectangle_add(evas_object_evas_get(parent));

   evas_object_size_hint_weight_set(padding, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(padding, EVAS_HINT_FILL, EVAS_HINT_FILL);

   return padding;
}

static void
_layout_resize_cb(void *data , Evas *e, Evas_Object *page_layout, void *event_info)
{
   int page_width;
   int page_height;
   int container_width;
   int container_height;
   appdata_s *ad = data;

   evas_object_geometry_get(page_layout, NULL, NULL, &page_width, &page_height);
   evas_object_geometry_get(ad->scroller, NULL, NULL, &container_width, &container_height);

   int padding_size = (container_width - page_width) / 2;
   //int padding_size = 0;

   evas_object_size_hint_min_set(ad->padding_start, padding_size, container_height);
   evas_object_size_hint_min_set(ad->padding_end, padding_size, container_height);

   elm_scroller_page_size_set(ad->scroller, page_width, page_height);
}


static void
_box_create(appdata_s *ad)
{
   ad->box = elm_box_add(ad->scroller);

   const int IMAGES_COUNT = 10;

   for (int i = 0; i < ad->item_count; ++i)
     {
        ad->page_layout = _page_layout_create(ad->box, i % IMAGES_COUNT);
        elm_box_pack_end(ad->box, ad->page_layout);
     }

   evas_object_event_callback_add(ad->page_layout, EVAS_CALLBACK_RESIZE, _layout_resize_cb, ad);

   ad->padding_start = _padding_item_create(ad->box);
   elm_box_pack_start(ad->box, ad->padding_start);

   ad->padding_end = _padding_item_create(ad->box);
   elm_box_pack_end(ad->box, ad->padding_end);

   elm_box_horizontal_set(ad->box, EINA_TRUE);
   evas_object_size_hint_weight_set(ad->box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


   evas_object_show(ad->box);
}

static void
_circle_scroller_create(appdata_s *ad)
{
   //ad->surface = eext_circle_surface_conformant_add(ad->nf);


   ad->circle_scroller = eext_circle_object_scroller_add(ad->scroller, ad->surface);

   eext_circle_object_scroller_policy_set(ad->circle_scroller,
                                          ELM_SCROLLER_POLICY_OFF,
                                          ELM_SCROLLER_POLICY_OFF);

   eext_rotary_object_event_activated_set(ad->circle_scroller, EINA_TRUE);
}

static void
_scroll_cb(void *data, Evas_Object *scroller, void *event)
{
   static int prev_h_page = 0;
   int cur_h_page         = 0;

   elm_scroller_current_page_get(scroller, &cur_h_page, NULL);
   if (cur_h_page != prev_h_page)
     {
        appdata_s *ad = data;
        evas_object_smart_callback_call(ad->index, PAGE_CHANGED_EVENT, NULL);

        prev_h_page = cur_h_page;
     }
}

static void
_scroller_create(appdata_s *ad)
{
   ad->scroller = elm_scroller_add(ad->layout);

   elm_scroller_policy_set(ad->scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);

   _box_create(ad);
   elm_object_content_set(ad->scroller, ad->box);


   evas_object_smart_callback_add(ad->scroller, "scroll", _scroll_cb, ad);

   _circle_scroller_create(ad);


   evas_object_show(ad->scroller);
}

static void
_active_page_changed_cb(void *data, Evas_Object *index, void *event)
{
   appdata_s *ad     = data;
   int cur_h_page = 0;

   elm_scroller_current_page_get(ad->scroller, &cur_h_page, NULL);
   if(!(depth))
   	   op = cur_h_page;
   else
   	   tts_num = cur_h_page;
   _page_indicator_selected_set(ad->index, cur_h_page);
}

static Evas_Object *
_index_create(appdata_s *ad)
{
   Evas_Object *index = elm_index_add(ad->layout);

   elm_object_style_set(index, "circle");
   elm_index_horizontal_set(index, EINA_TRUE);
   elm_index_autohide_disabled_set(index, EINA_TRUE);

   Eina_Bool is_even_count = ad->item_count % 2 == 0;
   const int CENTER_INDEX = is_even_count ? 10 : 9;
   int start_index = CENTER_INDEX - ad->item_count / 2;

   const char **style = is_even_count ? even_style : odd_style;

   for (int i = 0; i < ad->item_count; ++i)
     {
        Elm_Object_Item *it = elm_index_item_append(index, NULL, NULL, (void *)i);
        elm_object_item_style_set(it, style[start_index + i]);
     }

   elm_index_level_go(index, 0);

   _page_indicator_selected_set(index, 0);

   evas_object_smart_callback_add(index, PAGE_CHANGED_EVENT, _active_page_changed_cb, ad);

   evas_object_show(index);

   return index;
}

static void
_page_indicator_create(appdata_s *ad)
{
   const int MAX_INDEX_STYLE_ITEM = 20;

   if (ad->item_count > MAX_INDEX_STYLE_ITEM)
     {
        eext_circle_object_scroller_policy_set(ad->circle_scroller,
                                               ELM_SCROLLER_POLICY_OFF,
                                               ELM_SCROLLER_POLICY_OFF);
     }
   else
     {
        ad->index = _index_create(ad);
        elm_object_part_content_set(ad->layout, "elm.swallow.content", ad->index);
        eext_circle_object_scroller_policy_set(ad->circle_scroller,
                                               ELM_SCROLLER_POLICY_OFF,
                                               ELM_SCROLLER_POLICY_OFF);
     }
}

static void
_layout_create(appdata_s *ad)
{
   ad->layout = elm_layout_add(ad->nf);


   elm_layout_theme_set(ad->layout, "layout", "application", "default");

   _scroller_create(ad);
   elm_object_part_content_set(ad->layout, "elm.swallow.bg", ad->scroller);

   _page_indicator_create(ad);

   evas_object_show(ad->layout);
}

static Eina_Bool _naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	dlog_print(DLOG_INFO, LOG_TAG, "hello3\n");
	ui_app_exit();

	return EINA_FALSE;
}





static void
create_base_gui()
{
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */

	s_info.win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(s_info.win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(s_info.win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(s_info.win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(s_info.win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(s_info.win, EEXT_CALLBACK_BACK, win_back_cb, &s_info);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	s_info.conform = elm_conformant_add(s_info.win);
	elm_win_indicator_mode_set(s_info.win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(s_info.win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(s_info.conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(s_info.win, s_info.conform);



	// naviframe 만들기.
	s_info.nf = create_naviframe(s_info.conform);
	v_info.nf = s_info.nf;
	elm_object_content_set(s_info.conform, s_info.nf);
	s_info.surface = eext_circle_surface_conformant_add(s_info.nf);
	v_info.surface = s_info.surface;
	depth = 0;

	//layout 만들기
	_layout_create(&s_info);

	// gesture layer만들어서 layout에 올리기. long click 이벤트 위해서.
	s_info.g_layer = elm_gesture_layer_add(s_info.layout);


	//더보기 버튼 이미지 삽입
	more_image = elm_image_add(s_info.layout);

	char abs_path_to_image[PATH_MAX] = {0,};
	char *res_dir_path = app_get_resource_path();
	snprintf(abs_path_to_image,PATH_MAX, "%s%s", res_dir_path, "horizontal_more_ic.png");

	evas_object_image_file_set(more_image, abs_path_to_image, NULL);
	evas_object_geometry_set(more_image, 150, 310, 60, 60);
	dlog_print(DLOG_INFO, LOG_TAG, "image_path : %s",abs_path_to_image);
	evas_object_size_hint_weight_set(more_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(more_image, EVAS_HINT_FILL, EVAS_HINT_FILL);

	// 더보기 버튼에 long tap event로 opened_cb 함수 달아줌.
	elm_gesture_layer_attach(s_info.g_layer, more_image);
//	evas_object_smart_callback_add(more_image, "clicked", _to_longclick_popup_cb,NULL);
	dlog_print(DLOG_INFO, LOG_TAG, "address of s_info.g_layer : %d", s_info.g_layer);
	elm_gesture_layer_cb_set(s_info.g_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_END, _to_longclick_popup_cb, (void*)s_info.conform);
	elm_gesture_layer_cb_set(s_info.g_layer, ELM_GESTURE_N_LONG_TAPS, ELM_GESTURE_STATE_END, _opened_cb, (void*)more_image);
	//evas_object_event_callback_add (more_image, EVAS_CALLBACK_MOUSE_DOWN, _opened_cb, (void*)more_image);
	evas_object_show(more_image);





	view_push_item_to_naviframe(s_info.nf, s_info.layout, _naviframe_pop_cb, NULL);

	evas_object_show(s_info.nf);


	evas_object_show(s_info.conform);

	/* Show window after base gui is set up */
	evas_object_show(s_info.win);


	elm_object_content_set(s_info.nf, s_info.layout);

	app_start = 0;

	init_phonedb(&s_info);

	if(!app_start){
		//세팅 창 처음 킬때만 read함.
		read_db(get_ad());
		app_start=1;
	}


}

void
app_request_response_cb(ppm_call_cause_e cause, ppm_request_result_e result, const char *privilege, void *user_data)
{
    if (cause == PRIVACY_PRIVILEGE_MANAGER_CALL_CAUSE_ERROR) {
        /* Log and handle errors */

        return;
    }

    switch (result) {
        case PRIVACY_PRIVILEGE_MANAGER_REQUEST_RESULT_ALLOW_FOREVER:
            /* Update UI and start accessing protected functionality */
            break;
        case PRIVACY_PRIVILEGE_MANAGER_REQUEST_RESULT_DENY_FOREVER:
            /* Show a message and terminate the application */
            break;
        case PRIVACY_PRIVILEGE_MANAGER_REQUEST_RESULT_DENY_ONCE:
            /* Show a message with explanation */
            break;
    }
}

//for check Privacy-related Permissions
void
app_check_and_request_permission()
{
    ppm_check_result_e result;
    const char *privilege = "http://tizen.org/privilege/location";

    int ret = ppm_check_permission(privilege, &result);

    if (ret == PRIVACY_PRIVILEGE_MANAGER_ERROR_NONE) {
        switch (result) {
            case PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW:
                /* Update UI and start accessing protected functionality */
                break;
            case PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_DENY:
                /* Show a message and terminate the application */
                break;
            case PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ASK:
                ret = ppm_request_permission(privilege, app_request_response_cb, NULL);
                /* Log and handle errors */
                break;
        }
    }
    else {
        /* ret != PRIVACY_PRIVILEGE_MANAGER_ERROR_NONE */
        /* Handle errors */
    }
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */

	setting_on = 0;
	create_base_gui();

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}



int main(int argc, char *argv[]) {
	int ret = 0;

	phone_cnt = 0;


	strcpy(phone_its[0],"추가");
	strcpy(phone_its[1],"");




	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, NULL);

	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
