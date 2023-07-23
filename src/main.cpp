#include "atomic_block.hpp"
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <thread>
#include <vector>


void run(int N){
  int x = 0;
  std::vector<std::thread> v;
  for(int i = 0; i < N; ++i){
    v.emplace_back([&](){
        atomic_block {
          for(int i = 0; i < N; ++i) x += 2;
        };
    });
  }

  for(auto& ti : v) ti.join();

  printf("x = %d\n", x);
  assert(x == N*N*2);
}

int main (int argc, char** argv) {

  if (argc < 2) {
    printf("Usage: %s <NUM>\n", argv[0]);
  }
  else {
    int num = atoi(argv[1]);
    run(num);
  }
  return 0;
}
