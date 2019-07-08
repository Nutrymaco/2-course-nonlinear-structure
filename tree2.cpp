#include <iostream>
using namespace std;


class Tree{
    int **matrix;// son -> parent
    int size = 0, max_size = 0; //size - сколько использовано, max_size - сколько макс  возможно
    int topNode; // наивысшая вершина
    int *stright_array; // массив с точками для прямого обхода, нужен для объединения,
                        //создается функцией getStraightNodes
    int size_stright_array = 0; // текущий размер массива вершин при прямом обходе


    int getMax(int array[], int size){ //  максимум из массива
        int max = array[0];

        for (int i = 1; i < size; i++){
            if (array[i] > max) max = array[i];
        }

        return max;
    }

    int getMin(int array[], int size){ // минимум из массива
        int min = array[0];

      for (int i = 1; i < size; i++){
          if (array[i] < min) min = array[i];
      }

      return min;
    }

    // добавление курсора ребенок -> отец
    void addCursor(int son_value, int parent_value){ // TO DO: добавить проверку что матриц не закончилась и если что перезаписать в больший массив
        matrix[size][0] = son_value;
        matrix[size][1] = parent_value;
        //cout << "Added : " << son_value << " " << parent_value << endl;
        size++;
        //cout << son_value << " " << parent_value << endl;
    }


public:

    Tree(int value){
        // инициализируем основную матрицу с курсорами
        matrix = new int*[100];
        for (int i = 0; i < 100; i++){
            matrix[i] = new int [2];
        }
        max_size = 100;

        addCursor(value, NULL); // добавляем первый курсор с нулевым отцом, так как это первая вершина дерева
        size = 1;
        topNode = value;
        stright_array = new int[size];
    }

    // возвращает первую вершину
    int getTopNode(){
        return topNode;
    }

    // возвращает кол-во вершин в дереве
    int getSize(){
        return size;
    }

    //возвращает размер массива вершин в прямом порядке
    int getSizeOfStrightArray(){
        return size_stright_array;
    }

    // возврашает значение правого сына или NULL если его нет
    int getRightSon(int node){
        int sons[2], count = 0; // values
        for (int i = 0; i < size; i++){ // ищем вершины с отцом со значением node - их макс. 2
            if (matrix[i][1] == node and count < 2) {
                sons[count] = matrix[i][0];
                count ++;
            }
        }

        if (count == 2){ // если две, то возвращаем макс из них
            return getMax(sons, 2);
        }
        else if (count == 1){ // если найденная вершина больше возвращаем ее, иначе NULL
            if (sons[0] > node){
                return sons[0];
            }
            else{
                return NULL;
            }
        }
        else{ // не нашли ничего - возвр NULL
          //cout << "node: " << node << " no right sons" << endl;
          return NULL;
        }

    }

    // возвращает значение левого сына или NULL если его нет
    int getLeftSon(int node){
        int sons[2], count = 0;
        for (int i = 0; i < size; i++){ // ищем вершины с отцом со значением node - их макс. 2
            if (matrix[i][1] == node and count < 2) {
                sons[count] = matrix[i][0];
                count ++;
            }
        }
        if (count == 2){ // если две, то возвращаем мин из них
            return getMin(sons, 2);
        }
        else if(count == 1){ // если найденная вершина меньше возвращаем ее, иначе NULL
            if (sons[0] < node){
                return sons[0];
            }
            else{
              return NULL;
            }
        }
        else{ // не нашли ничего - возвр NULL
            //cout << "node: " << node << " no left sons" << endl;
            return NULL;
        }
    }

    // тоже самое что и две предыщее, только поведение опр-ся параметром route (1 - правый, 2 - левый)
    int getSon(int node, int route){
      int sons[2], count = 0;
      for (int i = 0; i < size; i++){
          if (matrix[i][1] == node and count < 2) {
              sons[count] = matrix[i][0];
              count ++;
          }
      }

        if (count == 2){
          //cout << node << " 2 sons" << endl;
          if (route == 1)  return getMax(sons, 2); // если надо правого брата - возвр макс
          else return getMin(sons, 2);            // если надо левого брата - возвр мин
        }
        else if (count == 1){
          //cout << node << ", 1 sons" << endl;
            if (sons[0] > node){
                if (route == 1) return sons[0]; // если надо правого и найд значение больше, то возвращаем его
                else return NULL;               // иначе NULL
            }
            else{
              if (route == 0) return sons[0]; // если найд значение меньше и надо левого брата, то возвр его
              else return NULL;               // иначе возвр NULL
            }
        }
        else{  // не нашли ничего - возвр NULL
            //cout << node << " no sons" << endl;
            return NULL;
        }

    }

    // добавляем вершину
    void addNode(int value){
        int next_node;
        int node = topNode;
        while (true) {
            if (node == value) {break;} // если в дереве уже есть такая вершина, то ее добавлять не надо
            next_node = getSon(node, value > node); // ищем следующую вершину в зависимости от того значение больше или меньше текущей вершины
            //cout << node << " " << value << " " << next_node << endl;
            if (next_node == NULL) {addCursor(value, node); break;} // если следующая вершина - NULL, то заменяем ее нашим значением и выходим из цикла
            else node = next_node; // если следующая вершина задана, то продолжаем искать дальше
        }
    }

    // вывод дерева на боку, параметры: node - первая вершина дерева getTopNode(), level = 0
    void print_Tree(int node,int level)
    {
        if (getRightSon(node) != NULL) print_Tree(getRightSon(node),level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        if (node != NULL) cout << node; else cout << "no"; cout << endl;
        if (getLeftSon(node) != NULL) print_Tree(getLeftSon(node),level + 1);

    }

    // вывод матрицы дерева (типо список курсоров)
    void printMatrix(){
        for (int i = 0; i < size; i++){
            cout << matrix[i][0] << " " << matrix[i][1] << endl;
        }
    }

    // вывод дерева в прямом обходом, параметры: node - первая вершина дерева getTopNode()
    void print_straight_tree(int node) {
        cout << node << " ";
        if (getLeftSon(node) != NULL)print_straight_tree(getLeftSon(node));
        if (getRightSon(node) != NULL)print_straight_tree(getRightSon(node));

    }

    // вывод дерева обратным обходом
    void print_back_tree(int node) {
        if (getLeftSon(node) != NULL)print_back_tree(getLeftSon(node));
        if (getRightSon(node) != NULL)print_back_tree(getRightSon(node));
        cout << node << " ";
    }

    // вывод дерева симметричным обходе, параметры: node - первая вершина дерева getTopNode()
    void print_sym_tree(int node) {
      if (getLeftSon(node) != NULL)print_sym_tree(getLeftSon(node));
      cout << node << " ";
      if (getRightSon(node) != NULL)print_sym_tree(getRightSon(node));
    }

    // генерируем и возвращаем список вершинв в порядке прмяого обхода
    int* getStraightNodes(int node){
        if (node != NULL){this->stright_array[size_stright_array] = node;size_stright_array++;};
        if (getLeftSon(node) != NULL)getStraightNodes(getLeftSon(node));
        if (getRightSon(node) != NULL)getStraightNodes(getRightSon(node));
        return this->stright_array;
    }

    // объединяем два дерево, как параметр передаем список вершин второго дерева и из кол-во
    void Union(int* array_nodes, int array_size){
      for (int i = 0; i < array_size; i++){
          if (array_nodes[i] != NULL) {
              addNode(array_nodes[i]);
              this->size++;
          }
      }
    }
};


int main(){
    Tree tree1(5);
    Tree tree2(3);
    tree1.addNode(7);
    tree1.addNode(3);
    tree1.addNode(9);
    tree1.addNode(4);
    tree1.addNode(1);
    tree1.addNode(8);
    tree1.addNode(11);
    tree1.addNode(0);
    tree1.addNode(4);
    tree1.addNode(10);

    tree2.addNode(2);
    tree2.addNode(5);
    tree2.addNode(8);
    tree2.addNode(1);
    tree2.addNode(-3);
    tree2.addNode(6);
    tree2.addNode(20);


    tree1.print_Tree(tree1.getTopNode(), 0);
    cout << "------------" << endl;
    tree1.print_back_tree(tree1.getTopNode());
    cout << endl << "------------" << endl;
    tree1.print_sym_tree(tree1.getTopNode());
    cout << endl << "------------"<< endl;
    tree1.print_straight_tree(tree1.getTopNode());
    cout << endl << "------------"<< endl;
    /*tree2.print_Tree(tree2.getTopNode(), 0);
    cout << endl << "------------"<< endl;
    tree1.Union(tree2.getStraightNodes(tree2.getTopNode()), tree2.getSizeOfStrightArray());
    tree1.print_Tree(tree1.getTopNode(), 0);
*/
    return 0;
}
