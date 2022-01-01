#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

//operation
double add(double a, double b){return a + b;}
double sub(double a, double b){return a - b;}
double mult(double a, double b){return a * b;}
double divi(double a, double b){return a/b;}


double (*operations[5])(double a, double b) = {add, sub, mult, divi, pow};


//double (*functions[3])(double a) = {sin, cos, tan};


typedef struct node {
	int operation_func_ptr_index;
	double value; 
	struct node* left;
	struct node* right; 
} node;




double eval(node* current){

//	printf("%ld \n", current->value);

	if(current->left == NULL && current->right == NULL){
		return (*current).value;
	}

	return (*operations[current->operation_func_ptr_index])( eval(current->left) , eval(current->right) );
	
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



void parse(Node* root, char* code){
	
	//char* *separated_code = (char*)malloc(1 * sizeof(char*));
	//separated_code[0] = code;

	char *raw_operatons[5] = (char*){'^', '*', '/', '+', '-'}; //add sin, cos, etc. later

	char grouping[2] = (char){'(', ')'};
	
	int number_open = 0;
	for(int i = 0; i < sizeof(code)/sizeof(char); i++){
		if(code[i] == grouping[0]){number_open++;}
		else if(code[i] == grouping[1]){number_open--;}
		
		if(number_open == 0){ //outside of ()
			
			for(int j = 0; j < 5; j++){
				if(code[i] == raw_operatons[j]){
					
				}
			}

		}

	}

	


	for(int j = 0; j < sizeof(raw_operatons)/sizeof(char); j++){
		if(code[0] == raw_operations[j]){
			head = (Node){j, NULL, new};
		}
	}

	
}



int main(){
	char* input = "(5*2)+((5+2)-(3*2))+(3)";
	printf("%s\n",input);
	printf("test: %lf\n", (*operations[0])(5, 2));
	printf("test: %lf\n", (*operations[2])(5, 2));
	
	struct node* solution;//root

	struct node* thing1 =  init_node(0, 5); 
	struct node* thing2 =  init_node(0, 6);




	solution = init_node(0,0);
	solution->left = thing1;
	solution->right = thing2;

	//parse(&solution, input);

	solution->value = eval(solution);

	printf("Solution: %lf", solution->value);

	

	return 0;
}




