## Expert Systems ##

+ Open the XML file if you'd like to view the network within the program
+ The .pngs are screenshots of the network and the scenarios

+ Scenario 1
+ Tires is observed to be false. Basic Transportation has P(F) = 1 since the vehicle does not have tires, and no
  vehicle is a useful form of basic transportation without tires. This is in spite of so many other nodes observed as
  true, such as brakes, brakelights, headlights, and even a Start P(T) = 0.92. The Safe Vehicle logically has P(T) = 1
  since without tires, the vehicle cannot be dangerous to the passenger in any way.

+ Scenario 2
+ Brakes is observed to be false. Basic Transportation P(F) = 0.95 - the vehicle does not have brakes, so in all
  likelihood, the vehicle is not a viable form of basic transportation. Safe Vehicle P(F) = 1, since there is no way the
  vehicle is safe without brakes, regardless of observable brakelights, a defroster, wipers, tires, etc.

+ Scenario 3
+ No attempted vehicle theft, but someone dings the door of your parked car. The Alarm P(T) = 0.80 as per the
  probability table, so this makes sense. However, let's say the brakes on the car aren't working, so Brakes is false.
  Brakelights P(T) = 0.93 which makes sense, since the door ding most likely triggers an Alarm P(T) = 0.8, and this
  alarm can trigger the brakelights, but so can working brakes. So, the brakelights will most likely go off even without
  working car brakes just because of the alarm. This brakelights behavior is expected.

## Game Playing ##
+ javac *.java
+ java main

+ There are 26 states where "[0-9]+ 20 [0-9]+ Yes" meaning there are > 0 lives left, a total score of 20, and a scratch
  score < 20. All of these states below have an extremely high chance of resulting in a win if you hold.

5 20 9 Yes 0.940036
3 20 18 Yes 0.962191
3 20 19 Yes 0.972222
3 20 16 Yes 0.929955
3 20 17 Yes 0.948538
3 20 14 Yes 0.870233
3 20 15 Yes 0.904661
4 20 14 Yes 0.953254
4 20 13 Yes 0.939536
4 20 16 Yes 0.981462
4 20 15 Yes 0.970562
4 20 18 Yes 0.992648
4 20 17 Yes 0.988326
4 20 19 Yes 0.995370
4 20 12 Yes 0.923437
4 20 11 Yes 0.905361
5 20 11 Yes 0.962175
5 20 10 Yes 0.951795
5 20 15 Yes 0.990984
5 20 14 Yes 0.984457
5 20 13 Yes 0.978509
5 20 12 Yes 0.971181
5 20 19 Yes 0.999228
5 20 18 Yes 0.998570
5 20 17 Yes 0.997352
5 20 16 Yes 0.995094

+ Winning pays $500, losing pays $0. The initial state is "5 0 0 No 0.504850" so the probabilty of winning is roughly
50%.  0.504850 * 599 = 252.425, so this is the amount I expect to win from this game if I played it once.
