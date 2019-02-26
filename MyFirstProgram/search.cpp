#include <iostream>
using namespace std;

int search(char *str1, char *str2);							//Прототип функции поиска одинаковых символов в строке
int search_reg(char *str1, char *str2);						//Прототип функции поиска одинаковых символов в строке(с учетом регистра)

int main(int argc, char *argv[])								//Основная функция(точка входа в программу)
{
  setlocale (LC_ALL, "Rus");									//Устоновка регионального языка
  
  int i = 0;								//Создание переменной для циклов
  int byte = 0;								//Создание переменной счетчика байт
  int total_line = 0;						//Создание переменной счетчика общего количества строк
  int count_word = 0;						//Создание переменной счетчика слов
  int count_total_word = 0;					//Создание переменной счетчика общего колличества совпадений
  int count_line = 0;						//Создание переменной счетчика строк
  char static mas1 [10000][10000] = {0};	//Массив для хранения текста
  char static mas2 [10000][10000] = {0};	//Массив для хранения текста2
  char buffer_line [10000] = {0};			//Создание буферного массива

  FILE *fp;																			//Инициализация fp
  if (argc != 4 && argc!=5){
	printf("\nОшибка: Неверный формат ввода\n");									//Условия для досрочного выходи из программы
    printf("Формат ввода: search.exe иточник приемник искомое слово\n");			//Вывод информации на консоль
	printf("(ключ r c учетом регистра)\n");
	exit(1);																		//Выход из функции если ошибка
  }

  if (argc == 5) {
    if (*argv [4] != 'r') {								//Проверка правельности формата ключа
      cout << "\nОшибка: Неверный формат ключа\n";
      exit(1);
    }
  }
  if ((fp = fopen(argv[1],"r"))==NULL){					//Открытие файла для чтения
    printf("Невозможно открыть файл\n");				//Вывод информации на консоль
    exit(1);											//Выход из функции если ошибка
  }

  fseek(fp, 0, SEEK_END);								//Перенос позиции файла в конец
  byte = ftell(fp);										//Посчет байт в файле
  fseek(fp, 0, SEEK_SET);								//Возврат позиции в начало файла
  
  while (!feof(fp)){									//Цикл пока не конец файла
    fgets(buffer_line, 10000, fp);						//Инициализация массива строкой из fp
	total_line++;										//Инкремент счетчика строк
  }

  fseek(fp, 0, SEEK_SET);
  
  for (i=0; i<total_line; i++){							
    fgets(mas1 [i], 10000, fp);							//Инициализация массива
  }

  fseek(fp, 0, SEEK_SET);

  for (i=0; i<total_line; i++){							
    fgets(mas2 [i], 10000, fp);							//Инициализация массива2
  }

  fseek(fp, 0, SEEK_SET);								

  fclose( fp );											//Закрытие файла
  
  if ((fp = fopen(argv[2],"a"))==NULL){					//Открытие файла для записи
    printf("Невозможно создать файл\n");				//Вывод информации на консоль
    exit(1);											//Выход из функции если ошибка
  }
  
  cout << "\nВсего строк: " << total_line << '\n';					//Вывод информации на консоль
  cout << "Всего байт: " << byte << '\n';
  cout << "В строке (Совпало)\n";
  for (i=0; i < total_line; i++){
    count_line = i+1;
	if (argc == 5) count_total_word += count_word = search_reg(argv[3],mas1 [i]);
	if (argc == 4) count_total_word += count_word = search(argv[3],mas1 [i]);
	  if (count_word)
	    cout << count_line << " (" << count_word << ")\n";		
  }
  cout << "Искомое слово: " << argv[3] << " (" << count_total_word  << " совпадений)";

  fputs("Всего байт: ",fp);												//Запись информации в файл
  sprintf(buffer_line,"%d",byte);										//Преобразование int  в char
  fputs(buffer_line,fp);
  fputs("\n",fp);
  sprintf(buffer_line,"%d",total_line);
  fputs("Всего строк: ",fp);
  fputs(buffer_line,fp);
  fputs("\n",fp);
  fputs("В строке (Совпало)\n",fp);
  for (i=0; i < total_line; i++){
    count_line = i+1;
	if (argc == 5) count_word = search_reg(argv[3],mas2 [i]);
	if (argc == 4) count_word = search(argv[3],mas2 [i]);
	if (count_word) {
	  sprintf(buffer_line,"%d",count_line);
      fputs(buffer_line,fp);
	  fputs(" (",fp);
	  sprintf(buffer_line,"%d",count_word);
	  fputs(buffer_line,fp);
	  fputs(")",fp);
	  fputs("\n",fp);
	}
  }
  fputs("Искомое слово: ",fp);
  fputs(argv [3],fp);
  
  fputs(" (",fp);
  sprintf(buffer_line,"%d",count_total_word);
  fputs(buffer_line,fp);
  fputs(" совпадений)",fp);
  
  fseek(fp, 0, SEEK_SET);
  
  fclose( fp );
  
return 0;
}

int search (char *str1, char *str2)   //Функция поиска одинаковых символов в строке (без учета регистра)
{
  int t,a = 0;                        //Создание, инициализация переменных
  char *p, *p2;                       //Создание указателей

   for (t=0; str2[t]; t++){				//Цикл сравнения символов пока не конец строки
    p = &str2[t];						//установка указателя на первый символ строки 2
	p2 = str1;							//установка указателя на первый символ строки 1

	*p = tolower(*p);					//Приводим оба знака к одинаковому регистру
	*p2 = tolower(*p2);
    
	while (*p2 && *p2 == *p){			//Выполнение цикла если символы в строке совпадают
	  p++;								//Инкримент указателя на следующий символ 
	  p2++;								//Инкримент указателя на следующий символ 
	}
	if (!*p2)							//Если конец строки 1
	  a++;								//Инкремент счетчика совпадений в строке
    }
return a;								//Возврат количества слов в строке
}

int search_reg(char *str1, char *str2)   //Функция поиска одинаковых символов в строке (с учетом регистра)
{
  int t,a = 0;
  char *p, *p2;

   for (t=0; str2[t]; t++){
    p = &str2[t];
	p2 = str1;
    
	while (*p2 && *p2 == *p){
	  p++;
	  p2++;
	}
	if (!*p2)
	  a++;
    }
return a;
}