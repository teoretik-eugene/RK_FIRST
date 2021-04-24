#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *input, char *dict);

int main()
{
    FILE *dict;     // Файл словаря
    if((dict=fopen("dict.txt", "r"))==NULL){
        printf("ERROR in opening dictionary");
    };

    FILE *input;    // Входной файл

    if((input=fopen("input.txt","r"))==NULL){
        printf("ERROR in opening input\n");
    }

    FILE *output;   // Указатель на выходной файл
    remove("output.txt");

    /*вывод содержимого файла в консоль*/
    int ch;     // Указатель на файл input
    int dic;    // Указатель на файл dic
    while((ch=getc(input))!=EOF){
        printf("%c", ch);
    }
    rewind(input);
    printf("\n-------------------\n");

    /*Найдем максимальную длину слова*/
    int max_len=0;
    while((ch=getc(input))!=EOF){
        int lett_=0;
        while((ch!=' ')&&(ch!=';')&&(ch!=EOF)&&(ch!='-')&&(ch!='\n')){
            ch=getc(input);
            lett_++;
        }
        if(lett_>max_len) max_len=lett_;
    }
    rewind(input);
    //printf("%d",max_len);
    //printf("\n");

    /*Начинаем анализировать и искать слова*/
    int warning=0;
    // letters здесь - это найденное СЛОВО!
    while((ch=getc(input))!=EOF){

        char *letters = (char*)malloc(max_len+1);// Выделили максимальную память для слова
        if(letters==NULL) printf("!ERROR!");

        int i =0;
        while((ch!=' ')&&(ch!=EOF)&&(ch!=';')&&(ch!='\n')&&(ch!='-')){
            letters[i] = ch;    // Создаем локальную строку и помещаем в нее символы,
            ch = getc(input);   // составляя слово
            i++;
        }
        letters[i]='\0';

        /*Сравнение со словарем*/
        int dict_state=0;
        while ((dic=getc(dict))!=EOF){
            char *dict_word = (char*)malloc(100);   // Можно также выполнить проверку
            if(dict_word==NULL) printf("!ERROR!");  // на максимальную длину слова
            //char dict_word[100];
            int j=0;        // Будет счетчиком
            while((dic!='\n')&&(dic!=EOF)){
                dict_word[j]=dic;
                dic=getc(dict);
                j++;
            }
            dict_word[i]='\0';
            if(check(letters, dict_word)){
                dict_state++;
                warning++;
            }
            free(dict_word);
        }
        if(dict_state){
            //printf("Nashlos");
        }
        else{
            /*Создание файла выходного файла*/

            output=fopen("output.txt", "a+");
            // Проверка: было ли уже это слово в словаре?
            int re; int repeat_state = 0;
            while((re=getc(output))!=EOF){
                char *repeat = (char*)malloc(max_len+1);
                int m=0;
                while((re!=' ') && (re!=EOF)){
                    repeat[m]=re;
                    re=getc(output);
                    m++;
                }
                if((check(letters,repeat))) repeat_state++;
            }
                if(repeat_state==0){
                    fputs(letters, output);
                    fputc(' ', output);
                    fclose(output);
                }
        }
        free(letters);
        rewind(dict);
        dict_state=0;
    }
    if(warning) printf("WARNING");
    return 0;
}
    // Функция для сравнивания строк
int check(char *input, char *dict){
    int inp_len = strlen(input);
    int dict_len = strlen(dict);

    for(int i=0; input[i]!='\0' && dict[i]!='\0'; i++){
        if(input[i]==dict[i]){
            continue;
        }
        else{
            return NULL;
        }
    }
    return 1;
}
