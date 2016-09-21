#pragma once
#include<string>
#include<stack>
#include<cmath>
#include<vector>
#include<algorithm>
using std::string;
using std::stack;
using std::cout;
using std::vector;

struct Calc_List{
  double c;
  double e;
  int size;
  Calc_List* next;
  Calc_List() :c(0),e(0),size(0),next(nullptr) {}
  Calc_List(double c, double e) :c(c), e(e),size(0), next(nullptr) {}
};

typedef Calc_List* Poly;

//attach a node to exist polyn.
void attach(double c, double e, Poly* p) {
  Poly temp = new Calc_List(c, e);
  (*p)->next = temp;
  *p = temp;
}

/*
Poly buildPl(string s) {
  int first = 1, flag = 0, c = 0, e = 0,fu = 0, temp = 0;
  Poly p = new Calc_List;
  Poly front = p;
  stack<char> cs;
  stack<char> es;
  for (int i = 0; i < s.length(); i++) {
    if (i==s.length()-1||(s[i] >= '0'&&s[i] <= '9') || s[i] == '+' || s[i] == '-') {
      if (!first && s[i - 1] == '^')flag = 1;
      if(flag)es.push(s[i]);

      if ((s[i] == '+' || s[i] == '-')&&(!first)&&s[i-1]!='^') {
        int cnt = 0;
        while (!es.empty()) {
          if (es.top() >= '0'&&es.top() <= '9') {
            int t = es.top() - '0';
            temp += t*(int)pow(10, cnt++);
            es.pop();
          }
          else if (es.top() == '-') {
            fu = 1;
          }
        }
        e = temp;
        if (fu)e *= -1;
        attach(c, e, &p);
        c = 0; e = 0; temp = 0; fu = 0; flag = 0;
      }
      if (first)first = 0;
      if(!flag)cs.push(s[i]);
      
    }
    else if (s[i] >= 'a'&&s[i] < 'z') {
      int cnt = 0;
      while (!cs.empty()) {
        if (cs.top() >= '0'&&cs.top() <= '9') {
          int t = cs.top() - '0';
          temp += t*(int)pow(10, cnt++);
          cs.pop();
        }
        else if (cs.top() == '-') {
          fu = 1;
        }
      }
      c = temp;
      if (fu)c *= -1;
      temp = 0; fu = 0;
    }
    else if (s[i] == '^')continue;
    else {
      throw("wrong format!");
    }    
  }

  return front;
}
*/

//Judgement of number and alph
bool is_num(char c) {
  return (c >= '0'&&c <= '9');
}
bool is_alph(char c) {
  return (c >= 'a'&&c <= 'z');
}

//create a node and attach it to the polyn.
void createNode(string s, Poly* p) {
  double c = 0, e = 0;
  bool con_num = 1;
  stack<char> cs;
  stack<char> es;
  if (is_alph(s[0])||((s[0]=='+'||s[0]=='-')&&is_alph(s[1]))) {
    c = 1.0;
  }
  for (size_t i = 0; i < s.length(); i++) {
    if (is_num(s[i]) || s[i] == '+' || s[i] == '-') {
      if ((i&&s[i - 1] == '^')||(c&&is_num(s[i]))) {
        es.push(s[i]);
      }
      else {
        cs.push(s[i]);
      }
    }
    if (s[i] == '^')con_num = 0;
    if (is_alph(s[i])) {
      int cnt = 0, fu = 0;
      double temp = 0;
      while (!cs.empty()) {
        if (cs.top() >= '0'&&cs.top() <= '9') {
          double t = cs.top() - '0';
          temp += t*(int)pow(10, cnt++);
          cs.pop();
        }
        else if (cs.top() == '-') {
          fu = 1;
          cs.pop();
        }
        else if (cs.top() == '+') {
          cs.pop();
        }
      }
      if(!c)c = temp;
      if (fu)c *= -1;     
    }

    if (i == s.length() - 1) {
      if (is_alph(s[i]))e = 1;
      else {
        int cnt = 0, fu = 0;
        double temp = 0;
        while (!es.empty()) {
          if (es.top() >= '0'&&es.top() <= '9') {
            double t = es.top() - '0';
            temp += t*(int)pow(10, cnt++);
            es.pop();
          }
          else if (es.top() == '-') {
            fu = 1;
            es.top();
          }
          else if (es.top() == '+') {
            es.pop();
          }
        }
        if(!e) e = temp;
        if (fu)e *= -1;
      }

      if (con_num) {
        int cnt = 0, fu = 0;
        double temp = 0;
        while (!cs.empty()) {
          if (cs.top() >= '0'&&cs.top() <= '9') {
            double t = cs.top() - '0';
            temp += t*(int)pow(10, cnt++);
            cs.pop();
          }
          else if (cs.top() == '-') {
            fu = 1;
            cs.pop();
          }
          else if (cs.top() == '+') {
            cs.pop();
          }
        }
        if (!c)c = temp;
        if (fu)c *= -1;
      }
    }
  }

  attach(c, e, p);
}

Poly buildPl(string s) {
  vector<string> vs;
  int size = 0;
  string temp = "";
  Poly p = new Calc_List;
  Poly front = p;
  for (size_t i = 0; i < s.length(); i++) {
    if ((i&&s[i-1]=='^')||(s[i] != '+'&&s[i] != '-')|| (i == 0 && s[i] == '-')) {
      temp += s[i];
    }
    else {
      vs.push_back(temp);
      createNode(temp,&p);
      size++;
      temp = "";
      temp += s[i];
    }
    if (i == s.length() - 1) {
      createNode(temp, &p);
      size++;
    }
  }
  front->size = size;
  return front;
}
Poly buildPl(int size, double* c, double* e) {
  Poly p = new Calc_List;
  Poly front = p;
  for (int i = 0; i < size; i++) {
    attach(c[i], e[i], &p);
  }
  front->size = size;
  return front;
}

void freePoly(Poly *p) {
  Poly a = (*p);
  Poly b = (*p)->next;
  Poly c = b->next;
  while (b) {
    delete b;
    b = c;
    if(b) c = b->next;
  }
  a->next = nullptr;
  p = &a;
}

bool cmp(Calc_List a, Calc_List b) {
  return a.e < b.e;
}

void poly_sort(Poly p, int size) {
  Poly front = p;
  p = p->next;
  Poly comp = p;
  while (p->next) {
    double data = p->e;
    comp = comp->next;
    while (comp) {
      if (data < comp->e) {
        comp = comp->next;
      }
      else {
        double tempe = comp->e;
        double tempc = comp->c;
        comp->e = p->e;
        comp->c = p->c;
        p->e = tempe;
        p->c = tempc;
        comp = comp->next;
      }
    }
    p = p->next;
    comp = p;
  }
}

//The function add 2 polyn.s up.
Poly polyAdd(Poly a, Poly b) {
  a = a->next;
  b = b->next;
  Poly result = new Calc_List;
  Poly front = result;
  int size = 0;
  while (a&&b) {
    if (a->e == b->e) {
      double c = a->c + b->c;
      if (c) {
        attach(c, a->e, &result); 
        size++;
      }
      a = a->next;
      b = b->next;
    }
    else if (a->e < b->e) {
      attach(a->c, a->e, &result);
      size++;
      a = a->next;
    }
    else if (a->e > b->e) {
      attach(b->c, b->e, &result);
      size++;
      b = b->next;
    }
  }


  while (a) {
    attach(a->c, a->e, &result);
    size++;
    a = a->next;
  }
  while (b) {
    attach(b->c, b->e, &result);
    size++;
    b = b->next;
  }

  front->size = size;
  poly_sort(front, size);

  return front;
}

//The function subtract 2 polyn.s
Poly polySub(Poly a, Poly b) {
  a = a->next;
  b = b->next;
  Poly result = new Calc_List;
  Poly front = result;
  int size = 0;
  while (a&&b) {
    if (a->e == b->e) {
      double c = a->c - b->c;
      if (c) {
        attach(c, a->e, &result);
        size++;
      }
      a = a->next;
      b = b->next;
    }
    else if (a->e < b->e) {
      attach(a->c, a->e, &result);
      size++;
      a = a->next;
    }
    else if (a->e > b->e) {
      double c = b->c*-1;
      attach(c, b->e, &result);
      size++;
      b = b->next;
    }
  }


  while (a) {
    attach(a->c, a->e, &result);
    size++;
    a = a->next;
  }
  while (b) {
    attach(b->c, b->e, &result);
    size++;
    b = b->next;
  }

  front->size = size;
  poly_sort(front, size);

  return front;
}

//The function multiply 2 polyn.s
Poly polyMulty(Poly a, Poly b) {
  Poly fronta = a;
  Poly frontb = b;
  a = a->next;
  b = b->next;
  Poly result = new Calc_List;
  Poly front = result;
  Poly temp = new Calc_List;
  Poly temp_front = temp;
  while (a) {
    while (b) {
      attach(a->c*b->c, a->e + b->e, &temp);
      b = b->next;
    }
    result = polyAdd(result, temp_front);
    freePoly(&temp_front);
    temp = temp_front;
    b = frontb->next;
    a = a->next;
  }
  front = result;
  return front;
}

//Compute the value of polynomial with the given value x
int cpt(int x, Poly p) {
  return 0;
}

//compute the derivative p'
Poly deriv(Poly p) {
  return new Calc_List;
}

//print the polyn. to the screnn 
//the first num. n is the total items number
void print(Poly p) {
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
    if ((p->c != 1 && p->c != -1) || (p->c == 1 && p->e == 0))cout << p->c;
    if (p->c == -1)cout << "-";
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
  if ((p->c != 1 && p->c != -1) || (p->c == 1 && p->e == 0))cout << p->c;
  if (p->c == -1)cout << "-";
  if (p->e) {
    if (p->e != 1) {
      cout << "x^" << p->e << std::endl;
    }
    else cout << 'x' << std::endl;
  }
}


