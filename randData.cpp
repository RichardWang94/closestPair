#include <iostream>
#include <cstdlib>
using namespace std;
int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "usage is ./randData int" << endl;
    exit(0);
  }
  if (atoi(argv[1]) == 0) {
    cout << "usage is ./randData int" << endl;
    exit(0);
  }
  int i = atoi(argv[1]);
  double min = -10000;
  double max = 10000;
  srand(time(NULL));
  for (i; i > 0; i--) {
    cout << min + (max-min)*(double)rand()/RAND_MAX << " " << min + (max-min)*(double)rand() / RAND_MAX << endl;
  }
}
