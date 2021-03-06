#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct inst
{
	int op;		//0 = no op, 1 = add, 2 = sub, 3 = mult, 4 = beq, 5 = addi, 6 = lw, 7 = sw
	int a;
	int b;
	int c;
}

struct inst IFIDLatch;
struct inst IDEXLatch;
struct inst EXMEMLatch;
struct inst MEMWBLatch;
struct inst *IMem;
int *reg;
int *DMem;
int pc;
int *RAWflag		// = 1 if read is in progress at reg locaion
int branchPending;
int timer;
int IFcount;
int IDcount;
int EXcount;
int MEMcount;
int WBcount;
int mode;	//1 single cycle, 2 batch
int halt;
int c;
int m;
int n;

char *progScanner(string);
struct inst parser(string);
void IF();
void ID();
void EX();
void MEM();
void WB();



int main(void) {
//initialization of memories and variables go here

	DMem = malloc((2048/4)*sizeof(int));
	IMem = malloc((2048/4)*sizeof(struct inst));
	reg = malloc(32*sizeof(int));
	RAWflag = malloc(32*sizeof(int));
	IFIDLatch = {0, 0, 0, 0};
	IDEXLatch = {0, 0, 0, 0};
	EXMEMLatch = {0, 0, 0, 0};
	MEMWBLatch = {0, 0, 0, 0};
	reg[0] = 0;
	branchPending = 0;
	timer = 0;
	IFcount = 0;
	IDcount = 0;
	EXcount = 0;
	MEMcount = 0;
	WBcount = 0;
	printf("enter c \n");
	scanf("%d", &c);
	printf("Enter m \n");
	scanf("%d", &m);
	printf("Enter n \n");
	scanf("%d", &n);
	printf("enter 1 for single cycle, 2 for batch \n")
	scanf("%d", &mode);
	assert(c>0);
	assert(m>0);
	assert(n>0);
	assert((mode==1)||(mode==2));
	while(!halt){
		WB();
		MEM();
		EX();
		ID();
		IF();
		reg[0] = 0;
		timer++;
		if(mode == 2){
			for(int q=0; q<32; q++){
				printf("register %d : %d \n", q, reg[q]])
			}
            printf("pc: %d \n", pc);
			getchar();
		}
	}
	printf("Time: %d \n", timer);
	printf("IF: %d \n", IFcount);
	printf("ID: %d \n", IDcount);
	printf("EX: %d \n", EXcount);
	printf("MEM: %d \n", MEMcount);
	printf("WB: %d \n", WBcount);

}
char *progScanner(){

}
struct inst parser(){

}
void IF(){

}
void ID(){
	static struct inst in = out;
	struct inst in = IFIDLatch;
	out = in;
	switch ( op.in ) {
	case 0:
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		if(RAWflag[b.in]&&RAWflag[c.in]){
			RAWflag[a.in] = 1;
			b.out = reg[b.in];
			c.out = reg[c.in];
			if(IDEXLatch.out == 0){
				IDcount++;
				IDEXLatch = out;
				IFIDLatch.op = 0;
			}
		}
		break;
	case 5:
		if(RAWflag[b.in]){
			b.out = reg[b.in];
			if(IDEXLatch.out == 0){
				IDcount++;
				IDEXLatch = out;
				IFIDLatch.op = 0;
			}
		}
		break;
	case 6:
	case 7:
		if(RAWflag[c.in]{
			c.out = reg[c.in];
			if(IDEXLatch.out == 0){
				IDcount++;
				IDEXLatch = out;
				IFIDLatch.op = 0;
			}
		}
		break;
	default:
		assert(1 != 1);
		break;
	}
}
void EX(){
	static int cycleNumber = 0;
	static struct inst out = in;
	if(cycleNumber = 0){
		struct inst in = IDEXLatch;
		out = in;
		switch ( op.in ) {
		case 0:
			break;
		case 1:
			b.out = b.in + c.in;
			cycleNumber = c;
			EXcount++;
			break;
		case 2:
			b.out = b.in - c.in;
			cycleNumber = c;
			EXcount++;
			break;
		case 3:
			b.out = b.in*c.in;
			cycleNumber = m;
			EXcount++;
			break;
		case 4:

			if(a.in == b.in)
				pc = pc + c.in;
			cycleNumber = n;
			branchPending = 0;
			EXcount++;
			break;
		case 5:
			b.out = b.in + c.in;
			cycleNumber = n;
			EXcount++;
			break;
		case 6:
			b.out = b.in + c.in;
			cycleNumber = n;
			EXcount++;
			break;

		case 7:
			b.out = b.in + c.in;
			cycleNumber = n;
			EXcount++;
			break;
		default:
			assert(1 != 1);
			break;
		}
	}
	else if(cycleNumber ==1){
		if(EXMEMLatch.out == 0){
			EXcount++;
			EXMEMLatch = out;
			IDEXLatch.op = 0;
			cycleNumber--;
		}
	}
	else{
		EXcount++;
		cycleNumber--;
	}
}
void MEM(){
	static int cycleNumber = 0;
	struct inst in = EXMEMLatch
	static struct inst out = in;
	if(cycleNumber == 0){
		switch ( op.in ) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if(MEMWBLatch.op == 0){
				MEMWBLatch = EXMEMLatch;
				EXMEMLatch.op = 0;
			}
			break;
		case 6:
			out = DMem[in.b];
			cycleNumber = c;
			break;
		case 7:
			DMem[in.b] = out;
			break;
		}
	}
	else if(cycleNumber==1){
		MEMWBLatch = out;
		EXMEMLatch.op = 0;
		cycleNumber--;
	}
	else{
		cycleNumber--;
	}
}
void WB(){

	struct inst in = MEMWBLatch;
	switch ( op.in ) {
	case 0:
	case 5:
	case 7:
	op.in = 0;
	break;
	case 1:
	case 2:		
	case 3:
	case 5:
	case 6:
		reg[a.in] = b.in;
		RAWflag[a.in] =0;
		op.in = 0;
		WBcount++;
		break;		
	default:
		assert(1 != 1);
		break;
	}
}

}
