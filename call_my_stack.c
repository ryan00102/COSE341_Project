#include<unistd.h>
#include<stdio.h>

#define my_stack_push 335 // os2023_push 시스템 콜을 고유번호로 매핑하는 define
#define my_stack_pop 336 // os2023_pop 시스템 콜을 고유번호로 매핑하는 define

int main(){
	int a = 0;
	
	a = syscall(my_stack_push, 1); //syscall를 사용하여 시스템 콜을 호출
	printf("Push : ");		//stack에 1 push. 
	printf("%d\n", a);
	
	a = syscall(my_stack_push, 1);//syscall를 사용하여 시스템 콜을 호출
	printf("Push : ");		//stack에 1 push. -> 기존 stack에 있던 1와 중복
	printf("%d\n", a);
	
	a = syscall(my_stack_push, 2); //syscall를 사용하여 시스템 콜을 호출
	printf("Push : ");		//stack에 2 push. 
	printf("%d\n", a);
	
	a = syscall(my_stack_push, 3); //syscall를 사용하여 시스템 콜을 호출
	printf("Push : ");		//stack에 3 push.
	printf("%d\n", a);
	
	a = syscall(my_stack_pop); //syscall를 사용하여 시스템 콜을 호출
	printf("Pop : ");		// stack에서 head index 원소를 빼내고 반환함. 
	printf("%d\n", a);
	
	a = syscall(my_stack_pop); //syscall를 사용하여 시스템 콜을 호출
	printf("Pop : ");		// stack에서 head index 원소를 빼내고 반환함. 
	printf("%d\n", a);
	
	a = syscall(my_stack_pop); //syscall를 사용하여 시스템 콜을 호출
	printf("Pop : ");		// stack에서 head index 원소를 빼내고 반환함. 
	printf("%d\n", a);
	
	return 0;
}
