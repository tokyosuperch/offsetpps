#include <pigpio.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define LOW 0
#define HIGH 1
#define IN_PORT 20
#define OUT_PORT 21

struct timespec out_ts;
struct timespec timer;
struct timespec sleeptime;

void gettime_out() {
	clock_gettime(CLOCK_REALTIME, &out_ts);  //時刻の取得
	printf("%ld.%09ld\n",out_ts.tv_sec, out_ts.tv_nsec);
}

int main() {
	int ret;
	timer.tv_nsec = 0;
	if (gpioInitialise() < 0) {
		perror("Failed to Initialize");
		return 0;
	}
	if (gpioSetMode(OUT_PORT, PI_OUTPUT) != 0) {
		perror("Failed to Set OUTPUT mode");
		return 1;
	}
	gpioWrite(OUT_PORT, HIGH);
	usleep(1000);
	while (1) {
		clock_gettime(CLOCK_REALTIME, &out_ts);
		if (out_ts.tv_nsec < timer.tv_nsec) {
			gpioWrite(OUT_PORT, LOW);
			gettime_out();
			usleep(1000);
			gpioWrite(OUT_PORT, HIGH);
			// 750ms以内にn.0秒は来ない
			usleep(750000);
		}
		timer.tv_nsec = out_ts.tv_nsec;
	}
	gpioTerminate();
}
