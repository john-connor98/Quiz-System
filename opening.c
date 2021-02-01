#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>

typedef struct                                       /// STRUCTURE TO STORE THE WHOLE QUESTION AS A VARIABLE
    {
        char question[50];
        char answer1[50];
        char answer2[50];
        char answer3[50];
        char answer4[50];
        char category[9];
        int marksAllotted;
        char marksallotted[3];
        int correctAnswer;
        char correctanswer[2];
        int questionId;
        char questionid[5];
        int selectedAnswer;
    }questionFormat;

int openinScreen();
void generateRandom(int questionNumber[]);
char quizWelcomeScreen(char* name);                                     /// c does not support reference variable concept
void createArray(questionFormat** s);
int convertStringToInt(char p[],int size);
int setValues(questionFormat** s);
void printquestios(questionFormat** s);
int marksAwarded(questionFormat*** point,int i);
int totalScore(questionFormat*** point);
int total(questionFormat*** point);
char quizEndScreen(char *name,questionFormat** s);

void createArray(questionFormat** s)
{
    *s = (questionFormat*)calloc(10,sizeof(questionFormat));
}

int openingScreen()                                        /// OPENING SCREEN
{
    int x=2;
    printf("\n===================================================================================================================\n");
    printf("Welcome to Simple Quiz Game..\n\n");
    printf("Your options\n");
    printf("============\n\n");
    printf("1. Start The Quiz\n");
    printf("2. Exit\n");
    scanf("%d",&x);
    return x;
}

char quizWelcomeScreen(char* name)                             /// WELCOME SCREEN
{
    printf("===================================================================================================================\n");
    printf("Welcome to Simple Quiz Game\n\n");
    printf("Player Name : ");
    fflush(stdin);
    gets(name);
    printf("\nReady(Y/N) : ");
    return getchar();
}

void generateRandom(int questionNumber[])          /// FUNCTION TO GENERATE RANDOM NUMBER USED AS INDEX TO GENERATE POINTERS TO THE QUESTIONS
{
    int num,flag=1;
    srand(time(NULL));
    for(int i=0;i<10;i++)
    {
        flag=1;
        num=0+rand()%29;
        for(int j=0;j<i;j++)
        {
            if(num==questionNumber[j])
            {
                flag=0;
                i--;
                break;
            }
        }
        if(flag)
            questionNumber[i]=num;
    }
}

int convertStringToInt(char p[],int size)                  /// CONVERT STRING TO INTEGER TO STORE INTEGER VALUES READ FROM FILE AS STRING
{
    int x=p[0]-48;
    for(int i=1;i<size;i++)
        x=x*10+p[i]-48;
    return x;
}

int setValues(questionFormat** s)                         /// READING FILE TO SAVE QUESTIONS IN STRUCTURE
{
    FILE* datafile;
    datafile = fopen("SQG-QTNBNK.txt","r");                /// OPENING THE FILE TO READ AND SAVE QUESTIONS
    if(datafile==NULL)
    {
        printf("=========================\n\n");
        printf("Error Loading The Content\n\n");
        printf("=========================\n\n");
        return 1;
    }
    int questionBank[30];                                /// QUESTION BANK TO SELECT QUESTIONS
    for(int i=0;i<30;i++)
        questionBank[i]=i*268;
    int questionNumber[10];                              /// ARRAY TO STORE THE QUESTION SELECTED AT RANDOM
    generateRandom(questionNumber);                      /// SELECTION RANDOM QUESTIONS

    for(int k=0,m=0;k<10;k++,m++)
    {
        fseek(datafile,questionBank[questionNumber[k]],SEEK_SET);                         /// READING CATAGORY
        int i=0;
        while(i<9)
            (*(s)+m)->category[i++]=fgetc(datafile);

        fseek(datafile,questionBank[questionNumber[k]]+9,SEEK_SET);                       /// READING QUESTION ID
        i=0;
        while(i<5)
            (*(s)+m)->questionid[i++]=fgetc(datafile);
        (*(s)+m)->questionId=convertStringToInt((*(s)+m)->questionid,5);                  /// CONVERT CHAR TO INT TYPE

        fseek(datafile,questionBank[questionNumber[k]]+14,SEEK_SET);                     /// READING QUESTION TEXT
        i=0;
        while(i<50)
             (*(s)+m)->question[i++]=fgetc(datafile);

        fseek(datafile,questionBank[questionNumber[k]]+64,SEEK_SET);                    /// READING OPTION 1
        i=0;
        while(i<50)
             (*(s)+m)->answer1[i++]=fgetc(datafile);

        fseek(datafile,questionBank[questionNumber[k]]+114,SEEK_SET);                  /// READING OPTION 2
        i=0;
        while (i<50)
                (*(s)+m)->answer2[i++]=fgetc(datafile);

        fseek(datafile,questionBank[questionNumber[k]]+164,SEEK_SET);                  /// READING OPTION 3
        i=0;
        while (i<50)
                (*(s)+m)->answer3[i++]=fgetc(datafile);

        fseek(datafile,questionBank[questionNumber[k]]+214,SEEK_SET);                 /// READING OPTION 4
        i=0;
        while (i<50)
                (*(s)+m)->answer4[i++]=fgetc(datafile);

        fseek(datafile,questionBank[questionNumber[k]]+264,SEEK_SET);                 /// READING THE CORRECT ANSWER FROM FILE
        i=0;
        while(i<1)
            (*(s)+m)->correctanswer[i++]=fgetc(datafile);
        (*(s)+m)->correctAnswer=convertStringToInt((*(s)+m)->correctanswer,1);                /// CONVERTING CHAR TO INT TYPE

        fseek(datafile,questionBank[questionNumber[k]]+265,SEEK_SET);                 /// RADING THE MARKS ALLOTTED TO THE QUESTION
        i=0;
        while(i<3)
            (*(s)+m)->marksallotted[i++]=fgetc(datafile);
        (*(s)+m)->marksAllotted=convertStringToInt((*(s)+m)->marksallotted,3);                 /// CONVERTING CHAR TO INT TYPE
    }
    fclose(datafile);                                                                  /// CLOSING THE FILE
}

void printquestios(questionFormat** s)                                       /// FUNCTION TO PRINT 10 RANDOM QUESTIONS ONE BY ONE
{
    for(int i=0;i<10;i++)
    {
        int x;
        printf("===================================================================================================================\n");
        printf("Question Number :%d\n",(*(s)+i)->questionId);
        printf("Question Category :");
        for(int j=0;j<8;j++)
            printf("%c",(*(s)+i)->category[j]);
        printf("\n");
        printf("Question Text :");
        for(int j=0;j<50;j++)
             printf("%c",(*(s)+i)->question[j]);
        printf("\n\nAvailable Answers :\n");
        printf("1.");
        for(int j=0;j<50;j++)
             printf("%c",(*(s)+i)->answer1[j]);
        printf("\n2.");
        for(int j=0;j<50;j++)
            printf("%c",(*(s)+i)->answer2[j]);
        printf("\n3.");
        for(int j=0;j<50;j++)
            printf("%c",(*(s)+i)->answer3[j]);
        printf("\n4.");
        for(int j=0;j<50;j++)
            printf("%c",(*(s)+i)->answer4[j]);
        printf("\nMarks Allotted :%d\n",(*(s)+i)->marksAllotted);
        printf("\nEnter the correct answer :");
        scanf("%d",&x);
        printf("Lock it (Y/N) :");
        fflush(stdin);
        if(getchar()=='Y')
            (*(s)+i)->selectedAnswer=x;
        else
            (*(s)+i)->selectedAnswer=-1;
        printf("\n\n");
    }
}

int marksAwarded(questionFormat*** point,int i)                            /// FUNCTION TO DISPLAY MARKS AWARDED IF ANSWER IS CORRECT
{
    if(((**point)+i)->correctAnswer==((**point)+i)->selectedAnswer)
        return ((**point)+i)->marksAllotted;
    else
        return 0;
}

int totalScore(questionFormat*** point)                                    /// FUNCTION TO COMPUTE THE TOTAL OF CORRECT ANSWERS
{
    int count=0;
    for(int i=0;i<10;i++)
    {
        if(((**point)+i)->selectedAnswer==((**point)+i)->correctAnswer)
            count+=((**point)+i)->marksAllotted;
    }
    return count;
}

int total(questionFormat*** point)                                          /// FUNCTION TO CALCULATE TOTAL MARKS
{
    int t=0;
    for(int i=0;i<10;i++)
            t+=((**point)+i)->marksAllotted;
    return t;
}

char quizEndScreen(char *name,questionFormat** s)                            /// SHOW END SCREEN OF QUIZ
{
    printf("===================================================================================================================\n\n");
    printf("Congratulations %s. You have completed the quiz\n",name);
    printf("You have scored %d out of 10\n",totalScore(&s));
    printf("Here are your answers ...\n\n");
    for(int i=0;i<10;i++)
    {
        printf("=======================================\n\n");
        printf("Question Category :");                                   /// DISPLAY QUESTION CATEGORY
        for(int j=0;j<8;j++)
            printf("%c",(*(s)+i)->category[j]);
        printf("\n");
        printf("Question %d: ",(*(s)+i)->questionId);                    /// DISPLAY QUESTION ID
        for(int j=0;j<50;j++)                                            /// DISPLAY QUESTION TEXT
             printf("%c",(*(s)+i)->question[j]);
        printf("\n");
        printf("Correct Answer : ");                                     /// DISPLAY CORRECT ANSWER
        if(((*s)+i)->correctAnswer==1)
        {
             printf("1.");
             for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer1[j]);
        }
        else if(((*s)+i)->correctAnswer==2)
        {
            printf("2.");
            for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer2[j]);
        }
        else if(((*s)+i)->correctAnswer==3)
        {
            printf("3.");
            for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer3[j]);
        }
        else
        {
            printf("4.");
            for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer4[j]);
        }
        printf("\nYour Answer : ");                                            /// DISPLAY SELECTED ANSWER
        if(((*s)+i)->selectedAnswer==1)
        {
             printf("1.");
             for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer1[j]);
        }
        else if(((*s)+i)->selectedAnswer==2)
        {
            printf("2.");
            for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer2[j]);
        }
        else if(((*s)+i)->selectedAnswer==3)
        {
            printf("3.");
            for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer3[j]);
        }
        else
        {
            printf("4.");
            for(int j=0;j<50;j++)
                printf("%c",(*(s)+i)->answer4[j]);
        }
        printf("\nMarks Awarded :%d\n",marksAwarded(&s,i));                          /// DISPLAY MARKS AWARDED
    }
    printf("\n\nYour Final Total Score : %d out of %d",totalScore(&s),total(&s));    /// FINAL SCORE

    printf("\nPress any key to go to main menu ..");
    return getch();
}

/*int main()
{
    char name[100];
 X: if(openingScreen()==2)
        return 0;
    else
    {
        if(quizWelcomeScreen(name)=='N')
            return 0;
        else
        {
           questionFormat* start=NULL;
           createArray(&start);
           setValues(&start);
           printquestios(&start);
           if(quizEndScreen(name,&start))
           goto X;                                      /// TO RETURN BACK TO THE OPENING SCREEN
        }
    }
    return 0;
}*/
