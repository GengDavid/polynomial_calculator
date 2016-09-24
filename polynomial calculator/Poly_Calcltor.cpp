#include"Poly_Calcltor.h"

//delete one list_node
void Poly_Calcltor::deleteNode(Poly *pre, Poly *p) {//这里还需要再理解一下
  (*pre)->next = (*p)->next;
  delete (*p);
  *p = (*pre)->next;
}

//delete redundant node if the exponets are same
Poly Poly_Calcltor::filter(Poly p) {
  Poly front = p;
  int size = p->size;
  p = p->next;
  Poly pre = p;
  p = p->next;
  while (p) {
    if (p->e == pre->e) {
      pre->c = pre->c + p->c;
      deleteNode(&pre, &p);
      size--;
      continue;
    }
    pre = pre->next;
    p = p->next;
  }
  front->size = size;
  return front;
}

//attach a new node to the exist polinomial list.
void Poly_Calcltor::attach(double c, double e, Poly* p) {
  Poly temp = new Calc_List(c, e);
  (*p)->next = temp;
  *p = temp;
}

//Judgement of number and alph
bool Poly_Calcltor::is_num(char c) {
  return ('.'==c||(c >= '0'&&c <= '9'));
}
bool Poly_Calcltor::is_alph(char c) {
  return (c >= 'a'&&c <= 'z');
}

//create a node and attach it to the polyn.
void Poly_Calcltor::createNode(string s, Poly* p) {
  double c = 0, e = 0;
  bool con_num = 1;
  stack<char> cs;
  stack<char> es;
  if (is_alph(s[0]) || ((s[0] == '+' || s[0] == '-') && is_alph(s[1]))) {
    c = 1.0;
  }
  for (size_t i = 0; i < s.length(); i++) {
    if (is_num(s[i]) || s[i] == '+' || s[i] == '-') {
      if ((i&&s[i - 1] == '^') || (c&&is_num(s[i]))) {
        es.push(s[i]);
      }
      else {
        cs.push(s[i]);
      }
    }
    if (s[i] == '^')con_num = 0;
    if (is_alph(s[i])) {
      bool xs = false;
      int cnt1 = 0, cnt2 = 0, fu = 0;
      double temp1 = 0, temp2 = 0;
      while (!cs.empty()) {
        if (is_num(cs.top())) {
          if (cs.top() != '.'&&xs == false) {
            double t = cs.top() - '0';
            temp1 += t*(int)pow(10, cnt1++);
            cs.pop();
          }
          else if (cs.top() == '.') {
            xs = true;
            cs.pop();
          }
          else if (xs) {
            double t = cs.top() - '0';
            temp2 += t*(int)pow(10, cnt2++);
            cs.pop();
          }
        }
        else if (cs.top() == '-') {
          fu = 1;
          cs.pop();
        }
        else if (cs.top() == '+') {
          cs.pop();
        }
      }
      if (!c) {
        if (xs) {
          c = temp1/pow(10, cnt1) + temp2;
        }
        else c = temp1;
      }
      if (fu)c *= -1;
    }

    if (i == s.length() - 1) {
      if (is_alph(s[i]))e = 1;
      else {
        bool xs = false;
        int cnt1 = 0, cnt2 = 0, fu = 0;
        double temp1 = 0, temp2 = 0;
        while (!es.empty()) {
          if (is_num(es.top())) {
            if (es.top() != '.'&&xs == false) {
              double t = es.top() - '0';
              temp1 += t*(int)pow(10, cnt1++);
              es.pop();
            }
            else if (es.top() == '.') {
              xs = true;
              es.pop();
            }
            else if (xs) {
              double t = es.top() - '0';
              temp2 += t*(int)pow(10, cnt2++);
              es.pop();
            }
          }
          else if (es.top() == '-') {
            fu = 1;
            es.pop();
          }
          else if (es.top() == '+') {
            es.pop();
          }
        }
        if (!e) {
          if (xs) {
            e = temp1 / pow(10, cnt1) + temp2;
          }
          else e = temp1;
        }
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

//initialize the polinomial using a string 
Poly Poly_Calcltor::buildPl(string s) {
  vector<string> vs;
  int size = 0;
  string temp = "";
  Poly p = new Calc_List;
  Poly front = p;
  for (size_t i = 0; i < s.length(); i++) {
    if ((i&&s[i - 1] == '^') || (s[i] != '+'&&s[i] != '-') || (i == 0 && s[i] == '-')) {
      temp += s[i];
    }
    else {
      vs.push_back(temp);
      createNode(temp, &p);
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

//clear a polinomial string
void Poly_Calcltor::freePoly(Poly *p) {
  Poly a = (*p);
  Poly b = (*p)->next;
  if (b == nullptr)return;
  Poly c = b->next;
  while (b) {
    delete b;
    b = c;
    if (b) c = b->next;
  }
  a->next = nullptr;
  p = &a;
}

//sort to ascending order
void Poly_Calcltor::poly_sort(Poly p, int size) {
  Poly front = p;
  p = p->next;
  Poly comp = p;
  while (p && p->next) {
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
Poly Poly_Calcltor::polyAdd(Poly a, Poly b) {
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
Poly Poly_Calcltor::polySub(Poly a, Poly b) {
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
    double c = b->c * -1;
    attach(c, b->e, &result);
    size++;
    b = b->next;
  }

  front->size = size;
  poly_sort(front, size);

  return front;
}

//multiply two polyn.s
Poly Poly_Calcltor::polyMulty(Poly a, Poly b) {
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
      double c = a->c*b->c;
      if(c) attach(c, a->e + b->e, &temp);
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

//compute with a given value
double Poly_Calcltor::cpt(double x, Poly p) {
  p = p->next;
  double result = 0;
  while (p) {
    result += p->c*pow(x, p->e);
    p = p->next;
  }
  return result;
}

Poly Poly_Calcltor::deriv(Poly p) {
  Poly dr = new Calc_List;
  Poly front = dr;
  int size = 0;
  while (p) {
    if (p->e == 0) {
      p = p->next;
      continue;
    }
    else {
      attach(p->c*(p->e), p->e - 1, &dr);
      size++;
    }
    p = p->next;
  }
  front->size = size;
  return front;
}

