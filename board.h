#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>

#define BOGGLE_NUM_DIE 16
#define BOGGLE_ROWS 4
#define BOGGLE_COLS 4

/* Dice:

   0: R, I, F, O, B, X
   1: I, F, E, H, E, Y
   2: D, E, N, O, W, S
   3: U, T, O, K, N, D
   4: H, M, S, R, A, O
   5: L, U, P, E, T, S
   6: A, C, I, T, O, A
   7: Y, L, G, K, U, E
   8: Qu, B, M, J, O, A
   9: E, H, I, S, P, N
  10: V, E, T, I, G, N
  11: B, A, L, I, Y, T
  12: E, Z, A, V, N, D
  13: R, A, L, E, S, C
  14: U, W, I, L, R, G
  15: P, A, C, E, M, D
*/
class Board {

  public:

    // Known board with a lot of words.
    // Testing purposes.
    Board(bool f) {
      std::vector<std::string> row1 = { "d", "s", "l", "r" };
      std::vector<std::string> row2 = { "e", "t", "a", "i" };
      std::vector<std::string> row3 = { "p", "r", "n", "t" };
      std::vector<std::string> row4 = { "u", "d", "e", "s" };
      board_.push_back(row1);
      board_.push_back(row2);
      board_.push_back(row3);
      board_.push_back(row4);
    }

    // Main constructor. Randomized board generator.
    Board() {
      srand(time(NULL));
      std::string die[16];
      die[0] = roll("rifobx");
      die[1] = roll("ifehey");
      die[2] = roll("denows");
      die[3] = roll("utoknd");
      die[4] = roll("hmsrao");
      die[5] = roll("lupets");
      die[6] = roll("acitoa");
      die[7] = roll("ylgkue");
      die[8] = roll("qbmjoa");
      if("q" == die[8]) die[8] = "qu";
      die[9] = roll("ehispn");
      die[10] = roll("vetign");
      die[11] = roll("baliyt");
      die[12] = roll("ezavnd");
      die[13] = roll("ralesc");
      die[14] = roll("uwilrg");
      die[15] = roll("pacemd");

      shuffle(die);

      int die_cnt = 0;
      for(int i = 0; i < BOGGLE_ROWS; i++) {
        std::vector<std::string> row;
        for(int j = 0; j < BOGGLE_COLS; j++) {
          row.push_back(die[die_cnt++]);
        }
        board_.push_back(row);
      }
    }

    void Print() const {
      for(int i = 0; i < BOGGLE_ROWS; i++) {
        std::vector<std::string> row = board_[i];
        for(int j = 0; j < BOGGLE_COLS; j++) {
          std::cout << row[j] << " ";
        }
        std::cout << std::endl;
      }
    }

    std::vector<std::vector<std::string> > Get() const {
      return board_;
    }

  private:

    void shuffle(std::string *die) {
      for(int i = 0; i < BOGGLE_NUM_DIE; i++) {
        int swap_idx = rand() % BOGGLE_NUM_DIE;
        std::string tmp = die[i];
        die[i] = die[swap_idx];
        die[swap_idx] = tmp;
      }
    }

    char roll(const std::string &die) {
      return die[rand() % 6];
    }
    std::vector<std::vector<std::string>> board_;
};
