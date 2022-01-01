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


double nil_func(double a){return a;}
double (*functions[4])(double a) = {nil_func, sin, cos, tan};

typedef struct node {
	int operation_func_ptr_index;
	int function_func_ptr_index;
	double value; 
	struct node* left;
	struct node* right; 
} node;


double eval(node* current);


struct node* init_node(int oper_index, int func_index, double val);


void parse(node* current, char* code);

/////////////////////////////////////////////////////////////////////////////////////

void snip(char* text, int start, int end, char* new){
	//char* result;//[end-start];
	for(int i = start; i<=end; i++){
		new[i-start]=text[i];

	}

	//return result;
}

int not_enclosed(char* code, int start){
	char grouping[2] = {'(', ')'};

	int number_open = 0;
	for(int i = start; i < strlen(code); i++){
		if(code[i] == grouping[0]){number_open++;}
		else if(code[i] == grouping[1]){number_open--;}
		
		if(number_open == 0){
			
          return i;
		}
	}

	return strlen(code);
}

void concat(char* first, char* second, char* new){
	int result_len = strlen(first) + strlen(second);
	//char* result;//[result_len];
	for(int i = 0; i < strlen(first); i++){
		new[i] = first[i];
	}

	for(int i = strlen(first); i < result_len; i++){
		new[i] = second[i];
	}

	//return result;
}

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
	
	

}
/////////////////////////////////////////////////////////////////////////////////////


int main(){


	struct node* sol;//root

	struct node* thing1 =  init_node(NO, NO, 5); // (node){0, 3, NULL, NULL};
	struct node* thing2 =  init_node(NO, NO, 6);//(node){0, 3, NULL, NULL};



  /*  root->left = newNode(2);
    root->right = newNode(3);
 
    root->left->left = newNode(4);*/


	sol = init_node(1, 1, 0);
	sol->left = thing1;
	sol->right = thing2;

	//parse(&solution, input);

	sol->value = eval(sol);

	printf("Solution: %lf", sol->value);
















	//char* input = "5*3+3";

	/*char* temp1;
	char* temp2;

snip("johnlins", 2, 4, temp1);
concat("john", "linssss", temp2);

	printf("%s\n", temp1);
	printf("%s\n", temp2);

	char* test = "2+(4/(3-1))+4";
	char* temp;
	prep(test, temp);
	printf("%s\n", temp);*/

	//struct node* solution;

	//solution = init_node(NO,NO, 0);

	//parse(solution, input);

	//solution->value = eval(solution);

	//printf("Solution: %lf", solution->value);

	return 0;
}


void parse(node* current, char* code){

	char raw_operatons[5] = {'+', '-', '*', '/', '^'}; //add sin, cos, etc. later

	char grouping[2] = {'(', ')'};
	
	int number_open = 0;
	for(int i = 0; i < strlen(code); i++){
		if(code[i] == grouping[0]){number_open++;}
		else if(code[i] == grouping[1]){number_open--;}
		
		if(number_open == 0){ //outside of ()
			
            for(int j = 0; j < 5; j++){
                if(code[i] == raw_operatons[j]){
                    current->operation_func_ptr_index = j;
                    current->left = init_node(NO,NO, (double)(code[i-1] - '0'));
                    current->right = init_node(NO, NO, (double)(code[i+1]- '0'));
                    current = current->left; //change this to either left or right depending on order of operations
                }
            }
		}
	}
}



struct node* init_node(int oper_index, int func_index, double val)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
 
	node->operation_func_ptr_index = oper_index;
	node->function_func_ptr_index = func_index;
    node->value = val;
	
 

    node->left = NULL;
    node->right = NULL;

    return (node);
}

double eval(node* current){
	if(current->left == NULL && current->right == NULL){
		return (*current).value;
	}

	return  (*functions[current->function_func_ptr_index])( (*operations[current->operation_func_ptr_index])( eval(current->left) , eval(current->right) ));
}