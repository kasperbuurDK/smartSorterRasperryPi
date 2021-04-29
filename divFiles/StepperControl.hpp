//
// Created by kaspe on 16-04-2021.
//

#define FULLCIRCLE 2048
#define HOLES 4
#define STEP_DELAY 2000
#define WAIT_BETWEEN_MOVES 600000

#define Pin1 6
#define Pin2 13
#define Pin3 19
#define Pin4 26

class StepperControl {

public:
    StepperControl();
    int stepForward();
    int getPostionReal();

private:
    int positionCounter;
    int positionReal;
	int step;
    int updatePosition(int value);
	int loop();
};