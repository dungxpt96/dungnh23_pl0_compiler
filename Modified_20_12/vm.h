#ifndef _VM_H
#define _VM_H


#define MAX_SIZE_STACK 1000
int stack[MAX_SIZE_STACK];

int b;
int t;
int pc;

void run_code();
void intepreter();
void print_instruction(int pc);
void print_stack();
int base(int p);

#endif