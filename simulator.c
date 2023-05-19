#include<stdio.h>
#include<stdlib.h>

int address, instruc;
int mem[999] = {0};
int reg[10] = {0};
int pReg, iReg;

void updatePanel(char r[], int value)
{
}

void pause(char msg[])
{
}
void display()
{
	int i;
	printf("P reg  %6.0d       I reg %6.0d\n",pReg,iReg);
	for(i=0;i<=9;i++)
		printf("reg %d	%6d\n",i,reg[i]);
}
         
int cycle()
{
	iReg = mem[pReg];
	display();
	printf("About to Retrieve Instruction:\n");
	//updatePanel("iReg", iReg);
	pReg += 1;
	display();
	printf("About to Execute Instruction :\n");
//	updatePanel("pReg", pReg);

	int opcode = (iReg/10000);
	int r = (iReg/1000) % 10;
	int addr = (iReg) % 1000;

	if(opcode == 0)	return;
	else if(opcode == 1)	reg[r] = mem[addr];
	else if(opcode == 2)	mem[addr] = reg[r];
	else if(opcode == 3)	reg[r] = addr;
	else if(opcode == 4)	reg[r] = mem[reg[addr]];
	else if(opcode == 5)	reg[r] = reg[r] + reg[addr];
	else if(opcode == 6)	reg[r] = reg[r] - reg[addr];
	else if(opcode == 7)	reg[r] = reg[r] * reg[addr];
	else if(opcode == 8)	reg[r] = reg[r] / reg[addr];
	else if(opcode == 10) {
		pReg = addr;
		display();
		//updatePanel("pReg", pReg);
	}
	else if(opcode == 11){
		if(reg[r] == 0) {
			pReg = addr;
			display();
			//updatePanel("pReg", pReg);
		}
	}
//	updatePanel();
	return 1;
}


void loadProgram(char *file)
{
	int i, j;
	char addresss[20], instrucs[20];
	FILE *fil;
	fil = fopen(file, "r");
	if(fil != NULL){
		char lin[150];
		while(fgets(lin, sizeof lin, fil) != NULL){
			if(lin[0] < '0')
				continue;
			i = j = 0;
			while(lin[i] != ' ') {
				addresss[i] = lin[i];
				i++;
			}
			addresss[i] = '\0';
			while(lin[i] == ' ' || lin[i] =='\t' || lin[i] == '\n')
				i++;

			while(lin[i] != ' ') {
				instrucs[j] = lin[i];
				i++;
				j++;
			}
			instrucs[j] = '\0';
			
			address = atoi(addresss);
			instruc = atoi(instrucs);
			printf("%d\t%d\n",address,instruc);
			mem[address] = instruc;
		}
//		for(i = 100; i<220;i++)
//				printf("%d\t%d\n",address,mem[address]);
	}
	fclose(fil);
}

main(int argc, char *argv[])
{
	loadProgram(argv[1]);
//	printf("\033[20;1H\033[0J%s",panel);
	pReg = 100;
	display();
	//updatePanel("pReg", pReg);
	while(1)
		if(!cycle())	break;
	return 0;
}

