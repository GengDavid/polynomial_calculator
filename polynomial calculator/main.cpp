#include<iostream>
#include<string>
#include<cstring>
#include"Calc_List.h"
using std::cin;
using std::cout;
using std::string;
using std::ios_base;

int main() {
  Poly p1, p2;
  string s1, s2;
  cin >> s1 >> s2;
  p1 = buildPl(s1);
  p2 = buildPl(s2);
  //int n;
  //cin >> n;
  //double *c = new double[n];
  //double *e = new double[n];
  //for (int i = 0; i < n; i++) {
  //  cin >> c[i] >> e[i];
  //}
  //p1 = buildPl(n, c, e);
  poly_sort(p1, p1->size);
  poly_sort(p2, p2->size);
  //memset(c, 0, sizeof(c));
  //memset(e, 0, sizeof(e));
  //cin >> n;
  //for (int i = 0; i < n; i++) {
  //  cin >> c[i] >> e[i];
  //}
  //p2 = buildPl(n, c, e);
  //delete[] c;
  //delete[] e;
  print(p1);
  print(p2);

  cout << "multi" << std::endl;
  print(polyMulty(p1, p2));
  return 0;
}