/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */

#pragma once

void seven_segment_setup();
void seven_segment_write_int(int integer);
void seven_segment_write_number(int number);
void seven_segment_clear();
