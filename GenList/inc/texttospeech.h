/*
 * tts.h
 *
 *  Created on: Nov 26, 2019
 *      Author: test
 */

#ifndef __texttospeech_H__
#define __texttospeech_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <tts.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "texttospeech"

#if !defined(PACKAGE)
#define PACKAGE "org.example.texttospeech"
#endif

void enter_tts(tts_h *tts, int index, char *style);
void exit_tts(tts_h *tts);
const char *get_text_to_speech(int index, void* user_data);

#endif /* __texttospeech_H__ */



