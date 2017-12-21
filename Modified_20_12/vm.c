#include "vm.h"
#include "parse.h"

void intepreter()
{
	pc = 0;
	t = -1;
	b = 0;
	printf("\n--------------------- RUN CODE -----------------------\n");
	do
	{
		int p = m_code[pc].p;
		int q = m_code[pc].q;

		//printf("In instruction: %-5d%-5d%-5d\n", m_code[pc].op, p, q);
		//print_instruction(pc);
		switch(m_code[pc].op)
		{
			case OP_LA:
			{
				t ++;
				stack[t] = base(p) + (q + 12) / 4;
				break;
			}
			case OP_LV:
			{
				t ++;
				stack[t] = stack[base(p) + (q + 12) / 4];
				break;
			}
			case OP_LC:
			{
				t ++;
				stack[t] = q;
				break;
			}
			case OP_LI:
			{
				stack[t] = stack[stack[t]];
				break;
			}
			case OP_INT:
			{
				t += q;
				//printf("--t=%d\n", t);
				break;
			} 
			case OP_DCT:
			{
				t -= q;
				//printf("--t=%d\n", t);
				break;
			}
			case OP_J:
			{
				pc = q - 1;
				break;
			}
			case OP_FJ:
			{
				if (stack[t] == 0)
				{
					pc = q - 1;
				}
				t --;
				break;
			}
			case OP_HL:
			{
				break;
			}
			case OP_ST:
			{
				stack[stack[t-1]] = stack[t];
				t = t -2;
				break;
			}
			case OP_CALL:
			{
				stack[t+2] = b;
				stack[t+3] = pc;
				stack[t+4] = base(p);
				b = t + 1;
				pc = q - 1;
				/*
				printf("--Stack[%d]:%d\n", t + 1, stack[t + 1]);
				printf("--Stack[%d]:%d\n", t +2,stack[t + 2]);
				printf("--Stack[%d]:%d\n", t +3,stack[t + 3]);
				printf("--Stack[%d]:%d\n", t+4,stack[t + 4]);
				printf("--Stack[%d]:%d\n", t+5,stack[t + 5]);
				printf("--Stack[%d]:%d\n", t+6,stack[t + 6]);
				printf("--t:%d\n", t);
				printf("--b:%d\n", b);
				printf("--pc:%d\n", pc);
				//*/
				break;
			}
			case OP_EP:
			{
				//printf("t=%d;b-1=%d;pc=%d;stack[b+2]=%d;stack[b+1]=%d\n", t,b-1,pc,stack[b+2], stack[b+1]);
				t = b - 1;
				pc = stack[b + 2];
				b = stack[b + 1];
				break;
			}
			case OP_EF:
			{
				break;
			}
			case OP_RC:
			{
				break;
			}
			case OP_RI:
			{
				char value[100];
				int i_value = -1;
				int i;
				printf("Enter a integer value: ");
				scanf("%s", value);
				for(i = 0; i < strlen(value); i++)
				{
					if ((i == 0) && (value[0] == '-'))
						continue;
					if (!isdigit(value[i]))
					{
						printf("Error: Value must be integer\n");
						exit(-1);
					}
				}

				i_value = atoi(value);
				if ((i_value > 999999) || (i_value < -999999))
				{
					printf("Error: Number is not valid\n");
					exit(-1);
				}
				t ++;
				stack[t] = i_value;
				break;
			}
			case OP_WRC:
			{
				break;
			}
			case OP_WRI:
			{	
				printf("write(%d)\n", stack[t]);
				break;
			}
			case OP_WLN:
			{
				break;
			}
			case OP_ADD:
			{
				t --;
				stack[t] = stack[t] + stack[t+1];
				break;
			}
			case OP_SUB:
			{
				t --;
				stack[t] = stack[t] - stack[t+1];
				break;
			}
			case OP_MUL:
			{
				t --;
				stack[t] = stack[t] * stack[t+1];
				break;
			}
			case OP_DIV:
			{
				t --;
				stack[t] = stack[t] / stack[t+1];
				break;
			}
			case OP_NEG:
			{
				stack[t] = - stack[t];
				break;
			}
			case OP_CV:
			{
				stack[t+1] = stack[t];
				t ++;
				break;
			}
			case OP_EQ:
			{
				t --;
				if (stack[t] == stack[t+1])
				{
					stack[t] = 1;
				}
				else
				{
					stack[t] = 0;
				}
				break;
			}
			case OP_NE:
			{
				t --;
				if (stack[t] != stack[t+1])
				{
					stack[t] = 1;
				}
				else
				{
					stack[t] = 0;
				}
				break;
			}
			case OP_GT:
			{
				t --;
				if (stack[t] > stack[t+1])
				{
					stack[t] = 1;
				}
				else
				{
					stack[t] = 0;
				}
				break;
			}
			case OP_LT:
			{
				t --;
				if (stack[t] < stack[t+1])
				{
					stack[t] = 1;
				}
				else
				{
					stack[t] = 0;
				}
				break;
			}
			case OP_GE:
			{
				t --;
				if (stack[t] >= stack[t+1])
				{
					stack[t] = 1;
				}
				else
				{
					stack[t] = 0;
				}
				break;
			}
			case OP_LE:
			{
				t --;
				if (stack[t] <= stack[t+1])
				{
					stack[t] = 1;
				}
				else
				{
					stack[t] = 0;
				}
				break;
			}
			case OP_BP:
			{
				break;
			}
		}
		//print_stack();
		pc ++;
	} while (m_code[pc].op != OP_HL);

}


int base(int p)
{
	int c = b;
	while (p > 0)
	{
		c = stack[c + 3];
		p --;
	}

	return c;
}

void print_stack()
{
	int i;
	printf("\n------------------STACK-------------------\n");
	for (i = 0; i <= t; i++)
	{
		printf("stack[%d]=%d\n", i,stack[i]);
	}
	printf("-------------------------------------------\n");
}

void print_instruction(int i)
{
	switch (m_code[i].op)
	{
		case OP_LA:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_LV:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LV", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_LC:
		{
			printf("%-5d%-5s%-5d\n", i, "LC", m_code[i].q);
			break;
		}
		case OP_LI:
		{
			printf("%-5d%-5s\n", i, "LI");
			break;
		}
		case OP_INT:
		{
			printf("%-5d%-5s%-5d\n", i, "INT", m_code[i].q);
			break;
		} 
		case OP_DCT:
		{
			printf("%-5d%-5s%-5d\n", i, "DCT", m_code[i].q);
			break;
		}
		case OP_J:
		{
			printf("%-5d%-5s%-5d\n", i, "J", m_code[i].q);
			break;
		}
		case OP_FJ:
		{
			printf("%-5d%-5s%-5d\n", i, "FJ", m_code[i].q);
			break;
		}
		case OP_HL:
		{
			printf("%-5d%-5s\n", i, "HL");
			break;
		}
		case OP_ST:
		{
			printf("%-5d%-5s\n", i, "ST");
			break;
		}
		case OP_CALL:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "CALL", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_EP:
		{
			printf("%-5d%-5s\n", i, "EP");
			break;
		}
		case OP_EF:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_RC:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_RI:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_WRC:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_WRI:
		{
			printf("%-5d%-5s\n", i, "WRI");
			break;
		}
		case OP_WLN:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_ADD:
		{
			printf("%-5d%-5s\n", i, "ADD");
			break;
		}
		case OP_SUB:
		{
			printf("%-5d%-5s\n", i, "SUB");
			break;
		}
		case OP_MUL:
		{
			printf("%-5d%-5s\n", i, "MUL");
			break;
		}
		case OP_DIV:
		{
			printf("%-5d%-5s\n", i, "DIV");
			break;
		}
		case OP_NEG:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}
		case OP_CV:
		{
			printf("%-5d%-5s\n", i, "CV");
			break;
		}
		case OP_EQ:
		{
			printf("%-5d%-5s\n", i, "EQ");
			break;
		}
		case OP_NE:
		{
			printf("%-5d%-5s\n", i, "NE");
			break;
		}
		case OP_GT:
		{
			printf("%-5d%-5s\n", i, "GT");
			break;
		}
		case OP_LT:
		{
			printf("%-5d%-5s\n", i, "LT");
			break;
		}
		case OP_GE:
		{
			printf("%-5d%-5s\n", i, "GE");
			break;
		}
		case OP_LE:
		{
			printf("%-5d%-5s\n", i, "LE");
			break;
		}
		case OP_BP:
		{
			printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
			break;
		}

		default:
		{

		} 
	}
}
