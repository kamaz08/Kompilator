#ifndef VALUE_H
#define VALUE_H

struct value{
	int isNum;
	int position;
	int declareted;
	char* value;
};

value* createValue(int pos, char* value);
value* createValue(int pos);

#endif