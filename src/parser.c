#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#define NO 0

//operation
double add(double a, double b){return a + b;}
double sub(double a, double b){return a - b;}
double mult(double a, double b){return a * b;}
double divi(double a, double b){return a/b;}

double (*operations[5])(double a, double b) = {add, sub, mult, divi, pow};
char raw_operatons[5] = {'+', '-', '*', '/', '^'}; //add sin, cos, etc. later
char grouping[2] = {'(', ')'};

//double (*functions[3])(double a) = {sin, cos, tan};

typedef struct node {
	int operation_func_ptr_index;
	double value; 
	struct node* left;
	struct node* right; 
} node;


double eval(node* current);
struct node* init_node(int oper_index, double val);
//void prep(char* code, char* modified);
int get_operation_index(char o);
void parse(char* code, node* current);


int main(){
	
	char* input = "(((2*1)+4)+(5*(2+2)))"; //does not work
	//char* input = "((2+4)+(5*4))"; //works
	struct node* solution;
	solution = init_node(0,0);
	parse(input, solution);
	solution->value = eval(solution);
	printf("Solution_new: %lf", solution->value);

	
	return 0;
}



struct node* init_node(int oper_index, double val)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
 
	node->operation_func_ptr_index = oper_index;
    node->value = val;
	
 

    node->left = NULL;
    node->right = NULL;

    return (node);
}



void parse(char* code, node* current){
	//printf("%s\n", code);
	if(strlen(code) == 5){ //single (a+b)
		current->left = init_node(NO, (double)(code[1] - '0'));
        current->right = init_node(NO, (double)(code[3]- '0'));
		current->operation_func_ptr_index = get_operation_index(code[2]);

		printf("l: %lf \n", (double)(code[1] - '0'));
		printf("r: %lf \n", (double)(code[3] - '0'));
	} else if (strlen(code) == 1){
		current->value = (double)(code[0] - '0');
	} else {

		int number_open = -1; //first paren
		for(int i = 0; i < strlen(code) - 1 /*last paren*/; i++){
			if(code[i] == grouping[0]){number_open++;}
			else if(code[i] == grouping[1]){number_open--;}
			
			if(number_open == 0){ //outside of ()
				int is_operator = get_operation_index(code[i]);
				if(is_operator != -1){
					//is_operator
					current->operation_func_ptr_index = is_operator;

					char left[i-1]; 
					char right[(strlen(code)-1)-(i+1)];

					strncpy(left, &code[1], i-1);
					strncpy(right, &code[i+1], strlen(code)-i-2);

					left[i-1] = '\0';
					right[strlen(code)-i-2] = '\0';

					printf("left: |%s|\n", left);
					printf("right: |%s|\n", right);

					current->left = init_node(NO, NO);
					current->right = init_node(NO,NO);

					parse(left, current->left); //cut(0, i-1, code)
					parse(right, current->right); //cut(i+1, strlen(code)-1, code)
					//^cut gives you a substring
				}
				
			}
		}

	}
	

}

int get_operation_index(char o){
	for(int i = 0; i < 5; i++){
		if(o == raw_operatons[i]){
			return i;
		}

	}
	return -1;
}

double eval(node* current){
	if(current->left == NULL && current->right == NULL){
		return (*current).value;
	}

	return (*operations[current->operation_func_ptr_index])( eval(current->left) , eval(current->right) );
}





///////////////////////
/*
void prep(char* code, char* modified){
	modified = code;

	

	for(int i = 0; i < strlen(code); i++){
		if(code[i] == '*' || code[i] == '/'){
			char* temp1;
			snip(modified, 0, i-2, temp1);

			char* temp2;
			snip(modified, i, not_enclosed(modified, i), temp2);

			char* temp3;
			concat("(", temp1, temp3);
			
			char* temp4;
			concat(temp2, ")", temp4);

			concat(  temp3,   temp4, modified); 
			
		}

		if(code[i] == '+' || code[i] == '-'){
			char* temp1;
			snip(modified, 0, i-2, temp1);

			char* temp2;
			snip(modified, i, not_enclosed(modified, i), temp2);

			char* temp3;
			concat("(", temp1, temp3);
			
			char* temp4;
			concat(temp2, ")", temp4);

			concat(  temp3,   temp4, modified); 
		}

	}
	
	

}*/