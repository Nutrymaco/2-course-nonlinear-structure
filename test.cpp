
#include <iostream>

using namespace std;

#define MAX 1000

/*

Базовыми операциями для вычисления F(n) будем считать следующие операции:

Сложение, умножение и тп

Сравнения (>,<,==, и тп)

Объявление переменной (int a;)

Обращение к элементу массива по индексу (a[i])

Обращение к переменной/функции объекта (stack.pop())

*/

int nop = 0; // Счетчик количества проделанных операций

class Stack

{

int top; // Указатель на последний элемент

public:

int a[MAX]; // Максимальное количество элементов в стеке

Stack() { top = -1; nop+=1;} // 1

~Stack() {top = -1;}

bool push(int x); // 4

int pop(); // 3

bool isEmpty(); // 1

int peek(); // 2

int length(); // 2

};

bool Stack::push(int x) // 4

{

if (top >= (MAX-1)) // 1

{

cout << "Stack Overflow";

return false;

}

else

{

a[++top] = x; // 3

nop += 4;

return true;

}

}

int Stack::peek() // 2

{

if (top < 0) // 1

{

cout << "Stack Underflow";

return 0;

}

else

{

nop += 2;

return a[top]; // 1

}

}

int Stack::pop() // 3

{

if (top < 0) // 1

{

cout << "Stack Underflow";

return 0;

}

else

{

nop += 3;

return a[top--]; //2

}

}

bool Stack::isEmpty() // 1

{

nop += 1;

return (top < 0); // 1

}

int Stack::length() {

nop += 2;

return top + 1;

} // 2

// --------------------------------------------------------

// Объеденить два стека в один

// s2[0], s2[1], .., s2[n], s1[0], s1[1], .., s1[m]

// Склеивание стеков затрачивает, в среднем, n/2 операций,

// т.к. нам необходимо перевернуть один стек и только после этого добавить его ко второму поэлементно

// 1 в лучшем и n в худшем случае

//, Следовательно, склеивание происходит за время O(n)

Stack combine (Stack s1, Stack s2) // 2 + 2 * (3 + (4+3) * (n-1))

{

struct Stack tmp; // 1

struct Stack ret; // 1

nop += 2;

while(!s1.isEmpty()){tmp.push(s1.pop()); nop += 9;} // 3 + summ(4+3) * (n-1)

while(!tmp.isEmpty()){s2.push(tmp.pop()); nop += 9;} // 3 + summ(4+3) * (n-1)

return s2;

}

// Сортировка Хоара. Quick sort

// Разбиение стека на два, происходит за время O(n)

// Всего будет ~logn уровней рекурсии, т.к. стек уменьшается вдвое, каждый уровень обрабатывается за время O(n)

// Значит алгоритм работает в среднем за время O(n*logn)

/*

https://pro-prof.com/archives/813

Методом математической индукции получаем:

11 + 8n + (27 + n/3*(log(n) + log((n-1)/2))) * (8 + 14(n-1))

*/

Stack quickSort(Stack s) // 9 + (2 + 8n) + ((27 + 2 * quicksort(n-1) + 2 * (1 + quicksort((n-1)/2)))/ 3) * (2 + 2 * (3 + (4+3) * (n-1)))

{

if (s.length() <= 1) {nop += 2; return s;} // 2

struct Stack part1; // 1 // Меньше опорного элемента

struct Stack part2; // 1 // Больше опорного элемента

int pivot = s.pop(); // 5 // Опорный элемент

nop += 5;

// Разбиваем стек на 2 стека относительно опорного элемента

while(!s.isEmpty()) // 2 + (2+1+5) * n

{

int x = s.pop(); // 2

nop += 4;

if (x < pivot) // 1 + 5

{

part1.push(x); // 5

nop += 6;

}

else if (x >= pivot) // 1 + 5

{

part2.push(x); // 5

nop += 7;

}

}

// Разбираемся куда засунуть опорный элемент (pivot)

// и рекурсивно продолжаем сортировать

// 27 + 2 * quicksort(n-1) + 2 * (1 + quicksort((n-1)/2))

if (part1.isEmpty()) // 8 + quicksort(n-1)

{

part1.push(pivot); // 5

part2 = quickSort(part2); // 1 + quicksort(n-1)

nop += 8;

}

else if (part2.isEmpty()) // 10 + quicksort(n-1)

{

part2.push(pivot); // 5

part1 = quickSort(part1); // 1 + quicksort(n-1)

nop += 10;

}

else // 9 + 2 * (1 + quicksort((n-1)/2))

{

part1 = quickSort(part1); // 1 + quicksort((n-1)/2)

part2 = quickSort(part2); // 1 + quicksort((n-1)/2)

part2.push(pivot); // 5

nop += 11;

}

return combine(part1, part2); // 2 + 2 * (3 + summ(4+3) * (n-1))

}

bool isSorted(Stack s) // 7 + 3n

{

bool b = true; // 1

int prev = s.pop(); // 4

nop+=7;

while (!s.isEmpty()) // 2 + 3n

{

if (prev > s.pop()) { b = false; nop+=1;} // 3

nop+=7;

}

return b;

}

/*

3 + 8n + 14 + 6n + 11 + 8n + (27 + n/3*(log(n) + log((n-1)/2))) * (8 + 14(n-1)) =

= 28 + 22n + (27 + n/27*(log(n) + log((n-1)/2))) * (14n - 6)

Итого: F(n) = 28 + 22n + (27 + n/27*(log(n) + log((n-1)/2))) * (14n - 6)

Переводя в нотацию O(n):

O(F(n)) = n^2

*/

int main()

{

srand(time(NULL)); // Устанавливаем сид рандомайзера

/*

Одноразовый прогон сортировки

*/

// struct Stack s; // 1

// // Заполняем стек рандомными числами

// for (int i=1; i < 100; i++) {s.push(rand() % i);} // 2 + 8n

// cout << std::boolalpha;

// cout<<"До сортировки"<<endl;

// cout<<"Стек отсортирован? - "<<isSorted(s)<<endl; // 7 + 3n

// s = quickSort(s); // 11 + 8n + (27 + n/27*(log(n) + log((n-1)/2))) * (8 + 14(n-1))

// cout<<"После сортировки"<<endl;

// cout<<"Стек отсортирован? - "<<isSorted(s)<<endl; // 7 + 3n

// cout<<"NOP "<<nop<<endl;

// // Вывод стека

// while (!s.isEmpty())

// {

// cout<<s.pop() << " popped from stack\n";

// }

/*

Вычисляем NOP (реальное количество проделанных операций)

Сортируем разные массивы из одинакового кол-ва элементов несколько раз

каждый раз считая NOP и затем находим его среднее значение

*/

int c = 100; // Количество прогонов

int e_count = 1000; // Количество элементов в массиве MAX=1000

int a[c];

for (int j=0; j < c; j++)

{

struct Stack s;

for (int i=1; i < 1000; i++) {s.push(rand() % i);}

s = quickSort(s);

a[j] = nop;

nop=0;

}

int meanNop = 0;

for (int i=1; i < c; i++)

{

meanNop += a[i];

}

cout<<"Среднее значение NOP: "<<meanNop/c;

return 0;

}
