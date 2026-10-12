#ifndef USART_H
#define USART_H

#include "main.h"

void usart2_init(void);
void usart2_send_char(char c);
void usart2_send_string(const char *str);
void usart2_send_num(uint32_t num);

#endif
