#include<string>
#include<map>
#include<iostream>
#include<fstream>
#include<assert.h>

class Dictionary {

  public:
    // returns: 1 if found
    //          -1 if partial found
    //          0 if nothing (no partial) 
    int Find(std::string word) const {

      // Found word
      if(dict_.end() != dict_.find(word)) {
        return 1;
      }

      int len = word.length();
      for(const auto &it : dict_) {
        std::string sub = it.first.substr(0, len);

        // Found prefix
        if(sub == word) {
          return -1;
        }
      }
      return 0;
    }

    Dictionary(const std::string file) {
      std::ifstream myfile;
      myfile.open(file);
      if(myfile.is_open()) {
        std::string word;
        while(std::getline(myfile, word)) {
          for(int i = 0; i < word.length(); i++) {
            word[i] = std::tolower(word[i]);
          }
          dict_[word] = true;
        }
      }
      else {
        std::cout << "Failed to open file: " << file << std::endl;
        assert(0);
      }
      myfile.close();
    }

    void Print() const {
      for(const auto &it : dict_) {
        std::cout << it.first << std::endl;
      }
    }

    std::map<std::string, bool> Get() const {
      return dict_;
    }

  private:
    std::map<std::string, bool> dict_;
};
