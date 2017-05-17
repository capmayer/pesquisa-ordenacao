#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

class Student {
   string name;
   string login;
   int mat;
   string group;
   int age;
   string home;
public:
   Student(int mat, string login, string name, string group, int age, string home) {
      this->name = name;
      this->login = login;
      this->mat = mat;
      this->group = group;
      this->age = age;
      this->home = home;
   }
   int getMat(){
     return mat;
   }
   int getAge(){
     return age;
   }
   string getLogin(){
     return login;
   }
   string getName(){
     return name;
   }
};

void loadTxt(Student* students[], string txt){
    ifstream data(txt);

    int x = 0;
    string line;
    string cell[6];

    while (getline(data, line)) {
       stringstream linestream(line);
       getline(linestream, cell[0], '|');
       getline(linestream, cell[1], '|');
       getline(linestream, cell[2], '|');
       getline(linestream, cell[3], '|');
       getline(linestream, cell[4], '|');
       getline(linestream, cell[5], '|');

       Student* ns = new Student(stoi(cell[0]), cell[1], cell[2], cell[3], stoi(cell[4]), cell[5]);

       students[x] = ns;
       x++;
    }
}

void showScores(Student* students[], string task){
   cout<< task;
   cout << endl;

   for (int x=0; x<5; x++){

      cout<< students[x]->getName();
      cout << endl;
    }
}

void orderByInsertionSort(Student* students[], int t) {
   int i, j;
   Student* temp;

   for (i = 1; i < t; i++) {
     j = i;
     while (j > 0 && students[j - 1]->getLogin() > students[j]->getLogin()) {
        temp = students[j];
        students[j] = students[j - 1];
        students[j - 1] = temp;
        j--;
    }
  }
}

// --- Begin Quicksort ---

int partition(Student* students[], int init, int end){
  int left = init;
  int right = end;
  int piv = students[init]->getMat();
  do {
    while ( piv > students[++left]->getMat())
      if (left == end) break;
    while ( piv < students[--right]->getMat())
      if (right == init) break;
    if (left < right)
      swap(students[left], students[right]);
  }while (left < right);
  swap(students[init], students[right]);
  return right;
}

void orderByQuickSort(Student* students[], int left, int right) {
  int l = left;
  int r = right;
  Student* temp;
  int i;
  if(l < r){
    i = partition(students, l, r);
    orderByQuickSort(students, left, i - 1);
    orderByQuickSort(students, i+1, right);
  }
}

// --- End Quicksort ---


// --- Begin Heapsort ---
void heap(Student* students[], int i, int n)
{
    int j = 2*i;
    Student* temp = students[i];
    while (j <= n)
    {
        if (j < n && students[j+1]->getAge() > students[j]->getAge())
            j++;
        if (temp->getAge() > students[j]->getAge())
            break;
        else if (temp->getAge() <= students[j]->getAge())
        {
            students[j/2] = students[j];
            j = 2*j;
        }
    }
    students[j/2] = temp;
    return;
}

void maxHeap(Student* students[], int n)
{
    for(int i = n/2; i >= 1; i--)
    {
        heap(students, i, n);
    }
}

void orderByHeapSort(Student* students[], int n)
{
    int i;
    Student* temp;
    maxHeap(students, n);
    for (i = n; i >= 2; i--)
    {
        temp = students[i];
        students[i] = students[1];
        students[1] = temp;
        heap(students, 1, i - 1);
    }
}


// --- End Heapsort ---


int main (int argc, char *argv[]){
  Student* students[5];

  loadTxt(students, argv[1]);

  // para ter um resultado mais preciso pode-se comentar os outros sorts

  orderByInsertionSort(students, 5);
  showScores(students, "Tarefa 01");

  orderByQuickSort(students, 0, 4);
  showScores(students, "Tarefa 02");

  orderByHeapSort(students, 4);
  showScores(students, "Tarefa 03");
}
