#include "Puzzle.h"
#include <iostream>
#include <set>
#include <sys/time.h>

// [ADDED: ksum, 11/1/2014]
#include <vector>
#include "CustomTuple.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define unsolvable_score -9999999

Puzzle::Puzzle(int rows, int cols, int min, int max, int test_puzzle) {
    nRows = rows;
    nColumns = cols;
    minVal = min;
    maxVal = max;

    puzzle = new int*[nRows];
    for(int i = 0; i < nRows; i++)
        puzzle[i] = new int[nColumns];

    if (test_puzzle == 1) {
        std::cout << "Generating test puzzle from pdf" << std::endl;
        puzzle[0][0] = 3;
        puzzle[0][1] = 2;
        puzzle[0][2] = 1;
        puzzle[0][3] = 4;
        puzzle[0][4] = 1;
        puzzle[1][0] = 3;
        puzzle[1][1] = 2;
        puzzle[1][2] = 1;
        puzzle[1][3] = 3;
        puzzle[1][4] = 3;
        puzzle[2][0] = 3;
        puzzle[2][1] = 3;
        puzzle[2][2] = 2;
        puzzle[2][3] = 1;
        puzzle[2][4] = 4;
        puzzle[3][0] = 3;
        puzzle[3][1] = 1;
        puzzle[3][2] = 2;
        puzzle[3][3] = 3;
        puzzle[3][4] = 3;
        puzzle[4][0] = 1;
        puzzle[4][1] = 4;
        puzzle[4][2] = 4;
        puzzle[4][3] = 3;
        puzzle[4][4] = 0;
        std::cout << "Finished generating test puzzle" << std::endl;
    }
    else if (test_puzzle == 2) {
        std::cout << "Generating 5x5 sample solution puzzle" << std::endl;
        puzzle[0][0] = 3;
        puzzle[0][1] = 2;
        puzzle[0][2] = 2;
        puzzle[0][3] = 2;
        puzzle[0][4] = 1;
        puzzle[1][0] = 1;
        puzzle[1][1] = 2;
        puzzle[1][2] = 1;
        puzzle[1][3] = 3;
        puzzle[1][4] = 1;
        puzzle[2][0] = 1;
        puzzle[2][1] = 2;
        puzzle[2][2] = 1;
        puzzle[2][3] = 3;
        puzzle[2][4] = 1;
        puzzle[3][0] = 3;
        puzzle[3][1] = 2;
        puzzle[3][2] = 1;
        puzzle[3][3] = 3;
        puzzle[3][4] = 1;
        puzzle[4][0] = 2;
        puzzle[4][1] = 4;
        puzzle[4][2] = 1;
        puzzle[4][3] = 3;
        puzzle[4][4] = 0;
        std::cout << "Finished generating test puzzle" << std::endl;
    }
    else if (test_puzzle == 3) {
        std::cout << "Generating 10x10 sample solution puzzle" << std::endl;
        puzzle[0][0] = 2;
        puzzle[0][1] = 5;
        puzzle[0][2] = 6;
        puzzle[0][3] = 5;
        puzzle[0][4] = 4;
        puzzle[0][5] = 2;
        puzzle[0][6] = 6;
        puzzle[0][7] = 2;
        puzzle[0][8] = 2;
        puzzle[0][9] = 6;

        puzzle[1][0] = 1;
        puzzle[1][1] = 1;
        puzzle[1][2] = 3;
        puzzle[1][3] = 1;
        puzzle[1][4] = 2;
        puzzle[1][5] = 2;
        puzzle[1][6] = 2;
        puzzle[1][7] = 7;
        puzzle[1][8] = 1;
        puzzle[1][9] = 3;

        puzzle[2][0] = 8;
        puzzle[2][1] = 7;
        puzzle[2][2] = 4;
        puzzle[2][3] = 6;
        puzzle[2][4] = 2;
        puzzle[2][5] = 2;
        puzzle[2][6] = 2;
        puzzle[2][7] = 7;
        puzzle[2][8] = 9;
        puzzle[2][9] = 5;

        puzzle[3][0] = 5;
        puzzle[3][1] = 5;
        puzzle[3][2] = 7;
        puzzle[3][3] = 6;
        puzzle[3][4] = 3;
        puzzle[3][5] = 4;
        puzzle[3][6] = 5;
        puzzle[3][7] = 3;
        puzzle[3][8] = 9;
        puzzle[3][9] = 9;

        puzzle[4][0] = 1;
        puzzle[4][1] = 4;
        puzzle[4][2] = 4;
        puzzle[4][3] = 2;
        puzzle[4][4] = 8;
        puzzle[4][5] = 7;
        puzzle[4][6] = 2;
        puzzle[4][7] = 4;
        puzzle[4][8] = 6;
        puzzle[4][9] = 1;

        puzzle[5][0] = 2;
        puzzle[5][1] = 1;
        puzzle[5][2] = 2;
        puzzle[5][3] = 5;
        puzzle[5][4] = 8;
        puzzle[5][5] = 3;
        puzzle[5][6] = 8;
        puzzle[5][7] = 4;
        puzzle[5][8] = 3;
        puzzle[5][9] = 4;

        puzzle[6][0] = 2;
        puzzle[6][1] = 3;
        puzzle[6][2] = 6;
        puzzle[6][3] = 2;
        puzzle[6][4] = 2;
        puzzle[6][5] = 8;
        puzzle[6][6] = 4;
        puzzle[6][7] = 1;
        puzzle[6][8] = 6;
        puzzle[6][9] = 6;

        puzzle[7][0] = 1;
        puzzle[7][1] = 9;
        puzzle[7][2] = 4;
        puzzle[7][3] = 4;
        puzzle[7][4] = 2;
        puzzle[7][5] = 3;
        puzzle[7][6] = 2;
        puzzle[7][7] = 2;
        puzzle[7][8] = 7;
        puzzle[7][9] = 1;

        puzzle[8][0] = 6;
        puzzle[8][1] = 1;
        puzzle[8][2] = 6;
        puzzle[8][3] = 5;
        puzzle[8][4] = 1;
        puzzle[8][5] = 4;
        puzzle[8][6] = 5;
        puzzle[8][7] = 5;
        puzzle[8][8] = 8;
        puzzle[8][9] = 5;

        puzzle[9][0] = 4;
        puzzle[9][1] = 7;
        puzzle[9][2] = 6;
        puzzle[9][3] = 3;
        puzzle[9][4] = 4;
        puzzle[9][5] = 8;
        puzzle[9][6] = 4;
        puzzle[9][7] = 5;
        puzzle[9][8] = 2;
        puzzle[9][9] = 0;

        std::cout << "Finished generating test puzzle" << std::endl;
    }
    else {
        RandomFill();
    }
}

// Neatly print the puzzle
void Puzzle::PrintPuzzle() {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            std::cout << puzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Evaluates the Puzzle object
int Puzzle::EvaluatePuzzle(bool print) {
    // clear persistent data from prior evaluation
    reachable_cells.clear();
    reaching_cells.clear();

    int best_sol_length[1];
    best_sol_length[0] = 0;
    // std::cout << "best_sol_length before forward BFS: " << best_sol_length[0] << std::endl;
    ForwardSearchBFS(best_sol_length);
    BackwardSearchBFS();

    if (print) {
        // std::cout << "best_sol_length from forward BFS: " << best_sol_length[0] << std::endl;
        if (best_sol_length[0] == 0) {
            std::cout << "Solution: No" << std::endl;
        } else {
            std::cout << "Solution: Yes" << std::endl;
        }
    }

    // PrintReachable();
    // PrintReaching();

    // PrintNonReachable();
    // PrintNonReaching();

    bool unique = UniqueShortest();
    int num_w = NumWhiteHoles();
    int num_bl = NumBlackHoles();
    int num_f = NumForcedForwardMoves();
    int num_bck = NumForcedBackwardMoves();

    if (print) {
        // [ADDED: ksum, 11/1/2014]
        std::cout << "Unique: " << (unique ? "Yes" : "No") << std::endl;

        std::cout << "Solution length: " << best_sol_length[0] << std::endl;
        std::cout << "# of black holes: " << num_bl << std::endl;
        std::cout << "# of white holes: " << num_w << std::endl;
        std::cout << "# of forced forward moves: " << num_f << std::endl;
        std::cout << "# of forced backward moves: " << num_bck << std::endl;
    }

    int score = PuzzleScore(best_sol_length[0], unique, num_w, num_bl, num_f,
                            num_bck);
    if (print) {
        std::cout << "Puzzle score: " << score << std::endl << std::endl;
    }
    return score;
}

// BFS forward search which finds shortest path to puzzle goal and also
// identifies reachable cells.
void Puzzle::ForwardSearchBFS(int best_sol_len[1]) {
    /*
      [CHANGED: ksum, 11/1/2014]
      old:

        struct tuple {
            int row;
            int col;
            int distance_from_origin;
        };

        tuple first = {0, 0, 0};
    */
    CustomTuple first(0, 0, 0);

    std::set<int> visited;

    // [CHANGED: ksum, 11/1/2014]
    // old: std::list<tuple> queue;
    std::vector<CustomTuple> queue;

    queue.push_back(first);
    visited.insert(0);

    // BFS continues until we find the goal cell
    while (queue.size() != 0) {
        // [CHANGED: ksum, 11/1/2014]
        // old: tuple cur_tup = queue.front();
        CustomTuple cur_tup = queue.front();

        // remove from head of queue
        // [CHANGED: ksum, 11/1/2014]
        // old: queue.pop_front();
        queue.erase(queue.begin() + 0);

        // [CHANGED: ksum, 11/1/2014]
        // old: reachable_cells[TwoDimToOneDim(cur_tup.row, cur_tup.col)] = true;
        reachable_cells.insert(TwoDimToOneDim(cur_tup.row, cur_tup.col));

        // std::cout << "at " << cur_tup.row << "," << cur_tup.col << std::endl;
        // std::cout << "at " << TwoDimToOneDim(cur_tup.row, cur_tup.col) << std::endl;

        int current_val = puzzle[cur_tup.row][cur_tup.col];

        // reached goal, only update best solution length if we've beaten
        // existing one
        /*
          [CHANGED: ksum, 11/1/2014]
          old:

            if (current_val == 0 &&
                (best_sol_len[0] == 0 ||
                 cur_tup.distance_from_origin < best_sol_len[0])) {
                best_sol_len[0] = cur_tup.distance_from_origin;
            }
        */
        if (current_val == 0 &&
            (best_sol_len[0] == 0 ||
             cur_tup.distance_from_goal < best_sol_len[0])) {
            best_sol_len[0] = cur_tup.distance_from_goal;
        }

        // account for all 4 possible neighbors based on move out of current
        // cell - check if the neighbor is valid piece of puzzle and has not
        // yet been visited
        if (cur_tup.row + current_val < nRows &&
            visited.count(TwoDimToOneDim(cur_tup.row + current_val,
                                          cur_tup.col)) == 0) {
            /*
              [CHANGED: ksum, 11/1/2014]
              old:

                tuple new_tup = {
                    cur_tup.row + current_val,
                    cur_tup.col,
                    cur_tup.distance_from_origin + 1
                };
            */
            CustomTuple new_tup(cur_tup.row + current_val, cur_tup.col,
                                cur_tup.distance_from_goal + 1);

            queue.push_back(new_tup);
            visited.insert(TwoDimToOneDim(cur_tup.row + current_val,
                                          cur_tup.col));
        }
        if (cur_tup.row - current_val >= 0 &&
            visited.count(TwoDimToOneDim(cur_tup.row - current_val,
                                          cur_tup.col)) == 0) {
            /*
              [CHANGED: ksum, 11/1/2014]
              old:

                tuple new_tup = {
                    cur_tup.row - current_val,
                    cur_tup.col,
                    cur_tup.distance_from_origin + 1
                };
            */
            CustomTuple new_tup(cur_tup.row - current_val, cur_tup.col,
                                cur_tup.distance_from_goal + 1);

            queue.push_back(new_tup);
            visited.insert(TwoDimToOneDim(cur_tup.row - current_val,
                                          cur_tup.col));
        }
        if (cur_tup.col + current_val < nColumns &&
            visited.count(TwoDimToOneDim(cur_tup.row,
                                          cur_tup.col + current_val)) == 0) {
            /*
              [CHANGED: ksum, 11/1/2014]
              old:

                tuple new_tup = {
                    cur_tup.row,
                    cur_tup.col + current_val,
                    cur_tup.distance_from_origin + 1
                };
            */
            CustomTuple new_tup(cur_tup.row, cur_tup.col + current_val,
                                cur_tup.distance_from_goal + 1);

            queue.push_back(new_tup);
            visited.insert(TwoDimToOneDim(cur_tup.row,
                                          cur_tup.col + current_val));
        }
        if (cur_tup.col - current_val >= 0 &&
            visited.count(TwoDimToOneDim(cur_tup.row,
                                          cur_tup.col - current_val)) == 0) {
            /*
              [CHANGED: ksum, 11/1/2014]
              old:

                tuple new_tup = {
                    cur_tup.row,
                    cur_tup.col - current_val,
                    cur_tup.distance_from_origin + 1
                };
            */
            CustomTuple new_tup(cur_tup.row, cur_tup.col - current_val,
                                cur_tup.distance_from_goal + 1);

            queue.push_back(new_tup);
            visited.insert(TwoDimToOneDim(cur_tup.row, cur_tup.col - current_val));
        }
    }
}

// Performs a backward search from the goal of the puzzle to identify reaching
// cells
void Puzzle::BackwardSearchBFS() {
    /*
      [CHANGED: ksum, 11/1/2014]
      old:

        struct tuple {
            int row;
            int col;
            int distance_from_goal;
        };

        tuple first = {nRows - 1, nColumns - 1, 0};
    */
    CustomTuple first(nRows - 1, nColumns - 1, 0);

    // [CHANGED: ksum, 11/1/2014]
    // old: std::list<tuple> queue;
    std::vector<CustomTuple> queue;

    std::set<int> visited;
    queue.push_back(first);
    visited.insert(TwoDimToOneDim(nRows - 1, nColumns - 1));
    int num_visits = 0;

    while (queue.size() != 0) {
        // [CHANGED: ksum, 11/1/2014]
        // old: tuple cell = queue.front();
        CustomTuple cell = queue.front();

        // remove from head of queue
        // [CHANGED: ksum, 11/1/2014]
        // old: queue.pop_front();
        queue.erase(queue.begin() + 0);

        // [CHANGED: ksum, 11/1/2014]
        // old: reaching_cells[TwoDimToOneDim(cell.row, cell.col)] = true;
        reaching_cells.insert(TwoDimToOneDim(cell.row, cell.col));

        num_visits += 1;
        // std::cout << num_visits << ": " << "at " << cell.row << "," << cell.col << std::endl;
        // std::cout << num_visits << ": " << "at " << TwoDimToOneDim(cell.row, cell.col) << std::endl;

        // for all possible move lengths to/from current cell, if the cell a
        // move length away is valid, contains value to move to the current
        // cell, and has not been visited, process it
        for (int i = minVal; i <= maxVal; i++) {
            if (cell.row + i < nRows &&
                puzzle[cell.row + i][cell.col] == i &&
                visited.count(TwoDimToOneDim(cell.row + i, cell.col)) == 0) {

                /*
                  [CHANGED: ksum, 11/1/2014]
                  old:

                    tuple new_tup = {
                        cell.row + i,
                        cell.col,
                        cell.distance_from_goal + 1
                    };
                */
                CustomTuple new_tup(cell.row + i, cell.col,
                                    cell.distance_from_goal + 1);

                visited.insert(TwoDimToOneDim(cell.row + i, cell.col));
                queue.push_back(new_tup);
            }
            if (cell.row - i >= 0 &&
                puzzle[cell.row - i][cell.col] == i &&
                visited.count(TwoDimToOneDim(cell.row - i, cell.col)) == 0) {

                /*
                  [CHANGED: ksum, 11/1/2014]
                  old:

                    tuple new_tup = {
                        cell.row - i,
                        cell.col,
                        cell.distance_from_goal + 1
                    };
                */
                CustomTuple new_tup(cell.row - i, cell.col,
                                    cell.distance_from_goal + 1);

                visited.insert(TwoDimToOneDim(cell.row - i, cell.col));
                queue.push_back(new_tup);
            }
            if (cell.col + i < nColumns &&
                puzzle[cell.row][cell.col + i] == i &&
                visited.count(TwoDimToOneDim(cell.row, cell.col + i)) == 0) {

                /*
                  [CHANGED: ksum, 11/1/2014]
                  old:

                    tuple new_tup = {
                        cell.row,
                        cell.col + i,
                        cell.distance_from_goal + 1
                    };
                */
                CustomTuple new_tup(cell.row, cell.col + i,
                                    cell.distance_from_goal + 1);

                visited.insert(TwoDimToOneDim(cell.row, cell.col + i));
                queue.push_back(new_tup);
            }
            if (cell.col - i >= 0 &&
                puzzle[cell.row][cell.col - i] == i &&
                visited.count(TwoDimToOneDim(cell.row, cell.col - i)) == 0) {

                /*
                  [CHANGED: ksum, 11/1/2014]
                  old:

                    tuple new_tup = {
                        cell.row,
                        cell.col - i,
                        cell.distance_from_goal + 1
                    };
                */
                CustomTuple new_tup(cell.row, cell.col - i,
                                    cell.distance_from_goal + 1);

                visited.insert(TwoDimToOneDim(cell.row, cell.col - i));
                queue.push_back(new_tup);
            }
        }
    }
}

bool Puzzle::UniqueShortest() {
    // TODO
    return true;
}

// Convert a row, col 2D index to corresponding 1D index
int Puzzle::TwoDimToOneDim(int row, int col) {
    return (row * nColumns) + col;
}

// Return the number of black holes. A cell is a black hole if and only if it
// is a reachable, non-reaching cell.
int Puzzle::NumBlackHoles() {
    int acc = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (reachable_cells.count(TwoDimToOneDim(i, j)) &&
                !reaching_cells.count(TwoDimToOneDim(i, j))) {
                // std::cout << TwoDimToOneDim(i, j) << " is black" << std::endl;
                acc += 1;
            }
        }
    }
    return acc;
}

// Return the number of white holes. A cell is a white hole if and only if it
// is a reaching, non-reachable cell
int Puzzle::NumWhiteHoles() {
    int acc = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (reaching_cells.count(TwoDimToOneDim(i, j)) &&
                !reachable_cells.count(TwoDimToOneDim(i, j))) {
                // std::cout << TwoDimToOneDim(i, j) << " is white" << std::endl;
                acc += 1;
            }
        }
    }
    return acc;
}

// Print all reachable cells
void Puzzle::PrintReachable() {
    std::cout << "Reachable cells" << std::endl;
    int count = 1;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (reachable_cells.count(TwoDimToOneDim(i, j))) {
                std::cout << count << ": " << i << ", " << j << std::endl;
                std::cout << TwoDimToOneDim(i, j) << std::endl;
                count += 1;
            }
        }
    }
}

// Print all non-reachable cells
void Puzzle::PrintNonReachable() {
    std::cout << "Non-Reachable cells" << std::endl;
    int count = 1;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (!reachable_cells.count(TwoDimToOneDim(i, j))) {
                std::cout << count << ": " << i << ", " << j << std::endl;
                // std::cout << TwoDimToOneDim(i, j) << std::endl;
                count += 1;
            }
        }
    }
}

// Print all reaching cells
void Puzzle::PrintReaching() {
    std::cout << "Reaching cells" << std::endl;
    int count = 1;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (reaching_cells.count(TwoDimToOneDim(i, j))) {
                std::cout << count << ": " << i << ", " << j << std::endl;
                // std::cout << TwoDimToOneDim(i, j) << std::endl;
                count += 1;
            }
        }
    }
}

// Print all non-reaching cells
void Puzzle::PrintNonReaching() {
    std::cout << "Non-Reaching cells" << std::endl;
    int count = 1;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (!reaching_cells.count(TwoDimToOneDim(i, j))) {
                std::cout << count << ": " << i << ", " << j << std::endl;
                // std::cout << TwoDimToOneDim(i, j) << std::endl;
                count += 1;
            }
        }
    }
}

// A forced forward move occurs when there is only one action that leaves a
// reachable cell. The goal cannot have any forced forward moves.
int Puzzle::NumForcedForwardMoves() {
    int acc = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            // given cell is not goal and is reachable
            if ((i != nRows - 1 || j != nColumns - 1) &&
                reachable_cells.count(TwoDimToOneDim(i, j))) {
                int num_actions = 0;
                int current_val = puzzle[i][j];

                if (i + current_val < nRows) {
                    num_actions += 1;
                }

                if (i - current_val >= 0) {
                    num_actions += 1;
                }

                if (j + current_val < nColumns) {
                    num_actions += 1;
                }

                if (j - current_val >= 0) {
                    num_actions += 1;
                }

                // if only one action leaves the cell
                if (num_actions == 1) {
                    // std::cout << i << ", " << j << " is a forced forward move" << std::endl;
                    acc += 1;
                }
            }
        }
    }
    return acc;
}

// Set of reaching cells that have only one action that reaches them. The start
// cannot have any forced backward moves.
int Puzzle::NumForcedBackwardMoves() {
    int acc = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            // given cell is not start and is a reaching cell
            if ((i != 0 || j != 0) &&
                reaching_cells.count(TwoDimToOneDim(i, j))) {
                int num_actions = 0;
                // check all possible neighboring cells and aggregate the
                // number that can reach current cell
                for (int k = minVal; k <= maxVal; k++) {
                    if (i + k < nRows && puzzle[i + k][j] == k) {
                        num_actions += 1;
                    }

                    if (i - k >= 0 && puzzle[i - k][j] == k) {
                        num_actions += 1;
                    }

                    if (j + k < nColumns && puzzle[i][j + k] == k) {
                        num_actions += 1;
                    }

                    if (j - k >= 0 && puzzle[i][j - k] == k) {
                        num_actions += 1;
                    }
                }
                // if only one cell can reach current reaching cell, we have a
                // forced backward move
                if (num_actions == 1) {
                    acc += 1;
                }
            }
        }
    }
    return acc;
}

// Computes the score of a puzzle
int Puzzle::PuzzleScore(int shortest_sol_length, bool unq_shortest, int num_w,
                        int num_bl, int num_f, int num_bck) {
    // try not to favor unsovable puzzles with a terrible score
    if (shortest_sol_length == 0) {
        return unsolvable_score;
    } else {
        int total_score = 0;
        total_score += shortest_sol_length * 5;
        if (unq_shortest)
            total_score += (nRows * nColumns);
        total_score -= (num_w + num_bl) * 2;
        total_score -= (num_f + num_bck) * 2;
        return total_score;
    }
}

// Pick a random cell, choose a random value, perform the change and
// re-evaluate the new puzzle. If second must_improve bool is true, the new
// puzzle must be an improvement over the existing, original puzzle that was
// modified. If false, we just make a random change and copy that changed
// puzzle over to our existing, original puzzle.
bool Puzzle::RandModifyPuzzle(int prior_value, bool must_improve) {
    int random_row = 0;
    int random_col = 0;

    // pick the random cell, excluding the goal cell
    do {
        /*
          [CHANGED: ksum, 11/1/2014]
          old:

            // http://en.cppreference.com/w/cpp/numeric/random/random_device
            std::random_device row_rd;
            std::uniform_int_distribution<int> row_dist(0, nRows - 1);
            random_row = row_dist(row_rd);

            std::random_device col_rd;
            std::uniform_int_distribution<int> col_dist(0, nColumns - 1);
            random_col = col_dist(col_rd);
        */
        // generate secret number between 0 and nRows - 1
        random_row = rand() % nRows;
        // generate secret number between 0 and nColumns - 1
        random_col = rand() % nColumns;
    } while (random_row == nRows - 1 && random_col == nColumns - 1);

    // pick the random value
    int random_val = 0;
    do {
        /*
          [CHANGED: ksum, 11/1/2014]
          old:

            std::random_device val_rd;
            std::uniform_int_distribution<int> val_dist(minVal, maxVal);
            random_val = val_dist(val_rd);
        */
        random_val = rand() % (maxVal - minVal + 1) + minVal;
    } while (puzzle[random_row][random_col] == random_val);

    // perform the substitution on a new, temporary puzzle
    Puzzle new_puzzle(nRows, nColumns, minVal, maxVal, false);
    CopyToPuzzle(&new_puzzle);
    new_puzzle.puzzle[random_row][random_col] = random_val;
    int evaluation = new_puzzle.EvaluatePuzzle(false);

    // take the better of the two puzzles
    if (must_improve) {
        if (evaluation > prior_value) {
            CopyFromPuzzle(new_puzzle);
            return true;
        } else {
            return false;
        }
    }
    // take the new puzzle regardless of an improvement, so long as it's
    // solvable
    else if (evaluation != unsolvable_score) {
        CopyFromPuzzle(new_puzzle);
        return true;
    }
    // unsolvable puzzle, let's avoid it
    else {
        return false;
    }
}

// Brute force: evaluate all possible successors of current puzzle and pick the
// best one.
bool Puzzle::BruteModifyPuzzle(int original_puzzle_value) {
    int changed_row = -1;
    int changed_col = -1;
    int changed_value = -1;
    int best_puzzle_value = original_puzzle_value;

    // for every single cell of current puzzle
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            // never change the goal value
            if (i != nRows - 1 || j != nColumns - 1) {
                int original_val = puzzle[i][j];
                // for every possible value of this cell
                for (int k = minVal; k <= maxVal; k++) {
                    // if this value != original cell's value, create a
                    // temporary Puzzle, update the particular cell with given
                    // value, and evaluate resulting puzzle
                    if (k != original_val) {
                        Puzzle new_puzzle(nRows, nColumns, minVal, maxVal, false);
                        // std::cout << "current puzzle" << std::endl;
                        // PrintPuzzle();
                        CopyToPuzzle(&new_puzzle);
                        new_puzzle.puzzle[i][j] = k;
                        // std::cout << "new puzzle, i: " << i << ", j: " << j << ", k: " << k << std::endl;
                        // new_puzzle.PrintPuzzle();
                        int new_puzzle_value = new_puzzle.EvaluatePuzzle(false);
                        // std::cout << "New puzzle value: " << new_puzzle_value << std::endl;
                        if (new_puzzle_value > best_puzzle_value) {
                            // std::cout << "New puzzle value: " << new_puzzle_value << ", changed " << i << "," << j << " from " << original_val << " to " << k << std::endl;
                            // new_puzzle.PrintPuzzle();
                            best_puzzle_value = new_puzzle_value;
                            changed_row = i;
                            changed_col = j;
                            changed_value = k;
                        }
                    }
                }
            }
        }
    }
    if (best_puzzle_value > original_puzzle_value) {
        puzzle[changed_row][changed_col] = changed_value;
        return true;
    } else {
        return false;
    }
}

// Fill the puzzle arrays with random values
void Puzzle::RandomFill() {
    /*
      [REMOVED: ksum, 11/1/2014]
      old:

        // http://en.cppreference.com/w/cpp/numeric/random/random_device
        std::random_device rd;
        // [minVal, maxVal]
        std::uniform_int_distribution<int> dist(minVal, maxVal);
    */

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            // [CHANGED: ksum, 11/1/2014]
            // old: puzzle[i][j] = dist(rd);
            puzzle[i][j] = rand() % (maxVal - minVal + 1) + minVal;
        }
    }
    puzzle[nRows - 1][nColumns - 1] = 0;
}

// Copy current puzzle contents to new_puzzle
void Puzzle::CopyToPuzzle(Puzzle* new_puzzle) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            new_puzzle->puzzle[i][j] = puzzle[i][j];
        }
    }
}

// Copy current puzzle contents from new_puzzle
void Puzzle::CopyFromPuzzle(const Puzzle& new_puzzle) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            puzzle[i][j] = new_puzzle.puzzle[i][j];
        }
    }
}
