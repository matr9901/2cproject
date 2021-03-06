#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
 
FILE * inputs;
 
enum code {
    HALT = 0,
    SYSCALL = 1,
    ADD = 2,
    ADDI = 3,
    SUB = 4,
    SUBI = 5,
    MUL = 6,
    MULI = 7,
    DIV = 8,
    DIVI = 9,
    LC = 12,
    SHL = 13,
    SHLI = 14,
    SHR = 15,
    SHRI = 16,
    AND = 17,
    ANDI = 18,
    OR = 19,
    ORI = 20,
    XOR = 21,
    XORI = 22,
    NOT = 23,
    MOV = 24,
    ADDD = 32,
    SUBD = 33,
    MULD = 34,
    DIVD = 35,
    ITOD = 36,
    DTOI = 37,
    PUSH = 38,
    POP = 39,
    CALL = 40,
    CALLI = 41,
    RET = 42,
    CMP = 43,
    CMPI = 44,
    CMPD = 45,
    JMP = 46,
    JNE = 47,
    JEQ = 48,
    JLE = 49,
    JL = 50,
    JGE = 51,
    JG = 52,
    LOAD = 64,
    STORE = 65,
    LOAD2 = 66,
    STORE2 = 67,
    LOADR = 68,
    LOADR2 = 69,
    STORER = 70,
    STORER2 = 71
};
 
enum type {
    RI = 0,
    RR = 1,
    RM = 2,
    BD = 3
};
 
enum code getCommandCode (char* commandName) {
    char command;
    if (!strcmp(commandName, "halt")) {
        command = 0;
    }
    if (!strcmp(commandName, "syscall")) {
        command = 1;
    }
    if (!strcmp(commandName, "add")) {
        command = 2;
    }
    if (!strcmp(commandName, "addi")) {
        command = 3;
    }
    if (!strcmp(commandName, "sub")) {
        command = 4;
    }
    if (!strcmp(commandName, "subi")) {
        command = 5;
    }
    if (!strcmp(commandName, "mul")) {
        command = 6;
    }
    if (!strcmp(commandName, "muli")) {
        command = 7;
    }
    if (!strcmp(commandName, "div")) {
        command = 8;
    }
    if (!strcmp(commandName, "divi")) {
        command = 9;
    }
    if (!strcmp(commandName, "lc")) {
        command = 12;
    }
    if (!strcmp(commandName, "shl")) {
        command = 13;
    }
    if (!strcmp(commandName, "shli")) {
        command = 14;
    }
    if (!strcmp(commandName, "shr")) {
        command = 15;
    }
    if (!strcmp(commandName, "shri")) {
        command = 16;
    }
    if (!strcmp(commandName, "and")) {
        command = 17;
    }
    if (!strcmp(commandName, "andi")) {
        command = 18;
    }
    if (!strcmp(commandName, "or")) {
        command = 19;
    }
    if (!strcmp(commandName, "ori")) {
        command = 20;
    }
    if (!strcmp(commandName, "xor")) {
        command = 21;
    }
    if (!strcmp(commandName, "xori")) {
        command = 22;
    }
    if (!strcmp(commandName, "not")) {
        command = 23;
    }
    if (!strcmp(commandName, "mov")) {
        command = 24;
    }
    if (!strcmp(commandName, "addd")) {
        command = 32;
    }
    if (!strcmp(commandName, "subd")) {
        command = 33;
    }
    if (!strcmp(commandName, "muld")) {
        command = 34;
    }
    if (!strcmp(commandName, "divd")) {
        command = 35;
    }
    if (!strcmp(commandName, "itod")) {
        command = 36;
    }
    if (!strcmp(commandName, "dtoi")) {
        command = 37;
    }
    if (!strcmp(commandName, "push")) {
        command = 38;
    }
    if (!strcmp(commandName, "pop")) {
        command = 39;
    }
    if (!strcmp(commandName, "call")) {
        command = 40;
    }
    if (!strcmp(commandName, "calli")) {
        command = 41;
    }
    if (!strcmp(commandName, "ret")) {
        command = 42;
    }
    if (!strcmp(commandName, "cmp")) {
        command = 43;
    }
    if (!strcmp(commandName, "cmpi")) {
        command = 44;
    }
    if (!strcmp(commandName, "cmpd")) {
        command = 45;
    }
    if (!strcmp(commandName, "jmp")) {
        command = 46;
    }
    if (!strcmp(commandName, "jne")) {
        command = 47;
    }
    if (!strcmp(commandName, "jeq")) {
        command = 48;
    }
    if (!strcmp(commandName, "jle")) {
        command = 49;
    }
    if (!strcmp(commandName, "jl")) {
        command = 50;
    }
    if (!strcmp(commandName, "jge")) {
        command = 51;
    }
    if (!strcmp(commandName, "jg")) {
        command = 52;
    }
    if (!strcmp(commandName, "load")) {
        command = 64;
    }
    if (!strcmp(commandName, "store")) {
        command = 65;
    }
    if (!strcmp(commandName, "load2")) {
        command = 66;
    }
    if (!strcmp(commandName, "store2")) {
        command = 67;
    }
    if (!strcmp(commandName, "loadr")) {
        command = 68;
    }
    if (!strcmp(commandName, "loadr2")) {
        command = 69;
    }
    if (!strcmp(commandName, "storer")) {
        command = 70;
    }
    if (!strcmp(commandName, "storer2")) {
        command = 71;
    }
    if (!strcmp(commandName, "end")) {
        command = 99;
    }
    return command;
}
 
enum type getCommandType(enum code command) {
    switch (command) {
        case HALT: return BD;
        case SYSCALL: return RI;
        case ADD: return RR;
        case ADDI: return RI;
        case SUB: return RR;
        case SUBI: return RI;
        case MUL: return RR;
        case MULI: return RI;
        case DIV: return RR;
        case DIVI: return RI;
        case LC: return RI;
        case SHL: return RR;
        case SHLI: return RI;
        case SHR: return RR;
        case SHRI: return RI;
        case AND: return RR;
        case ANDI: return RI;
        case OR: return RR;
        case ORI: return RI;
        case XOR: return RR;
        case XORI: return RI;
        case NOT: return RI;
        case MOV: return RR;
        case ADDD: return RR;
        case SUBD: return RR;
        case MULD: return RR;
        case DIVD: return RR;
        case ITOD: return RR;
        case DTOI: return RR;
        case PUSH: return RI;
        case POP: return RI;
        case CALL: return RR;
        case CALLI: return BD;
        case RET: return BD;
        case CMP: return RR;
        case CMPI: return RI;
        case CMPD: return RR;
        case JMP: return BD;
        case JNE: return BD;
        case JEQ: return BD;
        case JLE: return BD;
        case JL: return BD;
        case JGE: return BD;
        case JG: return BD;
        case LOAD: return RM;
        case STORE: return RM;
        case LOAD2: return RM;
        case STORE2: return RM;
        case LOADR: return RR;
        case LOADR2: return RM;
        case STORER: return RR;
        case STORER2: return RR;
        default: return BD;
    }
}
 
char* labels[100];
int* labelsNums;
int labelsCount;
int * stek;
//r->body = calloc(sizeof(int), r->bodysize);
//stek = calloc(sizeof(int), 1024);
unsigned int startCommand = 0;
int clearAsm() {
    FILE* input = fopen("input.fasm", "r");
    FILE* inputJumps = fopen("input_jumps.fasm", "w");
 
    char line[100];
    char commandStek[100];
    int lineNum = 0;
 
    while (fscanf(input, "%[^\n]\n", line) != EOF) {
        int i = 0;
        //int j;
        while ((i < 100) && (line[i] != ';') && (line[i] != ':')) {
            commandStek[i] = line[i];
            i++;
        }
        commandStek[i] = '\0';
 
        //printf("%s %d\n", commandStek, i);
 
        if (i != 0) {
            if (line[i] == ':') {
                labels[labelsCount] = malloc(100 * sizeof(char));
                strcpy(labels[labelsCount], commandStek);
                if ((labelsCount % 10) == 0) {
                    labelsNums = (int*) realloc(labelsNums, (labelsCount + 10) * sizeof(int));
                }
                labelsNums[labelsCount] = lineNum - labelsCount;
                labelsCount++;
            }
            lineNum++;
        }
    }
   
    fseek(input, 0L, SEEK_SET);
 
    while (fscanf(input, "%[^\n]\n", line) != EOF) {
        int i = 0;
        int j;
        while ((i < 100) && (line[i] != ';') && (line[i] != ':')) {
            commandStek[i] = line[i];
            i++;
        }
        commandStek[i] = '\0';
        //printf("%s %d\n", commandStek, i);
 
        if (i != 0) {
            if (line[i] != ':') {
                char command[10];
                char second[10];
                sscanf(commandStek, "%s %s", command, second);
                int commandCode = getCommandCode(command);
                if (((commandCode >= 46) && (commandCode <= 52)) || !strcmp(command, "end") || !strcmp(command, "call") || !strcmp(command, "calli")) {
                    for (j = 0; j < labelsCount; j++) {
                        if (!strcmp(labels[j], second)) {
                            fprintf(inputJumps, "%s %d\n", command, labelsNums[j]);
                            if (!strcmp(command, "end"))
                                startCommand = labelsNums[j];
                            break;
                        }
                    }
                } else {
                    fprintf(inputJumps, "%s\n", commandStek);
                }
            }
        }
    }      
    fclose(input);
    fclose(inputJumps);
    return 0;
}
 
 
unsigned int rr(char* line) {
    char* command;
    int reg1;
    int reg2;
    short int num;
   
    sscanf (line, "%ms r%d r%d %hd", &command, &reg1, &reg2, &num);
    int commandCode = getCommandCode(command);
    unsigned int res;
    res = commandCode << 24;
    res += reg1 << 20;
    res += reg2 << 16;
    res += num;
    free(command);
    return res;
}
 
unsigned int ri(char* line) {
    char* command;
    int reg1;
    int num;
   
    sscanf (line, "%ms r%d %d", &command, &reg1, &num);
    int commandCode = getCommandCode(command);
    unsigned int res;
    res = commandCode << 24;
    res += reg1 << 20;
    res += num & ((2 << 20) - 1);
    free(command);
    return res;
}
 
unsigned int rm(char* line) {
    char* command;
    int reg1;
    int num;
   
    sscanf (line, "%ms r%d %u", &command, &reg1, &num);
    int commandCode = getCommandCode(command);
    unsigned int res;
    res = commandCode << 24;
    res += reg1 << 20;
    res += num & ((2 << 20) - 1);
    free(command);
    return res;
}
unsigned int bd (char* line) {
    char* command;
    int num;
 
    sscanf (line, "%ms %u", &command, &num);
    int commandCode = getCommandCode(command);
    unsigned int res;
    res = commandCode << 24;
    res += num & ((2<<24) - 1);
    free(command);
    return res;
}

unsigned int end_command (char* line) {
    char* command;
    int num;
 
    sscanf (line, "%ms %u", &command, &num);
    return num;
}
 
int assembler() {
    FILE* input;
    FILE* output;
    input = fopen("input_jumps.fasm", "r");
    output = fopen("output.o", "w");
 
    int i = 0;
    char line[100];
    int mask = 255;
    unsigned int commandWithArgs = 0;
    //fseek(output, 0L, SEEK_SET);
    fprintf(output, "ThisIsFUPM2Exec%c", '\0'); // 16 byte
    fprintf(output, "%c%c%c%c", '\1', '\0', '\0', '\0'); // 4 byte
    fprintf(output, "%c%c%c%c", '\1', '\0', '\0', '\0'); // 4 byte
    fprintf(output, "%c%c%c%c", '\1', '\0', '\0', '\0'); // 4 byte
    //4 byte
    fprintf(output, "%c%c%c%c", (startCommand) & mask, (startCommand >> 8) & mask, (startCommand >> 16) & mask, (startCommand >> 24) & mask);
    fprintf(output, "%c%c%c%c", '\1', '\0', '\0', '\0'); // 4 byte
    for (i = 0; i < 476; i++)
        fprintf(output, "%c", '\0'); // up to 512 byte
    //fseek(output, 512L, SEEK_SET);
    while (fscanf(input, "%[^\n]\n", line) != EOF) {
        char command[10];
        enum code commandCode;
        enum type commandType;
 
        sscanf(line, "%s", command);
        commandCode = getCommandCode(command);
        commandType = getCommandType(commandCode);
        if (commandCode == 99) {
            startCommand = end_command(line);
            continue;
        }
        switch (commandType) {
            case RI:
                commandWithArgs = ri(line);
                break;
            case RM:
                commandWithArgs = rm(line);
                break;
            case RR:
                commandWithArgs = rr(line);
                break;
            case BD:
                commandWithArgs = bd(line);
                break;
        }
 
        fprintf(output, "%c%c%c%c", commandWithArgs & mask, (commandWithArgs >> 8) & mask, (commandWithArgs >> 16) & mask, (commandWithArgs >> 24) & mask);
    }
    
    fclose(input);
    fclose(output);
    return 0;
}
 
 
int reg[17];
int * memory;
int * memory2;
int m_pointer = 0;
//int * stek;
 
int trans_ri(char a, char b, char c, int* r, int* df){
    *r = (c & 240) >> 4;
    *df = ((c & 15) << 16) + (b << 8) + a;
    return 0;
 
}

int trans_rr(char a, char b, char c, int* r, int* l, int* df){
    *r = (c & 240) >> 4;
    *l = (c & 15);
    *df = (b << 8) + a;
    //printf("%d %d %d\n", *r, *l, *df);
    return 0;
}
int trans_rm(char a, char b, char c, int* r, unsigned* un){
    *r = (c & 240) >> 4;
    *un = ((c&15)  << 16) + (b << 8) + a;
    return 0;
}
int trans_bd(char a, char b, char c, unsigned* un){
    *un = (c << 16) + (b << 8) + a;
    return 0;
 
}
int halt(unsigned un){
    fclose(inputs);
    exit(0);
}
int syscall_fupm(int r, int df){
    int t = 1;
    int k = 0;
    char name[260];
    //void * buf;
    //int len;
    switch (df){
        case 0:
            fclose(inputs);
            exit(reg[r]);
            break;
        case 1:
            while (t){
                char c[4];
                c[0] = (char) (stek[reg[14]-1] >> 24);
                c[1] = (char)((stek[reg[14]-1] >> 16) & 255);
                c[2] = (char)((stek[reg[14]-1] >> 8)& 255);
                c[3] = (char)((stek[reg[14]-1] & 255));
                reg[14]--;
                int i = 0;
                while (c[i]!= '\0'){
                    name[k+i] = c[i];
                    i++;
                }
                if (c[i]== '\0'){
                    name[k+i] = c[i];
                    t = 0;
                }
                k += 4;
            }
            int mode = stek[reg[14]-1];
            reg[14]--;
            int file = open(name, mode, O_CREAT);
            reg[r] = file;
            break;
        case 2:
            /*while (t){
                char c[4];
                c[0] = (char)((stek[reg[14]-1] >> 24));
                c[1] = (char)((stek[reg[14]-1] >> 16) & 255);
                c[2] = (char)((stek[reg[14]-1] >> 8)& 255);
                c[3] = (char)((stek[reg[14]-1] & 255));
                reg[14]--;
                int i = 0;
                while (c[i]!= '\0'){
                    name[k+i] = c[i];
                    i++;
                }
                if (c[i]== '\0'){
                    name[k+i] = c[i];
                    t = 0;
                }
                k += 4;
            }
            buf = (void *)(reg[r]);
            len = stek[reg[14]-1];
            reg[14]--;
            read(name, buf, len);*/
            break;
        case 3:/*
            while (t){
                char c[4];
                c[0] = (char)((stek[reg[14]-1] >> 24));
                c[1] = (char)((stek[reg[14]-1] >> 16) & 255);
                c[2] = (char)((stek[reg[14]-1] >> 8)& 255);
                c[3] = (char)((stek[reg[14]-1] & 255));
                reg[14]--;
                int i = 0;
                while (c[i]!= '\0'){
                    name[k+i] = c[i];
                    i++;
                }
                if (c[i]== '\0'){
                    name[k+i] = c[i];
                    t = 0;
                }
                k += 4;
            }
            buf = (void *)(reg[r]);
            len = stek[reg[14]-1];
            reg[14]--;
            write(name, buf, len);*/
            break;
        case 4: 
            //close(reg[r]);
            break;
        case 5:
            //int size = reg[r];
            //reg[r] = malloc(reg[r]);
            break;
        case 6: 
            //free(&reg[r]);
            break;
        case 100: 
            scanf("%d", &reg[r]);
            break;
        case 101: 
            scanf("%d%d", &reg[r], &reg[r+1]);
            break;
        case 102: 
            printf("%d", reg[r]);
            break;
        case 103: 
            printf("%d%d", reg[r], reg[r+1]);
            break;
        case 104: 
            reg[r] = getchar();
            break;
        case 105: 
            putchar((char)(reg[r]));
            break;
        default:
            break;
    }
    return 0;
}
 
int add(int r, int l, int df){
    int var = reg[l] + df;
    reg[r] += var;
    return 0;
}
int addi(int r, int df){
    reg[r] += df;
    return 0;
}
int sub(int r, int l, int df){
    int var = reg[l] + df;
    reg[r] -= var;
    return 0;
}
int subi(int r, int df){
    reg[r] -= df;
    return 0;
}
int mul(int r, int l, int df){
    int first = reg[r];
    int second = reg[l];
    long long var = first * second;
    reg[r + 1] = (int)(var >> 32);
    reg[r] = (int)(var & 4294967295);
    return 0;
}
int muli(int r, int df){
    int first = reg[r];
    long long var = first * df;
    reg[r + 1] = (int)(var >> 32);
    reg[r] = (int)(var & 4294967295);
    return 0;
}
int divn(int r, int l, int df){
    long long var = ((long long)reg[r+1] << 32) + reg[r];
    int del = reg[l];
    int ost = var % del;
    int res = var / del;
    reg[r] = (int)(res);
    reg[r + 1] = (int)(ost);
    return 0;
}
int divi(int r, int df){
    long long var = ((long long)reg[r+1] << 32) + reg[r];
    int del = df;
    int ost = var % del;
    int res = var / del;
    reg[r] = (int)(res);
    reg[r + 1] = (int)(ost);
    return 0;
}
int lc(int r, int df){
    reg[r] = df;
    return 0;
}
int shl(int r, int l, int df){
    reg[r] <<= reg[l];
    return 0;
}
int shli(int r, int df){
    reg[r] <<= df;
    return 0;
}
int shr(int r, int l, int df){
    reg[r] >>= reg[l];
    return 0;
}
int shri(int r, int df){
    reg[r] >>= df;
    return 0;
}
int and(int r, int l, int df){
    reg[r] &= reg[l];
    return 0;
}
int andi(int r, int df){
    reg[r] &= df;
    return 0;
}
int or(int r, int l, int df){
    reg[r] |= reg[l];
    return 0;
}
int ori(int r, int df){
    reg[r] |= df;
    return 0;
}
int xor(int r, int l, int df){
    reg[r] ^= reg[l];
    return 0;
}
int xori(int r, int df){
    reg[r] ^= df;
    return 0;
}
int not(int r, int df){
    reg[r] = !reg[r];
    return 0;
}
int mov(int r, int l, int df){
    reg[r] = reg[l] + df;
    //printf("%d %d %d\n", r, l, df);
    return 0;
}
int addd(int r, int l, int df){
    int r_deg = ((reg[r] >> 21) & 1023);
    int l_deg = ((reg[r] >> 21) & 1023);
    unsigned long r_l = (unsigned long)(reg[r]);
    unsigned long r_1 = (unsigned long)(reg[r + 1]);
    unsigned long l_1 = (unsigned long)(reg[l + 1]);
    unsigned long l_l = (unsigned long)(reg[l]);
    char r_sign = (reg[r] >> 31);
    char l_sign = (reg[l] >> 31);
    unsigned long long r_int = ((r_l & 2097151) << 32) + r_1 + ((long long)1 << 54);
    unsigned long long l_int = ((l_l & 2097151) << 32) + l_1 + ((long long)1 << 54);
    if (r_deg > l_deg){
        while (l_deg != r_deg){
            l_deg ++;
            l_int >>= 1;
            if (l_int == 0){
                return 0;
            }
        }
    }
    else {
        while (l_deg != r_deg){
            r_deg ++;
            r_int >>= 1;
            if (r_int == 0){
                if (((r_sign) ^ (l_sign)) == 1) {
                    reg[r] = reg[l];
                    reg[r + 1] = reg[l + 1];
                    return 0;
                }
                else {
                    reg[r] = reg[l] ^ (1 << 31);
                    reg[r + 1] = reg[l + 1];
 
                }
            }
        }
    }
    if (((r_sign) ^ (l_sign)) == 0) {
        r_int += l_int;
    }
    else {
        if (r_int > l_int){
            r_int -= l_int;
        }
        else {
            r_int = l_int - r_int;
            r_sign = l_sign;
        }
    }
    r_deg += 10; //не уверен
    while ((r_int >> 63)!=1){
        r_int <<= 1;
        r_deg --;
    }
    r_int <<= 1;
    r_deg --;
 
    reg[r]=(int)((r_sign << 31) + (r_deg << 21) + ((r_int & 2097151) >> 43));  //Поменял немного скобки вроде на правильные
    reg[r + 1] = (int)(r_int >> 11);
    return 0;
}
int subd(int r, int l, int df){ //не работает на разных знаках пока как и сложение.
    int r_deg = ((reg[r] >> 21) & 1023);
    int l_deg = ((reg[r] >> 21) & 1023);
    unsigned long r_l = (unsigned long)(reg[r]);
    unsigned long r_1 = (unsigned long)(reg[r + 1]);
    unsigned long l_1 = (unsigned long)(reg[l + 1]);
    unsigned long l_l = (unsigned long)(reg[l]);
    char r_sign = (reg[r] >> 31);
    char l_sign = (reg[l] >> 31);
    unsigned long long r_int = ((r_l & 2097151) << 32) + r_1 + ((long long)1 << 54);
    unsigned long long l_int = ((l_l & 2097151) << 32) + l_1 + ((long long)1 << 54);
    if (r_deg > l_deg){
        while (l_deg != r_deg){
            l_deg ++;
            l_int >>= 1;
            if (l_int == 0){
                return 0;
            }
        }
    }
    else {
        while (l_deg != r_deg){
            r_deg ++;
            r_int >>= 1;
            if (r_int == 0){
                if (((r_sign) ^ (l_sign)) == 1) {
                    reg[r] = reg[l];
                    reg[r + 1] = reg[l + 1];
                    return 0;
                }
                else {
                    reg[r] = reg[l] ^ (1 << 31);
                    reg[r + 1] = reg[l + 1];
 
                }
            }
        }
    }
    if (((r_sign) ^ (l_sign)) == 1) {
        r_int += l_int;
    }
    else {
        if (r_int > l_int){
            r_int -= l_int;
        }
        else {
            r_int = l_int - r_int;
            r_sign = l_sign;
        }
    }
    r_deg += 10; //не уверен
    while ((r_int >> 63)!=1){
        r_int <<= 1;
        r_deg --;
    }
    r_int <<= 1;
    r_deg --;
 
    reg[r]=(int)((r_sign << 31) + (r_deg << 21) + ((r_int & 2097151) >> 43));
    reg[r + 1] = (int)(r_int >> 11);
    return 0;
}
int muld(int r, int l, int df){
    int r_deg = ((reg[r] >> 21) & 1023);
    int l_deg = ((reg[r] >> 21) & 1023);
    char r_sign = (reg[r] >> 31);
    char l_sign = (reg[l] >> 31);
    int r_int = (reg[r] & 2097151) + (1 << 22);
    int r_int1 = reg[r + 1];
    int l_int = (reg[l] & 2097151) + (1 << 22);
    int l_int1 = reg[l + 1];
    unsigned long long res_1 = r_int * l_int;
    unsigned long long res_2 = r_int * l_int1;
    unsigned long long res_3 = r_int1 * l_int;
    unsigned long long res_4 = ((long long)r_int1 * (long long)l_int1) >> 32;
    unsigned long long res_5 = res_4 + res_3;
    int m, n;
    if (res_5 < res_4 || res_5 < res_3) {m = 1;}
    else {m = 0;}
    unsigned long long res_6 = res_5 + res_2;
    if (res_5 < res_4 || res_5 < res_3) {n = 1;}
    else {n = 0;}
    unsigned long long res_7 = (res_6 >> 32)+ n + m + res_1;
    int f = 63;
    while (((1 << f) & res_7) == 0){
        f--;
    }
    f--;
    r_sign = r_sign ^ l_sign;
    r_deg += l_deg;
    r_deg &= 1024;
    reg[r] = (int)((r_sign << 31) + (r_deg << 21) + (res_7 >> (41 -f-64 + 2*f)));
    reg[r+1] = (int)(res_7 >> (11 - f-64 + 2*f));
    return 0;
}
int divd(int r, int l, int df){
    int r_deg = ((reg[r] >> 21) & 1023);
    int l_deg = ((reg[r] >> 21) & 1023);
    unsigned long r_l = (unsigned long)(reg[r]);
    unsigned long r_1 = (unsigned long)(reg[r + 1]);
    unsigned long l_1 = (unsigned long)(reg[l + 1]);
    unsigned long l_l = (unsigned long)(reg[l]);
    char r_sign = (reg[r] >> 31);
    char l_sign = (reg[l] >> 31);
    unsigned long long r_int = ((r_l & 2097151) << 32) + r_1 + ((long long)1 << 54);
    unsigned long long l_int = ((l_l & 2097151) << 32) + l_1 + ((long long)1 << 54);
    unsigned long long res = r_int/l_int;
    r_int /= l_int;
    int f = 63;
    while (((1 << f) & res) == 0){
        f--;
    }
    while (f < 52){
        f++;
        r_int <<= 1;
        res <<= 1;
        r_deg -=1;
        res +=(r_int/l_int);
    }
    if ((r_sign ^ l_sign)==1) r_sign =1;
    reg[r]=(int)((r_sign << 31) + ((r_deg - l_deg) << 21) + (((r_int & 2097151) >> 43)));
    reg[r + 1] =(int)(r_int >> 11);
    return 0;
}
 
//int *stek;
 
/*int **///commandstek = malloc(sizeof(int) * 1024);
int * commandstek;
int CommandStekNumber = 0;
int jumpPoint = -1;

int itod(int r, int l, int n){
    int r_sign;
    if (reg[r]< 0) r_sign = 1;
    else r_sign = 0;
    int r_deg = 31;
    unsigned r_body = reg[l] & (((unsigned)1 << 31) - 1);
    while ((r_body >> 31) !=0){
        r_deg --;
        r_body <<= 1;
    }
    unsigned long long r_int = (r_body << 23);
    reg[r]=(int)((r_sign << 31) + (r_deg << 21) + (((r_int & 2097151) >> 43)));
    reg[r + 1] =(int)(r_int >> 11);
    return 0;
}
 
int dtoi(int r, int l, int n){
    int l_deg = ((reg[r] >> 21) & 1023);
    unsigned long l_1 = (unsigned long)(reg[l + 1]);
    unsigned long l_l = (unsigned long)(reg[l]);
    char l_sign = (reg[l] >> 31);
    unsigned long long l_int = ((l_l & 2097151) << 32) + l_1 + ((long long)1 << 54);
    if ((l_deg - 511) >= 31) return 1;
    else if ((l_deg - 511) <0){
        reg[r] = 0;
        return 0;
    }
    reg[r] = (int)((l_sign << 31) + (l_int >> (23 + 32 - 511 + l_deg)));
    return 0;
}
 
int push(int r, int n){
    stek[reg[14]] = reg[r] + n;
    reg[14]++;
    return 0;
}
 
int pop(int r, int n){
    if (reg[14]<=0) return 1;
    reg[14]--;
    reg[r] = stek[reg[14]] + n;
    return 0;
}
 
int call(int r, int l, int n){
    commandstek[CommandStekNumber] = reg[15];
    CommandStekNumber++;
    reg[r] = reg[15];
    reg[15] = reg[l] + n;
    jumpPoint = reg[15];
    return 0;
}
 
int calli(unsigned int n){
    commandstek[CommandStekNumber] = reg[15];
    CommandStekNumber++;
    reg[15] = n;
    jumpPoint = n;
    return 0;
}
 
int ret(unsigned int n){
    reg[15] = commandstek[CommandStekNumber-1] + n;
    CommandStekNumber--;
    jumpPoint = reg[15];
    return 0;
}
 
// flags: reg[16]
// 0 - флаг переноса (переполнение при сложении для беззнаковых);
// 1 - флаг переполнения (для знаковых);
// 2 - флаг четности (четное число битов равных 1);
// 3 - флаг полупереноса (перенос из 3 бита в 4);
// 4 - флаг нуля();
// 5 - флаг знака (старший бит результата);
 
 
int cmp(int r1, int r2, int n){
    reg[16] = 0;
    if (reg[r1] < reg[r2]){
        reg[16] += 16;
    }
    else if (reg[r1] == reg[r2]){
        reg[16] += 8;
    }
    return 0;
}
 
int cmpi(int r, int n){
    reg[16] = 0;
    if (reg[r] < n){
        reg[16] += 16;
    }
    else if (reg[r] == n){
        reg[16] += 8;
    }
    return 0;
}
 
int cmpd(int r, int l, int df){
    reg[16] = 0;
    int r_deg = ((reg[r] >> 21) & 1023);
    int l_deg = ((reg[r] >> 21) & 1023);
    unsigned long r_l = (unsigned long)(reg[r]);
    unsigned long r_1 = (unsigned long)(reg[r + 1]);
    unsigned long l_1 = (unsigned long)(reg[l + 1]);
    unsigned long l_l = (unsigned long)(reg[l]);
    char r_sign = (reg[r] >> 31);
    char l_sign = (reg[l] >> 31);
    unsigned long long r_int = ((r_l & 2097151) << 32) + r_1 + ((long long)1 << 54);
    unsigned long long l_int = ((l_l & 2097151) << 32) + l_1 + ((long long)1 << 54);
    if ((r_sign ^ l_sign)== 1){
        if (r_sign == 1){
            reg[16] = 16;
        }
    }
    else {
        if (r_deg == l_deg){
            if(r_int == l_int){
                reg[16] = 8;
            }
            else if(((r_int < l_int) & (r_int == 1))||((r_int > l_int) & (r_int == 0))){
                reg[16] = 16;
            }
        }
        else if (((r_deg < l_deg) & (r_int == 1))||((r_deg > l_deg) & (r_int == 0))){
            reg[16] = 16;
        }
    }
    return 0;
}
int jmp(unsigned int n){
    reg[15] = n;
    jumpPoint = n;
    return 0;
}
 
int jne(unsigned int n){
    if ((reg[16] & 8) == 0){
        reg[15] = n;
        jumpPoint = n;
    }
    return 0;
}
 
int jeq(unsigned int n){
    if ((reg[16] & 8) == 8){
        reg[15] = n;
        jumpPoint = n;
    }
    return 0;  
}
 
int jle(unsigned int n){
    if (((reg[16] & 8) == 8) || ((reg[16] & 16) == 16)){
        reg[15] = n;
        jumpPoint = n;
    }
    return 0;
}
 
int jl(unsigned int n){
    if (((reg[16] & 8) != 8) && ((reg[16] & 16) == 16)){
        reg[15] = n;
        jumpPoint = n;
    }
    return 0;  
}
 
int jge(unsigned int n){
    if (((reg[16] & 8) == 8) || ((reg[16] & 16) != 16)){
        reg[15] = n;
        jumpPoint = n;
    }
    return 0;
}
 
int jg(unsigned int n){
    if (((reg[16] & 8) != 8) && ((reg[16] & 16) != 16)){
        reg[15] = n;
        jumpPoint = n;
    }
    return 0;  
}
int m_find(int n){
    int fd = 0;
    int hg = 0;
    while (n != memory2[fd] && fd < m_pointer){
        fd ++;
        if (n == memory2[fd]) hg = fd;
    }
    return hg;
}

 
int store(int r, unsigned n){
    memory[m_pointer] = reg[r];
    memory2[m_pointer] = n;
    m_pointer ++;
    return 0;
}
 
int load (int r, unsigned n){
    reg[r] = memory[m_find(n)];
    return 0;
}
 
int load2(int r, unsigned n){
    reg[r] = memory[m_find(n)];
    reg[r+1] = memory[m_find(n)+1];
    return 0;
}
 
int store2(int r, unsigned n){
    memory[m_pointer] = reg[r];
    memory2[m_pointer] = n;
    m_pointer ++;
    memory[m_pointer] = reg[r+1];
    memory2[m_pointer] = n+1;
    return 0;
}
 
int loadr(int r1, int r2, int n){
    if (r2 == 14){
        if (reg[14]<=0) return 1;
        reg[14]-= n;
        reg[r1] = stek[reg[14]];
        return 0;
    }   
    reg[r1] = memory[m_find(reg[r2] + n)];
    return 0;
}
 
int storer(int r1, int r2, int n){
    memory[m_pointer] = reg[r1];
    memory2[m_pointer] = n + reg[r2];
    m_pointer ++;
    return 0;
}
 
int loadr2(int r1, int r2, int n){
    reg[r1] = memory[m_find(n + reg[r2])];
    reg[r1+1] = memory[m_find(n + reg[r2])+1];
    return 0;
}
 
int storer2(int r1, int r2, int n){
    memory[m_pointer] = reg[r1];
    memory2[m_pointer] = n + reg[r2];
    m_pointer ++;
    memory[m_pointer] = reg[r1 + 1];
    memory2[m_pointer] = n + reg[r2] + 1;
    return 0;
}            

int debug () {
    int i;
    printf("regs: ");
    for (i = 0; i < 17; i++) {
        printf("%d ", reg[i]);
    }
    printf("\n");
    printf("stack: ");
    for (i = 0; i < reg[14]; i++) {
        printf("%d ", stek[i]);
    }
    printf("\n");
    printf("comandstack: ");
    for (i = 0; i < CommandStekNumber; i++) {
        printf("%d ", commandstek[i]);
    }

    printf("\n");
    return 0;
}


int interpreter(){
    inputs = fopen("output.o", "r");
    char a, b, c, d;
    int start;
    int r, l, df;
    //char* line[100];
    unsigned un;
    fseek(inputs, 28 ,SEEK_SET);
    fscanf(inputs, "%c%c%c%c", &a, &b, &c, &d);
    start = (d << 24) + (c << 16) + (b << 8) + a;
    reg[15] = start;
    fseek(inputs, 512 + (start * 4), SEEK_SET);
    //debug();
    while(fscanf(inputs,"%c%c%c%c", &a, &b, &c, &d) != EOF) {
        jumpPoint = -1;
        switch(d){
            case HALT:
                trans_bd(a, b, c, &un);
                halt(un);
                break;
            case SYSCALL:
                trans_ri(a, b, c, &r, &df);
                syscall_fupm(r, df);
                break;
            case ADD:
                trans_rr(a, b, c, &r, &l, &df);
                add(r, l, df);
                break;
            case ADDI:
                trans_ri(a, b, c, &r, &df);
                addi(r, df);
                break;
            case SUB:
                trans_rr(a, b, c, &r, &l, &df);
                sub(r, l, df);
                break;
            case SUBI:
                trans_ri(a, b, c, &r, &df);
                subi(r, df);
                break;
            case MUL:
                trans_rr(a, b, c, &r, &l, &df);
                mul(r, l, df);
                break;
            case MULI:
                trans_ri(a, b, c, &r, &df);
                muli(r, df);
                break;
            case DIV:
                trans_rr(a, b, c, &r, &l, &df);
                divn(r, l, df);
                break;
            case DIVI:
                trans_ri(a, b, c, &r, &df);
                divi(r, df);
                break;
            case LC:
                trans_ri(a, b, c, &r, &df);
                lc(r, df);
                break;
            case SHL:
                trans_rr(a, b, c, &r, &l, &df);
                shl(r, l, df);
                break;
            case SHLI:
                trans_ri(a, b, c, &r, &df);
                shli(r, df);
                break;
            case SHR:
                trans_rr(a, b, c, &r, &l, &df);
                shr(r, l, df);
                break;
            case SHRI:
                trans_ri(a, b, c, &r, &df);
                shri(r, df);
                break;
            case AND:
                trans_rr(a, b, c, &r, &l, &df);
                and(r, l, df);
                break;
            case ANDI:
                trans_ri(a, b, c, &r, &df);
                andi(r, df);
                break;
            case OR:
                trans_rr(a, b, c, &r, &l, &df);
                or(r, l, df);
                break;
            case ORI:
                trans_ri(a, b, c, &r,&df);
                ori(r, df);
                break;
            case XOR:
                trans_rr(a, b, c, &r,&l, &df);
                xor(r, l, df);
                break;
            case XORI:
                trans_ri(a, b, c, &r,&df);
                xori(r, df);
                break;
            case NOT:
                trans_ri(a, b, c, &r,&df);
                not(r, df);
                break;
            case MOV:
                trans_rr(a, b, c, &r, &l, &df);
                mov(r, l, df);
                break;
            case ADDD:
                trans_rr(a, b, c, &r,&l, &df);
                addd(r, l, df);
                break;
            case SUBD:
                trans_rr(a, b, c, &r,&l, &df);
                subd(r, l, df);
                break;
            case MULD:
                trans_rr(a, b, c, &r,&l, &df);
                muld(r, l, df);
                break;
            case DIVD:
                trans_rr(a, b, c, &r,&l, &df);
                divd(r, l, df);
                break;
            case ITOD:
                trans_rr(a, b, c, &r,&l, &df);
                itod(r, l, df);
                break;
            case DTOI:
                trans_rr(a, b, c, &r,&l, &df);
                dtoi(r, l, df);
                break;
            case PUSH:
                trans_ri(a, b, c, &r,&df);
                push(r, df);
                break;
            case POP:
                trans_ri(a, b, c, &r,&df);
                pop(r, df);
                break;
            case CALL:
                trans_rr(a, b, c, &r, &l, &df);
                call(r, l, df);
                break;
            case CALLI:
                trans_bd(a, b, c, &un);
                calli(un);
                break;
            case RET:
                trans_bd(a, b, c, &un);
                ret(un);
                break;
            case CMP:
                trans_rr(a, b, c, &r,&l, &df);
                cmp(r, l, df);
                break;
            case CMPI:
                trans_ri(a, b, c, &r,&df);
                cmpi(r, df);
                break;
            case CMPD:
                trans_rr(a, b, c, &r,&l, &df);
                cmpd(r, l, df);
                break;
            case JMP:
                trans_bd(a, b, c, &un);
                jmp(un);
                break;
            case JNE:
                trans_bd(a, b, c, &un);
                jne(un);
                break;
            case JEQ:
                trans_bd(a, b, c, &un);
                jeq(un);
                break;
            case JLE:
                trans_bd(a, b, c, &un);
                jle(un);
                break;
            case JL:
                trans_bd(a, b, c, &un);
                jl(un);
                break;
            case JGE:
                trans_bd(a, b, c, &un);
                jge(un);
                break;
            case JG:
                trans_bd(a, b, c, &un);
                jg(un);
                break;
            case LOAD:
                trans_rm(a, b, c, &r, &un);
                load(r, un);
                break;
            case STORE:
                trans_rm(a, b, c, &r, &un);
                store(r, un);
                break;
            case LOAD2:
                trans_rm(a, b, c, &r, &un);
                load2(r, un);
                break;
            case STORE2:
                trans_rm(a, b, c, &r, &un);
                store2(r, un);
                break;
            case LOADR:
                trans_rr(a, b, c, &r, &l, &df);
                loadr(r, l, df);
                break;
            case LOADR2:
                trans_rr(a, b, c, &r, &l, &df);
                loadr2(r, l, df);
                break;
            case STORER:
                trans_rr(a, b, c, &r, &l, &df);
                storer(r, l, df);
                break;
            case STORER2:
                trans_rr(a, b, c, &r, &l, &df);
                storer2(r, l, df);
                break;
            default:
                trans_bd(a, b, c, &un);
                break;
        }
        //debug();
        if (jumpPoint > -1) {
            fseek(inputs, jumpPoint * 4 + 512, SEEK_SET);
        } else {
            reg[15]++;
        }
    }
    return 0;
}


int main(){
    int i;
    for (i = 0; i < 17; i++) {
        reg[i] = 0;
    }
    stek = malloc(sizeof(int) * 1024);
    memory = malloc(sizeof(int) * 622144);
    memory2 = malloc(sizeof(int) * 622144);
    commandstek = malloc(sizeof(int) * 1024);
    clearAsm();
    assembler();
    interpreter();
    free(stek);
    free(memory);
    free(memory2);
    free(commandstek);
    return 0;
}