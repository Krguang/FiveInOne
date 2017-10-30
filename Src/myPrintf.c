#include <stdarg.h>   
#include "usart.h"

//#define __DEBUG__

/*
* ����������ת�����ַ����� 0 ת���� '0'
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
* ������ ch ����ʮ����/ʮ������ת�����ַ�
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
		if (*fmt == '\n') // ����ǻ��з���ת���ɻس���+���з�
		{
			*str++ = '\r';
			*str++ = '\n';
			continue;
		}

		if (*fmt != '%') // �����'%',�����str��������ǣ�Խ��ȡ��һ���ַ�����switch (*fmt)
		{
			*str++ = *fmt;
			continue;
		}

		fmt++;


		switch (*fmt)  // ����ֻ�ܽ���%c, %s, %x, %X, %d. �� %02d ���ֿ����Լ���չ
		{
		case 'c':
			*str++ = (unsigned char)va_arg(args, int);  // ����args��ָ�������Ȼ��argsָ����һ����������va_start(ap,fmt); ��argsָ��ڶ���������Ȼ���������ȡ����ͬ
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
	va_list ap;   //va_list ��һ���ַ�ָ�룬�������Ϊָ��ǰ������һ��ָ�룬ȡ�α���ͨ�����ָ�����
	unsigned char string[128];

	va_start(ap, fmt);//��apָ��ɱ����������ĵ�һ������
	my_vsprintf(string, fmt, ap);
	va_end(ap);
	sendstring(string);
#endif
}