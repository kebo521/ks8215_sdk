#ifndef  _USART_H
#define  _USART_H
 

int uart_open(char* port);
void uart_close(int fd) ; 
int uart_set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);
int uart_recv(int fd, void *rcv_buf,int data_len,int timeoutMs);
int uart_send(int fd, void *send_buf,int data_len);
 
#endif
