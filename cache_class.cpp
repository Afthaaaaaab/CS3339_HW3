#include<iostream>
#include<fstream>

using namespace std;

class Entry {
public:
  Entry() {
    valid = false;
    tag = 0;
    ref = 0;
  }

  ~Entry() {}

  void display(ofstream& outfile) {
    outfile << valid << " " << tag << endl;
  }

  void set_tag(int _tag) { tag = _tag; }
  int get_tag() { return tag; }

  void set_valid(bool _valid) { valid = _valid; }
  bool get_valid() { return valid; }

  void set_ref(int _ref) { ref = _ref; }
  int get_ref() { return ref; }

private:
  bool valid;
  unsigned tag;
  int ref;
};

class Cache {
public:
  Cache(int n, int a) {
    assoc = a;
    num_entries = n;
    num_sets = num_entries / assoc;

    entries = new Entry*[assoc];
    for (int i = 0; i < assoc; i++)
      entries[i] = new Entry[num_sets];
  }

  ~Cache() {
    for (int i = 0; i < assoc; i++)
      delete[] entries[i];
    delete[] entries;
  }

  int get_index(unsigned long addr) {
    return addr % num_sets;
  }

  int get_tag(unsigned long addr) {
    return addr / num_sets;
  }

  bool hit(ofstream& outfile, unsigned long addr) {
    int index = get_index(addr);
    int tag = get_tag(addr);

    for (int way = 0; way < assoc; way++) {
      if (entries[way][index].get_valid() &&
          entries[way][index].get_tag() == tag)
        return true;
    }

    return false;
  }

  void update(ofstream& outfile, unsigned long addr) {
    int index = get_index(addr);
    int tag = get_tag(addr);

    for (int way = 0; way < assoc; way++) {
      if (!entries[way][index].get_valid()) {
        entries[way][index].set_valid(true);
        entries[way][index].set_tag(tag);
        return;
      }
    }

    entries[0][index].set_tag(tag);
  }

private:
  int assoc;
  unsigned num_entries;
  int num_sets;
  Entry **entries;
};
