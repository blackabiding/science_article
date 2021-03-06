/*Программа имеет консольный интерфейс. В окне программы вводятся вопросы (не менее 20) и 4 варианта ответов к ним.
Предполагается два режима работы программы: режим тренировки и режим экзамена.
Режим экзамена: Пользователь вводит номер правильного ответа. В случае некорректного ввода запрос на ввод ответа повторяется.
Программа ведет одсчет правильных ответов и в конце выставляет оценку. После завершения теста кроме оценки на экране отображается количество ошибок и вопросы,в
которых эти ошибки допущены.
Режим тренировки. Для каждого заданного вопроса запрашивает ответ до тех пор, пока пользователь не ответи правильно. При это на экран выводятся сообщения "вы
ответили верно" или "вы ответили неверно"*/

//Библиотеки
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <time.h>

int test(unsigned short int *lim, int *mas, int *digit)
{
    for (short int i = 0; i < *lim; i++)
        if (mas[i] == *digit)
            return 1;
    return 0;
}

void inicialArray(int *arr)
{
    for (unsigned short int i=0;i<20;i++)
    {
        do
        {
            arr[i] = rand()%20;
        } while (test(&i, arr, &arr[i]));//вызов функции проверки на повторяющиеся значения элементов массива
    }
}

void printResultForExam(char questions[20][200], char answers[20][200], unsigned j, int *incor_answ, short int *true_answ)
{
    double mark;
    mark=*true_answ/4;
    printf("\n");
    printf("------------------------------------\n");
    printf("Поздравляю вас с прохождением теста!\n");
    printf("Ваша оценка: %.1lf.",mark);
    if(20-*true_answ == 0)
        printf("Ошибок допущено не было\n");
    else{
        printf("Количество допущенных ошибок: %d\n",20-*true_answ);
        printf("Ошибки были допущены в следующих вопросах: \n");
        for (short int i=0; i<j; i++)
        {
            printf("%s\n",questions[incor_answ[i]]);
        }
    }
}

void printQuestionsForExam(char questions[20][200], char answers[20][200], short int *true_answ, int *arr, int incor_answ[20])
{
    unsigned answer;
    unsigned j=0;
    for (unsigned i=0;i<20;i++)
    {
        printf("%s\n",questions[arr[i]]);
        printf("%s\n",answers[arr[i]]);
        printf("Ответ: "); scanf("%u", &answer);
        while (answer==0 || answer>4){
            printf("Некорректный ввод. Введите еще раз! \n");
            printf("Ответ: "); scanf("%u",&answer);
        }
        printf("----------- \n");
        if ((arr[i]+5)%4==0)
        {
            if (answer==4) *true_answ = *true_answ + 1;
            else
            {
                incor_answ[j]=arr[i];
                j++;
            }
        }
        else
        {
            if (answer==(arr[i]+5)%4) *true_answ = *true_answ + 1;
            else
            {
                incor_answ[j]=arr[i];
                j++;
            }
        }
    }
    printResultForExam(questions, answers, j, incor_answ, true_answ);
}

void exam(char questions[20][200],char answers[20][200])
{
    srand(time(NULL));
    short int *true_answ = (short int*)malloc(0);
    int *incor_answ = (int*)malloc(20); //инициализация массива неправильных ответов
    int *arr = (int*)malloc(20);
    inicialArray(arr);//инициализация массива, который будет заполняться рандомными числами
    printf("-------------------------------------\n");
    printf("Добро пожаловать в режим \"экзамен\"!\n");
    printf("-------------------------------------\n");
    printf("Условия: 20 вопросов, одна попытка на ответ\n");
    printf("\n");
    printQuestionsForExam(questions, answers, true_answ, arr, incor_answ);
}

void printQuestionsForTrain(char questions[20][200], char answers[20][200], int number)
{
    short int answer;
    printf("%s\n",questions[number]);
    printf("%s\n",answers[number]);
    printf("Ответ: "); scanf("%hd",&answer);
    while (answer==0 || answer>4){
        printf("Некорректный ввод. Введите еще раз! \n");
        printf("Ответ: "); scanf("%hd", &answer);
    }
    if ((number+5)%4==0)
    {
        while (answer!=4){
            printf("Вы ответили неверно! Повторите попытку!\n");
            printf("Ответ: "); scanf("%hd", &answer);
        }
        printf("Вы ответили верно! \n");
        printf("------------------ \n");
    }
    else
    {
        while (answer!=(number+5)%4){
            printf("Вы ответили неверно! Повторите попытку!\n");
            printf("Ответ: "); scanf("%hd", &answer);
        }
        printf("Вы ответили верно! \n");
        printf("------------------ \n");

    }
}

void train(char questions[20][200], char answers[20][200]){
    srand(time(NULL));
    int *arr = (int*)malloc(20);
    inicialArray(arr);
    printf("----------------------------------------\n");
    printf("Добро пожаловать в режим \"тренировка\"!\n");
    printf("----------------------------------------\n");
    printf("Условия: 20 вопросов, вопрос повтояется до получения правильного ответа на него\n");
    printf("\n");
    //рандомный вывод вопросов и вариантов ответов к ним на экран
    for (short int i=0; i<20;i++){
        printQuestionsForTrain(questions,answers,arr[i]);
    }
    printf("\n");
    printf("------------------------------------\n");
    printf("Поздравляю вас с прохождением теста!\n");
}

int main()
{
    setlocale(LC_ALL,"Russian");
    
    unsigned choice; //переменная выбора режима работы
    char questions [20][200]={//массив вопросов к тесту
        "Какой из указанных типов данных не является типом данных языка C++?",
        "Какая арифметическая операция позволяет получить остаток от деления числа А на Б?",
        "Как обозначается директива подключения библиотек в языке С/С++?",
        "Как обозначается цикл с предусловием в языке С/С++?",
        "Как обозначается целый беззнаковый тип данных в языке С/С++?",
        "Когда необходимо составлять блок-схему программы?",
        "Какая программа обеспечивает перевод программ с языка высокого уровня на язык более низкого уровня?",
        "Какая функция используется для вычисления квадратного корня в языке С/С++?",
        "Какая из перечисленных операций является логической?",
        "Какой набор переменных используется в выражении: sum=sqrt(x)+3*a?",
        "Как обозначается логическое ИЛИ в языке С/С++?",
        "Как обозначается цикл с постусловием в языке С/С++?",
        "Какой из перечисленных языков является языком низкого уровня?",
        "Какая функция используется для вычисления числа в степени в языке C/C++?",
        "Каким типом является тип переменных int в языке C/C++?",
        "Как обозначается оператор вывода в языке С/C++?",
        "Какой из перечисленных языков является языком высокого уровня?",
        "Как обозначается вещественнй тип данных с двойной точностью в языке С/С++?",
        "Как обозначается цикл c параметром в языке С/С++?",
        "Как называется алгоритм, в котором действия выполняются друг за другом, не прерываясь?",
    };
    char answers[20][200]={//массив вариантов ответов к тесту
        "1-real, 2-char, 3-int, 4-float",
        "1-*, 2-%, 3-&, 4-/",
        "1-$includ 2-@include, 3-#include, 4-*include",
        "1-if, 2-do while, 3-for, 4-while",
        "1-unsigned int, 2-double, 3-long int, 4-int",
        "1-После начала написания программы, 2-До начала написания программы, 3-Во время написания программы, 4-Никогда",
        "1-Ассемблер, 2-Паскаль, 3-Компилятор, 4-Фортран",
        "1-log(), 2-pow(), 3-exp(), 4-sqrt()",
        "1- &&, 2- %, 3- /, 4- *",
        "1-sum,sqrt,a; 2-sum,x,a; 3-sqrt,x,a; 4-sum,sqrt,x,a",
        "1-&&, 2-\\, 3-||, 4-//",
        "1-while, 2-if, 3-for, 4-do while",
        "1-Ассемблер, 2-Фортан, 3-PHP, 4-JavaScript",
        "1-sqrt(), 2-pow(), 3-ln(), 4-exp()",
        "1-Натуральный тип, 2-Логический тип, 3-Целочисленный тип, 4-Вещественный тип",
        "1-write, 2-scanf, 3-readln, 4-printf",
        "1-Phyton, 2-Восьмиричный язык, 3-Макроассемблер, 4-Ассемблер",
        "1- int, 2- double, 3- float, 4- char",
        "1- while, 2- do while, 3- for, 4- if",
        "1-Циклический, 2-Простой, 3-Разветвленный, 4-Линейный",
    };
    printf("Здравствуйте! В каком режиме вы хотите поработать?\nНажмите 1 чтобы выбрать режим \"экзамен\".\nНажмите 2 чтобы выбрать режим \"тренировка\"\n");
    scanf("%u", &choice);
    while (choice==0 || choice>2){//проверка корректности ввода пользователя
        printf("Некорректный ввод. Повотрите попытку \n"); scanf("%u", &choice);
    }
    switch(choice)
    {
        case 1: exam(questions,answers); break;
        case 2: train(questions, answers); break;
        default: break;
    }
    //system("pause");
    return 0;
}
