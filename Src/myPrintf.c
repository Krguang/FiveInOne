#include <stdarg.h>   
#include "usart.h"

//#define __DEBUG__

/*
* 将整形数字转换成字符，如 0 转换成 '0'
*/

static char number2char(int num)
{
	char ch;

	switch (num)
	{
	case 0: ch = '0'; break;
	case 1: ch = '1'; break;
	case 2: ch = '2'; break;
	case 3: ch = '3'; break;
	case 4: ch = '4'; break;
	case 5: ch = '5'; break;
	case 6: ch = '6'; break;
	case 7: ch = '7'; break;
	case 8: ch = '8'; break;
	case 9: ch = '9'; break;
	case 10: ch = 'A'; break;
	case 11: ch = 'B'; break;
	case 12: ch = 'C'; break;
	case 13: ch = 'D'; break;
	case 14: ch = 'E'; break;
	case 15: ch = 'F'; break;

	default: ch = '0'; break;
	}

	return ch;
}


/*
* 将整数 ch 按照十进制/十六进制转换成字符
*/
static char * convert_func(char *str, unsigned int ch, int num)
{
	char *pstr = str;
	int ww,qw,bw, sw, gw;
	int hw2,lw2,hw1, lw1;

	switch (num)
	{
	case 10:
		if (ww = ch / 10000)
			*pstr++ = number2char(ww);

		if (qw = (ch / 1000 % 10))
			*pstr++ = number2char(qw);
		else if (ww)
			*pstr++ = number2char(0);

		if (bw = (ch / 100) % 10)
			*pstr++ = number2char(bw);
		else if (qw)
			*pstr++ = number2char(0);

		if (sw = (ch / 10) % 10)
			*pstr++ = number2char(sw);
		else if (bw)
			*pstr++ = number2char(0);

		if (gw = ch % 10)
			*pstr++ = number2char(gw);
		else
			*pstr++ = number2char(0);


		break;
	case 16:
		*pstr++ = '0';
		*pstr++ = 'x';

		if(hw2=ch/0x1000)
			*pstr++ = number2char(hw2);
		
		if(hw2 = (ch / 0x100)%0x10)
			*pstr++ = number2char(hw2);
		else if (hw2)
			*pstr++ = number2char(0);


		if (hw1 = (ch / 0x10)%0x10)
			*pstr++ = number2char(hw1);
		else
			*pstr++ = number2char(0);

		if (lw1 = ch % 0x10)
			*pstr++ = number2char(lw1);
		else
			*pstr++ = number2char(0);

		break;
	default:
		break;
	}


	return pstr;
}


static int my_vsprintf(char *buf, const char *fmt, va_list args)
{
	int i;
	char * str;
	char *s;
	unsigned char ch;


	for (str = buf; *fmt; ++fmt)
	{
		if (*fmt == '\n') // 如果是换行符，转换成回车符+换行符
		{
			*str++ = '\r';
			*str++ = '\n';
			continue;
		}

		if (*fmt != '%') // 如果是'%',保存进str，如果不是，越过取下一个字符，见switch (*fmt)
		{
			*str++ = *fmt;
			continue;
		}

		fmt++;


		switch (*fmt)  // 这样只能解析%c, %s, %x, %X, %d. 像 %02d 这种可以自己扩展
		{
		case 'c':
			*str++ = (unsigned char)va_arg(args, int);  // 返回args所指向参数，然后args指向下一个参数，由va_start(ap,fmt); 将args指向第二个参数，然后逐个往后取，下同
			break;


		case 's':
			s = va_arg(args, char *);
			while (*s != '\0')
				*str++ = *s++;

			break;


		case 'd':
			str = convert_func(str, va_arg(args, int), 10);
			break;

		case 'x':
			str = convert_func(str, va_arg(args, int), 16);
			break;

		default:
			break;
		}
	}

	*str = '\0';

	return str - buf;
}

static void sendstring(unsigned char *string)
{
	while (*string)
	{
		HAL_UART_Transmit(&huart1, string, 1, 0xff);
		string++;
	}
}

void Uart_printf(const char *fmt, ...)
{
#ifdef __DEBUG__
	va_list ap;   //va_list 是一个字符指针，可以理解为指向当前参数的一个指针，取参必须通过这个指针进行
	unsigned char string[128];

	va_start(ap, fmt);//让ap指向可变参数表里面的第一个参数
	my_vsprintf(string, fmt, ap);
	va_end(ap);
	sendstring(string);
#endif
}