#!/bin/sh

sed 's/CSR_//' csrregs.h | awk '
/#define/ {
	print $2
}
' > csr-tmp.txt

awk '
BEGIN {
	print "/* Autogenerated by generate_csr.sh */"
	print "#include \"csrregs.h\""
}
{
	printf "\n/* %s */\n\n\
TEXT csr_read_%s(SB), $-4\n\
	CSRRS CSR(CSR_%s), R0, R8\n\
	RET\n\n\
TEXT csr_write_%s(SB), $-4\n\
	CSRRW CSR(CSR_%s), R8, R8\n\
	RET\n\n\
TEXT csr_set_%s(SB), $-4\n\
	CSRRS CSR(CSR_%s), R8, R8\n\
	RET\n\n\
TEXT csr_clear_%s(SB), $-4\n\
	CSRRC CSR(CSR_%s), R8, R8\n\
	RET\n",$1,$1,$1,$1,$1,$1,$1,$1,$1,$1
}
' csr-tmp.txt > csr.s

awk '
BEGIN {
	print "/* Autogenerated by generate_csr.sh */"
	print "#include \"csrregs.h\""
	print ""
	print "/*"
	print " * This file defines three functions for each CSR, where NAME is replaced by the name of the CSR:"
	print " * - long csr_read_NAME(void)"
	print " *     Returns the value of the CSR"
	print " *"
	print " * - long csr_write_NAME(long val)"
	print " *     Writes val to the CSR and returns the previous value"
	print " *"
	print " * - long csr_set_NAME(long mask)"
	print " *     Sets the bits it CSR corresponding to high bits in the mask"
	print " *"
	print " * - long csr_clear_NAME(long mask)"
	print " *     Clear the bits it CSR corresponding to high bits in the mask"
	print " */"
}
{
	printf "\n/* %s */\n", $1
	printf "long csr_read_%s(void);\n", $1
	printf "long csr_write_%s(long);\n", $1
	printf "long csr_set_%s(long);\n", $1
	printf "long csr_clear_%s(long);\n", $1
}
' csr-tmp.txt > csr.h

rm csr-tmp.txt
