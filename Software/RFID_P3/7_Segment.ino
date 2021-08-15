void Seg_begin() {
  tm1637.init();
  tm1637.set(bright * 2 + 1);
}

int left_rotate(int a) {
  int b = 0;
  for (int i = 0; i < 8; i++) {
    b = (b | (a & 1)) << 1;
    a = a >> 1;
  }
  return b >> 2;
}

void setrow(int d, int e, char f) {
  int data[4] = {3, 0, 1, 2};
  tm1637.name(data[e], left_rotate(f));
}

void setdigit(int d, int e, int f, bool g) {
  int data[4] = {3, 0, 1, 2};
  tm1637.display(data[e], f, g);
}
