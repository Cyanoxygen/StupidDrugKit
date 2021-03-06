#include <avr/pgmspace.h>
/*   字体索引 
 *  0 吃  1 当   2 定   3 放   4 该   5 盒   6 间   7 啦 
 *  8 录  9 秒  10 能  11 前  12 设  13 时  14 药  15 已
 * 16 音 17 正  18 智  19 在  20 ！  21 开  22 关
 */
static const unsigned char FontRes[37][33] PROGMEM =
{
  {
    0x00, 0x80, 0x00, 0x80, 0x79, 0x00, 0x49, 0xFE, 0x4A, 0x00, 0x4C, 0x00, 0x49, 0xF8, 0x48, 0x08,
    0x48, 0x10, 0x48, 0x60, 0x78, 0x80, 0x49, 0x00, 0x02, 0x02, 0x02, 0x02, 0x01, 0xFE, 0x00, 0x00,
  }, //0 吃
  {
    0x01, 0x00, 0x21, 0x08, 0x11, 0x08, 0x09, 0x10, 0x09, 0x20, 0x01, 0x00, 0x7F, 0xF8, 0x00, 0x08,
    0x00, 0x08, 0x00, 0x08, 0x3F, 0xF8, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x7F, 0xF8, 0x00, 0x08,
  },//1 当
  {
    0x02, 0x00, 0x01, 0x00, 0x7F, 0xFE, 0x40, 0x02, 0x80, 0x04, 0x00, 0x00, 0x3F, 0xF8, 0x01, 0x00,
    0x01, 0x00, 0x11, 0x00, 0x11, 0xF8, 0x11, 0x00, 0x11, 0x00, 0x29, 0x00, 0x47, 0xFE, 0x80, 0x00,
  },//2 定
  {
    0x20, 0x40, 0x10, 0x40, 0x00, 0x40, 0xFE, 0x80, 0x20, 0xFE, 0x21, 0x08, 0x3E, 0x88, 0x24, 0x88,
    0x24, 0x88, 0x24, 0x50, 0x24, 0x50, 0x24, 0x20, 0x44, 0x50, 0x54, 0x88, 0x89, 0x04, 0x02, 0x02,
  },//3 放
  {
    0x00, 0x80, 0x40, 0x40, 0x2F, 0xFE, 0x20, 0x80, 0x01, 0x10, 0x01, 0x10, 0xE2, 0x24, 0x27, 0xE4,
    0x20, 0x48, 0x20, 0x88, 0x21, 0x10, 0x2A, 0x20, 0x34, 0x50, 0x20, 0x88, 0x03, 0x04, 0x0C, 0x04,
  },//4 该
  {
    0x01, 0x00, 0x02, 0x80, 0x0C, 0x60, 0x30, 0x18, 0xCF, 0xE6, 0x00, 0x00, 0x1F, 0xF0, 0x10, 0x10,
    0x1F, 0xF0, 0x00, 0x00, 0x3F, 0xF8, 0x24, 0x48, 0x24, 0x48, 0x24, 0x48, 0xFF, 0xFE, 0x00, 0x00,
  },//5  盒
  {
    0x20, 0x00, 0x13, 0xFC, 0x10, 0x04, 0x40, 0x04, 0x47, 0xC4, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
    0x47, 0xC4, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x47, 0xC4, 0x40, 0x04, 0x40, 0x14, 0x40, 0x08,
  },//6 间
  {
    0x01, 0x20, 0x01, 0x10, 0x71, 0x10, 0x51, 0x7E, 0x57, 0x80, 0x51, 0x04, 0x51, 0x44, 0x51, 0xC4,
    0x51, 0x24, 0x53, 0x24, 0x75, 0x28, 0x51, 0x28, 0x01, 0x08, 0x01, 0x10, 0x05, 0x7E, 0x02, 0x00,
  },//7 啦
  {
    0x00, 0x00, 0x3F, 0xF0, 0x00, 0x10, 0x00, 0x10, 0x1F, 0xF0, 0x00, 0x10, 0x00, 0x10, 0xFF, 0xFE,
    0x01, 0x00, 0x21, 0x08, 0x11, 0x90, 0x05, 0x60, 0x09, 0x20, 0x31, 0x18, 0xC5, 0x06, 0x02, 0x00,
  },//8 录
  {
    0x08, 0x20, 0x1C, 0x20, 0xF0, 0x20, 0x10, 0xA8, 0x10, 0xA4, 0xFC, 0xA2, 0x11, 0x22, 0x31, 0x20,
    0x3A, 0x24, 0x54, 0x24, 0x54, 0x28, 0x90, 0x08, 0x10, 0x10, 0x10, 0x20, 0x10, 0xC0, 0x13, 0x00,
  },//9 秒
  {
    0x10, 0x40, 0x24, 0x44, 0x42, 0x48, 0xFF, 0x70, 0x01, 0x40, 0x00, 0x42, 0x7E, 0x42, 0x42, 0x3E,
    0x42, 0x00, 0x7E, 0x44, 0x42, 0x48, 0x42, 0x70, 0x7E, 0x40, 0x42, 0x42, 0x4A, 0x42, 0x44, 0x3E,
  },//10 能
  {
    0x10, 0x10, 0x08, 0x10, 0x08, 0x20, 0xFF, 0xFE, 0x00, 0x00, 0x3E, 0x08, 0x22, 0x48, 0x22, 0x48,
    0x3E, 0x48, 0x22, 0x48, 0x22, 0x48, 0x3E, 0x48, 0x22, 0x08, 0x22, 0x08, 0x2A, 0x28, 0x24, 0x10,
  },//11 前
  {
    0x00, 0x00, 0x21, 0xF0, 0x11, 0x10, 0x11, 0x10, 0x01, 0x10, 0x02, 0x0E, 0xF4, 0x00, 0x13, 0xF8,
    0x11, 0x08, 0x11, 0x10, 0x10, 0x90, 0x14, 0xA0, 0x18, 0x40, 0x10, 0xA0, 0x03, 0x18, 0x0C, 0x06,
  },//12 设
  {
    0x00, 0x08, 0x00, 0x08, 0x7C, 0x08, 0x44, 0x08, 0x45, 0xFE, 0x44, 0x08, 0x44, 0x08, 0x7C, 0x08,
    0x44, 0x88, 0x44, 0x48, 0x44, 0x48, 0x44, 0x08, 0x7C, 0x08, 0x44, 0x08, 0x00, 0x28, 0x00, 0x10,
  },//13 时
  {
    0x04, 0x40, 0x04, 0x40, 0xFF, 0xFE, 0x04, 0x40, 0x10, 0x80, 0x10, 0x80, 0x20, 0xFC, 0x45, 0x04,
    0xFA, 0x04, 0x10, 0x84, 0x20, 0x44, 0xFC, 0x44, 0x00, 0x04, 0x1C, 0x04, 0xE0, 0x28, 0x40, 0x10,
  },//14 药
  {
    0x00, 0x00, 0x3F, 0xF0, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x20, 0x10, 0x20, 0x10, 0x3F, 0xF0,
    0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x1F, 0xFC, 0x00, 0x00,
  },//15 已
  {
    0x02, 0x00, 0x01, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x08, 0x20, 0x04, 0x40, 0xFF, 0xFE, 0x00, 0x00,
    0x1F, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x1F, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x1F, 0xF0, 0x10, 0x10,
  },//16 音
  {
    0x00, 0x00, 0x7F, 0xFC, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x11, 0x00, 0x11, 0xF8,
    0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0xFF, 0xFE, 0x00, 0x00,
  },//17  正
  {
    0x20, 0x00, 0x3E, 0x7C, 0x48, 0x44, 0x08, 0x44, 0xFF, 0x44, 0x14, 0x44, 0x22, 0x7C, 0x40, 0x00,
    0x1F, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x1F, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x1F, 0xF0, 0x10, 0x10,
  },//18 智
  {
    0x02, 0x00, 0x02, 0x00, 0x04, 0x00, 0xFF, 0xFE, 0x08, 0x00, 0x08, 0x40, 0x10, 0x40, 0x30, 0x40,
    0x57, 0xFC, 0x90, 0x40, 0x10, 0x40, 0x10, 0x40, 0x10, 0x40, 0x10, 0x40, 0x1F, 0xFE, 0x10, 0x00,
  },//19 在
  {
    0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
    0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
  },//20 ！
  {
    0x00, 0x00, 0x7F, 0xFC, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0xFF, 0xFE,
    0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x10, 0x20, 0x10, 0x20, 0x20, 0x20, 0x40, 0x20,
  },//21 开
  {
    0x10, 0x10, 0x08, 0x10, 0x08, 0x20, 0x00, 0x00, 0x3F, 0xF8, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
    0xFF, 0xFE, 0x01, 0x00, 0x02, 0x80, 0x02, 0x80, 0x04, 0x40, 0x08, 0x20, 0x30, 0x18, 0xC0, 0x06,
  },//22 关
  {
    0x00,0x00,0x7F,0xFC,0x00,0x80,0x00,0x80,0x01,0x00,0x01,0x00,0x03,0x40,0x05,0x20,
    0x09,0x10,0x11,0x08,0x21,0x04,0x41,0x04,0x81,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
  }, //23 不
  {
    0x01,0x00,0x01,0x00,0x02,0x00,0x04,0x40,0x08,0x20,0x10,0x10,0x3F,0xF8,0x04,0x48,
    0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x40,0x08,0x42,0x10,0x42,0x20,0x42,0xC0,0x3E,
  }, //24,允
  {
    0x00,0x80,0x20,0x80,0x10,0x80,0x11,0xFC,0x01,0x20,0x02,0x20,0xF0,0x20,0x10,0x20,
    0x13,0xFE,0x10,0x20,0x10,0x20,0x10,0x20,0x14,0x20,0x18,0x20,0x10,0x20,0x00,0x20,

  }, // 25,许
  /*--  文字:  已 26 --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
{0x00,0x00,0x3F,0xF0,0x00,0x10,0x00,0x10,0x00,0x10,0x20,0x10,0x20,0x10,0x3F,0xF0,
0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x04,0x20,0x04,0x20,0x04,0x1F,0xFC,0x00,0x00,
},
/*--  文字:  停 27 --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
{0x10,0x80,0x10,0x40,0x17,0xFC,0x20,0x00,0x23,0xF8,0x62,0x08,0x63,0xF8,0xA0,0x00,
0x2F,0xFE,0x28,0x02,0x23,0xF8,0x20,0x40,0x20,0x40,0x20,0x40,0x21,0x40,0x20,0x80,
},{
/*--  文字:  止 28 --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0x00,0x11,0xF8,0x11,0x00,
0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xFE,0x00,0x00,
},{
/*--  文字:  提 29 --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x00,0x11,0xFC,0x11,0x04,0x11,0x04,0xFD,0xFC,0x11,0x04,0x11,0x04,0x15,0xFC,
0x18,0x00,0x33,0xFE,0xD0,0x20,0x11,0x20,0x11,0x3C,0x11,0x20,0x52,0xA0,0x24,0x7E,
},{
/*--  文字:  醒 30 --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFE,0x7C,0x28,0x44,0x28,0x7C,0xFE,0x44,0xAA,0x7C,0xAA,0x10,0xAA,0x50,
0xAE,0x7C,0xC2,0x90,0x82,0x10,0xFE,0x7C,0x82,0x10,0x82,0x10,0xFE,0xFE,0x82,0x00,
},
{
  0x04,0x00,0x04,0x00,0xFF,0xFE,0x08,0x00,0x08,0x00,0x13,0xF8,0x10,0x10,0x30,0x20,
  0x50,0x40,0x97,0xFE,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x11,0x40,0x10,0x80
}, //31
{
  0x10,0x20,0x10,0x20,0x18,0xFA,0x24,0x24,0x24,0x28,0x61,0xFE,0x60,0x20,0xBC,0x40,
  0x24,0xFC,0x25,0x44,0x26,0x44,0x24,0x7C,0x25,0x44,0x26,0x44,0x24,0x7C,0x20,0x44
},  //32
{
  0x20,0x00,0x10,0x00,0x01,0xFC,0xFC,0x44,0x08,0x44,0x10,0x44,0x10,0x44,0x34,0x44,
  0x58,0x44,0x94,0x44,0x14,0x44,0x10,0x84,0x10,0x84,0x11,0x04,0x12,0x28,0x14,0x10
}, //33
{
  0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x40,0xFC,0x48,0x24,0x84,0x25,0xFE,0x24,0x82,
  0x24,0x00,0x48,0xFC,0x28,0x84,0x10,0x84,0x28,0x84,0x44,0x84,0x80,0xFC,0x00,0x84
}, //34
{
  0x08,0x80,0x08,0x80,0x08,0x84,0x10,0x88,0x10,0x90,0x30,0xA0,0x30,0xC0,0x50,0x80,
  0x91,0x80,0x12,0x80,0x14,0x80,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x7E,0x10,0x00
}, //35
{
  0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
  0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00
}//36
};
static const unsigned int Pitches[9] PROGMEM = { 659,523,587,392,0,392,587,659,523};
static const byte ScreenRes[10][6] PROGMEM  = {
  {18,10,14,5},{1,11,13,6},//“智能药盒”，“当前时间”
  {17,19,8,16,9},{17,19,3,16},//“正在录音 秒”，“正在放音”
  {13,6,19,12,2}, // "时间已设定"
  {17,19,21,5},{17,19,22,5}, // "正在开盒"，“正在关盒”
  {4,0,14,7,20} // “该吃药啦！”
};

