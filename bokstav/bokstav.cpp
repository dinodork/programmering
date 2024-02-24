#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Byte = uint8_t;

const Byte INK_BLACK = 0b00000000;
const Byte INK_BLUE = 0b00000001;
const Byte INK_RED = 0b00000010;
const Byte INK_MAGENTA = 0b00000011;
const Byte INK_GREEN = 0b00000100;
const Byte INK_CYAN = 0b00000101;
const Byte INK_YELLOW = 0b00000110;
const Byte INK_WHITE = 0b00000111;

const Byte PAPER_BLACK = 0b00000000;
const Byte PAPER_BLUE = 0b00001000;
const Byte PAPER_RED = 0b00010000;
const Byte PAPER_MAGENTA = 0b00011000;
const Byte PAPER_GREEN = 0b00100000;
const Byte PAPER_CYAN = 0b00101000;
const Byte PAPER_YELLOW = 0b00110000;
const Byte PAPER_WHITE = 0b00111000;

const Byte BRIGHT = 0b01000000;
const Byte FLASH = 0b10000000;

using namespace std;

using Bitmap_mem = uint8_t[32 * 24 * 8];
using Attr_mem = uint8_t[24][32];
using Character = uint8_t[8];

Character char_a = {
    0b00000000, //
    0b00000000, //
    0b00111000, //
    0b00000100, //
    0b00111100, //
    0b01000100, //
    0b00111100, //
    0b00000000,
};

/*
  How to translate the screen memory address:

  Byte         15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0
               --+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
  Co-ordinate   0| 0| 0|Y7|Y6|Y2|Y1|Y0|Y5|Y4|Y3|X4|X3|X2|X1|X0
*/

constexpr uint16_t get_byte_address(size_t x_byte, size_t y_pixel) {
  uint16_t byte_offset = x_byte;
  byte_offset |= (y_pixel & 0x07) << 8;
  byte_offset |= (y_pixel & 0X38) << 2;
  byte_offset |= (y_pixel & 0xC0) << 5;
  return byte_offset;
}

void plot(size_t x, size_t y, Bitmap_mem &mem) {
  auto address = get_byte_address(x >> 3, y);
  mem[address] |= 0x80 >> (x & 7);
}

void draw(size_t x_start, size_t y_start, size_t x_end, size_t y_end,
          Bitmap_mem &mem) {
  if (x_end == x_start)
    for (auto y = y_start; y < y_end; ++y)
      plot(x_start, y, mem);
  if (y_end == y_start)
    for (auto x = x_start; x < x_end; ++x)
      plot(x, y_start, mem);
}

void writeLetterBig(const Character &c, size_t col, size_t row,
                    Bitmap_mem &bitmap_mem, Attr_mem &attr_mem) {

  for (int i = 0; i < sizeof(c); ++i) {
    for (auto j = 0; j < 8; ++j) {
      auto icol = col + j;
      auto irow = row + i;
      auto mask = 0x80 >> j;
      uint16_t pixel_row = c[i] << j;
      if (pixel_row & 0x80) {
        attr_mem[irow][icol] = BRIGHT | PAPER_MAGENTA;
        if (i == 0 || !(c[i - 1] & mask)) { // nothing above
          auto x = icol * 8, y = irow * 8 - 1;
          draw(x, y, x + 8, y, bitmap_mem);
        }
        if (!(pixel_row & 0x40)) { // nothing to the right
          auto x = (icol + 1) * 8, y = irow * 8;
          draw(x, y, x, y + 8, bitmap_mem);
        }
        if (i == sizeof(c) || !(c[i + 1] & mask)) { // nothing below
          auto x = icol * 8, y = (irow + 1) * 8;
          draw(x, y, x + 8, y, bitmap_mem);
        }
        if (!(pixel_row & 0x100)) { // nothing_to_the_left
          auto x = icol * 8 - 1, y = irow * 8;
          draw(x, y, x, y + 8, bitmap_mem);
        }
      }
    }
  }
}

int main() {
  ofstream myfile;
  myfile.open("bokstav.scr");

  Bitmap_mem bitmap_mem;
  Attr_mem attr_mem;

  for (auto &b : bitmap_mem)
    b = 0x00;

  for (auto &row : attr_mem)
    for (auto &col : row)
      col = BRIGHT | PAPER_BLACK | INK_WHITE;

  writeLetterBig(char_a, 10, 10, bitmap_mem, attr_mem);

  // Write to file
  for (auto b : bitmap_mem)
    myfile << b;

  for (auto &row : attr_mem)
    for (auto &col : row)
      myfile << col;

  myfile.close();
}
