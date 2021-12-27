//Name & Surname: AYÞEGÜL RANA ERDEMLÝ 
//username: aysegulrana
//ID: 26744

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynamicStrQueue.h"
#include "DynamicIntStack.h"
#include "DynamicStrStack.h"
#include "strutils.h"

using namespace std;

int special_regs[5] = {0};// namely CSA CSB CSC CSP CST
int general_regs[20] = {0}; // namely CSG0 CSG1 CSG2 ... CSG19
string variables[20] = {""}; // to store the variable names defined by the user. (e.g. var1, var2)
DynamicStrQueue instruction_queue; // to store the instructions in the queue
int def_counter = 0; // counting the def statements so that general reg - variable match holds
DynamicIntStack memory_stack; // needed for debugger
int instr_counter = 1; // counter for printing the instruction counts in print remaining instructions
DynamicStringStack myStack;

void Operations(bool v1string,bool v2string,string op,string storage,string ourvar,int one,int two,string &qstr,int countop,string var1,string var2, DynamicStrQueue &instruction_queue, string (&variables)[20], DynamicStringStack &myStack){

	if (!v1string && !v2string){ //if both of them are numbers
		if (countop==1 || countop==2){
			qstr+=op+" "+itoa(two)+" "+itoa(one); 

			if (op=="add")
				myStack.push(itoa(one+two)); //we pushed the result to use it in the other operations to come in the same line
			else if (op=="mul")
				myStack.push(itoa(one*two));
			else if (op=="div")
				myStack.push(itoa(one/two));
			else if (op=="sub")
				myStack.push(itoa(one*two));

			instruction_queue.enqueue(qstr);	//we converted this operation to machine code
			qstr="";
			instruction_queue.enqueue("push "+storage); //we need to push CSA to memory stack in machine code after such an operation
		}

		if (countop==3){ 
			instruction_queue.enqueue("pop"); 
			instruction_queue.enqueue("mov CST CSP");
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue(op+" CSP CST");
			instruction_queue.enqueue("push "+storage);
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov "+ourvar+" CSP");
		}

		else if (countop==4){
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov CST CSP");
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue(op+" CSP CST");
			instruction_queue.enqueue("push "+storage); 
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov "+ourvar+" CSP");
		}
	}
	else if (!v2string) { //the first one is number, second is var
		if (countop==1){
			qstr+=op+" "+itoa(two)+" "+var1; myStack.push(storage);
			instruction_queue.enqueue(qstr);	//we converted this operation to machine code
			qstr="";
			instruction_queue.enqueue("push "+storage);	//we need tos push CSA to memory stack in machine code after such an operation
			instruction_queue.enqueue("pop"); 
		}
		else if (countop==2){
			qstr+=op+" "+itoa(two)+" CSP";	myStack.push("CSP");
			instruction_queue.enqueue(qstr);	qstr="";
			instruction_queue.enqueue("push "+storage);	
			instruction_queue.enqueue("pop"); 
		}
		if (countop==3){ 
			qstr+=op+" "+" CSP "+var1;	
			instruction_queue.enqueue(qstr);	qstr="";
			instruction_queue.enqueue("push "+storage); myStack.push(storage);
		}

		else if (countop==4){
			qstr+=op+" "+itoa(two)+" "+var1;	myStack.push(storage);
			instruction_queue.enqueue(qstr); qstr="";
			instruction_queue.enqueue("push "+storage); 
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov CST CSP");
			instruction_queue.enqueue("pop");
		}
		else if (countop==5){
			qstr+=op+ " CSP CST";	myStack.push(storage);
			instruction_queue.enqueue(qstr);
			instruction_queue.enqueue("push "+storage); 	qstr="";
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov "+ourvar+" CSP");
		}	
	}

	else if (!v1string) { //the second is number, first one is var
		if (countop==1){
			qstr+=op+" "+var2+" "+itoa(one); myStack.push(storage);
			instruction_queue.enqueue(qstr);	//we converted this operation to machine code
			qstr="";
			instruction_queue.enqueue("push "+storage);	//we need to push CSA to memory stack in machine code after such an operation
			instruction_queue.enqueue("pop"); 
		}
		else if (countop==2){
			qstr+=op+" "+var2+" CSP";	myStack.push("CSP");
			instruction_queue.enqueue(qstr);	qstr="";
			instruction_queue.enqueue("push "+storage);	
			instruction_queue.enqueue("pop"); 
		}
		if (countop==3){ 
			qstr+=op+" "+" CSP "+itoa(one);	
			instruction_queue.enqueue(qstr);	qstr="";
			instruction_queue.enqueue("push "+storage); myStack.push(storage);
		}

		else if (countop==4){
			qstr+=op+" "+var2+" "+itoa(one);	myStack.push(storage);
			instruction_queue.enqueue(qstr); qstr="";
			instruction_queue.enqueue("push "+storage); 
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov CST CSP");
			instruction_queue.enqueue("pop");
		}
		else if (countop==5){
			qstr+=op+ " CSP CST";	myStack.push(storage);
			instruction_queue.enqueue(qstr);
			instruction_queue.enqueue("push "+storage); 	qstr="";
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov "+ourvar+" CSP");
		}	
	}

	else { //both are variables
		if (countop==1){
			qstr+=op+" "+var2+" "+var1; myStack.push(storage);
			instruction_queue.enqueue(qstr);	//we converted this operation to machine code
			qstr="";
			instruction_queue.enqueue("push "+storage);	//we need to push CSA to memory stack in machine code after such an operation
			instruction_queue.enqueue("pop"); 
		}

		else if (countop==2){
			qstr+=op+" "+var2+" CSP";	myStack.push("CSP");
			instruction_queue.enqueue(qstr);	qstr="";
			instruction_queue.enqueue("push "+storage);	
			instruction_queue.enqueue("pop"); 
		}
		if (countop==3){ 
			qstr+=op+" "+" CSP "+var1;	
			instruction_queue.enqueue(qstr);	qstr="";
			instruction_queue.enqueue("push "+storage);myStack.push(storage);
		}

		else if (countop==4){
			qstr+=op+" "+var2+" "+var1;	myStack.push(storage);
			instruction_queue.enqueue(qstr); qstr="";
			instruction_queue.enqueue("push "+storage); 
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov CST CSP");
			instruction_queue.enqueue("pop");
		}
		else if (countop==5){
			qstr+=op+ " CSP CST";	myStack.push(storage);
			instruction_queue.enqueue(qstr);
			instruction_queue.enqueue("push "+storage); 	qstr="";
			instruction_queue.enqueue("pop");
			instruction_queue.enqueue("mov "+ourvar+" CSP");
		}
	}
}

int Convert(string&CSG){ //if one of the general regs will be used, we will call this function and find its value

	int find;
	find=atoi(CSG.substr(3)); 
	return find;
}
void clear_regs_vars() {
	def_counter = 0;
	for (int &i : special_regs) {
		i = 0;
	}
	for (int &i : general_regs) {
		i = 0;
	}
	for (string &i : variables) {
		i = "";
	}
	instruction_queue.clear();
	memory_stack.clear();
}

bool transform_source() {
	bool invalid=true;
	ifstream input;
	string file, line;	
	cout<<"Please give me the input file name: ";
	cin>>file;
	input.open(file);

	if (input.fail()) {
		cout<< "There is a problem with the input file.";
		return false; }
	else {
		while (getline(input, line)){

			string qstr="";	int countop=0;
			if (line.find("main")==string::npos){

				if (line.find("int")!=string::npos && line.find("=")!=string::npos && line.find("(")==string::npos ){
					stringstream a(line); string val, intx, eq, num;
					a>>intx>>val>>eq>>num;
					for (int i=0; i<20; i++){
						if (variables[i]==""){
							variables[i]="CSG"+itoa(def_counter);
							qstr+="mov "+variables[i];
							def_counter++;
							i=20;
						}
					}
					if (!(num[0]<='z' && num[0]>='A')) {
						qstr+=" "+num;
					}
					else {
						qstr+=" CSG"+itoa(atoi(num.substr(1))-1);
					}
					instruction_queue.enqueue(qstr);
					a.clear();
				}
				else if (line.find("print")!=string::npos){
					istringstream x(line); string print, val;
					x>>print>>val;
					for (int i=0; i<20; i++){
						if (variables[i].substr(3)==itoa(atoi(val.substr(1))-1)){
							qstr+="push "+variables[(atoi(val.substr(1))-1)]; //we need to push first to print in machine code.
							i=20;
						}
					}
					instruction_queue.enqueue(qstr);
					instruction_queue.enqueue("print");
					x.clear();
				}
				else if (line.find("return")!=string::npos) {
					instruction_queue.enqueue("ret");
				}
				else if (line.find("int")==string::npos && line.find("(")==string::npos ) {
					istringstream a(line); string var, eq, num;
					a>>var>>eq>>num;

					if (!(num[0]<='z' && num[0]>='A')){
						for (int i=0; i<20; i++){
							if (atoi(variables[i].substr(3))==atoi(var.substr(1))-1){ 
								instruction_queue.enqueue("mov "+variables[i]+" "+num);
								i=20;
							}
						}
					}
					else {
						for (int i=0; i<20; i++){
							if (atoi(variables[i].substr(3))==atoi(var.substr(1))-1){ 
								qstr+="mov "+variables[i]; i=20; //we are assigning a variable's value to another if they are not numbers
							}
						}
						for (int i=0; i<20; i++){
							if (atoi(variables[i].substr(3))==atoi(num.substr(1))-1){ 
								qstr+=" "+variables[(atoi(num.substr(1))-1)];  instruction_queue.enqueue(qstr); qstr=""; i=20;
							}
						}
						a.clear();
					} 
				} 
				else if (line.find("(")!=string::npos){
					stringstream operation(line); string x, ourvar, op ; int counter=0; //op will be the one who will be popped
					while (operation>>x){        
						bool operation_done=false;//ourvar is the var before =
						if (x!="int" && counter==0){
							ourvar="CSG"+itoa(atoi(x.substr(1))-1); //we converted ax to CSGx-1
							counter++;
							if (line.find("int")!=string::npos){
								for (int i=0; i<20; i++){
									if (variables[i]==""){
										variables[i]=ourvar; i=20; def_counter++;
									}
								}
							}
						}

						else if (counter>0){

							if (x!="(" && x!="="){
								if (!(x[0]<='z' && x[0]>='A') && x!=")") { //if the element in the operation is a number or an operation sign
									myStack.push(x); //we directly push it to the stack 
								}
								else if (x!=")"){ //if it's a variable like a1
									for (int i=0; i<20 && variables[i]!=""; i++){
										if (variables[i].substr(3)==itoa(atoi(x.substr(1))-1)){ //we look for it if it is defined before
											myStack.push(variables[i]); i=20;
										}
									}
								}

								else if (x==")"){

									countop++; //which operation are we on
									while(!myStack.isEmpty() && operation_done==false ){
										int one=0, two=0; string ouroperator, var1, var2; bool v1string=false, v2string=false; 
										operation_done=true; //because we are going to do the operation with three things and we need to get out of the loop 
										myStack.pop(op); //we popped the last number or variable in the operation

										if (!(op[0]<='z' && op[0]>='A')){ //if it is a number
											one=atoi(op); } //one will be the first number we'll make operation with (the right one)
										else if (op!="CSA" || op!="CSB" || op!="CSC" || op!="CSP" || op!="CST"){
											var1=op; //if it's a variable, we assigned it to var1
											v1string=true; //var1 is a string
										}
										else {
											var1=op;	v1string=true;
										}
										myStack.pop(op);	ouroperator=op; //this we'll be the operator since it's the second on stack's top
										myStack.pop(op);		//this is the left var or number in the operation

										if (!(op[0]<='z' && op[0]>='A')){
											two=atoi(op); } //we check the same things for second num/var in the operation
										else if (op!="CSA" || op!="CSB" || op!="CSC" || op!="CSP" || op!="CST"){
											var2=op;
											v2string=true;
										}
										else {
											var1=op;
										}

										if(ouroperator=="+"){
											Operations(v1string, v2string, "add", "CSA", ourvar, one, two, qstr,  countop, var1, var2, instruction_queue, variables, myStack);
										}

										else if (ouroperator=="*"){
											Operations(v1string, v2string, "mul", "CSA", ourvar, one, two, qstr,  countop, var1, var2, instruction_queue, variables, myStack);

										}
										else if (ouroperator=="/"){ 
											Operations(v1string, v2string, "div", "CSB", ourvar, one, two, qstr,  countop, var1, var2, instruction_queue, variables, myStack);
										}

										else if (ouroperator=="%"){
											Operations(v1string, v2string, "div", "CSC", ourvar, one, two, qstr,  countop, var1, var2, instruction_queue, variables, myStack);

										}
										else if (ouroperator=="-"){
											Operations(v1string, v2string, "sub", "CSA", ourvar, one, two, qstr,  countop, var1, var2, instruction_queue, variables, myStack);
										}
									}
								}
							}
						}
					}
					operation.clear();
				}
				else if (line.find("return")!=string::npos) {
					instruction_queue.enqueue("ret");
				}
				else {
					istringstream b(line); string intx, var;
					b>>intx>>var;
					variables[def_counter]="CSG"+itoa(def_counter);	def_counter++; //defining a variable without assigning any value
					b.clear();
				}
			}
		}
		return true;
	}
}

void SpecialRegsOperations(int (&special_regs)[5], int passed2, string op, int passedval){ //this function is fit for every operation possible, 
																								//we just send the values and which operator we need to use
	if (op=="sub"){
		special_regs[0]=passedval-passed2;	 
	}
	else if (op=="add"){
		special_regs[0]=passedval+passed2;	
	}
	else if (op=="div"){
		special_regs[1]=passedval/passed2;	
		special_regs[2]=passedval%passed2;	
	}
	else if (op=="mul"){
		special_regs[0]=passedval*passed2;	
	}
}

void RunningInstructions(int &counter, string &inst, bool &undone){
	istringstream els(inst); string x;

	while (els>>x){
		counter++;
	}
	if (counter==3){ //if there are three words in the line there are different possibilites

		if (inst.find("mov")!=string::npos){
			string mov, first, sec;	istringstream els(inst);
			els>>mov>>first>>sec;

			if (first.substr(0, 3)=="CSG"){

				if (!(sec[0]<='z' && sec[0]>='A')) { //if it is assignedd to a number
					general_regs[Convert(first)]=atoi(sec);	
				}

				else if (sec.substr(0, 3)=="CSG"){
					general_regs[Convert(first)]=general_regs[Convert(sec)];	
				}
				else if (sec=="CSA"){
					general_regs[Convert(first)]=special_regs[0];	
				}
				else if (sec=="CSB"){
					general_regs[Convert(first)]=special_regs[1];	
				}
				else if (sec=="CSC"){
					general_regs[Convert(first)]=special_regs[2];	
				}
				else if (sec=="CSP"){
					general_regs[Convert(first)]=special_regs[3];	
				}
				else if (sec=="CST"){
					general_regs[Convert(first)]=special_regs[4];	
				}
			}
			else if (first=="CST"){
				if (sec=="CSP"){
					special_regs[4]=special_regs[3];  //we assign CSP's value to CST
				}
				else if (sec.substr(0, 3)=="CSG"){
					special_regs[4]=general_regs[Convert(sec)];

				}
			}
		}

		else if (inst.find("sub")!=string::npos || inst.find("add")!=string::npos || inst.find("div")!=string::npos || inst.find("mul")!=string::npos){
			string op, first, sec;	istringstream els(inst);
			els>>op>>first>>sec;

			if (!(first[0]<='z' && first[0]>='A')){ //we are checking all the possibilities of first and second var or num to make the operations accordingly

				if (!(sec[0]<='z' && sec[0]>='A')){
					int passed2=atoi(sec);	int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				} 
				else if (sec.substr(0, 3)=="CSG"){
					int passed2=general_regs[Convert(sec)];	int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSA"){
					int passed2=special_regs[0]; int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSB"){
					int passed2=special_regs[1];	int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSC"){
					int passed2=special_regs[2];	int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSP"){
					int passed2=special_regs[3];int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CST"){
					int passed2=special_regs[4];int passedval=atoi(first);
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
			}
			else if (first.substr(0, 3)=="CSG"){
				if (!(sec[0]<='z' && sec[0]>='A')){
					int passed2=atoi(sec);	int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				} 
				else if (sec.substr(0, 3)=="CSG"){
					int passed2=general_regs[Convert(sec)];	int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSA"){
					int passed2=special_regs[0];	int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSB"){
					int passed2=special_regs[1];int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSC"){
					int passed2=special_regs[2];int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSP"){
					int passed2=special_regs[3];int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CST"){
					int passed2=special_regs[4];int passedval=general_regs[Convert(first)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
			}
			else if (first=="CST" || first=="CSA" || first=="CSB" || first=="CSC" || first=="CSP") {
				int passedval;

				if (first=="CST") passedval=special_regs[4];	else if (first=="CSA") passedval=special_regs[0];
				else if (first=="CSB") passedval=special_regs[1];	else if (first=="CSC") passedval=special_regs[2];
				else if (first=="CSP") passedval=special_regs[3];

				if (!(sec[0]<='z' && sec[0]>='A')){
					int passed2=atoi(sec);	
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				} 
				else if (sec.substr(0, 3)=="CSG"){
					int passed2=general_regs[Convert(sec)];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSA"){
					int passed2=special_regs[0];	
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSB"){
					int passed2=special_regs[1];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSC"){
					int passed2=special_regs[2];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CSP"){
					int passed2=special_regs[3];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
				else if (sec=="CST"){
					int passed2=special_regs[4];
					SpecialRegsOperations(special_regs, passed2, op, passedval);
				}
			}
		}
	}

	else if (counter==1){ //if there is only one word in the instruction it can be print pop or ret 

		if (inst.find("print")!=string::npos){
			int thing;
			memory_stack.pop(thing);
			cout<<" Print Output: "<<thing<<endl;
		}
		else if (inst.find("pop")!=string::npos){
			int thing;
			memory_stack.pop(thing);
			special_regs[3]=thing; //we store the popped item in CSP
		}
		else if (inst.find("ret")!=string::npos){
			undone=false;
		}
	}
	else if (counter==2){ //if there are two words in the instruction, push instruction
		string push, thing;	istringstream els(inst);
		els>>push>>thing;

		if (!(thing[0]<='z' && thing[0]>='A')){ //if it is a number
			memory_stack.push(atoi(thing));
		}

		else if (thing.substr(0, 3)=="CSG"){
			memory_stack.push(general_regs[Convert(thing)]);
		}
		else if (thing=="CSA"){
			memory_stack.push(special_regs[0]);
		}
		else if (thing=="CSB"){
			memory_stack.push(special_regs[1]);
		}
		else if (thing=="CSC"){
			memory_stack.push(special_regs[2]);
		}
		else if (thing=="CSP"){
			memory_stack.push(special_regs[3]);
		}
		else if (thing=="CST"){
			memory_stack.push(special_regs[4]);
		}
	}
}

void run_one_instruction() {
	//dequeue one instruction from `instruction_queue` and run it accordingly
	if (instruction_queue.isEmpty()){
		cout<<"There is no instruction left."<<endl;
	}
	else{
		string inst, inst2; int counter=0; bool undone=true;
		instruction_queue.dequeue(inst); 
		RunningInstructions(counter, inst, undone);
		cout<<"Executed instruction: "<<inst<<endl;
	}
}

void run_until_end() {
	bool undone=true;
	if (instruction_queue.isEmpty()){
		cout<<"There is no instruction left."<<endl;
	}	
	else {
		while (!instruction_queue.isEmpty() && undone){
			string inst; int counter=0;
			instruction_queue.dequeue(inst);
			RunningInstructions(counter,inst, undone); //this function is reading the dequeued instruction and executes it.
		}
	}
}

void print_stack() {
	//print the values in the`memory_stack`
	if (memory_stack.isEmpty()){
		cout<<"Currently stack is empty.";
	}
	else {
		int top=memory_stack.GetTopPointer()->value;
		cout<<"Current Stack"<<endl<<endl;
			cout<<top; //i couldn't find a way to print the whole stack without emptying it. so i print just the top of it.
	}
}

void print_registers() {
	//print the registers
	cout<<"SPECIAL REGISTERS"<<endl<<endl;
	cout<<"CSA: "<<special_regs[0]<<endl<<"CSB: "<<special_regs[1]<<endl<<"CSC: "<<special_regs[2]<<endl
		<<"CSP: "<<special_regs[3]<<endl<<"CST: "<<special_regs[4]<<endl<<endl;
	cout<<"GENERAL USE REGISTERS"<<endl<<endl;
	for (int i=0; i<20; i++){
		cout<<"CSG"<<i<<": "<<general_regs[i]<<endl; //CSG0: 2... something like that will be printed for each
	}
}

void print_next_instruction() {
	//print the next Machine Code instruction to be executed
	if (instruction_queue.isEmpty()){
		cout<<"There is no instruction left."<<endl;
	}
	else{
		string inst1;
		cout<<endl<<"Next Instruction is: "<<instruction_queue.GetFront()->value; //we are getting the front value of the queue which is the next one to be dequeued.
	}
}

void print_remaining_instructions(int instr_counter) {
	//print the remaining instructions to execute in the `instruction_queue`

	if (instruction_queue.isEmpty()){
		cout<<"There is no instruction left."<<endl;
	}
	else {
		cout<<"******** INSTRUCTIONS ********"<<endl;	string inst;
		while(inst!="ret"){
			instruction_queue.dequeue(inst);
			cout<<"["<<instr_counter<<"] "<<inst<<endl;
			instr_counter++;
			instruction_queue.enqueue(inst); //we put the instruction back because we don't want to lose it
		}
	}
}

void print_variables() {
	//print the defined variables and their values
	cout<<"******** DEFINED VARIABLES ********"<<endl;
	for (int i=0; i<def_counter;i++)
		cout<<"a"+itoa(atoi(variables[i].substr(3))+1)<<": "<<general_regs[i]<<endl; //the a version of CSG's will be printed with this.
}

int main() {
	bool input_OK = false;
	while (true) {
		cout << endl;
		cout << "***********************************************************************" << endl
			<< "**************** 0 - EXIT PROGRAM                          ************" << endl
			<< "**************** 1 - GIVE INPUT FILE                       ************" << endl
			<< "**************** 2 - RUN UNTIL THE END                     ************" << endl
			<< "**************** 3 - RUN ONE INSTRUCTION                   ************" << endl
			<< "**************** 4 - PRINT CURRENT STACK                   ************" << endl
			<< "**************** 5 - PRINT REGISTER VALUES                 ************" << endl
			<< "**************** 6 - PRINT NEXT INSTRUCTION                ************" << endl
			<< "**************** 7 - PRINT REMAINING INSTRUCTIONS          ************" << endl
			<< "**************** 8 - PRINT DEFINED VARIABLES               ************" << endl
			<< "***********************************************************************" << endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 8): ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "PROGRAM EXITING ... " << endl;
			system("pause");
			exit(0);
		case 1:
			if (transform_source()) {
				input_OK = true;
			}
			else {
				cout << "There is a problem with the input file." << endl;
			}
			break;
		case 2:
			if (input_OK) {
				run_until_end();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 3:
			if (input_OK) {
				run_one_instruction();
				print_next_instruction();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 4:
			if (input_OK) {
				print_stack();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 5:
			if (input_OK) {
				print_registers();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 6:
			if (input_OK) {
				print_next_instruction();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 7:
			if (input_OK) {
				print_remaining_instructions(instr_counter);
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 8:
			if (input_OK) {
				print_variables();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		default:
			cout << "INVALID OPTION!!! Try again" << endl;
		}
	}

	return 0;
}