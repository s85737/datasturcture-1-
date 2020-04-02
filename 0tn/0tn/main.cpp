#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(void) {
   int a[10];
   int b[10];

   vector<int> resultU(10), resultI(10), resultD1(10), resultD2(10), resultS(10);

   vector<int>::iterator iter;

   for (int i = 0; i < 10; i++) {
      cout << "A집합 입력 : ";
      cin >> a[i];
      if (a[i] == -1) {
         break;
      }
   }
   
   for (int j = 0; j < 10; j++) {
      cout << "B집합 입력 : ";
      cin >> b[j];
      if (b[j] == -1) {
         break;
      }
   }
   
   iter = set_union(a, a + 5, b, b + 5, resultU.begin());

   resultU.resize(iter - resultU.begin());

   cout << "A ∪ B:";

   for (int i = 0; i < resultU.size(); i++)

      cout << ' ' << resultU[i];

   cout << endl;
   

   iter = set_intersection(a, a + 5, b, b + 5, resultI.begin());

   resultI.resize(iter - resultI.begin());

   cout << "A ∩ B:";

   for (int i = 0; i < resultI.size(); i++)

      cout << ' ' << resultI[i];

   cout << endl;
   

   iter = set_difference(a, a + 5, b, b + 5, resultD1.begin());

   resultD1.resize(iter - resultD1.begin());

   cout << "A － B:";

   for (int i = 0; i < resultD1.size(); i++)

      cout << ' ' << resultD1[i];

   cout << endl;
}
