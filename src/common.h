#pragma once

#include <QTextCodec>

extern QTextCodec *g_textcodec;

#define Utf8Str(src) g_textcodec->toUnicode(src).toUtf8().data()

#define tee3_avd_server "3tee.cn"
#define tee3_app_key "F89EB5C71E494850A061CC0C5F42C177"
#define tee3_secret_key "DDDF7445961C4D27A7DCE106001BBB4F"

#define tee3_local_server "192.168.1.200:8080"
//#define tee3_local_server "192.168.1.241:8080"
#define tee3_local_app_key "demo_access"
#define tee3_local_secret_key "demo_secret"

enum Protocol
{
	PTL_TCP,
	PTL_UDP
};
