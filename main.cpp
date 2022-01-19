#include "board.h"
#include "dictionary.h"

void find_words(const Board &b, const Dictionary &d, std::map<std::string, bool> &o);

// Unnecessary double check that every word found is in the dictionary.
static void validate(const std::map<std::string, bool> &res, const Dictionary &d) {
  
  for(const auto &it : res) {
    if(d.Get().end() == d.Get().find(it.first)) {
      std::cout << "Failed to find: " << it.first << std::endl;
      assert(0);
    }  
  }
}

// Sample main.
int main() {

  Board b(true);
  Dictionary d("words.txt");
  std::cout << "Starting .."  << std::endl;

  std::map<std::string, bool> res;
  find_words(b, d, res);

  //validate(res, d);

  for(const auto &it : res) {
    std::cout << it.first << std::endl;
  }

  std::cout << "Total unique words "  << res.size() << std::endl;
  b.Print();
}
