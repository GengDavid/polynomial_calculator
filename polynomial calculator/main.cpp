#include<iostream>
#include<string>
#include<cstring>
#include"Poly_Calcltor.h"
#include"Calc_List.h"
using std::cin;
using std::cout;
using std::string;
using std::ios_base;
using std::endl;

int main() {
  string s1, s2;
  cout << "Welcome to use the Polynomial calculator!" << endl;
  int begin = 1;
  while (begin) {
    cout << "Please input 2 polynomials to be compute" << endl;
    cin >> s1 >> s2;
    //try {
    Poly_Calcltor pc(s1, s2);
    //}
    //catch (...) {
    //cout << "Input invalid!" << endl;
    //cout << "Please input again." << endl;
    //}
    cout << "Please select a operation" << endl;
    cout << "1:  a + b:  if you want to add these two polinomial up, click [1]" << endl;
    cout << "2:  a - b:  if you want to use the 1st polinomial substract the 2nd polinomial, click [2]" << endl;
    cout << "3:  b - a:  if you want to use the 2nd polinomial substract the 1st polinomial, click [3]" << endl;
    cout << "4:  a * b:  if you want to multiply these two polinomial, click [4]" << endl;
    cout << "5:  a':  if you want to get the derivative of the 1st polinomial, click [5]" << endl;
    cout << "6:  b':  if you want to get the derivative of the 2nd polinomial, click [6]" << endl;
    cout << "7:  a(x):  if you want to compute the 1st polinomial the a certain number, click [7]" << endl;
    cout << "8:  b(x):  if you want to compute the 2nd polinomial the a certain number, click [8]" << endl;
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
      cout << pc.cpt(x1, 1) << endl;
      break;
    case 8:
      cout << "Please input a number to be calculate" << endl;
      int x2;
      cin >> x2;
      cout << pc.cpt(x2, 2) << endl;
      break;
    default:
      break;
    }

    cout << "If you want to continue with these two polinomials, click [1]" << endl;
    cout << "If you want to use another two polinomials, click [2]" << endl;
    cout << "If you want to exit, click [0]" << endl;
    cin >> begin;
    if (1 == begin) {
      continue;
    }
    else if (2 == begin) {
      cin >> s1 >> s2;
      pc.update(s1, s2);
    }
    else if (0 == begin) {
      cout << "Thanks for using" << endl;
      pc.freePc();
      break;
    }
  }
  
  //int n;
  //cin >> n;
  //double *c = new double[n];
  //double *e = new double[n];
  //for (int i = 0; i < n; i++) {
  //  cin >> c[i] >> e[i];
  //}
  //p1 = buildPl(n, c, e);
  //memset(c, 0, sizeof(c));
  //memset(e, 0, sizeof(e));
  //cin >> n;
  //for (int i = 0; i < n; i++) {
  //  cin >> c[i] >> e[i];
  //}
  //p2 = buildPl(n, c, e);
  //delete[] c;
  //delete[] e;
  
  return 0;
}