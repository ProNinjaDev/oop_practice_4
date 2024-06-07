#include <iostream>
#include <locale.h>
#include <vector>
//#include <string>



class String {
protected:
	char* arr;
	int size;

public:
	String() { size = 0; }

	String(const char* str) {
		size = 0;
		while (str[size] != '\0') {
			size += 1;
		}

		arr = new char[size + 1];
		for (int i = 0; i != size; ++i) {
			arr[i] = str[i];
		}

		arr[size] = '\0';
		

	}

	String(char symbol) {
		size = 1;
		arr = new char[size + 1];
		arr[0] = symbol;
		arr[1] = '\0';
	}

	
	String(const String& str) {
		size = str.size;

		arr = new char[size + 1];
		for (int i = 0; i != size; ++i) {
			arr[i] = str.arr[i];
		}

		arr[size] = '\0';

	}

	int GetLengthString() const {
		return size;
	}
	char* GetString() const {
		return arr;
	}

	void PrintString() const {
		for (int i = 0; i != size; ++i) {
			std::cout << arr[i];
		}
		std::cout << std::endl;
	}
	virtual bool IsInt() const { return false; }

	void ClearString() {
		delete[] arr;
		size = 0;
	}

	void PrintString() {
		for (int i = 0; i != size; ++i) {
			std::cout << arr[i];
		}
	}

	~String() {
		if (arr != nullptr) 
			delete[] arr;
		size = 0;
	}

};

class TypeMismatch {
	String m_message;

public:
	TypeMismatch(String message) {
		m_message = message;
	}
	
	void GetMessage() const {
		std::cout << std::endl;
		m_message.PrintString();
	}
};


class NumericString : public String {
public:

	NumericString() : String() {}

	NumericString(const char* arr) : String(arr) {
		bool isValid = true;
		
		if (arr[0] == '+' || arr[0] == '-')
			for (int i = 1; i != size; ++i) {
				if (arr[i] < '0' || arr[i] > '9') {
					isValid = false;
					break;
				}
			}
		else {
			for (int i = 0; i != size; ++i) {
				if (arr[i] < '0' || arr[i] > '9') {
					isValid = false;
					break;
				}
			}
		}

		if (!isValid) {
			ClearString();
			std::cout << std::endl << "Строка не соответствует условиям десятичной строки" << std::endl;
		}
	}

	NumericString(char symbol) : String(symbol) {
		if (arr[0] < '0' || arr[0] > '9') {
			ClearString();
			std::cout << std::endl << "Строка не соответствует условиям десятичной строки" << std::endl;
		}
		
	}

	NumericString(const String& str) : String(str) {
		bool isValid = true;

		/*size = str.GetLengthString();

		arr = new char[size + 1];*/

		if (arr[0] == '+' || arr[0] == '-')
			for (int i = 1; i < size; i++) {
				if (arr[i] < '0' || arr[i] > '9') {
					isValid = false;
					break;
				}
			}
		else {
			for (int i = 0; i < size; i++) {
				if (arr[i] < '0' || arr[i] > '9') {
					isValid = false;
					break;
				}
			}
		}
		/*char* head = str.GetString();
		for (int i = 0; i < size; i++) {
			arr[i] = head[i];
		}*/

		if (!isValid) {
			ClearString();
			std::cout << std::endl << "Строка не соответствует условиям десятичной строки" << std::endl;
		}
	}


	bool IsInt() const override {
		NumericString minusInt = "-2147483648";
		NumericString plusInt = "2147483648";

		if (!GetLengthString()) {
			return false;
		}

		if (arr[0] == '0')
			return false;

		if (arr[0] == '-' || arr[0] == '+') {
			if (GetLengthString() > minusInt.size)
				return false;

			if (GetLengthString() == minusInt.size) {
				for (int i = 1; i != minusInt.size; ++i) {
					if (arr[i] > minusInt.arr[i]) {
						return false;
						break;
					}
				}
			}
		}
		else
		{
			if (GetLengthString() > plusInt.size)
				return false;

			if (GetLengthString() == plusInt.size) {
				for (int i = 0; i != plusInt.size; ++i) {
					if (arr[i] > plusInt.arr[i]) {
						return false;
						break;
					}
				}
			}
		}
		return true;
	}

	NumericString& operator = (const NumericString& str) {
		ClearString();

		size = str.size;
		arr = new char[size + 1];
		for (int i = 0; i != size; ++i) {
			arr[i] = str.arr[i];
		}
		arr[size] = '\0';
		
		return *this;
	}

	bool operator < (const NumericString str) {
		if (!this->IsInt() || !str.IsInt()) 
			throw TypeMismatch("Сравнивать можно только величины типа int!");
		

		if (this->size != str.size) {
			if (this->arr[0] == '-' && str.arr[0] != '-') {
				return true;
			}
			else if (this->arr[0] != '-' && str.arr[0] == '-') {
				return false;
			}
			else if (this->arr[0] == '-' && str.arr[0] == '-') {
				
				if (this->size > str.size) return false;
				if (this->size < str.size) return true;
			}
		}

		for (int i = 0; i < this->size; i++) {
			if (this->arr[i] > str.arr[i]) return false;
			if (this->arr[i] < str.arr[i]) return true;
		}
		
		return false;
	}

	bool operator > (const NumericString& str) const {
		if (!this->IsInt() || !str.IsInt())
			throw TypeMismatch("Сравнивать можно только величины типа Int!");

		else if (this->arr[0] == '-' && str.arr[0] != '-') {
			return false;
		}
		else if (this->arr[0] != '-' && str.arr[0] == '-') {
			return true;
		}

		for (int i = 0; i < this->size; i++) {
			if (this->arr[i] < str.arr[i]) return false;
			if (this->arr[i] > str.arr[i]) return true;
		}

		return false;
	}

	
};

void bubbleSort(std::vector<String*>& strings) {
	int lenStr = strings.size();
	for (int i = 0; i < lenStr - 1; i++) {
		for (int j = 0; j < lenStr - i - 1; j++) {
			NumericString* numStr = dynamic_cast<NumericString*>(strings[j]);
			NumericString* nextNumStr = dynamic_cast<NumericString*>(strings[j + 1]);

			if (*numStr > *nextNumStr) {
				std::swap(*numStr, *nextNumStr);
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "Rus");
	std::vector<String*> strings;

	const char* str1 = "324242334324589797897897898797123";
	const char* str2 = "-1778879987987897889788978877823";
	String str3 = "49199929392393292939392993293929293292932";
	char str4 = '5';
	const char* str5 = "neInt";

	try {

		strings.push_back(new NumericString(str1));
		strings.push_back(new NumericString(str2));
		strings.push_back(new NumericString(str3));
		strings.push_back(new NumericString(str4));
		strings.push_back(new String(str5));

		for (int i = 0; i < strings.size(); i++) {
			strings[i]->PrintString();

			std::cout << std::endl << "Длина строки: " << strings[i]->GetLengthString() << std::endl;

			NumericString* numString = dynamic_cast<NumericString*>(strings[i]);
			if (strings[i]->IsInt())
				std::cout << "Перевод в int возможен" << std::endl;
			else
				std::cout << "Перевод в int невозможен" << std::endl;

			std::cout << std::endl << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
		}

		std::cout << std::endl;

		NumericString* numString1 = dynamic_cast<NumericString*>(strings[0]);
		NumericString* numString3 = dynamic_cast<NumericString*>(strings[2]);

		std::cout << "Сравнение первой десятичной строки с третьей: "; 
		numString1->PrintString();
		std::cout <<" < ";
		numString3->PrintString();
		std::cout << " - " << std::boolalpha << (*numString1 < *numString3) << std::endl;

		strings.pop_back();
		strings.pop_back();

		bubbleSort(strings);
		std::cout << std::endl << "Отсортированный массив:" << std::endl;
		for (String* str : strings) {
			str->PrintString();
			std::cout << std::endl;
		}


	}
	catch (TypeMismatch error) {
		error.GetMessage();
	}

	for (auto& str : strings) {
		delete str;
	}

	strings.clear();
}