#pragma once

#include "quantum.h"

#define ___ KC_NO

// K7D is not Enter
// K7D is not Up Arrow
// K1C is not [

#define LAYOUT( \
            K50, K51, K52, K53, K54, K55, K56,    K57, K58, K59, K5A, K5B, K5C, K6A, K7A, K6C,  \
  K61, K71, K40, K41, K42, K43, K44, K45, K46,    K47, K48, K49, K4A, K4B, K4C,       K4D, K69, \
  K62, K72, K30, K31, K32, K33, K34, K35,         K17, K18, K19, K1A, K1B, K1C, K1D, K0D, K79, \
  K63, K73, K20, K21, K22, K23, K24, K25,         K27, K28, K29, K2A, K2B, K2C,       K7D, K6B, \
  K64, K74, K10, K11, K12, K13, K14, K15,      K37, K38, K39, K3A, K3B,       K3D, K0C, K7B, \
  K65, K75, K00, K01, K02, K03, K04,           K6D,           K0A, K0B, K07, K77, K68, K78   \
){ \
  { K00,    K01,    K02,    K03,    K04,    ___,  ___,  K07,    ___,    ___,    K0A,   K0B,   K0C,   ___ }, \
  { K10,    K11,    K12,    K13,    K14,    K15,  ___,  K17,    K18,    K19,    K1A,   K1B,   ___,   K1D }, \
  { K20,    K21,    K22,    K23,    K24,    K25,  ___,  K27,    K28,    K29,    K2A,   K2B,   K2C,   ___ }, \
  { K30,    K31,    K32,    K33,    K34,    K35,  ___,  K37,    K38,    K39,    K3A,   K3B,   ___,   K3D }, \
  { K40,    K41,    K42,    K43,    K44,    K45,  K46,  K47,    K48,    K49,    K4A,   K4B,   K4C,   K4D }, \
  { K50,    K51,    K52,    K53,    K54,    K55,  K56,  K57,    K58,    K59,    K5A,   K5B,   K5C,   ___ }, \
  { ___,    K61,    K62,    K63,    K64,    K65,  ___,  ___,    K68,    K69,    K6A,   K6B,   K6C,   K6D }, \
  { ___,    K71,    K72,    K73,    K74,    K75,  ___,  K77,    K78,    K79,    K7A,   K7B,   ___,   K7D }  \
}

#define LAYOUT_iso( \
            K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K68, K78,  \
  K74, K64, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C,       K69, K79, \
  K73, K63, K30, K31, K32, K33, K34, K35,      K37, K38, K39, K3A, K3B, K3C, K3D,       K7A, \
  K72, K62, K20, K21, K22, K23, K24, K25,      K27, K28, K29, K2A, K2B, K2C, K2D, K6B, K7B,  \
  K71, K61, K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B,       K1D, K6C, K7C, \
  K70, K60, K00, K01, K02, K03, K04,           K07,           K0A, K0B, K0C, K0D, K6D, K7D   \
){ \
  { K00,    K01,    K02,    K03,    K04,    ___,  ___,  K07,  ___,  ___,    K0A,   K0B,   K0C,   K0D }, \
  { K10,    K11,    K12,    K13,    K14,    K15,  K16,  K17,  K18,  K19,    K1A,   K1B,   ___,   K1D }, \
  { K20,    K21,    K22,    K23,    K24,    K25,  ___,  K27,  K28,  K29,    K2A,   K2B,   K2C,   K2D }, \
  { K30,    K31,    K32,    K33,    K34,    K35,  ___,  K37,  K38,  K39,    K3A,   K3B,   K3C,   K3D }, \
  { K40,    K41,    K42,    K43,    K44,    K45,  K46,  K47,  K48,  K49,    K4A,   K4B,   K4C,   ___ }, \
  { K50,    K51,    K52,    K53,    K54,    K55,  K56,  K57,  K58,  K59,    K5A,   K5B,   K5C,   K5D }, \
  { K60,    K61,    K62,    K63,    K64,    ___,  ___,  ___,  K68,  K69,    ___,   K6B,   K6C,   K6D }, \
  { K70,    K71,    K72,    K73,    K74,    ___,  ___,  ___,  K78,  K79,    K7A,   K7B,   K7C,   K7D }  \
}

#define NUMLOCK_LED_PIN D0
#define CAPSLOCK_LED_PIN D1
#define SCROLLLOCK_LED_PIN D6
