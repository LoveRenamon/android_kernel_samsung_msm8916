/*
 * =================================================================
 *
 *
 *	Description:  samsung display panel file
 *
 *	Author: jb09.kim
 *	Company:  Samsung Electronics
 *
 * ================================================================
 */
/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2012, Samsung Electronics. All rights reserved.

*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#ifndef _SAMSUNG_DSI_SMART_DIMMING_S6E8AA5X01_AMS497HY01_H_
#define _SAMSUNG_DSI_SMART_DIMMING_S6E8AA5X01_AMS497HY01_H_

#include "../ss_dsi_panel_common.h"
#include "../ss_dsi_smart_dimming_common.h"

/*
*	From 4.8 inch model use AID function
*	CASE#1 is used for now.
*/
#define AID_OPERATION

enum {
	GAMMA_CURVE_1P9 = 0,
	GAMMA_CURVE_2P15,
	GAMMA_CURVE_2P0,
	GAMMA_CURVE_2P2,
};

#define REV_A	0x02
#define REV_B	0x02
#define REV_C	0x03
#define REV_E	0x03

#define LUMINANCE_MAX 62
#define GAMMA_SET_MAX 33
#define BIT_SHIFT 22
/*
	it means BIT_SHIFT is 22.  pow(2,BIT_SHIFT) is 4194304.
	BIT_SHIFT is used for right bit shfit
*/
#define BIT_SHFIT_MUL 4194304

#define GRAY_SCALE_MAX 256

/* 5.8 * 4194304 */
#define VREG0_REF_5P8 24326963
/* 5.6 * 4194304 */
#define VREG0_REF_5P6 23488102

/*V0,V3,V11,V23,V35,V51,V87,V151,V203,V255*/
#define ARRAY_MAX 11

/* PANEL DEPENDENT THINGS */
#define MIN_CANDELA	5

/*
*	ID 0x20
*/
#define V255_300CD_R_MSB_20 0x01
#define V255_300CD_R_LSB_20 0x00

#define V255_300CD_G_MSB_20 0x01
#define V255_300CD_G_LSB_20 0x00

#define V255_300CD_B_MSB_20 0x01
#define V255_300CD_B_LSB_20 0x00

#define V203_300CD_R_20 0x80
#define V203_300CD_G_20 0x80
#define V203_300CD_B_20 0x80

#define V151_300CD_R_20 0x80
#define V151_300CD_G_20 0x80
#define V151_300CD_B_20 0x80

#define V87_300CD_R_20 0x80
#define V87_300CD_G_20 0x80
#define V87_300CD_B_20 0x80

#define V51_300CD_R_20 0x80
#define V51_300CD_G_20 0x80
#define V51_300CD_B_20 0x80

#define V35_300CD_R_20 0x80
#define V35_300CD_G_20 0x80
#define V35_300CD_B_20 0x80

#define V23_300CD_R_20 0x80
#define V23_300CD_G_20 0x80
#define V23_300CD_B_20 0x80

#define V11_300CD_R_20 0x80
#define V11_300CD_G_20 0x80
#define V11_300CD_B_20 0x80

#define V3_300CD_R_20 0x80
#define V3_300CD_G_20 0x80
#define V3_300CD_B_20 0x80

#define VT_300CD_R_20 0x00
#define VT_300CD_G_20 0x00
#define VT_300CD_B_20 0x00

/* PANEL DEPENDENT THINGS END*/

enum {
	V1_INDEX = 0,
	V3_INDEX = 1,
	V11_INDEX = 2,
	V23_INDEX = 3,
	V35_INDEX = 4,
	V51_INDEX = 5,
	V87_INDEX = 6,
	V151_INDEX = 7,
	V203_INDEX = 8,
	V255_INDEX = 9,
};

struct GAMMA_LEVEL {
	int level_0;
	int level_1;
	int level_3;
	int level_11;
	int level_23;
	int level_35;
	int level_51;
	int level_87;
	int level_151;
	int level_203;
	int level_255;
} __packed;

struct RGB_OUTPUT_VOLTARE {
	struct GAMMA_LEVEL R_VOLTAGE;
	struct GAMMA_LEVEL G_VOLTAGE;
	struct GAMMA_LEVEL B_VOLTAGE;
} __packed;

struct GRAY_VOLTAGE {
	/*
		This voltage value use 14bit right shit
		it means voltage is divied by 16384.
	*/
	int R_Gray;
	int G_Gray;
	int B_Gray;
} __packed;

struct GRAY_SCALE {
	struct GRAY_VOLTAGE TABLE[GRAY_SCALE_MAX];
	struct GRAY_VOLTAGE VT_TABLE;
} __packed;

/*V0,V1,V3,V11,V23,V35,V51,V87,V151,V203,V255*/

struct MTP_SET {
	char OFFSET_255_MSB;
	char OFFSET_255_LSB;
	char OFFSET_203;
	char OFFSET_151;
	char OFFSET_87;
	char OFFSET_51;
	char OFFSET_35;
	char OFFSET_23;
	char OFFSET_11;
	char OFFSET_3;
	char OFFSET_1;
} __packed;

struct MTP_OFFSET {
	struct MTP_SET R_OFFSET;
	struct MTP_SET G_OFFSET;
	struct MTP_SET B_OFFSET;
} __packed;

struct illuminance_table {
	int lux;
	char gamma_setting[GAMMA_SET_MAX];
} __packed;

struct SMART_DIM {
	struct MTP_OFFSET MTP_ORIGN;

	struct MTP_OFFSET MTP;
	struct RGB_OUTPUT_VOLTARE RGB_OUTPUT;
	struct GRAY_SCALE GRAY;

	/* Because of AID funtion, below members are added*/
	int lux_table_max;
	int *plux_table;
	struct illuminance_table gen_table[LUMINANCE_MAX];

	int brightness_level;
	int ldi_revision;
	int vregout_voltage;
} __packed;

#define AOR_DIM_BASE_CD	115

#define CANDELA_MAX_TABLE 61
#define RGB_COMPENSATION 24

static int candela_table[][2] = {
	{5, 0,},
	{6, 1,},
	{7, 2,},
	{8, 3,},
	{9, 4,},
	{10, 5,},
	{11, 6,},
	{12, 7,},
	{13, 8,},
	{14, 9,},
	{15, 10,},
	{16, 11,},
	{17, 12,},
	{19, 13,},
	{20, 14,},
	{21, 15,},
	{22, 16,},
	{24, 17,},
	{25, 18,},
	{27, 19,},
	{29, 20,},
	{30, 21,},
	{32, 22,},
	{34, 23,},
	{37, 24,},
	{39, 25,},
	{41, 26,},
	{44, 27,},
	{47, 28,},
	{50, 29,},
	{53, 30,},
	{56, 31,},
	{60, 32,},
	{64, 33,},
	{68, 34,},
	{72, 35,},
	{77, 36,},
	{82, 37,},
	{87, 38,},
	{93, 39,},
	{98, 40,},
	{105, 41,},
	{111, 42,},
	{119, 43,},
	{126, 44,},
	{134, 45,},
	{143, 46,},
	{152, 47,},
	{162, 48,},
	{172, 49,},
	{183, 50,},
	{195, 51,},
	{207, 52,},
	{220, 53,},
	{234, 54,},
	{249, 55,},
	{265, 56,},
	{282, 57,},
	{300, 58,},
	{316, 59,},
	{333, 60,},
	{360, 61,},
};
static int base_luminance_revA[][2] = {
	{5, 112,},
	{6, 112,},
	{7, 112,},
	{8, 112,},
	{9, 112,},
	{10, 112,},
	{11, 112,},
	{12, 112,},
	{13, 112,},
	{14, 112,},
	{15, 112,},
	{16, 112,},
	{17, 112,},
	{19, 112,},
	{20, 112,},
	{21, 112,},
	{22, 112,},
	{24, 112,},
	{25, 112,},
	{27, 112,},
	{29, 112,},
	{30, 112,},
	{32, 112,},
	{34, 112,},
	{37, 112,},
	{39, 112,},
	{41, 112,},
	{44, 112,},
	{47, 112,},
	{50, 112,},
	{53, 112,},
	{56, 112,},
	{60, 112,},
	{64, 112,},
	{68, 112,},
	{72, 119,},
	{77, 126,},
	{82, 134,},
	{87, 142,},
	{93, 151,},
	{98, 160,},
	{105, 172,},
	{111, 180,},
	{119, 192,},
	{126, 201,},
	{134, 213,},
	{143, 226,},
	{152, 239,},
	{162, 253,},
	{172, 253,},
	{183, 253,},
	{195, 253,},
	{207, 253,},
	{220, 253,},
	{234, 253,},
	{249, 253,},
	{265, 271,},
	{282, 286,},
	{300, 304,},
	{316, 318,},
	{333, 335,},
	{360, 360,},
};

static int base_luminance_revC[][2] = {
	{5, 113,},
	{6, 113,},
	{7, 113,},
	{8, 113,},
	{9, 113,},
	{10, 113,},
	{11, 113,},
	{12, 113,},
	{13, 113,},
	{14, 113,},
	{15, 113,},
	{16, 113,},
	{17, 113,},
	{19, 113,},
	{20, 113,},
	{21, 113,},
	{22, 113,},
	{24, 113,},
	{25, 113,},
	{27, 113,},
	{29, 113,},
	{30, 113,},
	{32, 113,},
	{34, 113,},
	{37, 113,},
	{39, 113,},
	{41, 113,},
	{44, 113,},
	{47, 113,},
	{50, 113,},
	{53, 113,},
	{56, 113,},
	{60, 113,},
	{64, 113,},
	{68, 113,},
	{72, 118,},
	{77, 127,},
	{82, 135,},
	{87, 142,},
	{93, 151,},
	{98, 160,},
	{105, 172,},
	{111, 180,},
	{119, 192,},
	{126, 192,},
	{134, 192,},
	{143, 192,},
	{152, 192,},
	{162, 192,},
	{172, 192,},
	{183, 192,},
	{195, 204,},
	{207, 215,},
	{220, 228,},
	{234, 240,},
	{249, 255,},
	{265, 271,},
	{282, 286,},
	{300, 303,},
	{316, 318,},
	{333, 336,},
	{360, 360,},
};

static int base_luminance_revE[][2] = {
	{ 5 ,113 },
	{ 6 ,113 },
	{ 7 ,113 },
	{ 8 ,113 },
	{ 9 ,113 },
	{ 10 ,113 },
	{ 11 ,113 },
	{ 12 ,113 },
	{ 13 ,113 },
	{ 14 ,113 },
	{ 15 ,113 },
	{ 16 ,113 },
	{ 17 ,113 },
	{ 19 ,113 },
	{ 20 ,113 },
	{ 21 ,113 },
	{ 22 ,113 },
	{ 24 ,113 },
	{ 25 ,113 },
	{ 27 ,113 },
	{ 29 ,113 },
	{ 30 ,113 },
	{ 32 ,113 },
	{ 34 ,113 },
	{ 37 ,113 },
	{ 39 ,113 },
	{ 41 ,113 },
	{ 44 ,113 },
	{ 47 ,113 },
	{ 50 ,113 },
	{ 53 ,113 },
	{ 56 ,113 },
	{ 60 ,113 },
	{ 64 ,113 },
	{ 68 ,113 },
	{ 72 ,118 },
	{ 77 ,127 },
	{ 82 ,135 },
	{ 87 ,142 },
	{ 93 ,151 },
	{ 98 ,160 },
	{ 105 ,172 },
	{ 111 ,180 },
	{ 119 ,192 },
	{ 126 ,192 },
	{ 134 ,192 },
	{ 143 ,192 },
	{ 152 ,192 },
	{ 162 ,192 },
	{ 172 ,192 },
	{ 183 ,192 },
	{ 195 ,204 },
	{ 207 ,215 },
	{ 220 ,228 },
	{ 234 ,240 },
	{ 249 ,255 },
	{ 265 ,271 },
	{ 282 ,286 },
	{ 300 ,303 },
	{ 316 ,318 },
	{ 333 ,336 },
	{ 360 ,360 },
};

static int gradation_offset_revA[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 4, 3, 3, 4, 4, 7, 10, 4},
	{0, 2, 4, 3, 3, 3, 6, 9, 4},
	{0, 2, 4, 3, 3, 3, 5, 8, 4},
	{0, 3, 4, 3, 3, 3, 5, 7, 4},
	{0, 3, 4, 3, 3, 3, 5, 7, 4},
	{0, 2, 2, 1, 2, 1, 4, 6, 4},
	{0, 3, 2, 1, 2, 1, 4, 6, 4},
	{0, 2, 2, 1, 2, 1, 3, 5, 4},
	{0, 2, 2, 1, 2, 1, 3, 5, 4},
	{0, 2, 1, 1, 2, 1, 3, 4, 4},
	{0, 2, 2, 1, 2, 1, 3, 4, 4},
	{0, 2, 2, 1, 2, 1, 3, 4, 4},
	{0, 3, 2, 1, 2, 1, 3, 4, 4},
	{0, 3, 2, 1, 2, 1, 3, 4, 4},
	{0, 3, 3, 2, 3, 1, 3, 4, 5},
	{0, 3, 3, 2, 3, 1, 4, 5, 5},
	{0, 3, 3, 2, 3, 2, 4, 6, 6},
	{0, 3, 3, 2, 3, 2, 4, 6, 6},
	{0, 3, 3, 2, 3, 2, 4, 6, 7},
	{0, 3, 3, 2, 3, 2, 4, 6, 7},
	{0, 3, 3, 2, 3, 2, 4, 6, 7},
	{0, 3, 3, 2, 3, 2, 4, 6, 7},
	{0, 3, 3, 2, 3, 2, 4, 5, 7},
	{0, 3, 3, 3, 3, 2, 4, 5, 6},
	{0, 3, 3, 3, 3, 2, 4, 5, 6},
	{0, 3, 3, 3, 3, 2, 4, 5, 6},
	{0, 3, 3, 3, 3, 2, 3, 4, 5},
	{0, 3, 3, 3, 3, 2, 3, 4, 5},
	{0, 3, 3, 3, 3, 2, 3, 4, 5},
	{0, 3, 3, 3, 3, 2, 3, 3, 5},
	{0, 3, 3, 3, 3, 2, 3, 3, 4},
	{0, 3, 3, 3, 3, 2, 3, 3, 4},
	{0, 3, 3, 3, 3, 2, 3, 3, 4},
	{0, 3, 3, 3, 3, 2, 3, 3, 4},
	{0, 3, 3, 3, 3, 2, 3, 3, 4},
	{0, 3, 3, 4, 3, 2, 3, 3, 4},
	{0, 3, 3, 3, 3, 2, 3, 3, 4},
	{0, 3, 3, 4, 3, 2, 3, 2, 4},
	{0, 2, 3, 4, 3, 2, 3, 2, 4},
	{0, 2, 3, 4, 3, 2, 3, 2, 4},
	{0, 3, 3, 4, 3, 2, 3, 2, 4},
	{0, 2, 3, 4, 2, 2, 3, 2, 4},
	{0, 2, 3, 3, 2, 2, 3, 2, 4},
	{0, 2, 3, 3, 3, 2, 3, 2, 4},
	{0, 2, 4, 4, 3, 3, 3, 2, 4},
	{0, 2, 4, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 2, 2, 2, 2, 3},
	{0, 3, 3, 4, 2, 2, 2, 2, 3},
	{0, 3, 3, 4, 2, 2, 2, 2, 3},
	{0, 3, 3, 3, 2, 2, 2, 2, 2},
	{0, 2, 3, 3, 2, 2, 2, 1, 2},
	{0, 2, 3, 3, 2, 2, 2, 1, 2},
	{0, 2, 3, 3, 2, 2, 2, 1, 1},
	{0, 2, 3, 3, 2, 2, 2, 1, 1},
	{0, 1, 3, 3, 2, 2, 2, 1, 1},
	{0, 1, 1, 1, 2, 2, 1, 0, 0},
	{0, 1, 1, 2, 2, 1, 1, 1, 0},
	{0, 0, 2, 2, 1, 1, 1, 0, 0},
	{0, 1, 2, 2, 1, 1, 0, 1, 0},
	{0, 1, 1, 2, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static int gradation_offset_revC[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 3, 2, 2, 3, 3, 7, 9, 5},
	{0, 2, 1, 2, 3, 3, 6, 9, 5},
	{0, 3, 2, 2, 3, 3, 6, 9, 5},
	{0, 3, 2, 1, 2, 3, 5, 8, 5},
	{0, 3, 2, 1, 2, 2, 5, 7, 5},
	{0, 2, 1, 1, 2, 2, 5, 7, 5},
	{0, 2, 1, 1, 1, 2, 4, 7, 5},
	{0, 3, 2, 1, 2, 2, 4, 6, 5},
	{0, 2, 1, 1, 1, 2, 4, 6, 5},
	{0, 3, 2, 1, 2, 2, 4, 5, 5},
	{0, 2, 1, 1, 1, 2, 3, 5, 5},
	{0, 2, 1, 1, 1, 1, 3, 4, 5},
	{0, 3, 2, 1, 1, 1, 3, 4, 5},
	{0, 2, 1, 1, 1, 1, 3, 4, 5},
	{0, 3, 2, 1, 1, 1, 3, 4, 5},
	{0, 3, 2, 1, 1, 1, 3, 4, 5},
	{0, 3, 2, 1, 1, 2, 3, 4, 5},
	{0, 3, 2, 1, 2, 2, 3, 4, 5},
	{0, 3, 2, 2, 2, 2, 4, 5, 5},
	{0, 3, 3, 2, 2, 2, 4, 5, 5},
	{0, 3, 3, 2, 2, 2, 4, 5, 5},
	{0, 3, 3, 2, 2, 2, 4, 5, 5},
	{0, 3, 3, 2, 2, 2, 4, 5, 5},
	{0, 3, 3, 2, 2, 2, 4, 5, 5},
	{0, 3, 3, 2, 2, 2, 4, 4, 5},
	{0, 3, 3, 2, 2, 2, 3, 4, 5},
	{0, 3, 3, 2, 2, 2, 3, 4, 5},
	{0, 3, 3, 2, 2, 2, 3, 4, 4},
	{0, 3, 3, 2, 2, 2, 3, 3, 4},
	{0, 3, 3, 2, 2, 2, 3, 3, 4},
	{0, 3, 3, 2, 2, 2, 2, 3, 4},
	{0, 3, 3, 2, 2, 2, 2, 3, 4},
	{0, 3, 3, 2, 2, 2, 2, 3, 3},
	{0, 3, 3, 2, 2, 2, 2, 3, 3},
	{0, 3, 3, 2, 2, 2, 2, 3, 3},
	{0, 3, 3, 2, 2, 2, 2, 3, 3},
	{0, 3, 3, 2, 2, 2, 2, 2, 3},
	{0, 3, 3, 3, 2, 2, 2, 2, 3},
	{0, 3, 3, 4, 2, 2, 2, 2, 3},
	{0, 3, 3, 4, 2, 2, 2, 2, 3},
	{0, 3, 3, 4, 2, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 3},
	{0, 2, 3, 4, 3, 2, 2, 2, 2},
	{0, 2, 3, 4, 2, 2, 2, 2, 2},
	{0, 2, 3, 3, 2, 2, 2, 2, 2},
	{0, 2, 3, 3, 2, 2, 2, 2, 2},
	{0, 1, 3, 3, 2, 2, 2, 2, 2},
	{0, 1, 3, 3, 2, 2, 2, 2, 2},
	{0, 1, 3, 3, 2, 2, 2, 2, 2},
	{0, 1, 3, 3, 2, 2, 2, 1, 2},
	{0, 1, 3, 3, 2, 2, 2, 1, 2},
	{0, 1, 3, 3, 2, 2, 2, 1, 2},
	{0, 1, 3, 3, 2, 2, 2, 0, 1},
	{0, 1, 2, 2, 2, 2, 1, 0, 1},
	{0, 1, 1, 2, 2, 2, 1, 0, 0},
	{0, 0, 1, 2, 2, 1, 1, 0, 0},
	{0, 0, 1, 1, 2, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static int gradation_offset_revE[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{ 0, 3, 2, 2, 3, 3, 7, 9, 5 },
	{ 0, 2, 1, 2, 3, 3, 6, 9, 5 },
	{ 0, 3, 2, 2, 3, 3, 6, 9, 5 },
	{ 0, 3, 2, 1, 2, 3, 5, 8, 5 },
	{ 0, 3, 2, 1, 2, 2, 5, 7, 5 },
	{ 0, 2, 1, 1, 2, 2, 5, 7, 5 },
	{ 0, 2, 1, 1, 1, 2, 4, 7, 5 },
	{ 0, 3, 2, 1, 2, 2, 4, 6, 5 },
	{ 0, 2, 1, 1, 1, 2, 4, 6, 5 },
	{ 0, 3, 2, 1, 2, 2, 4, 5, 5 },
	{ 0, 2, 1, 1, 1, 2, 3, 5, 5 },
	{ 0, 2, 1, 1, 1, 1, 3, 4, 5 },
	{ 0, 3, 2, 1, 1, 1, 3, 4, 5 },
	{ 0, 2, 1, 1, 1, 1, 3, 4, 5 },
	{ 0, 3, 2, 1, 1, 1, 3, 4, 5 },
	{ 0, 3, 2, 1, 1, 1, 3, 4, 5 },
	{ 0, 3, 2, 1, 1, 2, 3, 4, 5 },
	{ 0, 3, 2, 1, 2, 2, 3, 4, 5 },
	{ 0, 3, 2, 2, 2, 2, 4, 5, 5 },
	{ 0, 3, 3, 2, 2, 2, 4, 5, 5 },
	{ 0, 3, 3, 2, 2, 2, 4, 5, 5 },
	{ 0, 3, 3, 2, 2, 2, 4, 5, 5 },
	{ 0, 3, 3, 2, 2, 2, 4, 5, 5 },
	{ 0, 3, 3, 2, 2, 2, 4, 5, 5 },
	{ 0, 3, 3, 2, 2, 2, 4, 4, 5 },
	{ 0, 3, 3, 2, 2, 2, 3, 4, 5 },
	{ 0, 3, 3, 2, 2, 2, 3, 4, 5 },
	{ 0, 3, 3, 2, 2, 2, 3, 4, 4 },
	{ 0, 3, 3, 2, 2, 2, 3, 3, 4 },
	{ 0, 3, 3, 2, 2, 2, 3, 3, 4 },
	{ 0, 3, 3, 2, 2, 2, 2, 3, 4 },
	{ 0, 3, 3, 2, 2, 2, 2, 3, 4 },
	{ 0, 3, 3, 2, 2, 2, 2, 3, 3 },
	{ 0, 3, 3, 2, 2, 2, 2, 3, 3 },
	{ 0, 3, 3, 2, 2, 2, 2, 3, 3 },
	{ 0, 3, 3, 2, 2, 2, 2, 3, 3 },
	{ 0, 3, 3, 2, 2, 2, 2, 2, 3 },
	{ 0, 3, 3, 3, 2, 2, 2, 2, 3 },
	{ 0, 3, 3, 4, 2, 2, 2, 2, 3 },
	{ 0, 3, 3, 4, 2, 2, 2, 2, 3 },
	{ 0, 3, 3, 4, 2, 2, 2, 2, 3 },
	{ 0, 2, 3, 4, 3, 2, 2, 2, 3 },
	{ 0, 2, 3, 4, 3, 2, 2, 2, 3 },
	{ 0, 2, 3, 4, 3, 2, 2, 2, 3 },
	{ 0, 2, 3, 4, 3, 2, 2, 2, 3 },
	{ 0, 2, 3, 4, 3, 2, 2, 2, 3 },
	{ 0, 2, 3, 4, 3, 2, 2, 2, 2 },
	{ 0, 2, 3, 4, 2, 2, 2, 2, 2 },
	{ 0, 2, 3, 3, 2, 2, 2, 2, 2 },
	{ 0, 2, 3, 3, 2, 2, 2, 2, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 2, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 2, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 2, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 1, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 1, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 1, 2 },
	{ 0, 1, 3, 3, 2, 2, 2, 0, 1 },
	{ 0, 1, 2, 2, 2, 2, 1, 0, 1 },
	{ 0, 1, 1, 2, 2, 2, 1, 0, 0 },
	{ 0, 0, 1, 2, 2, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 2, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

static int rgb_offset_revA[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{0, 0, 1, 0, 0, 1, 0, 0, 1, -2, 0, 0, -5, 0, 3, -3, 1, -1, -10, 2, -3, -13, 2, 1,},
	{0, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -4, 0, 2, -4, 1, -1, -9, 2, -3, -15, 2, 1,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 1, -3, 0, 2, -1, 1, -1, -11, 2, -5, -16, 1, 2,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 1, -3, 0, 1, -3, 1, -2, -9, 2, -4, -15, 2, 1,},
	{0, 0, 1, 0, 0, 1, -2, 0, 1, -1, 0, 0, -2, 0, 3, -3, 1, -3, -10, 2, -4, -15, 2, 0,},
	{0, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 0, -2, 0, 1, -3, 1, -4, -7, 2, -2, -17, 1, 0,},
	{0, 0, 1, 0, 0, 1, -1, 0, 0, -2, 0, 0, -1, 0, 2, -3, 1, -5, -7, 2, -2, -16, 2, 1,},
	{0, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 1, -2, 1, -4, -9, 2, -4, -15, 2, 1,},
	{0, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 1, -2, 1, -4, -8, 2, -4, -15, 2, 2,},
	{0, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 2, -2, 1, -4, -8, 1, -5, -16, 2, 2,},
	{0, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 0, -1, 0, 1, -1, 2, -2, -7, 1, -6, -15, 2, 4,},
	{0, 0, 1, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, 0, 1, -1, 1, -4, -7, 1, -5, -15, 2, 4,},
	{0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 1, -3, -8, 1, -6, -13, 1, 4,},
	{0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 1, 0, 1, -4, -7, 1, -6, -14, 1, 5,},
	{0, 0, 1, -1, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 1, 1, 1, -4, -8, 1, -6, -14, 1, 5,},
	{0, 0, 1, -1, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 1, 1, 1, -4, -6, 1, -7, -13, 1, 2,},
	{0, 0, 1, -1, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 1, 1, 1, -4, -6, 1, -7, -11, 0, 3,},
	{0, 0, 1, -1, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, 1, 1, -4, -5, 1, -7, -11, 0, 2,},
	{0, 0, 1, -1, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, 1, 1, -4, -4, 1, -7, -11, 0, 0,},
	{0, 0, 1, -1, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, 1, 1, -5, -4, 1, -7, -11, 2, 1,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, -5, -5, 1, -7, -9, 2, 0,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, -6, -5, 1, -7, -10, 2, -1,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1, -5, -6, 1, -8, -10, 2, -5,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1, -5, -5, 1, -7, -9, 2, -3,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1, -5, -4, 1, -7, -9, 2, -1,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -5, 1, -7, -7, 2, 0,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -5, 1, -8, -7, 2, 1,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -4, 1, -7, -7, 2, 2,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -4, 0, -7, -7, 2, 2,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -3, 0, -7, -7, 2, 1,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -4, 0, -7, -5, 1, 2,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -4, -4, 0, -8, -4, 1, 4,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -4, -3, 0, -7, -4, 1, 5,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -4, -3, 0, -7, -4, 0, 6,},
	{0, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, -5, -3, 0, -6, -4, 0, 6,},
	{-2, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 2, 2, 0, -4, -4, 0, -7, -4, 0, 6,},
	{-1, 0, 1, -2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 2, 0, -3, -3, 0, -6, -4, 0, 4,},
	{-1, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 2, 0, -5, -3, 0, -6, -4, 0, 4,},
	{0, 0, 1, -1, 0, 0, -1, 0, 1, 1, 0, 1, 0, 0, 2, 2, 0, -3, -3, 0, -7, -4, 0, 4,},
	{-1, 0, 2, -1, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0, 3, 1, 0, -3, -4, 0, -6, -4, 0, 4,},
	{-1, 0, 1, -1, 0, 1, -1, 0, 1, 0, 0, 0, 1, 0, 2, 1, 0, -2, -4, 0, -6, -5, 0, 4,},
	{0, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, 0, -3, -2, 0, -4, -5, 0, 2,},
	{0, 0, 1, 0, 0, 0, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, 0, -2, -2, 0, -4, -4, 0, 2,},
	{0, 0, 1, 0, 0, 0, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, 0, -1, -2, 0, -3, -4, 0, 2,},
	{0, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 1, 2, 0, -2, -1, 0, -2, -3, 0, 1,},
	{0, 0, 1, -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, -1, 0, 0, -3, -3, 0, 2,},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 2, 0, -1, 0, 0, -3, -4, 0, 2,},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, -1, -1, 0, -1, -2, 0, 1,},
	{-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, -1, -2, 0, 2,},
	{-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, -1, -2, 0, 2,},
	{-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0, 3,},
	{-1, 0, 1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0, 5,},
	{-1, 0, 1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0, -1, 0, 0, 5,},
	{-1, 0, 1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0, 5,},
	{-1, 0, 1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0, 5,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};
static int rgb_offset_revC[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{2, 0, 1, 0, 0, 1, -1, 0, 2, -3, 0, 0, -5, 0, 4, -6, 0, -3, -14, 0, -2, 0, 0, 1},
	{2, 0, 1, 0, 0, 1, -1, 0, 1, -2, 0, 0, -4, 0, 4, -6, 0, -3, -13, 0, -4, -3, 0, 1},
	{2, 0, 1, 0, 0, 1, 0, 0, 2, -3, 0, 0, -4, 0, 3, -5, 0, -3, -13, 0, -3, -6, 0, 0},
	{2, 0, 1, 0, 0, 1, 0, 0, 2, -1, 0, 1, -4, 0, 3, -5, 0, -4, -12, 0, -4, -8, 0, 0},
	{2, 0, 1, 0, 0, 1, 0, 0, 2, -1, 0, 1, -3, 0, 3, -5, 0, -5, -10, 0, -2, -10, 0, 1},
	{2, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 1, -4, 0, 2, -4, 0, -3, -8, 0, -2, -12, 0, -1},
	{2, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 1, -3, 0, 2, -4, 0, -3, -9, 0, -3, -13, 0, -1},
	{2, 0, 1, 0, 0, 1, -1, 0, 1, -1, 0, 1, -2, 0, 3, -3, 0, -5, -9, 0, -2, -13, 0, -1},
	{2, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 1, -3, 0, 2, -3, 0, -5, -7, 0, -1, -11, 0, -1},
	{2, 0, 1, 0, 0, 1, 0, 0, 2, -2, 0, 0, -2, 0, 3, -2, 0, -5, -5, 0, -2, -11, 0, -1},
	{2, 0, 1, 0, 0, 1, 0, 0, 1, -2, 0, 0, -2, 0, 3, -1, 0, -4, -7, 0, -3, -11, 0, -2},
	{2, 0, 1, 0, 0, 1, 0, 0, 1, -2, 0, 0, -1, 0, 3, -1, 0, -4, -5, 0, -3, -13, 0, -2},
	{2, 0, 1, 0, 0, 1, 0, 0, 2, -2, 0, 0, -2, 0, 2, -1, 0, -4, -5, 0, -3, -11, 0, 0},
	{2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, -1, 0, -4, -5, 0, -4, -9, 0, 1},
	{2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, -1, 0, -4, -5, 0, -3, -8, 0, 2},
	{2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, 0, 0, -4, -6, 0, -5, -7, 0, 0},
	{2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, 0, 0, -4, -6, 0, -4, -7, 1, -3},
	{2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, 0, 0, -4, -6, 0, -6, -7, 1, -3},
	{2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -3, 0, 1, 0, 0, -5, -5, 0, -5, -9, 0, -4},
	{2, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 0, 0, -5, -3, 0, -5, -9, 0, -5},
	{2, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 0, 0, -5, -3, 0, -5, -9, 0, -5},
	{2, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 0, 0, -6, -4, 0, -5, -9, 0, -7},
	{2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 1, 0, -6, -3, 0, -5, -9, 0, -6},
	{2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -1, 0, 1, 1, 0, -6, -3, 0, -4, -9, 0, -6},
	{2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -1, 0, 1, 1, 0, -6, -2, 0, -4, -9, 0, -7},
	{2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -1, 0, 1, 1, 0, -6, -2, 0, -5, -8, 0, -4},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 2, 0, -6, -1, 0, -4, -8, 0, -3},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 2, 0, -6, -1, 0, -4, -7, 0, -2},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 2, 0, -6, -1, 0, -4, -6, 0, -3},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, -2, 0, -4, -5, 0, -1},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, -1, 0, -4, -5, 0, 0},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, -1, 0, -4, -5, 0, 1},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, 0, 0, -4, -5, 0, 3},
	{2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, 0, 0, -4, -5, 0, 4},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 3, 0, -5, 0, 0, -4, -6, 0, 0},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 2, 0, -4, 0, 0, -4, -5, 0, 0},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 1, 0, -5, 0, 0, -3, -3, 0, 0},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 1, 0, -4, 0, 0, -3, -5, 0, 4},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, -1, 0, 0, 3, 1, 0, -4, 0, 0, -4, -3, 0, 1},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, -1, -1, 0, 2, 3, 0, -4, 0, 0, -4, -3, 0, 0},
	{1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, -1, 0, 0, 2, 3, 0, -3, 0, 0, -4, -3, 0, 0},
	{1, 0, 0, -1, 0, 0, 0, 0, 1, -1, 0, -1, 0, 0, 2, 1, 0, -4, 0, 0, -4, -4, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, -1, 0, 0, 2, 1, 0, -3, 0, 0, -4, -3, 0, -1},
	{0, 0, 0, 1, 0, -1, -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, -3, 1, 0, -1, -2, 0, -1},
	{0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, -1, 0, 0},
	{0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, -1, 0, 0},
	{0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, 0, 0, 1},
	{0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, 1, 0, 1},
	{0, 0, 0, 1, 0, -1, -1, 0, 0, 0, 0, 1, -1, 0, 1, 1, 0, -3, 0, 0, -2, 0, 0, 1},
	{0, 0, 0, 1, 0, -1, -1, 0, 0, 0, 0, 1, -1, 0, 1, 1, 0, -3, 0, 0, -2, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static int rgb_offset_revE[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{ 2, 0, 1, 0, 0, 1, -1, 0, 2, -3, 0, 0, -5, 0, 4, -6, 0, -3, -14, 0, -2, 0, 0, 1 },
	{ 2, 0, 1, 0, 0, 1, -1, 0, 1, -2, 0, 0, -4, 0, 4, -6, 0, -3, -13, 0, -4, -3, 0, 1 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 2, -3, 0, 0, -4, 0, 3, -5, 0, -3, -13, 0, -3, -6, 0, 0 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 2, -1, 0, 1, -4, 0, 3, -5, 0, -4, -12, 0, -4, -8, 0, 0 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 2, -1, 0, 1, -3, 0, 3, -5, 0, -5, -10, 0, -2, -10, 0, 1 },
	{ 2, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 1, -4, 0, 2, -4, 0, -3, -8, 0, -2, -12, 0, -1 },
	{ 2, 0, 1, 0, 0, 1, -1, 0, 1, 0, 0, 1, -3, 0, 2, -4, 0, -3, -9, 0, -3, -13, 0, -1 },
	{ 2, 0, 1, 0, 0, 1, -1, 0, 1, -1, 0, 1, -2, 0, 3, -3, 0, -5, -9, 0, -2, -13, 0, -1 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 1, -3, 0, 2, -3, 0, -5, -7, 0, -1, -11, 0, -1 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 2, -2, 0, 0, -2, 0, 3, -2, 0, -5, -5, 0, -2, -11, 0, -1 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 1, -2, 0, 0, -2, 0, 3, -1, 0, -4, -7, 0, -3, -11, 0, -2 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 1, -2, 0, 0, -1, 0, 3, -1, 0, -4, -5, 0, -3, -13, 0, -2 },
	{ 2, 0, 1, 0, 0, 1, 0, 0, 2, -2, 0, 0, -2, 0, 2, -1, 0, -4, -5, 0, -3, -11, 0, 0 },
	{ 2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, -1, 0, -4, -5, 0, -4, -9, 0, 1 },
	{ 2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, -1, 0, -4, -5, 0, -3, -8, 0, 2 },
	{ 2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, 0, 0, -4, -6, 0, -5, -7, 0, 0 },
	{ 2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, 0, 0, -4, -6, 0, -4, -7, 1, -3 },
	{ 2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -2, 0, 2, 0, 0, -4, -6, 0, -6, -7, 1, -3 },
	{ 2, 0, 1, -1, 0, 0, 0, 0, 2, 0, 0, 1, -3, 0, 1, 0, 0, -5, -5, 0, -5, -9, 0, -4 },
	{ 2, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 0, 0, -5, -3, 0, -5, -9, 0, -5 },
	{ 2, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 0, 0, -5, -3, 0, -5, -9, 0, -5 },
	{ 2, 0, 1, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 0, 0, -6, -4, 0, -5, -9, 0, -7 },
	{ 2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -2, 0, 1, 1, 0, -6, -3, 0, -5, -9, 0, -6 },
	{ 2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -1, 0, 1, 1, 0, -6, -3, 0, -4, -9, 0, -6 },
	{ 2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -1, 0, 1, 1, 0, -6, -2, 0, -4, -9, 0, -7 },
	{ 2, 0, 0, -1, 0, 1, 0, 0, 2, -1, 0, 0, -1, 0, 1, 1, 0, -6, -2, 0, -5, -8, 0, -4 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 2, 0, -6, -1, 0, -4, -8, 0, -3 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 2, 0, -6, -1, 0, -4, -7, 0, -2 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 2, 0, -6, -1, 0, -4, -6, 0, -3 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, -2, 0, -4, -5, 0, -1 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, -1, 0, -4, -5, 0, 0 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, -1, 0, -4, -5, 0, 1 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, 0, 0, -4, -5, 0, 3 },
	{ 2, 0, 0, -1, 0, 1, -1, 0, 2, -1, 0, 0, -1, 0, 1, 3, 0, -5, 0, 0, -4, -5, 0, 4 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 3, 0, -5, 0, 0, -4, -6, 0, 0 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 2, 0, -4, 0, 0, -4, -5, 0, 0 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 1, 0, -5, 0, 0, -3, -3, 0, 0 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, 0, 0, 0, 2, 1, 0, -4, 0, 0, -3, -5, 0, 0 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, -1, 0, 0, 3, 1, 0, -4, 0, 0, -4, -3, 0, 1 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, -1, -1, 0, 2, 3, 0, -4, 0, 0, -4, -3, 0, 0 },
	{ 1, 0, 0, -1, 0, 0, -1, 0, 1, -1, 0, -1, 0, 0, 2, 3, 0, -3, 0, 0, -4, -3, 0, 0 },
	{ 1, 0, 0, -1, 0, 0, 0, 0, 1, -1, 0, -1, 0, 0, 2, 1, 0, -4, 0, 0, -4, -4, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, -1, 0, 0, 2, 1, 0, -3, 0, 0, -4, -3, 0, -1 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, -3, 1, 0, -1, -2, 0, -1 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, -1, 0, 0 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, -1, 0, 0 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, 0, 0, 1 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 0, -3, 1, 0, -1, 1, 0, 1 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 0, 0, 0, 1, -1, 0, 1, 1, 0, -3, 0, 0, -2, 0, 0, 1 },
	{ 0, 0, 0, 1, 0, -1, -1, 0, 0, 0, 0, 1, -1, 0, 1, 1, 0, -3, 0, 0, -2, 0, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
#endif
