#include <iostream>
#include <string>

using namespace std;

void AddCharNumbers(string, string, string&);
void SubtractCharNumbers(string, string, string&);
void MultiplyCharNumbers(string, string, string&);
void DivideCharNumbers(string, string, string&);
void DivideSmallCharNumbers(string, string, string&, string&);
void RemoveLeadingZero(string&);
void ZeroIfEmpty(string&);

int main() {
  string a = "";
  string b = "";
  string sum = "";
  string line = "";
  int number_of_tests = 0;
  cin >> number_of_tests;
  for (size_t i = 0; i < number_of_tests; i++) {
    cin >> line;
    size_t found = line.find("+");
    sum = "";
    if (found != -1) {
      a = line.substr(0, found);
      b = line.substr(found + 1, line.length());
      AddCharNumbers(a, b, sum);
      ZeroIfEmpty(sum);
    }
    found = line.find("*");
    if (found != -1) {
      a = line.substr(0, found);
      b = line.substr(found + 1, line.length());
      MultiplyCharNumbers(a, b, sum);
      ZeroIfEmpty(sum);
    }
    found = line.find("-");
    if (found != -1) {
      a = line.substr(0, found);
      b = line.substr(found + 1, line.length());
      SubtractCharNumbers(a, b, sum);
      ZeroIfEmpty(sum);
    }
    found = line.find("/");
    if (found != -1) {
      a = line.substr(0, found);
      b = line.substr(found + 1, line.length());
      DivideCharNumbers(a, b, sum);
      ZeroIfEmpty(sum);
    }
    cout << sum << endl;
  }
}

void AddCharNumbers(string a, string b, string& result) {
  bool carry = 0;
  string temp_sum = "";
  if (a.length() > b.length()) {
    string temp;
    temp = b;
    b = a;
    a = temp;
  }
  for (size_t i = 1; i <= b.length(); i++) {
    int a_int = (i < a.length() + 1) ? (a[a.length() - i] - '0') : 0;
    int b_int = (i < b.length() + 1) ? (b[b.length() - i] - '0') : 0;
    int current_number = (b_int + a_int + carry);
    carry = (current_number > 9) ? 1 : 0;
    temp_sum.insert(0, to_string(current_number % 10));
  }
  if (carry) {
    temp_sum.insert(0, to_string(carry));
  }
  RemoveLeadingZero(temp_sum);
  result = temp_sum;
}

void SubtractCharNumbers(string a, string b, string& result) {
  bool carry = 0;
  string temp_sum = "";
  if (a.length() < b.length()) {
    for (size_t i = 0; i < a.length() - b.length(); i++) {
      a.insert(0, "0");
    }
  }
  for (size_t i = 1; i <= a.length(); i++) {
    int a_int = (i < a.length() + 1) ? (a[a.length() - i] - '0') : 0;
    int b_int = (i < b.length() + 1) ? (b[b.length() - i] - '0') : 0;
    int current_number = a_int - b_int - carry;
    if (current_number < 0) {
      carry = 1;
      current_number += 10;
    } else {
      carry = 0;
    }
    temp_sum.insert(0, to_string(current_number % 10));
  }
  if (carry) {  // a < b
    temp_sum = "";
    SubtractCharNumbers(b, a, temp_sum);
    temp_sum.insert(0, "-");
  }
  RemoveLeadingZero(temp_sum);
  result = temp_sum;
}

void MultiplyCharNumbers(string a, string b, string& result) {
  string temp_result = "";
  for (size_t i = 1; i <= b.length(); i++) {
    int current_number = 0;
    int carry = 0;
    string temp_sum = "";
    int b_int = (i < b.length() + 1) ? (b[b.length() - i] - '0') : 0;
    for (size_t j = 1; j <= a.length(); j++) {
      int a_int = (j < a.length() + 1) ? (a[a.length() - j] - '0') : 0;
      current_number = (b_int * a_int) + carry;
      if (current_number > 9) {
        carry = current_number / 10;
        current_number = current_number % 10;
      } else {
        carry = 0;
      }
      temp_sum.insert(0, to_string(current_number));
    }
    for (size_t k = 0; k < i - 1; k++) {
      temp_sum += "0";
    }
    if (carry) {
      temp_sum.insert(0, to_string(carry));
    }
    if (temp_result.length()) {
      AddCharNumbers(temp_sum, temp_result, temp_result);
    } else {
      temp_result = temp_sum;
    }
  }
  RemoveLeadingZero(temp_result);
  result = temp_result;
}

void DivideSmallCharNumbers(string a, string b, string& sum, string& rem) {
  string temp_sum = "";
  string temp_sum2 = "";
  string temp_rem = a;
  int sum_int = 0;
  RemoveLeadingZero(b);
  if (b == "") {
    sum = "NaN";
    return;
  }
  while (1) {
    AddCharNumbers(temp_sum, b, temp_sum);
    SubtractCharNumbers(a, temp_sum, temp_sum2);
    RemoveLeadingZero(temp_sum2);
    if (temp_sum2[0] == '-') {
      break;
    } else {
      temp_rem = temp_sum2;
    }
    sum_int++;
  }
  rem = temp_rem;
  sum = to_string(sum_int);
}

void DivideCharNumbers(string a, string b, string& result) {
  string temp_result = "";
  string temp_rem = a.substr(0, 1);
  RemoveLeadingZero(b);
  if (b == "") {
    result = "NaN";
    return;
  }
  for (size_t i = 0; i < a.length(); i++) {
    DivideSmallCharNumbers(temp_rem, b, temp_result, temp_rem);
    result.append(temp_result);
    temp_rem.append(a.substr(i + 1, 1));
  }
  RemoveLeadingZero(result);
}

void RemoveLeadingZero(string& str) {
  str.erase(0, str.find_first_not_of('0'));
}

void ZeroIfEmpty(string& str) {
  if (str.length() == 0) str = "0";
}