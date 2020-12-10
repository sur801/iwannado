/*
 * tts.c
 *
 *  Created on: Nov 26, 2019
 *      Author: test
 */
#include "texttospeech.h"
#include "data.h"

/* Callback for whenever TTS changes state */
void state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data)
{
	if (TTS_STATE_READY == current && TTS_STATE_CREATED == previous) {
		int ret;
		const char* text = (char *)user_data;

		const char* language = "ko_KR"; // Language
		int voice_type = TTS_VOICE_TYPE_FEMALE; // Voice type
		int speed = TTS_SPEED_AUTO; // Read speed
		int utt_id; // Utterance ID for the requested text

		ret = tts_add_text(tts, text, language, voice_type, speed, &utt_id);

		ret = tts_play(tts);
		dlog_print(DLOG_INFO, LOG_TAG, "Added text and started playing");
	}
}

/* Function which handles all the work of setting up and starting TTS */
void enter_tts(tts_h *tts, int index, char *style) {
	char *text = get_text_to_speech(index, style);

	int ret;
	ret = tts_create(tts);
	ret = tts_set_state_changed_cb(*tts, state_changed_cb, text);
	ret = tts_prepare(*tts);
}

void exit_tts(tts_h *tts) {
	int ret;
	ret = tts_stop(*tts);
	ret = tts_unprepare(*tts);
	ret = tts_unset_utterance_completed_cb(*tts);
	ret = tts_unset_state_changed_cb(*tts);
	ret = tts_destroy(*tts);
	dlog_print(DLOG_INFO, LOG_TAG, "exit_tts completed");
}

const char *get_text_to_speech(int index, void* user_data) {
	char *style = (char *)user_data;

	if (style == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "style is NULL.");
		return NULL;
	}

	if (!strcmp(style, "core")) {
		return data_get_core_text((void *)index, NULL, "elm.text");
	} else if (!strcmp(style, "class")) {
		return data_get_class_text((void *)index, NULL, "elm.text");
	} else if (!strcmp(style, "mart")) {
		return data_get_mart_text((void *)index, NULL, "elm.text");
	} else if (!strcmp(style, "food")) {
		return data_get_food_text((void *)index, NULL, "elm.text");
	} else if (!strcmp(style, "hospital")) {
		return data_get_hospital_text((void *)index, NULL, "elm.text");
	} else if (!strcmp(style, "pe")) {
		return data_get_pe_text((void *)index, NULL, "elm.text");
	}

	return NULL;
}

