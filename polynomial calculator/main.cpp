#include<iostream>
#include<string>
#include<cstring>
#include"Poly_Calcltor.h"
using std::cin;
using std::cout;
using std::string;
using std::ios_base;
using std::endl;

int main() {
  string s1, s2;
  cout << "Welcome to use the Polynomial calculator!" << endl;
  int begin = 4;
  Poly_Calcltor pc;
  while (begin) {   
    if (4 == begin) {
      cout << "Please input 2 polynomials to be compute" << endl;
      cin >> s1 >> s2;
      pc.update(s1, s2);
    }
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Please select a operation" << endl;
    cout << "1:  a + b:   add these two polinomial up, type [1]" << endl;
    cout << "2:  a - b:   use the 1st polinomial substract the 2nd polinomial, type [2]" << endl;
    cout << "3:  b - a:   use the 2nd polinomial substract the 1st polinomial, type [3]" << endl;
    cout << "4:  a * b:   multiply these two polinomial, type [4]" << endl;
    cout << "5:  a':   get the derivative of the 1st polinomial, type [5]" << endl;
    cout << "6:  b':   get the derivative of the 2nd polinomial, type [6]" << endl;
    cout << "7:  a(x):   compute the 1st polinomial the a certain number, type [7]" << endl;
    cout << "8:  b(x):   compute the 2nd polinomial the a certain number, type [8]" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    int cmd;
    cin >> cmd;
    Poly result;
    switch (cmd) {
    case 1:
      result = pc.add();
      print(result);
      break;
    case 2:
      result = pc.sub(1);
      print(result);
      break;
    case 3:
      result = pc.sub(2);
      print(result);
      break;
    case 4:
      result = pc.multy();
      print(result);
      break;
    case 5:
      result = pc.deriv(1);
      print(result);
      break;
    case 6:
      result = pc.deriv(2);
      print(result);
      break;
    case 7:
      cout << "Please input a number to be calculate" << endl;
      int x1;
      cin >> x1;
      cout << "a(" << x1 << ") = " << pc.cpt(x1, 1) << endl;
      break;
    case 8:
      cout << "Please input a number to be calculate" << endl;
      int x2;
      cin >> x2;
      cout << "b(" << x2 << ") = " << pc.cpt(x2, 2) << endl;
      break;
    default:
      break;
    }
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << " continue with these two polinomials, type [1]" << endl;
    cout << " use another two polinomials, type [2]" << endl;
    cout << " exit, type [0]" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cin >> begin;
    if (1 == begin) {
      continue;
    }
    else if (2 == begin) {
      cin >> s1 >> s2;
      pc.update(s1, s2);
    }
    else if (0 == begin) {
      cout << "Thanks for using~~~" << endl;
      pc.freePc();
      break;
    }
  } 
  return 0;
}