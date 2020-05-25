import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class GamePlayer {

    private int numStartingLives;
    private int winningScore;
    private Map<String, Node> states;
    final boolean DEBUG = false;

    public GamePlayer(int numLives, int winningScore) {
        this.numStartingLives = numLives;
        this.winningScore = winningScore;
        this.states = new HashMap<String, Node>();
    }

    /**
     * Initially I tried to generate the tree as a whole using BFS from the initial, root state.
     * However, each node can potentially have 11 children, so the size explodes. This can take
     * forever to calculate. Instead, treat it as a DAG. Otherwise, you have this exponential blow
     * up. You should have a single state for each combination of total lives, total score, and
     * scratch score, and only store these in the memory. Then, when you want to compute the value
     * of a state, you look up the values of the states that the die roll (or yelling "hold") can
     * lead to. But you have to be careful about the order you compute the values of these states
     * (for instance, you have to compute the value for 4 0 0 before trying to compute the value of
     * 5 0 0, since you need 4 0 0's value to compute 5 0 0's value).
     * */
    public void generateStates() {
        for (int i = numStartingLives; i >= 0; i--) {
            for (int j = 0; j <= winningScore; j++) {
                for (int k = 0; k <= winningScore; k++) {
                    if (i == 0) {
                        // losing terminal state
                        states.put(i + " " + j +  " " + k, new Node(i, j, k, 0));
                    } else if (i > 0 && j + k >= winningScore) {
                        // winning terminal state: states where the sum of the total and scratch
                        // scores is at least winning score are terminal (since it is always optimal
                        // to hold and win)
                        states.put(i + " " + j +  " " + k, new Node(i, j, k, 1));
                    } else {
                        states.put(i + " " + j +  " " + k, new Node(i, j, k));
                    }

                }
            }
        }
    }

    /**
     * Calculate the values/probabilities of all nodes/states
     * */
    public void calculateProbabilities() {
        for (String key : states.keySet()) {
            String[] key_sp = key.split(" ");
            computeStateValue(Integer.parseInt(key_sp[0]), Integer.parseInt(key_sp[1]),
                              Integer.parseInt(key_sp[2]));
        }
    }

    /**
     * Compute the value of a state given the number of lives, total score, and scratch score and
     * accounting for children's probabilities
     */
    private void computeStateValue(int numLives, int totalScore, int scratchScore) {
        Node cur_n = states.get(numLives + " " + totalScore + " " + scratchScore);
        // if we haven't yet calculated this node's probability
        if (cur_n.probability == -1) {
            if (DEBUG) {
                System.out.println("Computing value of state: " + numLives + " " + totalScore +
                                   " " + scratchScore);
            }
            float hold_prob_sum = holdComputeHelper(cur_n);
            float no_hold_prob_sum = noHoldComputeHelper(cur_n);
            determineHold(cur_n, hold_prob_sum, no_hold_prob_sum);
        }
    }

    /**
     * Compute cumulative probability of winning when holding then rolling from current node/state
     * */
    private float holdComputeHelper(Node cur_n) {
        float hold_prob_sum = 0;
        // If both the scratch score and the number of lives are above zero, hold then roll
        if (cur_n.scratchScore > 0 && cur_n.numLives > 0) {
            // Whenever you hold, you lose a life. Your total score is increased by your scratch
            // score and your scratch score is set to 0.
            int heldNumLives = cur_n.numLives - 1;
            int heldTotalScore = cur_n.totalScore + cur_n.scratchScore;

            // now perform the roll after hold
            for (int i = 1; i <= 6; i++) {
                if (i == 6) {
                    if (DEBUG) {
                        System.out.println("Fetching value of state (after hold): " +
                                           (heldNumLives - 1) + " " + heldTotalScore + " 0");
                    }

                    // yet another life is lost upon rolling 6
                    Node temp_n = states.get(heldNumLives - 1 + " " + heldTotalScore + " 0");
                    if (temp_n == null) {
                        // automatic win by holding in this case, otherwise this node is a terminal,
                        // losing node so we add 0/do nothing to the cumulative probability
                        if (heldNumLives - 1 > 0 && heldTotalScore >= winningScore) {
                            hold_prob_sum += 1;
                        }
                    }
                    else if (temp_n.probability != -1) {
                        // already calculated probability of this child node
                        hold_prob_sum += temp_n.probability;
                    } else {
                        computeStateValue(heldNumLives - 1, heldTotalScore, 0);
                        Node child_n = states.get((heldNumLives - 1) + " " + heldTotalScore + " 0");
                        hold_prob_sum += child_n.probability;
                    }
                } else {
                    if (DEBUG) {
                        System.out.println("Fetching value of state (after hold): " + heldNumLives +
                                           " " + heldTotalScore + " " + i);
                    }

                    Node temp_n = states.get(heldNumLives + " " + heldTotalScore + " " + i);
                    if (temp_n == null && heldTotalScore + i >= winningScore) {
                        hold_prob_sum += 1;
                    }
                    else if (temp_n.probability != -1) {
                        // already calculated probability of this child node
                        hold_prob_sum += temp_n.probability;
                    } else {
                        computeStateValue(heldNumLives, heldTotalScore, i);
                        Node child_n = states.get(heldNumLives + " " + heldTotalScore + " " + i);
                        hold_prob_sum += child_n.probability;
                    }
                }
            }
        }
        return hold_prob_sum;
    }

    /**
     * Compute cumulative probability of winning when rolling without holding from current
     * node/state
     * */
    private float noHoldComputeHelper(Node cur_n) {
        float no_hold_prob_sum = 0;
        for (int i = 1; i <= 6; i++) {
            // If you rolled a 6, then you lose a life and your scratch score is set to zero.
            if (i == 6) {
                if (DEBUG) {
                    System.out.println("Fetching value of state: " + (cur_n.numLives - 1) +
                                       " " + cur_n.totalScore + " 0");
                }

                Node temp_n = states.get((cur_n.numLives - 1) + " " + cur_n.totalScore + " 0");
                // if we've already calculated probability of this child node
                if (temp_n.probability != -1) {
                    no_hold_prob_sum  += temp_n.probability;
                } else {
                    computeStateValue(cur_n.numLives - 1, cur_n.totalScore, 0);
                    Node child_n = states.get((cur_n.numLives - 1) + " " + cur_n.totalScore + " 0");
                    no_hold_prob_sum += child_n.probability;
                }
            }
            else {
                if (DEBUG) {
                    System.out.println("Fetching value of state: " + cur_n.numLives + " " +
                                       cur_n.totalScore + " " + (cur_n.scratchScore + i));
                }

                // If you rolled a 1 to 5, then the rolled number is added to your scratch score
                Node temp_n = states.get(cur_n.numLives + " " + cur_n.totalScore + " " +
                                         (cur_n.scratchScore + i));
                if (temp_n == null && cur_n.totalScore + cur_n.scratchScore + i >= winningScore) {
                    no_hold_prob_sum += 1;
                } else if (temp_n.probability != -1) {
                    // already calculated probability of this child node
                    no_hold_prob_sum  += temp_n.probability;
                } else {
                    computeStateValue(cur_n.numLives, cur_n.totalScore, cur_n.scratchScore + i);
                    Node child_n = states.get(cur_n.numLives + " " + cur_n.totalScore + " " +
                                              (cur_n.scratchScore + i));
                    no_hold_prob_sum += child_n.probability;
                }
            }
        }
        return no_hold_prob_sum;
    }

    /**
     * Based on the cumulative probabilities of winning when holding and not holding, update the
     * state/Node to mirror the optimal strategy
     * */
    private void determineHold(Node cur_n, float hold_prob_sum, float no_hold_prob_sum) {
        float hold_prob_win = hold_prob_sum / new Float(6.0);
        float no_hold_prob_win = no_hold_prob_sum / new Float(6.0);

        if (DEBUG) {
            System.out.println("hold prob win: " + hold_prob_win + ", no hold prob win: " +
                               no_hold_prob_win);
        }

        if (hold_prob_win > no_hold_prob_win) {
            cur_n.hold = true;
            cur_n.probability = hold_prob_win;
        } else {
            cur_n.hold = false;
            cur_n.probability = no_hold_prob_win;
        }

        if (DEBUG) {
            System.out.println("Finished computing value of state: " + cur_n.numLives + " " +
                               cur_n.totalScore + " " + cur_n.scratchScore + ": " +
                               cur_n.probability);
        }
    }

    /**
     * Output initial states
     */
    public void printInitialStates() {
        for (String key : states.keySet()) {
            System.out.println(key);
        }
    }

    /**
     * Output final states
     * */
    public void printFinalStates() {
        for (String key : states.keySet()) {
            Node n = states.get(key);
            // don't print out any states where you can't hold
            if (n.scratchScore != 0 && n.probability != 0 && n.probability != 1) {
                if (n.hold) {
                    System.out.println(n.numLives + " " + n.totalScore + " " + n.scratchScore +
                                       " Yes " + String.format("%.6f", n.probability));
                } else {
                    System.out.println(n.numLives + " " + n.totalScore + " " + n.scratchScore +
                                       " No " + String.format("%.6f", n.probability));
                }
            }
        }
        // Node root = states.get(numStartingLives + " 0 0");
        // if (root.hold) {
        //     System.out.println(root.numLives + " " + root.totalScore + " " + root.scratchScore +
        //                        " Yes " + String.format("%.6f", root.probability));
        // } else {
        //     System.out.println(root.numLives + " " + root.totalScore + " " + root.scratchScore +
        //                        " No " + String.format("%.6f", root.probability));
        // }
    }
}
