// 8 регистров R1 ... R8
// флаг F
// регистр команд PC
// указатель стека SP

#define NOP 0x00	// NOP ничего не делать + 
#define HALT 0x01	// HALT выйти +
#define RET 0x02	// RET возвтрат из функции +/-
#define CALL 0x03	// CALL <function_name> вызов функции +/-

#define ADD 0x04	// ADD <register>, <register> сложение двух регистров +
#define SUB 0x05	// SUB <register>, <register> вычитание двух регистров +
#define MUL 0x06	// MUL <register>, <register> умножение двух регистров +
#define DIV 0x07	// DIV <register>, <register> деление двух регистров +

#define AND 0x08	// AND <register>, <register> и +
#define OR 0x09		// OR  <register>, <register> или +
#define XOR 0x0A	// XOR <refister>, <register> иск. или +

#define PUSHD 0x0B	// PUSH <data> положить данные в стек +
#define IN 0x0C		// IN <port>
#define OUT 0x0D	// OUT <post>
#define MOV 0x0E	// MOV [<register>], <register> положить в память по адресу, взятому из регистра
#define MOVRR 0x0F	// MOV <register>, <register>

//MOVD 0x10 - 0x7	// MOV <register>, <data> положить в регистр данные (двухбайтное число) + 
#define MOVD1 0x10
#define MOVD2 0x11
#define MOVD3 0x12
#define MOVD4 0x13
#define MOVD5 0x14
#define MOVD6 0x15
#define MOVD7 0x16
#define MOVD8 0x17

//NOT 0x18 - 0x1F	// NOT <register> не регистра +
#define NOT1 0x18
#define NOT2 0x19
#define NOT3 0x1A
#define NOT4 0x1B
#define NOT5 0x1C
#define NOT6 0x1D
#define NOT7 0x1E
#define NOT8 0x1F

//INC 0x20 - 0x27 INC <register> // инкремент регистра +
#define INC1 0x20
#define INC2 0x21
#define INC3 0x22
#define INC4 0x23
#define INC5 0x24
#define INC6 0x25
#define INC7 0x26
#define INC8 0x27

//DEC 0x28 - 0x2F DEC <register> // декремент регистра +
#define DEC1 0x28
#define DEC2 0x29
#define DEC3 0x2A
#define DEC4 0x2B
#define DEC5 0x2C
#define DEC6 0x2D
#define DEC7 0x2E
#define DEC8 0x2F

//PUSH 0x30 - 0x37 PUSH <register> // положить в стек регистр +
#define PUSH1 0x30
#define PUSH2 0x31
#define PUSH3 0x32
#define PUSH4 0x33
#define PUSH5 0x34
#define PUSH6 0x35
#define PUSH7 0x36
#define PUSH8 0x37

//POP 0x38 - 0x3F POP <register> // вытащить из стека в регистр +
#define POP1 0x38
#define POP2 0x39
#define POP3 0x3A
#define POP4 0x3B
#define POP5 0x3C
#define POP6 0x3D
#define POP7 0x3E
#define POP8 0x3F

//MOVTR 0x40 - 0x47 MOV <register>, [<addr>] // переместить в регистр из памяти +
#define MOVTR1 0x40
#define MOVTR2 0x41
#define MOVTR3 0x42
#define MOVTR4 0x43
#define MOVTR5 0x44
#define MOVTR6 0x45
#define MOVTR7 0x46
#define MOVTR8 0x47

//MOVFR 0x48 - 0x4F MOV [<addr>], <register> // переместить в память из регистра +
#define MOVFR1 0x48
#define MOVFR2 0x49
#define MOVFR3 0x4A
#define MOVFR4 0x4B
#define MOVFR5 0x4C
#define MOVFR6 0x4D
#define MOVFR7 0x4E
#define MOVFR8 0x4F

#define JMP 0x50	// JMP <label> переход +
#define CMP 0x51	// CMP <register>, <register> сравнение +
#define JE 0x52		// JE <label> если равно +
#define JNE 0x53	// JNE <label> если не равно +
#define JL 0x54		// JL <label> если меньше +
#define JLE 0x55	// JLE <label> если меньше или равно +
#define JG 0x56		// JG <label> если больше +
#define JGE 0x57	// JGE <label> если больше или равно +

// CMPD 0x58 - 0x5F // CMP <register>, <data> сравнить знасение регистра с числом +
#define CMPD1 0x58
#define CMPD2 0x59
#define CMPD3 0x5A
#define CMPD4 0x5B
#define CMPD5 0x5C
#define CMPD6 0x5D
#define CMPD7 0x5E
#define CMPD8 0x5F

// ADDD 0x60 - 0x67	// ADD <register>, <data> сложение +
#define ADDD1 0x60
#define ADDD2 0x61
#define ADDD3 0x62
#define ADDD4 0x63
#define ADDD5 0x64
#define ADDD6 0x65
#define ADDD7 0x66
#define ADDD8 0x67

// SUBD 0x68 - 0x6F // SUB <register>, <data> вычитание +
#define SUBD1 0x68
#define SUBD2 0x69
#define SUBD3 0x6A
#define SUBD4 0x6B
#define SUBD5 0x6C
#define SUBD6 0x6D
#define SUBD7 0x6E
#define SUBD8 0x6F

//MULD 0x70 - 0x77 // MUL <register>, <data> умножение +
#define MULD1 0x70
#define MULD2 0x71
#define MULD3 0x72
#define MULD4 0x73
#define MULD5 0x74
#define MULD6 0x75
#define MULD7 0x76
#define MULD8 0x77

//DIVD 0x78 - 0x7F // DIV <register>, <data> деление +
#define DIVD1 0x78
#define DIVD2 0x79
#define DIVD3 0x7A
#define DIVD4 0x7B
#define DIVD5 0x7C
#define DIVD6 0x7D
#define DIVD7 0x7E
#define DIVD8 0x7F

#define STDIN_PORT 0x00
#define STDOUT_PORT 0x01














