#include "board.h"
#include "dictionary.h"
#include <assert.h>

#define BOGGLE_MAX_1D_IDX BOGGLE_ROWS * BOGGLE_COLS

static int twod_to_oned(int i, int j) {
  int idx = (i * BOGGLE_ROWS) + j;
  assert(idx < 16);
  return idx;
}

typedef struct qdata {
  int i, j;
  std::map<int, bool> used;
  std::string word;

  qdata(int i_, int j_, std::string w, const std::map<int, bool> &u) {
    i = i_; j = j_; word = w; used = u;
    used[twod_to_oned(i, j)] = true;
  }

  qdata(int i_, int j_, std::string w) {
    i = i_; j = j_; word = w;
    used[twod_to_oned(i, j)] = true;
  } 

  qdata() {
    i = -1; j = -1; word = "";
  }
} qdata;

static inline void queue_insert(int i, int j, const std::string &top_word,
                                std::vector<qdata> &queue,
                                const qdata &top,
                                const std::vector<std::vector<std::string> > &board) {

  if(top.used.end() == top.used.find(twod_to_oned(i, j))) {
    queue.push_back(qdata(i, j, top_word + board.at(i).at(j), top.used));
  }
}

void do_bfs(int in_i, int in_j,
            const std::vector<std::vector<std::string> > &board,
            const Dictionary &d,
            std::map<std::string, bool> &out) {

  std::vector<qdata> queue;

  int i = in_i, j = in_j;

  std::string word = board.at(i).at(j);
  queue.push_back(qdata(i, j, word));

  while(queue.size() > 0) {
    qdata top = queue[0]; 
    std::string top_word = top.word;
    bool explore = true;
    if(top_word.length() > 2) {
      int result = d.Find(top_word);
      if(1 == result) {
        out[top_word] = true;
      }
      if(0 == result) {
        explore = false;
      }
    }
    if(true == explore) {
      const int cur_i = top.i;
      const int cur_j = top.j;
      // explore current row to left
      if(cur_j > 0) {
        j = cur_j - 1;
        i = cur_i;
        queue_insert(i, j, top_word, queue, top, board);
      }
      // explore current row to right
      if(cur_j < (BOGGLE_COLS - 1)) {
        j = cur_j + 1;
        i = cur_i;
        queue_insert(i, j, top_word, queue, top, board);
      }
      // Explore previous row
      if(cur_i > 0) {
        i = cur_i - 1;
        j = cur_j;
        queue_insert(i, j, top_word, queue, top, board);

        // explore 1 above + 1 right
        if(cur_j < (BOGGLE_COLS - 1)) {
          j = cur_j + 1;
          queue_insert(i, j, top_word, queue, top, board);
        }
        // explore 1 above - 1 left
        if(cur_j > 0) {
          j = cur_j - 1;
          queue_insert(i, j, top_word, queue, top, board);
        }
      }
      // Explore next row
      if(cur_i < (BOGGLE_ROWS - 1)) {
        i = cur_i + 1;
        j = cur_j;
        queue_insert(i, j, top_word, queue, top, board);

        // explore 1 below + 1 right
        if(cur_j < (BOGGLE_COLS - 1)) {
          j = cur_j + 1;
          queue_insert(i, j, top_word, queue, top, board);
        }

        // explore 1 below - 1 left
        if(cur_j > 0) {
          j = cur_j - 1;
          queue_insert(i, j, top_word, queue, top, board);
        }
      }
    }
    queue.erase(queue.begin());
  }
}

void find_words(const Board &b, const Dictionary &d, std::map<std::string, bool> &out) {

  std::vector<std::vector<std::string> > board = b.Get();
  for(int i = 0; i < BOGGLE_ROWS; i++) {
    for(int j = 0; j < BOGGLE_COLS; j++) {
      do_bfs(i, j, board, d, out);
    }
  }
}
