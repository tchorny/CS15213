/* 
 * CS:APP Data Lab 
 * 
 * Aleksandr Chornyi
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int minus_x = ~x + 0x01;                                                                                             
  int mask = (x >> 31);                                                                                                
  return (minus_x & mask) + (x & (~mask));
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* Compute ((x | -x) & 0x80000000) >> 31 and
     add 1 to the result */
  return (((0x80 << 24) & (x | (~x + 0x01))) >> 31) + 0x01;
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /* mask1 = 0x55555555, mask2 = 0x33333333, mask3 = 0x0f0f0f0f
     mask4 = 0x00ff00ff, mask5 = 0x0000ffff*/
  int mask1 = 0x55 | (0x55 << 8);
  int mask2 = 0x33 | (0x33 << 8);
  int mask3 = 0x0f | (0x0f << 8);
  int mask4 = 0xff | (0xff << 16);
  int mask5 = 0xff | (0xff << 8);
  mask1 = mask1 | (mask1 << 16);
  mask2 = mask2 | (mask2 << 16);
  mask3 = mask3 | (mask3 << 16);
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask3) + ((x >> 4) & mask3);
  x = (x & mask4) + ((x >> 8) & mask4);
  return (x & mask5) + ((x >> 16) & mask5);
}
/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
  int mask = x >> 31;
  x = (mask & (x + ~(~0x00 << n))) | (~mask & x);
  return x >> n;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int mask = x >> 31;
  /* x = x >> (n - 1) */
  x = x >> (~0x00 + n);
  return !(x ^ mask);
}
/* 
 * floatInt2Float - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatInt2Float(int x) {
  unsigned sign, exp = 158, frac, masked_x;
	int mask = 0x80000000, msb;

  /* x == 0 and x == TMin - special cases */
  if(x == 0) return 0u;
  if(x == 0x80000000) return 0xCF000000u;
  sign = x & 0x80000000u;
 
  /* convert x to abs(x) */
  x = (x < 0) ? -x : x;

  while(!(x & mask)) {
		mask = mask >> 1;
		exp--;
  }

	msb = exp - 150;
  masked_x = (x & ~mask);
	exp = exp << 23;

  if(masked_x >= 0x3FFFFFC0) {

    exp += 0x00800000;
    frac = 0u;

  } else if(msb > 0) {

		frac = masked_x >> msb;
		masked_x = masked_x << (32 - msb);
    if((masked_x & 0x80000000) && ((frac & 1) || (masked_x << 1))) frac++;

  } else frac = masked_x << (-msb);

  return (sign | exp | frac);
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  if(((uf & 0x7f800000) == 0x7f800000) && ((uf & 0x007fffff) != 0x00)) return uf;
  return uf + 0x80000000;
}
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	// if Special value
	if((uf & 0x7F800000) == 0x7F800000) return uf;

	// if Normalized value
	if(uf & 0x7F800000) {
    uf += 0x00800000;
		if((uf & 0x7F800000) == 0x7F800000) uf = uf & 0xFF800000;
		return uf;

	//else Denormalized value
	} else if(uf & 0x00400000) return ( ( (uf & 0x007FFFFF) << 1 ) | (uf & 0xFF800000) );

	else return ( ( (uf & 0x003FFFFF) << 1 ) | (uf & 0x80000000) );
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return (x >> (n << 3)) & 0xff;
}
/*
 * intLog2 - return floor(log base 2 of x), where x > 0
 *   Example: intLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int intLog2(int x) {
  /* bitCount masks */
  int mask1 = 0x55 | (0x55 << 8);
  int mask2 = 0x33 | (0x33 << 8);
  int mask3 = 0x0f | (0x0f << 8);
  int mask4 = 0xff | (0xff << 16);
  int mask5 = 0xff | (0xff << 8);
  mask1 = mask1 | (mask1 << 16);
  mask2 = mask2 | (mask2 << 16);
  mask3 = mask3 | (mask3 << 16);
  /* get all ones after msb */
  x = x >> 1;
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  /* count number of ones */
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask3) + ((x >> 4) & mask3);
  x = (x & mask4) + ((x >> 8) & mask4);
  return (x & mask5) + ((x >> 16) & mask5);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int xor = x ^ y;
  int xor2 = 0;
  xor = xor | (xor >> 1);
  xor = xor | (xor >> 2);
  xor = xor | (xor >> 4);
  xor = xor | (xor >> 8);
  xor = xor | (xor >> 16);
  xor2 = ~(xor >> 1) & xor;
 return !!((!xor) | (xor2 & y) | (xor & x & (0x80 << 24)));
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x) {
  return !(x >> 31) ^ !x;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  return (x >> n) & (~(((0x80 << 24) >> n) << 1));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 0x01;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x80 << 24;
}
