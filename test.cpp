struct Shoe {
  int size;
  bool is_tied;
};

void shoe_init(Shoe* s, int x) {
    s->size = x;
    s->is_tied = false;
}

int main() {
  Shoe shoe;

  shoe_init(&shoe, 10);
}