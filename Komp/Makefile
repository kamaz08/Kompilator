parser : bison.tab.c scan.c veriable.c condition.c expression.c command.c helper.c generatecode.c
			gcc veriable.c condition.c expression.c command.c helper.c generatecode.c scan.c bison.tab.c -lm -o parser	

bison.tab.c	: bison.y
				bison -d bison.y

scan.c		:  flex.l
				flex -o scan.c flex.l




