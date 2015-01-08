#include <stdio.h>
#include <stdlib.h>

#define SIZE 4  // 游戏需要给定的数字的个数

/* Exp类型：         用来表达一个可打印、可求值的表达式（数字是最简单的表达式）
 * expression字段：  以字符串的形式存储表达式
 * value字段：       表达式的值
 */
typedef struct {
	double value;
	char expression[5 * (SIZE - 1) + SIZE * 2 + 1];  // 最终的表达式长度不会超过 3 * (SIZE - 1) + SIZE * 2 + 1
} Exp;

/* process24 功能：
 * 在 size 个表达式之间进行+、-、*、/运算
 * 如果可以计算出24，就输出完整表达式，并返回true
 * 如果无法计算出24，返回false
 */
int process24(Exp* exps, int size) {
	Exp* stack = (Exp*) calloc(size - 1, sizeof(Exp));

	/*
	 * 如果牌堆里只有一张牌，判断是否就是需要的目标
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
	* 接下来的两层循环：从size个表达式中任选两个exps[m], exps[n]
	*/
	int m, n, i, t;
	for (m = 0; m < size - 1; m++) {
		for (n = m + 1; n < size; n++) {

			/*
			* 将除这两个表达式之外的表达式放入stack中。此时stack还有一个Exp的空间
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
			* 将选中的两个表达式做和后放入stack中
			*/
			stack[size - 2].value = exps[m].value + exps[n].value;
			sprintf(stack[size - 2].expression, "(%s + %s)", exps[m].expression, exps[n].expression);
			if (process24(stack, size - 1)) {
				return 1;
			}

			/*
			* 将选中的两个表达式做差后放入stack中
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
			* 将选中的两个表达式之积放入stack中
			*/
			stack[size - 2].value = exps[m].value * exps[n].value;
			sprintf(stack[size - 2].expression, "%s * %s", exps[m].expression, exps[n].expression);
			if (process24(stack, size - 1)) {
				return 1;
			}

			/*
			* 将选中的两个表达式之商放入stack中
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

	return 0;  // 若到此时仍没有返回，则说明无法计算出24，最终返回0
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
