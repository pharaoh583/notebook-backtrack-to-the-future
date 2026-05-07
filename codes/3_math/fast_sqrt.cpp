float rsqrt(float number){ //calcula 1/sqrt(n)
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = * ( long * ) &y; //evil floating bit trick
  i = 0x5f3759df - (i>>1); //What the fuck?
  y = * ( float *) &i;
  y = y * (threehalfs - (x2 * y * y)); //metodo de Newton 
  y = y * (threehalfs - (x2 * y * y)); //si 
  return y;
}
