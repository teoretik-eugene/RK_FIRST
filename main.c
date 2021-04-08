#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *input, char *dict);

int main(int argc, char *argv[])
{
    FILE *dict;     // ���� �������
    if((dict=fopen(argv[2], "r"))==NULL){        // argv[2]
        printf("ERROR in opening dictionary");
    };

    FILE *input;    // ������� ����

    if((input=fopen(argv[1],"r"))==NULL){       // argv[1]
        printf("ERROR in opening input\n");
    }

    FILE *output;   // ��������� �� �������� ����
    remove(argv[3]);                       // argv[3]

    /*����� ����������� ����� � �������*/
    int ch;     // ��������� �� ���� input
    int dic;    // ��������� �� ���� dic
    while((ch=getc(input))!=EOF){
        printf("%c", ch);
    }
    rewind(input);
    printf("\n-------------------\n");

    /*������ ������������ ����� �����*/
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

    /*�������� ������������� � ������ �����*/
    int warning=0;
    // letters ����� - ��� ��������� �����!
    while((ch=getc(input))!=EOF){

        char *letters = (char*)malloc(max_len+1);// �������� ������������ ������ ��� �����
        if(letters==NULL) printf("!ERROR!");

        int i =0;
        while((ch!=' ')&&(ch!=EOF)&&(ch!=';')&&(ch!='\n')&&(ch!='-')){
            letters[i] = ch;    // ������� ��������� ������ � �������� � ��� �������,
            ch = getc(input);   // ��������� �����
            i++;
        }
        letters[i]='\0';

        /*��������� �� ��������*/
        int dict_state=0;
        while ((dic=getc(dict))!=EOF){
            char *dict_word = (char*)malloc(100);   // ����� ����� ��������� ��������
            if(dict_word==NULL) printf("!ERROR!");  // �� ������������ ����� �����
            //char dict_word[100];
            int j=0;        // ����� ���������
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
            /*�������� ����� ��������� �����*/

            output=fopen(argv[3], "a+");           // argv[3]
            // ��������: ���� �� ��� ��� ����� � �������?
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
    // ������� ��� ����������� �����
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