#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/linkage.h>

int stack[100];//stack이라는 integer 배열 생성 stack에 저장할 수 있는 entry의 최대 개수는 100으로 설정
int head = 0;//value가 push되거나 pop되는 배열의 index
int i, j = 0;
int value = 0;//push하거나 pop하는 value


SYSCALL_DEFINE1(os2023_push, int, a){
	
	if (head >= 99) { //stack의 head의 위치가 stack의 맥시멈 사이즈와 같다면 stack이 full인상태
		printk(KERN_INFO "Stack is full\n");
		return -2;
	}
	
	for ( i = 0; i<=head ;i++) {//stack에 내가 지금 넣으려는 값과 중복되는 값이 있는지 확인
		if (a == stack[i])
		{	
			printk(KERN_INFO "[System call] os2023_push : ------\n");//stack 출력
			printk("Stack Top--------------------\n");
			for (i = head; i > 0 ; i--)
				printk("%d\n", stack[i]); 
			printk("Stack Bottom--------------------\n");
			return a;
		}
	}
	stack[++head] = a; //stack에 값 추가

	printk(KERN_INFO "[System call] os2023_push : ------\n");//stack 출력
	printk("Stack Top--------------------\n");
	for (i = head; i > 0 ; i--)
		printk("%d\n", stack[i]); 
	printk("Stack Bottom--------------------\n");
	
	return a;
}

SYSCALL_DEFINE0(os2023_pop){
	
	if (head == 0) { //stack이 비어있는지 확인
		printk(KERN_INFO "Stack is empty\n");
		return -2;
	}
	value = stack[head--]; //stack의 head 인덱스의 값 제거 
	
	printk(KERN_INFO "[System call] os2023_pop : ------\n");//stack 출력
	printk("Stack Top--------------------\n");

	
	for (j = head; j > 0 ; j--)
		printk("%d\n", stack[j]); 
	
	printk("Stack Bottom--------------------\n");

	return value;
}
