#include<stdio.h>
#include"custom.h"

int cal(void) {
	double a = 0, b = 0, value = 0;
	char op;

	printf("���� �Է�");
	scanf("%lf %c %lf", &a, &op, &b);

	switch (op)
	{
	default:
		printf("�ùٸ� ��ȣ");
		break;
	case '+':
		value = a + b;
		break;
	case '*':
		value = a * b;
		break;
	case '-':
		value = a - b;
		break;
	case '/':
		value = a / b;

		break;
	}


	printf("%f %c %f = %f",a,op,b,value);
	return 0;
}