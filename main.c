#include <stdio.h>
#include <stdlib.h>

#define SIZE 4  // ��Ϸ��Ҫ���������ֵĸ���

/* Exp���ͣ�         �������һ���ɴ�ӡ������ֵ�ı��ʽ����������򵥵ı��ʽ��
 * expression�ֶΣ�  ���ַ�������ʽ�洢���ʽ
 * value�ֶΣ�       ���ʽ��ֵ
 */
typedef struct {
	double value;
	char expression[5 * (SIZE - 1) + SIZE * 2 + 1];  // ���յı��ʽ���Ȳ��ᳬ�� 3 * (SIZE - 1) + SIZE * 2 + 1
} Exp;

/* process24 ���ܣ�
 * �� size �����ʽ֮�����+��-��*��/����
 * ������Լ����24��������������ʽ��������true
 * ����޷������24������false
 */
int process24(Exp* exps, int size) {
	Exp* stack = (Exp*) calloc(size - 1, sizeof(Exp));

	/*
	 * ����ƶ���ֻ��һ���ƣ��ж��Ƿ������Ҫ��Ŀ��
	 */
	if(size == 1) {
		if(exps[0].value == 24) {
			printf( "24 = %s\n", exps[0].expression  );
			return 1;
		} else {
			return 0;
		}
	}

	/*
	* ������������ѭ������size�����ʽ����ѡ����exps[m], exps[n]
	*/
	int m, n, i, t;
	for (m = 0; m < size - 1; m++) {
		for (n = m + 1; n < size; n++) {

			/*
			* �������������ʽ֮��ı��ʽ����stack�С���ʱstack����һ��Exp�Ŀռ�
			*/
			t = 0;
			for (i = 0; i < size; i++) {
				if (i != m && i != n) {
					stack[t].value = exps[i].value;
					sprintf(stack[t].expression, "%s", exps[i].expression);
					t++;
				}
			}

			/*
			* ��ѡ�е��������ʽ���ͺ����stack��
			*/
			stack[size - 2].value = exps[m].value + exps[n].value;
			sprintf(stack[size - 2].expression, "(%s + %s)", exps[m].expression, exps[n].expression);
			if (process24(stack, size - 1)) {
				return 1;
			}

			/*
			* ��ѡ�е��������ʽ��������stack��
			*/
			if (exps[m].value > exps[n].value) {
				stack[size - 2].value = exps[m].value - exps[n].value;
				sprintf(stack[size - 2].expression, "(%s - %s)", exps[m].expression, exps[n].expression);
			}
			else {
				stack[size - 2].value = exps[n].value - exps[m].value;
				sprintf(stack[size - 2].expression, "(%s - %s)", exps[n].expression, exps[m].expression);
			}
			if (process24(stack, size - 1)) {
				return 1;
			}

			/*
			* ��ѡ�е��������ʽ֮������stack��
			*/
			stack[size - 2].value = exps[m].value * exps[n].value;
			sprintf(stack[size - 2].expression, "%s * %s", exps[m].expression, exps[n].expression);
			if (process24(stack, size - 1)) {
				return 1;
			}

			/*
			* ��ѡ�е��������ʽ֮�̷���stack��
			*/
			if (exps[m].value != 0) {
				stack[size - 2].value = exps[n].value / exps[m].value;
				sprintf(stack[size - 2].expression, "%s / %s", exps[n].expression, exps[m].expression);
				if (process24(stack, size - 1)) {
					return 1;
				}
			}
			if (exps[n].value != 0) {
				stack[size - 2].value = exps[m].value / exps[n].value;
				sprintf(stack[size - 2].expression, "%s / %s", exps[m].expression, exps[n].expression);
				if (process24(stack, size - 1)) {
					return 1;
				}
			}
		}
	}

	return 0;  // ������ʱ��û�з��أ���˵���޷������24�����շ���0
}


int main(void) {
	int i, number;
	Exp exps[SIZE];

	for (i = 0; i < SIZE; i++) {
		scanf("%d", &number);
		exps[i].value = (double) number;
		sprintf(exps[i].expression, "%d", number);
	}

	if (process24(exps, SIZE)) {
		printf("Done\n");
	} else {
		printf("No answer, try another 4 numbers.\n");
	}

	return 0;
}
