/**********************************
* ПИ-221                          *
* Иванов Тимофей                  *
* Калькулятор                     *
* 17.11.2022                      *
**********************************/

https://onlinegdb.com/N7HnPFdKM

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printNumber (string number) {
  int flag = 1;
  for (int position = 0; position < number.length() - 1; ++position) {
    if (number[position] != '0') {
      flag = 0;
    }
    if (flag == 0) {
      cout << number[position];
    }
  }
  cout << number[number.length() - 1];
}

int comparison(string firstNumber, string secondNumber, char firstSign, char secondSign) {
  if (firstSign == '+' && secondSign == '-') {
    printNumber(firstNumber);
    cout << " больше";
    return 0;
  }
  if (firstSign == '-' && secondSign == '+') {
    printNumber(secondNumber);
    cout << " больше";
    return 0;
  }
  if (firstSign == '+') {
    if (firstNumber > secondNumber) {
      printNumber(firstNumber);
      cout << " больше";
    }
    else if (firstNumber < secondNumber) {
      printNumber(secondNumber);
      cout << " больше";    
    }
    else {
      cout << "числа равны";
    }
  } 
  else {
    if (firstNumber > secondNumber) {
      cout << secondSign;
      printNumber(secondNumber);
      cout << " больше";
    }
    else if (firstNumber < secondNumber) {
      cout << firstSign;
      printNumber(firstNumber);
      cout << " больше";    
    }
    else {
      cout << "числа равны";
    }
  }
  return 0;
}

string summation(string firstNumber, string secondNumber) {
  for (int position = firstNumber.length() - 1; position > 0; --position){
    char result = firstNumber[position] + secondNumber[position] - 48;
    if (result > 57) {
      firstNumber[position - 1] += 1;
      firstNumber[position] = result - 10;
    }
    else {
      firstNumber[position] = result;
    }
  }
  char result = firstNumber[0] + secondNumber[0] - 48;
  if (result > 57) {
    firstNumber[0] = result - 10;
    firstNumber = '1' + firstNumber;
  }
  else {
    firstNumber[0] = result;
  }
  return firstNumber;
}

string subtraction(string firstNumber, string secondNumber) {
  while (secondNumber.length() < firstNumber.length()) {
    secondNumber = "0" + secondNumber;
  }
  while (firstNumber.length() < secondNumber.length()) {
    firstNumber = "0" + firstNumber;
  }
  for (int position = secondNumber.length() - 1; position >= 0; --position) {
    if (firstNumber[position] >= secondNumber[position]) {
      firstNumber[position] = firstNumber[position] - secondNumber[position] + 48;
    }
    else {
      int reservePosition = position - 1;
      while (firstNumber[reservePosition] == '0') {
        firstNumber[reservePosition] = '9';
        reservePosition -= 1;
      }
      firstNumber[reservePosition] = firstNumber[reservePosition] - 1;
      firstNumber[position] = 58 - (secondNumber[position] - firstNumber[position]);
    }
  }
  while ((firstNumber[0] == '0') && (firstNumber.length() > 1)) {
    firstNumber.replace(0, 1, "");
  }
  return firstNumber;
}

void multiplication(string firstNumber, string secondNumber, char firstSign, char secondSign) {
  int nearResult;
  int result[firstNumber.length() + secondNumber.length()];
  for (int position = 0; position < firstNumber.length() + secondNumber.length(); ++position) {
    result[position] = 0;
  }
  for (int firstDigit = firstNumber.length() - 1; firstDigit >= 0; --firstDigit) {
    for (int secondDigit = secondNumber.length() - 1; secondDigit >= 0; --secondDigit) {
      nearResult = (firstNumber[firstDigit] - 48) * (secondNumber[secondDigit] - 48) + result[firstDigit + secondDigit + 1]; //т.к. числа в ASCII начинаются с 48
      result[firstDigit + secondDigit] += nearResult / 10;
      result[firstDigit + secondDigit + 1] = nearResult % 10;
    }
  }
  if (firstSign != secondSign) {
    cout << "-";
  }
  int flag = 1;
  for (int position = 0; position < firstNumber.length() + secondNumber.length() - 1; ++position) {
    if (result[position] != 0) {
      flag = 0;
    }
    if (flag == 0) {
      cout << result[position];
    }
  }
  cout << result[firstNumber.length() + secondNumber.length() - 1];
}

void division(string firstNumber, string secondNumber, char firstSign, char secondSign) {
  vector <int> result;
  while ((firstNumber.length() > secondNumber.length()) || ((firstNumber >= secondNumber) && (firstNumber.length() == secondNumber.length()))) {
    string partOfFirst;
    partOfFirst.assign(firstNumber, 0, secondNumber.length());
    if (partOfFirst < secondNumber) {
      partOfFirst.assign(firstNumber, 0, secondNumber.length() + 1);
    }
    firstNumber.assign(firstNumber, partOfFirst.length());
    result.push_back(1);
    partOfFirst = subtraction(partOfFirst, secondNumber);
    while ((partOfFirst.length() > secondNumber.length()) || ((partOfFirst.length() == secondNumber.length()) && (partOfFirst >= secondNumber))) {
      partOfFirst = subtraction(partOfFirst, secondNumber);
      result[result.size() - 1] += 1;
    }
    firstNumber = partOfFirst + firstNumber;
  }
  if (firstSign != secondSign) {
    cout << "-";
  }
  if (result.size() == 0) {
    cout << "0";
  }
  for (int position = 0; position < result.size(); ++position) {
    cout << result[position];
  }
}

int main() {
  string firstNumber, secondNumber;
  char action;
  cout << "Доступные действия: + | - | * | / | ?(для сравнения)\n" << "Введите пример: ";
  cin >> firstNumber >> action >> secondNumber;
  char firstSign = '+';
  char secondSign = '+';
  if (firstNumber[0] == '-') {
    firstSign = '-';
    firstNumber.erase(0, 1);        // убираем занк "-" из строки с числом;
  }
  if (secondNumber[0] == '-') {
    secondSign = '-';
    secondNumber.erase(0, 1);
  }
  
  if (action == '*') {
    multiplication(firstNumber, secondNumber, firstSign, secondSign);
    return 0;
  }
  if (action == '/') {
    if (secondNumber == "0") {
      cout << "на ноль делить нельзя";
      return 0;
    }
    division(firstNumber, secondNumber, firstSign, secondSign);
    return 0;
  }
  
  while (secondNumber.length() < firstNumber.length()) {
    secondNumber = "0" + secondNumber;
  }
  while (firstNumber.length() < secondNumber.length()) {
    firstNumber = "0" + firstNumber;
  }
  
  if (action == '?') {
    comparison(firstNumber, secondNumber, firstSign, secondSign);
    return 0;
  }
  
  bool switchSign = false;
  if (firstNumber < secondNumber) {
    string reserveNumber = secondNumber;
    secondNumber = firstNumber;
    firstNumber = reserveNumber;
    switchSign = true;
  }
    
  if (action == '+') {
    if (firstSign == secondSign) {
      if (firstSign == '-') {
        cout << '-';
      }
    }
    else if (((firstSign == '-') && (!switchSign)) || ((firstSign == '+') && (switchSign))) {
      cout << '-';
    }
    if (firstSign == secondSign) {
      cout << summation(firstNumber, secondNumber);
    }
    else {
      cout << subtraction(firstNumber, secondNumber);
    }
    return 0;
  }
  if (action == '-'){
    if (firstSign == secondSign) {
      string result = subtraction(firstNumber, secondNumber);
      if ((((firstSign == '+') && switchSign) || ((firstSign == '-') && !switchSign)) && (result != "0")) {
        cout << '-';
      }
      cout << result;
      return 0;
    }
    else {
      string result = summation(firstNumber, secondNumber);
      if (firstSign == '-') {
        cout << '-';
      }
      cout << result;
      return 0;
    }
  }
  cout << "Недоступное действие";
  return 0;
}
