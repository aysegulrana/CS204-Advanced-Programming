#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class Encrypter {
private:
	const T key;
	const int nShifts;

public:
	vector<int> listFlips;

	Encrypter (T t, int i, vector<int> vec): key(t), nShifts(i), listFlips(vec){
	}

	T encrypt(const T decrypted){

		T x = decrypted^key;

		cout<<"Xor result: "<<x<<endl;

		T left;

		int shift=nShifts;
		if (shift>(sizeof(x)*8)) shift=shift%(sizeof(x)*8); 

		//circular shift starts
		for (int i=0; i<shift; i++){ //in each iteration we look at the left bit
			left = (1<<(sizeof(x)*8)-1) & x; //we found the left bit of x by this
			x = x << 1; //we shifted, left element disappeared but we held it in left
			x = x | (left >> (sizeof(x)*8)-1); //we assigned the right bit to the held left bit of x
		}

		cout<<"Shift result: "<< x <<endl;

		T fliphelper = 0;
		T a;
		vector<int> flipvec;
		for (int i=0; i < listFlips.size(); i++){
			if (listFlips[i] < sizeof(x)*8){
				a=(T)1<<listFlips[i]; //we created a object which has all 0s but one 1 in its bits, 1 is on the given index 
				fliphelper = fliphelper+a; //fliphelper was zero, we added a and now the given index of fliphelper is 1 too
				flipvec.push_back(listFlips[i]); //we pushed the flipped index, the indexes which are out of range won't be pushed
			}
		}

		x=x^fliphelper; //now the 1 indexes flipped with xor operation

		listFlips=flipvec; //listflips became flipvec because we did not use some of it's indexes
		return x;
	}

	T decrypt(const T encrypted){ //this makes operations just in the opposite way 

		T fliphelper = 0;
		T a;
		for (int i=0; i < listFlips.size(); i++){
			if (listFlips[i] < sizeof(encrypted)*8){
				a=(T)1<<listFlips[i];
				fliphelper = fliphelper+a;
			}
		}

		T x=encrypted;
		x=x^fliphelper;

		T right;

		int shift=nShifts;
		if (shift>(sizeof(x)*8)) shift=shift%(sizeof(x)*8);

		for (int i=0; i<shift; i++){
			right = 1 & x;
			x = x >> 1;
			x = x | (right << (sizeof(x)*8)-1);
		}

		x = x^key;
		return x;
	}
};


int main() {

	int nShifts = 12;
	vector<int> listFlips;
	listFlips.push_back(0); listFlips.push_back(1); listFlips.push_back(2); listFlips.push_back(3);
	listFlips.push_back(4); listFlips.push_back(9); listFlips.push_back(15); listFlips.push_back(30); listFlips.push_back(35);


	unsigned char key1 = 101;
	unsigned char chClear = 'b';
	Encrypter<unsigned char> encrypterChar(key1, nShifts, listFlips);

	cout << "Char to encrypt: " << chClear << endl;
	unsigned char encryptedCh = encrypterChar.encrypt(chClear);
	unsigned char decryptedCh = encrypterChar.decrypt(encryptedCh);

	cout << "Char encrypted: " << encryptedCh << endl;
	cout << "Char decrypted: " << decryptedCh << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterChar.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;

	unsigned short int key2 = 101;
	unsigned short int intShortClear = 500;
	Encrypter<unsigned short int> encrypterShortInt(key2, nShifts, listFlips);

	cout << "Short Int to encrypt: " << intShortClear << endl;
	unsigned short int encryptedShortInt = encrypterShortInt.encrypt(intShortClear);
	unsigned short int decryptedShortInt = encrypterShortInt.decrypt(encryptedShortInt);

	cout << "Short Int encrypted: " << encryptedShortInt << endl;
	cout << "Short Int decrypted: " << decryptedShortInt << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterShortInt.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;

	unsigned int key3 = 101;
	unsigned int intClear = 32800;
	Encrypter<unsigned int> encrypterInt(key3, nShifts, listFlips);

	cout << "Int to encrypt: " << intClear << endl;
	unsigned int encryptedInt = encrypterInt.encrypt(intClear);
	unsigned int decryptedInt = encrypterInt.decrypt(encryptedInt);

	cout << "Int encrypted: " << encryptedInt << endl;
	cout << "Int decrypted: " << decryptedInt << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterInt.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;

	unsigned long long int key4 = 101;
	unsigned long long int intLLClear = 34359738368;
	Encrypter<unsigned long long int> encrypterLLInt(key4, nShifts, listFlips);

	cout << "Long Long Int to encrypt: " << intLLClear << endl;
	unsigned long long int encryptedLLInt = encrypterLLInt.encrypt(intLLClear);
	unsigned long long int decryptedLLInt = encrypterLLInt.decrypt(encryptedLLInt);

	cout << "Long Long Int encrypted: " << encryptedLLInt << endl;
	cout << "Long Long Int decrypted: " << decryptedLLInt << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterLLInt.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;


	system("pause");
	return 0;
}