#include <iostream>
#include <string>
using namespace std;

class Human {
protected: //we made these protected because all the subclasses need to access and have these member variables
	string name;
	int age;

public:
	Human (){}
	Human (string name, int age): age(age), name(name) { } // all humans (muggles, wizardkins (students, grownups)) will have an age and name
	~Human () {}

	virtual void printInfo(){ //we made this one virtual in order to prevent confusion
		cout<<"Human informations"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Age: "<<age<<endl;
	}
};

class Muggle : public Human {

public:
	Muggle(string name, int age, string job): Human(name, age), job(job) { } //we assign name and age with human base class
	~Muggle(){}

	void printInfo(){
		cout<<"Muggle Informations"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Age: "<<age<<endl;
		cout<<"Job: "<<job<<endl<<endl;
	}

private:
	string job;

};

class Wizardkind : public Human {

public:
	Wizardkind(string name, int age, string wand): Human(name, age), wand(wand) { }
	~Wizardkind(){}

	virtual void printInfo() {
		cout<<"Wizardkind Informations"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Age: "<<age<<endl;
		cout<<"Wand: "<<wand<<endl;
	}
	void doSpell(string spell){
		cout<<name<<" used spell: "<<spell<<endl;
	}

protected:
	string wand; //wand will be used in the subclasses of wizardkind that's why we made that variable protected
};

class Student : public Wizardkind {

public:
	Student(string name, int age, string wand, string pet, string house): Wizardkind(name, age, wand), 
		pet(pet), houseName(house) { } //we assigned age, wand and name to the base class. additional member variables are pet and houe for a student
	~Student(){}

	void printInfo(){
		cout<<"Student Wizardkind Informations"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Age: "<<age<<endl;
		cout<<"House: "<<houseName<<endl;
		cout<<"Wand: "<<wand<<endl;
		cout<<"Pet: "<<pet<<endl;
	}
	void feedPet() {
		cout<<name<<" fed "<<pet<<endl; 
	}

private:
	string pet;
	string houseName;
};

class GrownUp : public Wizardkind {

public:
	GrownUp(string name, int age, string wand, string job): Wizardkind(name, age, wand), job(job){ } //besides wizardkind variables, grownup wizardkinds have an aditional job variable
	~GrownUp(){}

	void printInfo(){
		cout<<"Grownup Wizardkind Informations"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Age: "<<age<<endl;
		cout<<"Wand: "<<wand<<endl;
		cout<<"Job: "<<job<<endl;	}

private: //this class doesn't have a subclass so we can make the variable job private
	string job;
};


int main(){
	Muggle vernon("Vernon Dursley", 50, "Director at Grunnings");
	vernon.printInfo();
	cout << endl;
	Student Harry("Harry Potter", 16, "Phoenix Feather", "Hedwig", "Gryffindor");
	Harry.printInfo();
	cout << endl;
	GrownUp Dumbledore("Albus Dumbledore", 110, "Elder Wand", "Headmaster");
	Dumbledore.printInfo();
	cout << endl;
	Dumbledore.doSpell("Expecto Patronum");
	cout << endl;
	Harry.doSpell("Expelliarmus");
	cout << endl;
	Harry.feedPet();
	cout << endl;
	Student Ginny("Ginny Weasley", 15, "Yew wood", "Arnold", "Gryffindor");
	GrownUp Snape("Severus Snape", 35, "Dragon Heartstring", "Potion Master");
	Student Hermione("Hermione Granger", 16, "Vine", "Crookshanks", "Gryffindor");
	Human hArray[6];
	hArray[0] = vernon;
	hArray[1] = Harry;
	hArray[2] = Dumbledore;
	hArray[3] = Ginny;
	hArray[4] = Snape;
	hArray[5] = Hermione;
	Human * hPtr;
	for (int i = 0; i < 6; i++) {
		cout << endl;
		hPtr = &hArray[i];
		hPtr->printInfo();
	}
	cout << endl;
	system("pause");
	return 0;
}