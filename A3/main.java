/**
 * "variant1-3-25"  is a policy for a different version of question 2 where you start with 3 lives
 * and are trying to reach a total score of 25. "variant2-3-25" is the policy for the bonus game
 * played with 3 lives and target score is 25.
 *
 * 3 17 7 Yes 0.972222
 * You first hold (adding scratch score to total score) then roll the die (adding die roll to
 * scratch score. So, holding gives you:
 * roll 1: 2 24 1
 * roll 2: 2 24 2
 * roll 3: 2 24 3
 * roll 4: 2 24 4
 * roll 5: 2 24 5
 * roll 6: 1 24 0
 * */

public class main {
    public static void main(String args[]) {
        // GamePlayer g = new GamePlayer(3, 25);
        GamePlayer g = new GamePlayer(5, 40);
        g.generateStates();
        // g.printInitialStates();
        g.calculateProbabilities();
        g.printFinalStates();
    }
}
