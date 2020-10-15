#include	"l.h"

Optab	optab[] =
{
 /* add		*/	AADD,		C_REG,		C_REG,		0,	4,	OOP,		0,	0,
 /* sub		*/	ASUB,		C_REG,		C_REG,		0,	4,	OOP,		0,	0x20,
 /* sll		*/	ASLL,		C_REG,		C_REG,		0,	4,	OOP,		1,	0,
 /* slt		*/	ASLT,		C_REG,		C_REG,		0,	4,	OOP,		2,	0,
 /* sltu	*/	ASLTU,		C_REG,		C_REG,		0,	4,	OOP,		3,	0,
 /* xor		*/	AXOR,		C_REG,		C_REG,		0,	4,	OOP,		4,	0,
 /* srl		*/	ASRL,		C_REG,		C_REG,		0,	4,	OOP,		5,	0,
 /* sra		*/	ASRA,		C_REG,		C_REG,		0,	4,	OOP,		5,	0x20,
 /* or		*/	AOR,		C_REG,		C_REG,		0,	4,	OOP,		6,	0,
 /* and		*/	AAND,		C_REG,		C_REG,		0,	4,	OOP,		7,	0,
 /* mul		*/	AMUL,		C_REG,		C_REG,		0,	4,	OOP,		0,	0x01,
 /* mulh	*/	AMULH,		C_REG,		C_REG,		0,	4,	OOP,		1,	0x01,
 /* mulhsu	*/	AMULHSU,	C_REG,		C_REG,		0,	4,	OOP,		2,	0x01,
 /* mulhu	*/	AMULHU,		C_REG,		C_REG,		0,	4,	OOP,		3,	0x01,
 /* div		*/	ADIV,		C_REG,		C_REG,		0,	4,	OOP,		4,	0x01,
 /* divu	*/	ADIVU,		C_REG,		C_REG,		0,	4,	OOP,		5,	0x01,
 /* rem		*/	AREM,		C_REG,		C_REG,		0,	4,	OOP,		6,	0x01,
 /* remu	*/	AREMU,		C_REG,		C_REG,		0,	4,	OOP,		7,	0x01,

 /* slli	*/	ASLL,		C_SCON,		C_REG,		1,	4,	OOP_IMM,	1,	0,
 /* srli	*/	ASRL,		C_SCON,		C_REG,		1,	4,	OOP_IMM,	5,	0,
 /* srai	*/	ASRA,		C_SCON,		C_REG,		1,	4,	OOP_IMM,	5,	0x20,

 /* addi	*/	AADD,		C_SCON,		C_REG,		2,	4,	OOP_IMM,	0,	0,
 /* slti	*/	ASLT,		C_SCON,		C_REG,		2,	4,	OOP_IMM,	2,	0,
 /* sltiu	*/	ASLTU,		C_SCON,		C_REG,		2,	4,	OOP_IMM,	3,	0,
 /* xori	*/	AXOR,		C_SCON,		C_REG,		2,	4,	OOP_IMM,	4,	0,
 /* ori		*/	AOR,		C_SCON,		C_REG,		2,	4,	OOP_IMM,	6,	0,
 /* andi	*/	AAND,		C_SCON,		C_REG,		2,	4,	OOP_IMM,	7,	0,

 /* beq		*/	ABEQ,		C_REG,		C_LBRA,		3,	4,	OBRANCH,	0,	0,
 /* bne		*/	ABNE,		C_REG,		C_LBRA,		3,	4,	OBRANCH,	1,	0,
 /* blt		*/	ABLT,		C_REG,		C_LBRA,		3,	4,	OBRANCH,	4,	0,
 /* bge		*/	ABGE,		C_REG,		C_LBRA,		3,	4,	OBRANCH,	5,	0,
 /* bltu	*/	ABLTU,		C_REG,		C_LBRA,		3,	4,	OBRANCH,	6,	0,
 /* bgeu	*/	ABGEU,		C_REG,		C_LBRA,		3,	4,	OBRANCH,	7,	0,

 /* jal		*/	AJAL,		C_NONE,		C_SBRA,		4,	4,	OJAL,	0,	REGLINK,
 /* jal		*/	AJMP,		C_NONE,		C_SBRA,		4,	4,	OJAL,	0,	REGZERO,
 /* jalr	*/	AJAL,		C_NONE,		C_SOREG,	5,	4,	OJALR,	0,	REGLINK,
 /* jalr	*/	AJMP,		C_NONE,		C_SOREG,	5,	4,	OJALR,	0,	REGZERO,

 /* ecall	*/	AECALL,		C_NONE,		C_NONE,		0,	4,	OSYSTEM,	0,	0,
 /* ebreak	*/	AEBREAK,	C_NONE,		C_NONE,		0,	4,	OSYSTEM,	0,	1,

 /* sb		*/	AMOVB,		C_REG,		C_SOREG,	6,	4,	OSTORE,	0,	0,
 /* sb		*/	AMOVBU,		C_REG,		C_SOREG,	6,	4,	OSTORE,	0,	0,
 /* sh		*/	AMOVH,		C_REG,		C_SOREG,	6,	4,	OSTORE,	1,	0,
 /* sw		*/	AMOVW,		C_REG,		C_SOREG,	6,	4,	OSTORE,	2,	0,
 /* sw		*/	AMOVW,		C_ZCON,		C_SOREG,	6,	4,	OSTORE,	2,	0,

 /* sb		*/	AMOVB,		C_REG,		C_LEXT,		12,	8,	OSTORE,	0,	0,
 /* sb		*/	AMOVBU,		C_REG,		C_LEXT,		12,	8,	OSTORE,	0,	0,
 /* sh		*/	AMOVH,		C_REG,		C_LEXT,		12,	8,	OSTORE,	1,	0,
 /* sw		*/	AMOVW,		C_REG,		C_LEXT,		12,	8,	OSTORE,	2,	0,
 /* sw		*/	AMOVW,		C_ZCON,		C_LEXT,		12,	8,	OSTORE,	2,	0,

 /* sb		*/	AMOVB,		C_REG,		C_LAUTO,		15,	12,	OSTORE,	0,	0,
 /* sb		*/	AMOVBU,		C_REG,		C_LAUTO,		15,	12,	OSTORE,	0,	0,
 /* sh		*/	AMOVH,		C_REG,		C_LAUTO,		15,	12,	OSTORE,	1,	0,
 /* sw		*/	AMOVW,		C_REG,		C_LAUTO,		15,	12,	OSTORE,	2,	0,
 /* sw		*/	AMOVW,		C_ZCON,		C_LAUTO,		15,	12,	OSTORE,	2,	0,

 /* lb		*/	AMOVB,		C_SOREG,	C_REG,		7,	4,	OLOAD,	0,	0,
 /* lh		*/	AMOVH,		C_SOREG,	C_REG,		7,	4,	OLOAD,	1,	0,
 /* lw		*/	AMOVW,		C_SOREG,	C_REG,		7,	4,	OLOAD,	2,	0,
 /* lbu		*/	AMOVBU,		C_SOREG,	C_REG,		7,	4,	OLOAD,	4,	0,
 /* lhu		*/	AMOVHU,		C_SOREG,	C_REG,		7,	4,	OLOAD,	5,	0,

 /* lui		*/	AMOVW,		C_UCON,		C_REG,		8,	4,	OLUI,	0,	0,

 /* lb		*/	AMOVB,		C_LEXT,		C_REG,		13,	8,	OLOAD,	0,	0,
 /* lh		*/	AMOVH,		C_LEXT,		C_REG,		13,	8,	OLOAD,	1,	0,
 /* lw		*/	AMOVW,		C_LEXT,		C_REG,		13,	8,	OLOAD,	2,	0,
 /* lbu		*/	AMOVBU,		C_LEXT,		C_REG,		13,	8,	OLOAD,	4,	0,
 /* lhu		*/	AMOVHU,		C_LEXT,		C_REG,		13,	8,	OLOAD,	5,	0,

 /* lb		*/	AMOVB,		C_LAUTO,		C_REG,		16,	12,	OLOAD,	0,	0,
 /* lh		*/	AMOVH,		C_LAUTO,		C_REG,		16,	12,	OLOAD,	1,	0,
 /* lw		*/	AMOVW,		C_LAUTO,		C_REG,		16,	12,	OLOAD,	2,	0,
 /* lbu		*/	AMOVBU,		C_LAUTO,		C_REG,		16,	12,	OLOAD,	4,	0,
 /* lhu		*/	AMOVHU,		C_LAUTO,		C_REG,		16,	12,	OLOAD,	5,	0,

 /* add		*/	AMOVW,		C_REG,		C_REG,		0,	4,	OOP,		0,	0,
 /* addi	*/	AMOVW,		C_SCON,		C_REG,		11,	4,	OOP_IMM,	0,	0,
 /* addi	*/	AMOVW,		C_SECON,	C_REG,		11,	4,	OOP_IMM,	0,	0,
 /* addi	*/	AMOVW,		C_SACON,	C_REG,		11,	4,	OOP_IMM,	0,	0,
 /* lui,addi*/	AMOVW,		C_LCON,		C_REG,		9,	8,	OOP_IMM,	0,	0,
 /* ",addi  */	AADD,		C_LCON,		C_REG,		14,	12,	OOP_IMM,	0,	0,

 /* andi	*/	AMOVBU,		C_REG,		C_REG,		10,	4,	OOP_IMM,	7,	0xFF,
 /* srli,srli	*/	AMOVHU,		C_REG,		C_REG,		10,	8,	OOP_IMM,	5,	16,
 /* srli,srai	*/	AMOVB,		C_REG,		C_REG,		10,	8,	OOP_IMM,	5,	24+(0x20<<5),
 /* srli,srai	*/	AMOVH,		C_REG,		C_REG,		10, 	8,	OOP_IMM,	5,	16+(0x20<<5),

 /* int->float	*/	AMOVWD,		C_REG,		C_FREG,		24,	4,	Ocustom_2,	0,	1,
 /* float->int  */	AMOVDW,		C_FREG,		C_FREG,		24,	4,	Ocustom_2,	0,	1,
 /* float load	*/	AMOVD,		C_SOREG,	C_FREG,		24,	4,	Ocustom_2,	0,	1,
 /* float load	*/	AMOVD,		C_LEXT,		C_FREG,		24,	4,	Ocustom_2,	0,	1,
 /* float store */	AMOVD,		C_FREG,		C_SOREG,	24,	4,	Ocustom_2,	0,	1,
 /* float store */	AMOVD,		C_FREG,		C_LEXT,	24,	4,	Ocustom_2,	0,	1,
 /* float move  */	AMOVD,		C_FREG,		C_FREG,	24,	4,	Ocustom_2,	0,	1,
 /* bug?        */	AMOVW,		C_FREG,		C_REG,	24,	4,	Ocustom_2,	0,	1,
					ACMPEQD,	C_FREG,		C_REG,		24,	4,	Ocustom_2,	0,	1,
					ACMPLED,	C_FREG,		C_REG,		24,	4,	Ocustom_2,	0,	1,
					ACMPLTD,	C_FREG,		C_REG,		24,	4,	Ocustom_2,	0,	1,
					AADDD,	C_FREG,		C_FREG,		24,	4,	Ocustom_2,	0,	1,
					ASUBD,	C_FREG,		C_FREG,		24,	4,	Ocustom_2,	0,	1,
					AMULD,	C_FREG,		C_FREG,		24,	4,	Ocustom_2,	0,	1,
					ADIVD,	C_FREG,		C_FREG,		24,	4,	Ocustom_2,	0,	1,

 /* -		*/	AWORD,		C_NONE,		C_LCON,		25, 	4, 	0,		0,	0,
 /* -		*/	ATEXT,		C_LEXT,		C_LCON,		26,	0,	0,		0,	0,
 /* -		*/	AXXX,		C_NONE,		C_NONE,		0,	0,	0,		0,	0,
};
