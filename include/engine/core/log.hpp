#pragma once

#include <iostream>

#define Loge(fmt, ...) printf("[ERROR][%s - %s][%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define Logw(fmt, ...) printf("[WARN][%s - %s][%d]: " fmt "\n",  __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define Logi(fmt, ...) printf("[INFO][%s - %s][%d]: " fmt "\n",  __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define Logd(fmt, ...) printf("[DEBUG][%s - %s][%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define Logt(fmt, ...) printf("[TRACE][%s - %s][%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)

// log once
#define Loge1(fmt, ...) do { static bool logged = false; if (!logged) { printf("[ONCE][ERROR][%s - %s][%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); logged = true;} } while(0)
#define Logw1(fmt, ...) do { static bool logged = false; if (!logged) { printf("[ONCE][WARN][%s - %s][%d]: " fmt "\n",  __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); logged = true;} } while(0)
#define Logi1(fmt, ...) do { static bool logged = false; if (!logged) { printf("[ONCE][INFO][%s - %s][%d]: " fmt "\n",  __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); logged = true;} } while(0)
#define Logd1(fmt, ...) do { static bool logged = false; if (!logged) { printf("[ONCE][DEBUG][%s - %s][%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); logged = true;} } while(0)
#define Logt1(fmt, ...) do { static bool logged = false; if (!logged) { printf("[ONCE][TRACE][%s - %s][%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); logged = true;} } while(0)
