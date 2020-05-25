/*
  NAME: Kyle Sum
  STUDENT ID: 6464547821
*/

#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include "Timer.h"
#include "Puzzle.h"

// [ADDED: ksum, 11/1/2014]
#include <stdlib.h>     /* srand, rand */

#define max_time_limit 59

void GeneratePuzzles(int nRows, int nColumns, int minVal, int maxVal, Timer &t)
{
	// YOUR CODE HERE

    // [ADDED: ksum, 11/1/2014]
    srand(time(NULL));

    int result;

    // Puzzle pt1(5, 5, 1, 4, 1);
    // pt1.PrintPuzzle();
    // result = pt1.EvaluatePuzzle(true);

    // Puzzle pt2(5, 5, 1, 4, 2);
    // pt2.PrintPuzzle();
    // result = pt2.EvaluatePuzzle(true);

    // Puzzle pt3(10, 10, 1, 9, 3);
    // pt3.PrintPuzzle();
    // result = pt3.EvaluatePuzzle(true);

    Puzzle p(nRows, nColumns, minVal, maxVal, -1);
    // p.PrintPuzzle();
    result = p.EvaluatePuzzle(false);
    int num_unchanged = 0;

    // store the best puzzle found
    Puzzle best_puzzle_found(nRows, nColumns, minVal, maxVal, -1);
    best_puzzle_found.CopyFromPuzzle(p);
    int best_puzzle_score_found = result;
    // bool just_accepted_worse = false;

    while (t.GetElapsedTime() < max_time_limit) {
        // std::cout << t.GetElapsedTime() << std::endl;

        // randomly choose between picking the best possible successor or a
        // better, random successor
        if (num_unchanged < 3) {
            /*
              [CHANGED: ksum, 11/1/2014]
              old:

                std::random_device rd;
                std::uniform_int_distribution<int> dist(1, 3);
                int rand_val = dist(rd);
            */

            // http://www.cplusplus.com/reference/cstdlib/rand/
            // initialize random seed
            // generate secret number between 1 and 3
            int rand_val = rand() % 3 + 1;

            // best possible successor
            if (rand_val == 1 || rand_val == 2) {
                bool improved = p.BruteModifyPuzzle(result);
                if (improved) {
                    result = p.EvaluatePuzzle(false);
                    // p.PrintPuzzle();
                    // std::cout << "Brute modification improved to above puzzle, score: " << result << std::endl << std::endl;
                    if (result > best_puzzle_score_found) {
                        best_puzzle_found.CopyFromPuzzle(p);
                        best_puzzle_score_found = result;
                    }
                    num_unchanged = 0;
                }
                else {
                    // std::cout << "Brute modification did not find improvement" << std::endl;
                    num_unchanged += 1;
                }
            }
            // better, random successor
            else {
                bool improved = p.RandModifyPuzzle(result, true);
                if (improved) {
                    result = p.EvaluatePuzzle(false);
                    // p.PrintPuzzle();
                    // std::cout << "Random improvement modification created above puzzle, score: " << result << std::endl << std::endl;
                    if (result > best_puzzle_score_found) {
                        best_puzzle_found.CopyFromPuzzle(p);
                        best_puzzle_score_found = result;
                    }
                    // just_accepted_worse = false;
                    num_unchanged = 0;
                } else {
                    num_unchanged += 1;
                }
            }
        }
        // let's make a random change and accept a worse score or randomly
        // restart
        else {
            /*
              [CHANGED: ksum, 11/1/2014]
              old:

                old: std::random_device rd;
                old: std::uniform_int_distribution<int> dist(1, maxVal);
                old: int rand_val = dist(rd);
            */

            // generate secret number between 1 and maxVal
            int rand_val = rand() % maxVal + 1;

            // random restart
            if (rand_val == 1) {
                p.RandomFill();
            } else {
                for (int i = 0; i < rand_val - 1; i++) {
                    bool modified = p.RandModifyPuzzle(result, false);
                    // as long as new puzzle is solvable
                    if (modified) {
                        result = p.EvaluatePuzzle(false);
                        if (result > best_puzzle_score_found) {
                            // p.PrintPuzzle();
                            // std::cout << "Random modification improved puzzle, score: " << result << std::endl;
                            best_puzzle_found.CopyFromPuzzle(p);
                            best_puzzle_score_found = result;
                        } else {
                            // p.PrintPuzzle();
                            // std::cout << "Random modification deprecated puzzle, score: " << result << std::endl;
                        }
                        // just_accepted_worse = true;
                        num_unchanged = 0;
                    }
                }
            }
        }
    }

    // std::cout << "Final result (best puzzle score found: " << best_puzzle_score_found << ")" << std::endl;

    // [ADDED: ksum, 11/1/2014]
    std::cout << std::endl << "Puzzle:" << std::endl;

    best_puzzle_found.PrintPuzzle();
    best_puzzle_found.EvaluatePuzzle(true);
}

int main(int argc, char **argv)
{
    // Process the arguments
    if (argc != 5)
        {
            std::cout << "Please specify the number of rows and columns and the minimum and maximum values for each cell (requires 4 parameters)" << std::endl;
            exit(0);
        }
    int nRows = atoi(argv[1]);
    int nColumns = atoi(argv[2]);
    int minVal = atoi(argv[3]);
    int maxVal = atoi(argv[4]);

    // Start the timer
    Timer t;
    t.StartTimer();

    // Generate the puzzle
    std::cout << "Generating a " << nRows << "x" << nColumns <<
        " puzzle with values in range [" << minVal << "-" << maxVal << "]"
              << std::endl;

    GeneratePuzzles(nRows, nColumns, minVal, maxVal, t);

    // Print the elapsed time
    printf("Total time: %.6lf seconds\n", t.GetElapsedTime());

    return 0;
}
