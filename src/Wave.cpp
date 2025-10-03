#include "Wave.h"

Wave::Wave(){
	return;
}

void Wave::Issue(Command task) {
	taskQueue.push(task);
}