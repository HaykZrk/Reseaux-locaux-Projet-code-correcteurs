#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t set_nth_bit(int n, uint16_t m);
uint16_t get_nth_bit(int n, uint16_t m);
uint16_t chg_nth_bit(int n, uint16_t m);
void print_word(int k, uint16_t m);

uint16_t encode_G(uint16_t m);
uint8_t cnt_bits(uint16_t m);
uint8_t dist_code_G();

int main(int argc, char* argv[]) {
  uint16_t m = 0b0011100100000000;
  print_word(16, m);
  print_word(16, encode_G(m));
  return 0;
}

uint16_t set_nth_bit(int n, uint16_t m) {
  return m | (0b1000000000000000 >> n);
}

uint16_t get_nth_bit(int n, uint16_t m) {
  return (m >> (15 - n)) & 0b1;
}

uint16_t chg_nth_bit(int n, uint16_t m) {
  return m ^ 0b1000000000000000 >> n;
}

void print_word(int k, uint16_t m) {
  printf("0b");
  for (int i = 0; i < k; i++) printf("%d", get_nth_bit(i,m));
  printf("\n");
}

uint16_t encode_G(uint16_t m) {
  uint16_t bits[8];
  for (size_t i = 0; i < 8; i++) bits[i] = get_nth_bit(i,m);
  
  uint16_t c8 = bits[2] ^ bits[3] ^ bits[6] ^ bits[7];
  uint16_t c9 = bits[0] ^ bits[2] ^ bits[4] ^ bits[6];
  uint16_t c10 = bits[0] ^ bits[1] ^ bits[3] ^ bits[5] ^ bits[7];
  uint16_t c11 = bits[0] ^ bits[1] ^ bits[3] ^ bits[4] ^ bits[7];
  uint16_t c12 = bits[1] ^ bits[3] ^ bits[4] ^ bits[5] ^ bits[6] ^ bits[7];
  uint16_t c13 = bits[0] ^ bits[3] ^ bits[4] ^ bits[5];
  uint16_t c14 = bits[0] ^ bits[1] ^ bits[4] ^ bits[5] ^ bits[6];
  uint16_t c15 = bits[1] ^ bits[2] ^ bits[5] ^ bits[6] ^ bits[7];
  return m | c8<<7 | c9<<6 | c10<<5 | c11<<4 | c12<<3 | c13<<2 | c14<<1 | c15;
}

uint8_t cnt_bits(uint16_t m) {
  uint8_t total = 0b0;
  for (size_t i = 0; i < 16; i++) total += get_nth_bit(i,m);
  return total;
}

// TODO : refaire sans coder G directement
uint8_t dist_code_G(){
  uint16_t G[8]=
  {
    0b1000000001110110,
    0b0100000000111011,
    0b0010000011000001,
    0b0001000010111100,
    0b0000100001011110,
    0b0000010000101111,
    0b0000001011001011,
    0b0000000110111001
  };
  uint8_t distTemp;
  uint16_t min_dist=16; 
  for(int i = 0 ; i<8 ; i++)
  {
    for(int j = i+1 ; j < 8; j++)
    {
      distTemp=0;
      for(int k=0; k<16 ; k++) {
        if(get_nth_bit(k,G[i])!= get_nth_bit(k,G[j])) distTemp++;
      }
      if(min_dist>distTemp) min_dist=distTemp;
    }
  }
  return min_dist;
}