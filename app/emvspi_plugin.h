/*
 * emvplug.h
 *
 *  Created on: 2012-8-7
 *      Author: seacles
 */

#ifndef EMVPLUG_H_
#define EMVPLUG_H_

//extern void emvplugin_Init_term_apps(void);

//extern int emvplugin_int_term_capk(void);



extern int emvspi_Init(void);
extern int emvspi_Start(int comm);
extern int emvspi_end(int comm);


#endif /* EMVPLUG_H_ */
