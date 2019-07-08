#include <iostream>
using namespace std;
#define MAX 1000
#include <ctime>

//add in finish, del in start

#define MAX 1000

/*

Базовыми операциями для вычисления F(n) будем считать следующие операции:

Сложение, умножение и тп

Сравнения (>,<,==, и тп)

Объявление переменной (int a;)

Обращение к элементу массива по индексу (a[i])

Обращение к переменной/функции объекта (stack.pop())

*/



class Queue{

  public:
    int top;
    int *array;
    Queue(int count){
      array = new int(5);
      top = count;
    };
    ~Queue(){
      top = -1;
    };
    int getLength();
    bool isEmpty();
    bool addToArray(int number);
    void delElement();
    int getElement(int index);
};


bool Queue::addToArray(int number){
  if (top < MAX){   // 1
    array[top] = number; // 1
    top++;    // 1
    return true;
  }
  else{
    return false;
  }
}

int Queue::getLength(){
    return top; // 1
}

int Queue::getElement(int index){
  return array[index]; // 1
}

void Queue::delElement(){
    for (int i = 0;i < top-1; i++){ // 3
        array[i] = array[i + 1]; // 2
    }
    top--; // 1
}

int main(){

    Queue array, sorted_array;
    int addl_array[MAX], act = 0;
    int n = 10, k = 50;


    // fill arrays
    for (int i = 0; i < MAX; i++){
        addl_array[i] = 0;
    }

    for (int i = 0; i < n; i++){
        array.addToArray(rand() % k);
        cout << i << ": " << array.getElement(i) << endl;
    }


    srand(time(0));
    // sort arrays
    // 4 + 3n
    act += 4;
    for (int i = 0; i < array.getLength(); i++){ // 4
        addl_array[array.getElement(i)]++; // 3
        //act += 3;
    }

    // k - max
    // 3 + 4k + 3n
    act += 3;
    for (int i = 0;i < MAX; i++){ // 3
      act += 4;
        for (int j = 0; j < addl_array[i];j++){ // 4
            sorted_array.addToArray(i); // 3
          //  act += 3;

        }
    }

    cout << "Time : " << clock()/10000.0 << endl;

    //F(n) = 6n + 4k + 7
    //O(F(n)) = O(k+n)


    // print sorted arrays
    for (int i = 0; i < sorted_array.getLength(); i++){
        cout << i << ": " << sorted_array.getElement(i) << endl;
    }
    cout << "Actions = " << act << endl;

}
