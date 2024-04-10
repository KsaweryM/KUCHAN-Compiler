# KUCHAN-Compiler
The KUCHAN compiler is a simple programming language project. Its implementation uses Flex and Bison for lexical and syntactic analysis and for the creation of a abstract syntax tree. LLVM is utilized to generate efficient output code from the abstract syntax tree of the analyzed source code.

A sample code that the compiler in the current version can translate to LLVM IR:

```
BEGIN
	a = 1;
	b = 1;
	tmp = 1;

	i = 0;
	nrFibonaccinumbers = 10;
	createNextNumber = 1;

	WHILE(createNextNumber == 1) DO
		IF(i == nrFibonaccinumbers) THEN
			createNextNumber = 0;
		ELSE
			PRINT(a);
			tmp = a;
			a = b;
			b = b + tmp;
			i = i + 1;
		FI
	DONE
END
```