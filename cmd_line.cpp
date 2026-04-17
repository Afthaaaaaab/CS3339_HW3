#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

#include "cache_class.cpp"

int main(int argc, char* argv[]) {

  if (argc < 4) {
    cout << "Usage: " << endl;
    cout << "./cache num_entries associativity filename" << endl;
    return 0;
  }

  unsigned entries = atoi(argv[1]);
  unsigned assoc = atoi(argv[2]);
  string input_filename = argv[3];

  ifstream input(input_filename);
  ofstream output("cache_sim_output");

  Cache cache(entries, assoc);

  unsigned long addr;

  while (input >> addr) {
    if (cache.hit(output, addr)) {
      output << addr << " : HIT" << endl;
    }
    else {
      output << addr << " : MISS" << endl;
      cache.update(output, addr);
    }
  }

  input.close();
  output.close();

  return 0;
}
