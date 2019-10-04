/*
Copyright 2017 MechMerlin <mechmerlin@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "matrix.h"
#include "util.h"
#include "print.h"
#include "debug.h"

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(uint8_t col);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void backlight_init_ports(void)
{
  // DDRD  |=  0b11010000;
  // PORTD &= ~0b01010000;
  // PORTD |=  0b10000000;
  // DDRB  |=  0b00011111;
  // PORTB &= ~0b00001110;
  // PORTB |=  0b00010001;
  // DDRE  |=  0b01000000;
  // PORTE &= ~0b01000000;
}

void matrix_init(void) {
  backlight_init_ports();
  unselect_cols();
  init_rows();

  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);

    uint8_t rows = read_rows(col);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        if (debouncing) {
            dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
        }
        debouncing = DEBOUNCE;
      }
    }
    unselect_cols();
  }

  if (debouncing) {
    if (--debouncing) {
      _delay_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }

  matrix_scan_quantum();
  return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

/* Row pin configuration
 * row: 0    1    2    3    4   
 * pin: PD0  PD1  PD2  PD3  PD5  
 *
 * Caps Lock uses its own pin PE2
 */
static void init_rows(void) {
    DDRD  &= ~0b00101111;
    PORTD &= ~0b00101111;

    DDRE  &= ~0b00000100;
    PORTE |=  0b00000100;
}

static uint8_t read_rows(uint8_t col) {

    return (PIND&(1<<0) ? (1<<0) : 0) |
            (PIND&(1<<1) ? (1<<1) : 0) |
            (PIND&(1<<2) ? (1<<2) : 0) |
            (PIND&(1<<3) ? (1<<3) : 0) |
            (PIND&(1<<5) ? (1<<4) : 0) |
            (col==0 ? ((PINE&(1<<2) ? 0 : (1<<2))) : 0);
    
}

uint8_t read_fwkey(void)
{
  return PINE&(1<<2) ? 0 : (1<<2);
}

/* Columns 0 - 7
 * These columns use 1 74HC237D 3 to 8 bit demultiplexers.
 * col / pin:    PC6 (E2)  PF0 (A0)  PF1 (A1) PC7 (A2)  
 * 0: (Y0)         1         0        0        0    
 * 1: (Y1)         1         1        0        0    
 * 2: (Y2)         1         0        1        0    
 * 3: (Y3)         1         1        1        0    
 * 4: (Y4)         1         0        0        1    
 * 5: (Y5)         1         1        0        1   
 * 6: (Y6)         1         0        1        1    
 * 7: (Y7)         1         1        1        1     
 *
 * * Columns 8 - 14
 * These columns are driven by pins on the atmega32u4 mcu. 
 * 8:  E6
 * 9:  B0
 * 10: B7
 * 11: D4
 * 12: D6
 * 13: D7
 * 14: B3
 */
static void unselect_cols(void) {
  // Columns tied to 74HC237D for 74HC237D pins A0, A1, A2. 
  DDRC  |=  0b11000000;
  PORTC &= ~0b11000000;

  DDRF  |=  0b00000011;
  PORTF &= ~0b00000011;

  // Columns driven by atmega32u4 mcu. 
  DDRB  |=  0b10001001;
  PORTB &= ~0b10001001;

  DDRD  |=  0b11010000;
  PORTD &= ~0b11010000;

  DDRE  |=  0b01000000;
  PORTE &= ~0b01000000;
}

static void select_col(uint8_t col) {
 
   switch (col) {
        case 0:
            PORTC |= 0b01000000;
            break;
        case 1:
            PORTC |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 2:
            PORTC |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 3:
            PORTC |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 4:
            PORTC |= 0b11000000;
            break;
        case 5:
            PORTC |= 0b11000000;
            PORTF |= 0b00000001;
            break;
        case 6:
            PORTC |= 0b11000000;
            PORTF |= 0b00000010;
            break;
        case 7:
            PORTC |= 0b11000000;
            PORTF |= 0b00000011;
            break;
        case 8:
            PORTE |= 0b01000000;
            break;
        case 9:
            PORTB |= 0b00000001;
            break;
        case 10:
            PORTB |= 0b10000000;
            break;
        case 11:
            PORTD |= 0b00010000;
            break;
        case 12:
            PORTD |= 0b01000000;
            break;
        case 13:
            PORTD |= 0b10000000;
            break;
        case 14:
            PORTB |= 0b00001000;
            break;
            
    }
}
