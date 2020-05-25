public class Node {

    public int scratchScore;
    public int totalScore;
    public int numLives;
    public boolean hold;
    public float probability;

    public Node(int lives, int tot_s, int scratch_s, boolean hold, float prob) {
        this.numLives = lives;
        this.totalScore = tot_s;
        this.scratchScore = scratch_s;
        this.hold = hold;
        this.probability = prob;
    }

    public Node(int lives, int tot_s, int scratch_s, float prob) {
        this.numLives = lives;
        this.totalScore = tot_s;
        this.scratchScore = scratch_s;
        this.probability = prob;
    }

    public Node(int lives, int tot_s, int scratch_s) {
        this.numLives = lives;
        this.totalScore = tot_s;
        this.scratchScore = scratch_s;
        this.hold = false;
        this.probability = -1;
    }
}
