#include <iostream>
using namespace std;
#include <ctime>


class Queue{

public:
    int *array;
    int size;
    int reserve_size = 10;
    int max_size;
    int array_size;
    Queue(int size){
        array = new int[size + reserve_size];
        this -> size = 0;
        max_size = size + reserve_size;
        array_size = size;

    }
    void fillRandom(){
        for (int i = 0; i < array_size; i++){
            this -> addElement(rand() % 1000);
        }
    }
    void show(){
        for (int i = 0; i < size; i++){
            cout << i + 1 << ") " << array[i] << endl;
        }
    }
    void addElement(int number){
        if (size != max_size){
            array[size] = number;
            size ++;
        }
        else{
            int *new_array = new int[max_size + reserve_size];

            for (int i = 0; i < max_size; i++){
                new_array[i] = array[i];
            }
            new_array[max_size] = number;

            size++;
            max_size += reserve_size;

            array = new_array;
        }
    }
    void deleteElement(){
        for (int i = 0; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
    }
    int getElement(int index){ // 1
        return array[index];
    }
    int getMax(){
        int max = array[0];
        for (int i = 1; i < size; i++){
            if (array[i] > max) max = array[i];
        }
        return max;
    }
    int getMin(){
        int min = array[0];
        for (int i = 1; i < size; i++){
            if (array[i] < min) min = array[i];
        }
        return min;
    }
    int getSize(){
      return size;
    }
};

Queue sort(Queue array){
    int max = array.getMax(), min = array.getMin();
    int dif = max-min;
    int add_array[dif];
    Queue new_array(array.getSize());
    int nop = 0;
    for (int i = 0; i < dif+1; i++){
        add_array[i] = 0;
    }

    nop += 1;
    for (int i = 0; i < array.size; i++){ // 6n + 1
        add_array[array.getElement(i) - min] ++; // 4
        nop += 6;
    }

    srand(time(0));
    // 4n + 3k + 4
    nop += 1;
    for (int i = 0; i < dif+1; i++){ // 3(k + 1) + 1
      nop += 3;
        for (int j = 0; j < add_array[i]; j++){ // сумма add_array[j] = длине изначального массива, поэтому 4n + 1
            new_array.addElement(i + min);
            nop += 4;
        }
    }
    //  = 10n + 3k + 5
    cout << "nop = " << nop << " n, k = " << array.getSize() << " " << dif << " time: " << clock()/10000.0 << endl;
    return new_array;
}


int main(int argc, char const *argv[]) {
    Queue array = Queue(10);
    array.fillRandom();
    sort(array);
  return 0;
}
