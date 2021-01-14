#include <iostream>
#include <string>

using namespace std;

void AddCharNumbers(string a, string b, string& sum);
void SubtractCharNumbers(string a, string b, string& sum);

int main() {
  string a = "12345678901234567890";
  string b = "98765432109876543210";
  string sum = "";
  AddCharNumbers(a, b, sum);
  cout << a << endl << b << endl << sum << endl << endl;

  sum = "";
  SubtractCharNumbers(a, b, sum);
  cout << a << endl << "-" << b << endl << sum << endl << endl;
}

void AddCharNumbers(string a, string b, string& sum) {
  bool carry = 0;
  int a_int = 0;
  int b_int = 0;
  int current_number = 0;
  if (a.length() > b.length()) {
    string temp;
    temp = b;
    b = a;
    a = temp;
  }
  for (size_t i = 1; i <= b.length(); i++) {
    a_int = (i < a.length() + 1) ? (a[a.length() - i] - '0') : 0;
    b_int = (i < b.length() + 1) ? (b[b.length() - i] - '0') : 0;
    current_number = (b_int + a_int + carry);
    carry = (current_number > 9) ? 1 : 0;
    sum.insert(0, to_string(current_number % 10));
  }
  if (carry) {
    sum.insert(0, to_string(carry));
  }
}

void SubtractCharNumbers(string a, string b, string& sum) {
  bool carry = 0;
  int a_int = 0;
  int b_int = 0;
  int carry_number = 0;
  bool flag = 0;
  if (a.length() < b.length()) {
    for (size_t i = 0; i < b.length()-a.length(); i++) {
      a.insert(0, "0");
    }
  }
  for (size_t i = 1; i <= a.length(); i++) {
    a_int = (i < a.length() + 1) ? (a[a.length() - i] - '0') : 0;
    b_int = (i < b.length() + 1) ? (b[b.length() - i] - '0') : 0;
    carry_number = a_int - b_int - carry;
    if (carry_number < 0) {
      carry = 1;
      carry_number += 10;
    } else {
      carry = 0;
    }
    sum.insert(0, to_string(carry_number % 10));
  }
  if (carry) { // a < b
    sum = "";
    SubtractCharNumbers(b, a, sum);
    sum.insert(0, "-");
  }
}