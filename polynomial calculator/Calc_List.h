#pragma once
#include<string>
#include<stack>
#include<cmath>
#include<vector>
#include<algorithm>


struct Calc_List{
  double c;
  double e;
  int size;
  Calc_List* next;
  Calc_List() :c(0),e(0),size(0),next(nullptr) {}
  Calc_List(double c, double e) :c(c), e(e),size(0), next(nullptr) {}
};

typedef Calc_List* Poly;
