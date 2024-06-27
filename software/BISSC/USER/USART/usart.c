#include "usart.h"

int fputc(int ch, FILE *f)
{
 	while((huart1.Instance->SR & 0X40) == 0);
 		huart1.Instance->DR = (unsigned char) ch;      
 return ch;
}
