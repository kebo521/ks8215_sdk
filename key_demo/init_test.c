#include <stdio.h>
#include "demo.h"
int inputCallback(int fd, short revents, void *data) {
    struct input_event ev;

    int retval = ev_get_input(fd, revents, &ev);
    if(retval < 0)
        return -1;

    /**Adjust the value to match LCD resolution*/
    //adjustEv(&ev);

    return 0;
}
int main()
{
	ev_init(inputCallback, NULL);

    t_input_running = true;
	while(t_input_running) {
        
		if(!ev_wait(-1))
            ev_dispatch();
    }
}
