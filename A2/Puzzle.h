// [CHANGED: ksum, 11/1/2014]
// old: #include <random>
// [CHANGED: ksum, 11/1/2014]
// old: #include <list>
// [CHANGED: ksum, 11/1/2014]
// old: #include <unordered_map>
#include <set>

#ifndef PUZZLE_H
#define PUZZLE_H

class Puzzle {
public:
    // int key is 1D index of (row, col)
    // [CHANGED: ksum, 11/1/2014]
    // old: std::unordered_map<int, bool> reachable_cells;
    // old: std::unordered_map<int, bool> reaching_cells;
    std::set<int> reachable_cells;
    std::set<int> reaching_cells;

    int nRows;
    int nColumns;
    int minVal;
    int maxVal;
    int** puzzle;

    Puzzle(int rows, int cols, int min, int max, int test_puzzle);
    void PrintPuzzle();
    int EvaluatePuzzle(bool print);
    bool RandModifyPuzzle(int prior_value, bool must_imrove);
    bool BruteModifyPuzzle(int original_puzzle_value);
    bool AnnealingModifyPuzzle(int original_puzzle_value, float temp);
    void CopyToPuzzle(Puzzle* new_puzzle);
    void CopyFromPuzzle(const Puzzle& new_puzzle);
    void RandomFill();

private:
    void ForwardSearchBFS(int best_sol_len[1]);
    void BackwardSearchBFS();
    bool UniqueShortest();
    int TwoDimToOneDim(int row, int col);
    int NumBlackHoles();
    int NumWhiteHoles();
    void PrintReachable();
    void PrintNonReachable();
    void PrintReaching();
    void PrintNonReaching();
    int NumForcedForwardMoves();
    int NumForcedBackwardMoves();
    int PuzzleScore(int shortest_sol_length, bool unq_shortest, int num_w,
                    int num_bl, int num_f, int num_bck);
};

#endif
