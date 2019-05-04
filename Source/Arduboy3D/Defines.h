#pragma once

#if _WIN32
#include <stdint.h>
#include <string.h>
#define PROGMEM
#define PSTR
#define pgm_read_byte(x) (*((uint8_t*)x))
#define pgm_read_word(x) (*((uint16_t*)x))
#define pgm_read_ptr(x) (*((uintptr_t*)x))
#define strlen_P(x) strlen(x)
#else
#include <avr/pgmspace.h>
//#define pgm_read_ptr pgm_read_word
#endif

#ifdef _WIN32
constexpr int DISPLAY_WIDTH { 128 };
constexpr int DISPLAY_HEIGHT { 64 };
#else
constexpr int DISPLAY_WIDTH { 128 };
constexpr int DISPLAY_HEIGHT { 64 };
#endif

constexpr unsigned char TARGET_FRAMERATE { 30 };

constexpr unsigned char INPUT_LEFT { 1 << 0 };
constexpr unsigned char INPUT_RIGHT { 1 << 1 };
constexpr unsigned char INPUT_UP { 1 << 2 };
constexpr unsigned char INPUT_DOWN { 1 << 3 };
constexpr unsigned char INPUT_A { 1 << 4 };
constexpr unsigned char INPUT_B { 1 << 5 };

constexpr unsigned char COLOUR_WHITE { 1 };
constexpr unsigned char COLOUR_BLACK { 0 };

constexpr unsigned int FIXED_ANGLE_MAX { 256 };

constexpr int CAMERA_SCALE { 1 };
constexpr int CLIP_PLANE { 32 };
constexpr int CLIP_ANGLE { 32 };
constexpr int NEAR_PLANE_MULTIPLIER { 130 };
constexpr int NEAR_PLANE { (DISPLAY_WIDTH * NEAR_PLANE_MULTIPLIER / 256) };
constexpr int HORIZON { (DISPLAY_HEIGHT / 2) };
constexpr int MAP_SIZE { 8 };
constexpr int CELL_SIZE { 256 };
constexpr int PARTICLES_PER_SYSTEM { 8 };
constexpr int BASE_SPRITE_SIZE { 16 };
constexpr int MAX_SPRITE_SIZE { (DISPLAY_HEIGHT / 2) };
constexpr int MIN_TEXTURE_DISTANCE { 4 };

constexpr int TURN_SPEED { 3 };