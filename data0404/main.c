#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element* data;		// data�� �����ͷ� ���ǵȴ�. 
	int capacity;		// ���� ũ��
	int top;
} StackType;

// ���� ���� �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
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
// �����Լ�
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

// ���� ǥ�� ���� ��� �Լ�
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
			value = ch - '0';	// �Է��� �ǿ������̸�
			push(&s, value);
		}
		else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {	//�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //������ �����ϰ� ���ÿ� ���� 
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
	char formu[100]; //�Է¹޴� ��
	
	printf("����ǥ����� �Է����ּ��� : ");
	scanf_s("%s", formu,sizeof(formu));
	
	result = eval(formu);
	printf("������� %d\n", result);
	return 0;
}