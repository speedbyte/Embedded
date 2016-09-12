/* Choose kind of copter: */
#define Quadro_Plus 1
//#define Quadro_X 1
//#define Okto_Plus 1

int readTestcaseFile(char testcase[] , int length);

int kbhit(void);
int calcPwmValue(char controllChar , int motorNumber, int pwmValue);
extern void sendSensorData();
