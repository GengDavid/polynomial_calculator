#pragma once
#include<iostream>
#include<string>
#include"Calc_List.h"
using std::stack;
using std::cout;
using std::vector;
using std::string;

class Poly_Calcltor {
public:
  Poly_Calcltor() {
    a = new Calc_List;
    b = new Calc_List;
  }

  Poly_Calcltor(string s1,string s2) {
    a = buildPl(s1);
    poly_sort(a, a->size);
    b = buildPl(s2);
    poly_sort(b, b->size);
  }

  void update(string s1, string s2) {
    a = buildPl(s1);
    poly_sort(a, a->size);
    b = buildPl(s2);
    poly_sort(b, b->size);
  }

  //The function add 2 polyn.s up.
  Poly add() {
    return polyAdd(a, b);
  }
  //The function subtract 2 polyn.s
  Poly sub(int select) {
    Poly re = nullptr;
    if(1==select) re = polySub(a, b);
    else if (2 == select) re = polySub(b, a);
    return re;
  }

  //The function multiply 2 polyn.s

  Poly multy() {
    return polyMulty(a, b);
  }
  //Compute the value of polynomial with the given value x
  double cpt(double x, int select) {
    if (1 == select) {
      return cpt(x, a);
    }
    else if(2==select) {
      return cpt(x, b);
    }
    else {
      throw("ie");
    }
  }
  //compute the derivative p'
  Poly deriv(int select) {
    Poly re = nullptr;
    if (1 == select) {
      re = deriv(a);
    }
    else if (2 == select) {
      re = deriv(b);
    }
    return re;
  }

  void freePc() {
    freePoly(&a);
    freePoly(&b);
  }


private:
  Poly a;
  Poly b;
  //attach a node to exist polyn.

  void attach(double c, double e, Poly * p);

  bool is_num(char c);

  bool is_alph(char c);

  void createNode(string s, Poly * p);

  Poly buildPl(string s);

  Poly buildPl(int size, double * c, double * e);

  void freePoly(Poly * p);

  bool cmp(Calc_List a, Calc_List b);

  void poly_sort(Poly p, int size);

  Poly polyAdd(Poly a, Poly b);

  Poly polySub(Poly a, Poly b);

  Poly polyMulty(Poly a, Poly b);

  double cpt(double x, Poly p);

  Poly deriv(Poly p);

};

//print the polyn. to the screnn 
//the first num. n is the total items number
inline void print(Poly p) {
  int f = 1;
  p = p->next;
  while (p->next) {
    if (f) {
      f = 0;
    }
    else if (!f && p->c > 0)cout << "+";
    else if (p->c == 0) {
      p = p->next;
      continue;
    }
    if ((p->c != 1 && p->c != -1) ||
      (p->c == 1 && p->e == 0) ||
      (p->c == -1 && p->e == 0))cout << p->c;
    if (p->c == -1 && p->e)cout << "-";
    if (p->e) {
      if (p->e != 1) {
        cout << "x^" << p->e;
      }
      else cout << 'x';
    }
    p = p->next;
  }
  if (!f && p->c > 0)cout << "+";
  else if (p->c == 0) {
    return;
  }
  if ((p->c != 1 && p->c != -1) ||
    (p->c == 1 && p->e == 0) ||
    (p->c == -1 && p->e == 0))cout << p->c;
  if (p->c == -1)cout << "-";
  if (p->e) {
    if (p->e != 1) {
      cout << "x^" << p->e << std::endl;
    }
    else cout << 'x' << std::endl;
  }
}


