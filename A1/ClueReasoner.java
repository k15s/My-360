/**
 * ClueReasoner.java - project skeleton for a propositional reasoner
 * for the game of Clue.  Unimplemented portions have the comment "TO
 * BE IMPLEMENTED AS AN EXERCISE".  The reasoner does not include
 * knowledge of how many cards each player holds.  See
 * http://cs.gettysburg.edu/~tneller/nsf/clue/ for details.
 *
 * @author Todd Neller
 * @version 1.0
 *

Copyright (C) 2005 Todd Neller

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Information about the GNU General Public License is available online at:
  http://www.gnu.org/licenses/
To receive a copy of the GNU General Public License, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

 */

import java.io.*;
import java.util.*;

public class ClueReasoner
{
    private int numPlayers;
    private int playerNum;
    private int numCards;
    private SATSolver solver;
    private String caseFile = "cf";
    private String[] players = {"sc", "mu", "wh", "gr", "pe", "pl"};
    private String[] suspects = {"mu", "pl", "gr", "pe", "sc", "wh"};
    private String[] weapons = {"kn", "ca", "re", "ro", "pi", "wr"};
    private String[] rooms = {"ha", "lo", "di", "ki", "ba", "co", "bi", "li", "st"};
    private String[] cards;

    public ClueReasoner()
    {
        numPlayers = players.length;

        // Initialize card info
        cards = new String[suspects.length + weapons.length + rooms.length];
        int i = 0;
        for (String card : suspects)
            cards[i++] = card;
        for (String card : weapons)
            cards[i++] = card;
        for (String card : rooms)
            cards[i++] = card;
        numCards = i;

        // Initialize solver
        solver = new SATSolver();
        addInitialClauses();
    }

    private int getPlayerNum(String player)
    {
        if (player.equals(caseFile))
            return numPlayers;
        for (int i = 0; i < numPlayers; i++)
            if (player.equals(players[i]))
                return i;
        System.out.println("Illegal player: " + player);
        return -1;
    }

    private int getCardNum(String card)
    {
        for (int i = 0; i < numCards; i++)
            if (card.equals(cards[i]))
                return i;
        System.out.println("Illegal card: " + card);
        return -1;
    }

    private int getPairNum(String player, String card)
    {
        return getPairNum(getPlayerNum(player), getCardNum(card));
    }

    private int getPairNum(int playerNum, int cardNum)
    {
        return playerNum * numCards + cardNum + 1;
    }

    public void addInitialClauses()
    {
        // TODO

        // Each card is in AT LEAST one place (including case file). That is,
        // each card is in a player’s hand or the case file. We do not allow
        // the possibility that a card was accidentally left in the box
        for (int c = 0; c < numCards; c++) {
            // single clause for this card: {CP1 CP2 CP3...etc} since this
            // individual card can be in multiple places/with multiple players
            //
            // IMPORTANT FROM TA:
            // The provided code says l_1 OR l_2 OR ... OR l_7, therefore
            // a single clause array's components are OR'D together and all the
            // clauses are AND'D together
            int[] clause = new int[numPlayers + 1];
            for (int p = 0; p <= numPlayers; p++) {
                clause[p] = getPairNum(p, c);
            }
            solver.addClause(clause);
        }

        // If a card is in one place, it cannot be in another place. So if it's
        // in one player's hand, it's not in any other hand. For each pair of
        // places/players, it cannot be in both.
        //
        // for all cards
        for (int c = 0; c < numCards; c++) {
            // for every pair of players (mirroring iteration from loop above)
            for (int p1 = 0; p1 <= numPlayers; p1++) {
                for (int p2 = p1 + 1; p2 <= numPlayers; p2++) {
                    // (CP1 AND notCP2) or (notCP1 and CP2) or (notCP1 AND notCP2)
                    //
                    // Simpler propositional theorem: not(A ^ B) = notA V notB
                    // for each pair of players, card cannot belong to both, so
                    // not(CP1 AND CP2) = notCP1 V notCP2 therefore one clause
                    int[] clause = new int[2];
                    clause[0] = -getPairNum(p1, c);
                    clause[1] = -getPairNum(p2, c);
                    solver.addClause(clause);
                }
            }
        }

        // AT LEAST (can have multiple, >= 1) one card of each category is in
        // the case file.
        //
        // There are 3 card categories: suspects, weapons, and rooms
        //
        // For all cards, at least one card is associated with case file so
        // CFC1 OR CFC2 OR CFC3 OR etc. so for each category, all logic goes
        // into one clause array

        // Suspects clause
        int[] clause = new int[suspects.length];
        int iterator = 0;
        for (String card : suspects) {
            clause[iterator] = getPairNum(caseFile, card);
            iterator += 1;
        }
        solver.addClause(clause);

        // Weapons clause
        clause = new int[weapons.length];
        iterator = 0;
        for (String card : weapons) {
            clause[iterator] = getPairNum(caseFile, card);
            iterator += 1;
        }
        solver.addClause(clause);

        // Rooms clause
        clause = new int[rooms.length];
        iterator = 0;
        for (String card : rooms) {
            clause[iterator] = getPairNum(caseFile, card);
            iterator += 1;
        }
        solver.addClause(clause);

        // No two cards in each category can both be in the case file.
        //
        // There are 3 card categories: suspects, weapons, and rooms
        //
        // This is similar to the earlier case where a card only belongs to
        // one place at a time. So, not(CFC1 AND CFC2) = notCFC1 OR notCFC2

        // Suspects
        for (String card : suspects) {
            for (String otherCard : suspects) {
                // if we're dealing with two separate cards
                if (!card.equals(otherCard)) {
                    clause = new int[2];
                    clause[0] = -getPairNum(caseFile, card);
                    clause[1] = -getPairNum(caseFile, otherCard);
                    solver.addClause(clause);
                }
            }
        }

        // Weapons
        for (String card : weapons) {
            for (String otherCard : weapons) {
                // if we're dealing with two separate cards
                if (!card.equals(otherCard)) {
                    clause = new int[2];
                    clause[0] = -getPairNum(caseFile, card);
                    clause[1] = -getPairNum(caseFile, otherCard);
                    solver.addClause(clause);
                }
            }
        }

        // Rooms
        for (String card : rooms) {
            for (String otherCard : rooms) {
                // if we're dealing with two separate cards
                if (!card.equals(otherCard)) {
                    clause = new int[2];
                    clause[0] = -getPairNum(caseFile, card);
                    clause[1] = -getPairNum(caseFile, otherCard);
                    solver.addClause(clause);
                }
            }
        }
    }

    public void hand(String player, String[] cards)
    {
        // set player perspective
        playerNum = getPlayerNum(player);

        // TODO

        // At the beginning of the game, the player is dealt a hand (set) of
        // cards. THIS IS PRIVATE INFORMATION THE PLAYER HAS ABOUT WHAT IS NOT
        // IN THE CASE FILE. Before the beginning of the game, we use the hand
        // method to (1) set the player whose perspective we are reasoning from
        // and (2) note that the given cards are in the possession of that
        // player. Here the programmer should add to the SATSolver the simple
        // clauses representing the known possession of these cards.
        //
        // The player knows his/her cards are not in the caseFile, as they are
        // his/hers. So for each card, PC AND notCFC, meaning the player owns
        // the card and the case file doesn't have the card. A single clause
        // array OR's its contents together. We want to AND them, so this forms
        // two separate clauses - those are then AND'D together.
        int iterator = 0;
        for (String card : cards) {
            int[] clause = new int[1];
            clause[0] = getPairNum(player, card);
            solver.addClause(clause);

            clause = new int[1];
            clause[0] = -getPairNum(caseFile, card);
            solver.addClause(clause);
        }
    }

    public void suggest(String suggester, String card1, String card2,
                        String card3, String refuter, String cardShown)
    {
        // TODO

        /**
         * In the game of clue, a player may suggest a suspect, a weapon, and a
         * room, upon entering that room on the board.
         *
         * When a suggestion of three cards is made, the player to the left of
         * the suggester (clockwise) checks their private cards to see if any
         * of the cards are part of the suggestion. If so, the player must
         * refute the suggestion by privately showing one of these refuting
         * cards to the suggester. If not, the player states that they cannot
         * refute the suggestion, and attention then turns to the next player
         * clockwise. The next player does the same, either refuting or not,
         * and this continues clockwise until the first possible refutation, or
         * until all other players have stated that they cannot refute the
         * suggestion.
         * */

        // a refuter exists
        if (refuter != null) {
            // In many cases, a player does not get to see the card that is
            // shown to refute the suggestion. In this case, the cardShown
            // parameter is null. Consider the method call suggest("wh", "mu",
            // "re", "ba", "pe", null). White suggests that Mustard committed
            // the murder with the revolver in the ballroom. Peacock refutes
            // the suggestion by showing a card privately to White, but the
            // player (Scarlet) does not get to see this card. In this case we
            // learn that Green does not have these cards SINCE GREEN IS RIGHT
            // NEIGHBOR OF WHITE. We also learn that Peacock has at least one
            // of these cards. The information gained is similar to other
            // previous case(s). The difference is that at least one of the
            // three suggested cards must be in the refuter’s hand.
            if (cardShown == null) {
                // refuter has at least one (>= 1) of the cards so
                // RC1 OR RC2 OR RC3 therefore they all fit in one clause
                int[] clause = new int[3];
                clause[0] = getPairNum(refuter, card1);
                clause[1] = getPairNum(refuter, card2);
                clause[2] = getPairNum(refuter, card3);
                solver.addClause(clause);

                // The players who couldn't refute don't have any of the cards.
                // So in the above example, notGC1 AND notGC2 AND notGC3. These
                // 3 statements are AND'D together, so 3 different clauses
                ArrayList<String> playersBeforeRefuter = getPlayersBeforeRefuter(suggester, refuter);
                for (String playerBeforeRefuter : playersBeforeRefuter) {
                    clause = new int[1];
                    clause[0] = -getPairNum(playerBeforeRefuter, card1);
                    solver.addClause(clause);

                    clause = new int[1];
                    clause[0] = -getPairNum(playerBeforeRefuter, card2);
                    solver.addClause(clause);

                    clause = new int[1];
                    clause[0] = -getPairNum(playerBeforeRefuter, card3);
                    solver.addClause(clause);
                }
            }
            // default case: a refuter exists and a card is shown to the player
            //
            // Suppose all six players are playing with the following turn
            // order: Scarlet, Mustard, White, Green, Peacock, Plum. The
            // meaning of the method call suggest("sc", "wh", "pi", "ha", "pe",
            // "ha") is as follows: suggester Miss Scarlet suggested that Mrs.
            // White committed the murder with the lead pipe in the hall
            // (parameters card1, card2, and card3). This was refuted by
            // refuter Mrs. Peacock, who showed Scarlet the hall card
            // (cardShown).
            //
            // Consider that we learn much more than the fact that Mrs. Peacock
            // has the hall card. After Scarlet suggested {wh, pi, ha},
            // all players between Scarlet and the refuter Peacock must have
            // been unable to refute the suggestion. Thus we also learn that
            // these players, Mustard, White, and Green, do not have any of
            // these cards. The knowledge we gain from a suggestion is both
            // negative, which players do not have the suggested cards, and
            // positive, which card a player has.
            else {
                // the refuter definitely has the card
                int[] clause = new int[1];
                clause[0] = getPairNum(refuter, cardShown);
                solver.addClause(clause);

                // The players who couldn't refute don't have any of the cards.
                // So for non-refuting player P, notPC1 AND notPC2 AND notPC3.
                // So 3 separate clauses
                ArrayList<String> playersBeforeRefuter = getPlayersBeforeRefuter(suggester, refuter);
                for (String playerBeforeRefuter : playersBeforeRefuter) {
                    clause = new int[1];
                    clause[0] = -getPairNum(playerBeforeRefuter, card1);
                    solver.addClause(clause);

                    clause = new int[1];
                    clause[0] = -getPairNum(playerBeforeRefuter, card2);
                    solver.addClause(clause);

                    clause = new int[1];
                    clause[0] = -getPairNum(playerBeforeRefuter, card3);
                    solver.addClause(clause);
                }
            }
        }
        // In some cases, there may not be a refuter at all. This is indicated
        // by having the refuter parameter with the value null. (The cardShown
        // parameter should then also be null.) If no player can refute the
        // suggestion, we simply gain information that all players except the
        // suggester do not have the suggested cards. The suggester is never
        // part of the refutation.
        else {
            // all players except the suggester do not have the suggested cards
            // So for player p, notPC1 AND notPC2 AND notPC3 - this player
            // doesn't have any of the 3 cards. An array clause's contents are
            // OR'D together, and arrays as wholes are AND'D together. We want
            // to AND these 3 together, so 3 separate clauses.
            for (String player : players) {
                if (!player.equals(suggester)) {
                    int[] clause = new int[1];
                    clause[0] = -getPairNum(player, card1);
                    solver.addClause(clause);

                    clause = new int[1];
                    clause[0] = -getPairNum(player, card2);
                    solver.addClause(clause);

                    clause = new int[1];
                    clause[0] = -getPairNum(player, card3);
                    solver.addClause(clause);
                }
            }
        }

    }

    /**
     * From suggest(), given a suggester and a refuter, this method accumulates
     * all players in between the suggester and refuter in clockwise order
     * */
    private ArrayList<String> getPlayersBeforeRefuter(String suggester,
                                                      String refuter) {
        ArrayList<String> storage = new ArrayList<String>();
        int suggesterIndex = getPlayerNum(suggester);
        int refuterIndex = getPlayerNum(refuter);
        int iterator = suggesterIndex + 1;
        while (true) {
            if (iterator == refuterIndex) {
                return storage;
            }
            // wrap around clockwise
            else if (iterator >= players.length) {
                iterator = 0;
            } else {
                storage.add(players[iterator]);
                iterator += 1;
            }
        }
    }

    public void accuse(String accuser, String card1, String card2,
                       String card3, boolean isCorrect)
    {
        // TODO

        // Consider the example method call accuse("sc", "pe", "pi", "bi",
        // true). This represents the fact that the accuser Scarlet accused
        // Mrs. Peacock of committing the murder with the pipe in the billiard
        // room, and that this accusation is correct (parameter isCorrect is
        // true). From a correct accusation, we gain knowledge that these three
        // cards (parameters card1, card2, and card3) are in the case file.
        //
        // CFC1 AND CFC2 AND CFC3
        // A single clause OR's its elements together, so we have 3 separate
        // clauses for this case
        if (isCorrect) {
            int[] clause = new int[1];
            clause[0] = getPairNum(caseFile, card1);
            solver.addClause(clause);

            clause = new int[1];
            clause[0] = getPairNum(caseFile, card2);
            solver.addClause(clause);

            clause = new int[1];
            clause[0] = getPairNum(caseFile, card3);
            solver.addClause(clause);
        }
        else {
            // Now consider what happens when the accusation is not correct.
            // Suppose we have the method call accuse("sc", "pe", "pi", "li",
            // false). Then we learn that at least one (>= 1, maybe multiple
            // cards) of the three cards of the accusation is NOT in the case
            // file.
            //
            // notCFCi OR notCFC2 OR notCFC3
            //
            // The contents of a single clause array are OR'D together, so
            // we have one clause containing all 3
            int[] clause = new int[3];
            clause[0] = -getPairNum(caseFile, card1);
            clause[1] = -getPairNum(caseFile, card2);
            clause[2] = -getPairNum(caseFile, card3);
            solver.addClause(clause);
        }
    }

    public int query(String player, String card)
    {
        return solver.testLiteral(getPairNum(player, card));
    }

    public String queryString(int returnCode)
    {
        if (returnCode == SATSolver.TRUE)
            return "Y";
        else if (returnCode == SATSolver.FALSE)
            return "n";
        else
            return "-";
    }

    public void printNotepad()
    {
        PrintStream out = System.out;
        for (String player : players)
            out.print("\t" + player);
        out.println("\t" + caseFile);
        for (String card : cards) {
            out.print(card + "\t");
            for (String player : players)
                out.print(queryString(query(player, card)) + "\t");
            out.println(queryString(query(caseFile, card)));
        }
    }

    public static void main(String[] args)
    {
        ClueReasoner cr = new ClueReasoner();
        String[] myCards = {"wh", "li", "st"};
        cr.hand("sc", myCards);
        cr.suggest("sc", "sc", "ro", "lo", "mu", "sc");
        cr.suggest("mu", "pe", "pi", "di", "pe", null);
        cr.suggest("wh", "mu", "re", "ba", "pe", null);
        cr.suggest("gr", "wh", "kn", "ba", "pl", null);
        cr.suggest("pe", "gr", "ca", "di", "wh", null);
        cr.suggest("pl", "wh", "wr", "st", "sc", "wh");
        cr.suggest("sc", "pl", "ro", "co", "mu", "pl");
        cr.suggest("mu", "pe", "ro", "ba", "wh", null);
        cr.suggest("wh", "mu", "ca", "st", "gr", null);
        cr.suggest("gr", "pe", "kn", "di", "pe", null);
        cr.suggest("pe", "mu", "pi", "di", "pl", null);
        cr.suggest("pl", "gr", "kn", "co", "wh", null);
        cr.suggest("sc", "pe", "kn", "lo", "mu", "lo");
        cr.suggest("mu", "pe", "kn", "di", "wh", null);
        cr.suggest("wh", "pe", "wr", "ha", "gr", null);
        cr.suggest("gr", "wh", "pi", "co", "pl", null);
        cr.suggest("pe", "sc", "pi", "ha", "mu", null);
        cr.suggest("pl", "pe", "pi", "ba", null, null);
        cr.suggest("sc", "wh", "pi", "ha", "pe", "ha");
        cr.suggest("wh", "pe", "pi", "ha", "pe", null);
        cr.suggest("pe", "pe", "pi", "ha", null, null);
        cr.suggest("sc", "gr", "pi", "st", "wh", "gr");
        cr.suggest("mu", "pe", "pi", "ba", "pl", null);
        cr.suggest("wh", "pe", "pi", "st", "sc", "st");
        cr.suggest("gr", "wh", "pi", "st", "sc", "wh");
        cr.suggest("pe", "wh", "pi", "st", "sc", "wh");
        cr.suggest("pl", "pe", "pi", "ki", "gr", null);
        cr.printNotepad();
        cr.accuse("sc", "pe", "pi", "bi", true);
    }
}
