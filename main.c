#include <stdio.h>
#include <stdlib.h>

// структура дерева
typedef struct Node {
    int data;
    struct Node* left, * right;
}Node;

// структура для ветвей дерева
typedef struct Trunk {
    struct Trunk* prev;
    char* str;
}Trunk;

// создание дерева
Node* create_node(int data) 
{
    Node* newNode = (Node*)malloc(sizeof(struct Node)); // выделение памяти
    // установка значения данных, левых и правых поддеревьев, а также высоты
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    return newNode;
}

// вставка нового узла
Node* insert(Node* root, int data) 
{
    if (root == NULL) // если узел пуст, то создается новый
        return create_node(data);

    // двоичный рекурсивный поиск места для нового элемента
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root; // дубликаты не допускаются

    return root;
}

int find_max_el_on_level(Node* root, int level, int currentLevel) 
{
    if (root == NULL)
        return -1; // возвращает -1, если достигнут конец дерева

    if (currentLevel == level) // если на нужном уровне функция возвращает значение текущего узла
        return root->data;

    // получение максимальных значений на правом и левом поддервеьях
    int leftMax = find_max_el_on_level(root->left, level, currentLevel + 1);
    int rightMax = find_max_el_on_level(root->right, level, currentLevel + 1);

    return (leftMax > rightMax) ? leftMax : rightMax; // выбор максмимального значения 
}

// Функция для вычисления высоты дерева
int get_hight(Node* root) 
{
    if (root == NULL) // если дерево пусто, вернет ноль
        return 0;
    else 
    {
        // получение значений высот левого и правого поддеревьев
        int leftHeight = get_hight(root->left);
        int rightHeight = get_hight(root->right);

        // высота дерева = максимум из высот поддеревьев + 1 (текущий узел)
        return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
}

// функция удаления дерева
void deleteTree(Node* root) 
{
    if (root != NULL) // пока дерево не удалится полностью, рекурсивно удаляем каждое поддерево
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

// функция для рекурсивного вывода дерева
void showTrunks(Trunk* p) {
    if (p == NULL) {
        return;
    }

    showTrunks(p->prev);
    printf("%s", p->str);
}

// 
void printTree(Node* root, Trunk* prev, int isLeft) 
{
    if (root == NULL) // если дерево пустое, завершаем работу
        return;

    // создается новый объект Trunk с предыдущей ветвью prev и строкой prev_str
    char* prev_str = "    ";
    Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk));
    trunk->prev = prev;
    trunk->str = prev_str;

    printTree(root->right, trunk, 1); // рекурсивный вывод для правого поддерева 

    // в зависимости от структуры дерева и типа ветви выводим разные символы
    if (!prev) 
        trunk->str = "———-";

    else if (isLeft) 
    {
        trunk->str = ".———-";
        prev_str = "   |";
    } 

    else 
    {
        trunk->str = "`———-";
        prev->str = prev_str;
    }

    // вывод ветвей и значений узлов
    showTrunks(trunk);
    printf(" %d\n", root->data);

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, 0); // вывод левого поддерева
}


int main() 
{
    Node* root = NULL; // инициализация дерева

    // открытие, чтение данных из файла, построение дерева и закрытие файла
    FILE* inputFile = fopen("input.txt", "r");
    int value;
    while (fscanf(inputFile, "%d", &value) == 1)
        root = insert(root, value);
    fclose(inputFile);

    // вывод дерева
    printTree(root, NULL, 0);


    // удаление всего дерева
    deleteTree(root);

    return 0;
}
