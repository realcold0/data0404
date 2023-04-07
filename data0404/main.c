#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element* data;		// data은 포인터로 정의된다. 
	int capacity;		// 현재 크기
	int top;
} StackType;

// 스택 생성 함수
void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType* s, element item)
{
	if (is_full(s)) {
		s->capacity *= 2;
		s->data =
			(element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		printf("pop -1\n");
		fprintf(stderr, "Stack Empty!\n");
		return;
	}
	else
	{
		return s->data[(s->top)--];
	}
}

// 후위 표기 수식 계산 함수
int eval(char exp[])
{
	int  value, i = 0;
	int op1, op2;
	int len = strlen(exp);
	char ch;
	StackType s;
	
	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		
		if (ch >= '0' && ch <= '9') {
			value = ch - '0';	// 입력이 피연산자이면
			push(&s, value);
		}
		else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {	//연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1  * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
		else {
			//printf("ERROR:Invalid character\n");
			printf("ERROR:Invalid character\n");
			system("pause");
		
		}
	}
	return pop(&s);
}

int main(void)
{
	int result;
	char formu[100]; //입력받는 식
	
	printf("후위표기식은 입력해주세요 : ");
	scanf_s("%s", formu,sizeof(formu));
	
	result = eval(formu);
	printf("결과값은 %d\n", result);
	return 0;
}