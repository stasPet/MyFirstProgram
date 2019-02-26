#include <iostream>
using namespace std;

int search(char *str1, char *str2);							//�������� ������� ������ ���������� �������� � ������
int search_reg(char *str1, char *str2);						//�������� ������� ������ ���������� �������� � ������(� ������ ��������)

int main(int argc, char *argv[])								//�������� �������(����� ����� � ���������)
{
  setlocale (LC_ALL, "Rus");									//��������� ������������� �����
  
  int i = 0;								//�������� ���������� ��� ������
  int byte = 0;								//�������� ���������� �������� ����
  int total_line = 0;						//�������� ���������� �������� ������ ���������� �����
  int count_word = 0;						//�������� ���������� �������� ����
  int count_total_word = 0;					//�������� ���������� �������� ������ ����������� ����������
  int count_line = 0;						//�������� ���������� �������� �����
  char static mas1 [10000][10000] = {0};	//������ ��� �������� ������
  char static mas2 [10000][10000] = {0};	//������ ��� �������� ������2
  char buffer_line [10000] = {0};			//�������� ��������� �������

  FILE *fp;																			//������������� fp
  if (argc != 4 && argc!=5){
	printf("\n������: �������� ������ �����\n");									//������� ��� ���������� ������ �� ���������
    printf("������ �����: search.exe ������� �������� ������� �����\n");			//����� ���������� �� �������
	printf("(���� r c ������ ��������)\n");
	exit(1);																		//����� �� ������� ���� ������
  }

  if (argc == 5) {
    if (*argv [4] != 'r') {								//�������� ������������ ������� �����
      cout << "\n������: �������� ������ �����\n";
      exit(1);
    }
  }
  if ((fp = fopen(argv[1],"r"))==NULL){					//�������� ����� ��� ������
    printf("���������� ������� ����\n");				//����� ���������� �� �������
    exit(1);											//����� �� ������� ���� ������
  }

  fseek(fp, 0, SEEK_END);								//������� ������� ����� � �����
  byte = ftell(fp);										//������ ���� � �����
  fseek(fp, 0, SEEK_SET);								//������� ������� � ������ �����
  
  while (!feof(fp)){									//���� ���� �� ����� �����
    fgets(buffer_line, 10000, fp);						//������������� ������� ������� �� fp
	total_line++;										//��������� �������� �����
  }

  fseek(fp, 0, SEEK_SET);
  
  for (i=0; i<total_line; i++){							
    fgets(mas1 [i], 10000, fp);							//������������� �������
  }

  fseek(fp, 0, SEEK_SET);

  for (i=0; i<total_line; i++){							
    fgets(mas2 [i], 10000, fp);							//������������� �������2
  }

  fseek(fp, 0, SEEK_SET);								

  fclose( fp );											//�������� �����
  
  if ((fp = fopen(argv[2],"a"))==NULL){					//�������� ����� ��� ������
    printf("���������� ������� ����\n");				//����� ���������� �� �������
    exit(1);											//����� �� ������� ���� ������
  }
  
  cout << "\n����� �����: " << total_line << '\n';					//����� ���������� �� �������
  cout << "����� ����: " << byte << '\n';
  cout << "� ������ (�������)\n";
  for (i=0; i < total_line; i++){
    count_line = i+1;
	if (argc == 5) count_total_word += count_word = search_reg(argv[3],mas1 [i]);
	if (argc == 4) count_total_word += count_word = search(argv[3],mas1 [i]);
	  if (count_word)
	    cout << count_line << " (" << count_word << ")\n";		
  }
  cout << "������� �����: " << argv[3] << " (" << count_total_word  << " ����������)";

  fputs("����� ����: ",fp);												//������ ���������� � ����
  sprintf(buffer_line,"%d",byte);										//�������������� int  � char
  fputs(buffer_line,fp);
  fputs("\n",fp);
  sprintf(buffer_line,"%d",total_line);
  fputs("����� �����: ",fp);
  fputs(buffer_line,fp);
  fputs("\n",fp);
  fputs("� ������ (�������)\n",fp);
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
  fputs("������� �����: ",fp);
  fputs(argv [3],fp);
  
  fputs(" (",fp);
  sprintf(buffer_line,"%d",count_total_word);
  fputs(buffer_line,fp);
  fputs(" ����������)",fp);
  
  fseek(fp, 0, SEEK_SET);
  
  fclose( fp );
  
return 0;
}

int search (char *str1, char *str2)   //������� ������ ���������� �������� � ������ (��� ����� ��������)
{
  int t,a = 0;                        //��������, ������������� ����������
  char *p, *p2;                       //�������� ����������

   for (t=0; str2[t]; t++){				//���� ��������� �������� ���� �� ����� ������
    p = &str2[t];						//��������� ��������� �� ������ ������ ������ 2
	p2 = str1;							//��������� ��������� �� ������ ������ ������ 1

	*p = tolower(*p);					//�������� ��� ����� � ����������� ��������
	*p2 = tolower(*p2);
    
	while (*p2 && *p2 == *p){			//���������� ����� ���� ������� � ������ ���������
	  p++;								//��������� ��������� �� ��������� ������ 
	  p2++;								//��������� ��������� �� ��������� ������ 
	}
	if (!*p2)							//���� ����� ������ 1
	  a++;								//��������� �������� ���������� � ������
    }
return a;								//������� ���������� ���� � ������
}

int search_reg(char *str1, char *str2)   //������� ������ ���������� �������� � ������ (� ������ ��������)
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