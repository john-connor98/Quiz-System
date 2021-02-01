#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include"opening.c"

using namespace std;
int openingScreen();
int attendQuiz();
int convertStrToInt(string p,int size);

class authentication                                           /// CLASS FOR AUTHENTICATION ONLY
    {
        string name;
        string password;
    public:
        int administratorLogin()                                    /// REQUESTING AND CONFORMING USER NAME AND PASSWORD
       {
           char x;
           cout<<"Administrator Login\n";
           cout<<"===================\n";
           cout<<"User Name :";
           cin.sync();
           getline(cin,name);
           cout<<"\nPassword  :";
           getline(cin,password);
           cout<<"\nConfirm (Y/N) :";
           cin>>x;
           if(x=='Y')
           {
               string line, pass;
               ifstream myfile;
               myfile.open ("admins.txt");
               if(myfile.fail())                                      /// FAIL() RETURNS TRUE IF AN INPUT OR OUTPUT OPERATION FAILS
                {
                    cout << "Input file opening failed.\n";
                    return 0;                                        /// ///exit(1); RETURNS FROM THE MAIN
                }
                while(myfile)
                    {
                        getline(myfile,line);
                        if(line==name)
                        {
                            getline(myfile,pass);
                            if(pass==password)
                            {
                                cout<<"\nAccepted\n";
                                return 1;
                            }
                            else
                            {
                                cout<<"\nAccess denied\n";
                                return 0;
                            }
                        }
                    getline(myfile,pass);
                    }
                    myfile.close();
                    cout<<"\nAccess denied\n";
           }
           else
               return 0;
       }
    };

    class manageQuestions
    {
        char categ[10];                                   /// CHARACTER ARRAYS TO STORE CHANGES IN CONTENT
        char id[6];
        char que[51];
        char option1[51];
        char option2[51];
        char option3[51];
        char option4[51];
        char correctOption[2];
        char allottedMarks[5];
    public:
         void addNewQuestions()                           /// FUNCTION TO ADD NEW QUESTION
        {
            cout<<"\n\t\t\t\tAdd New Questions";
            cout<<"\n\t\t\t    =======================\n";
            cin.sync();
            cout<<"\nQuestion category :  ";
            gets(categ);
            cout<<"Question Id   :  ";
            gets(id);
            cout<<"Question Text :  ";
            gets(que);
            cout<<"Ist Option      :  ";
            gets(option1);
            cout<<"2nd Option      :  ";
            gets(option2);
            cout<<"3rd Option      :  ";
            gets(option3);
            cout<<"4th Option      :  ";
            gets(option4);
            cout<<"Correct  Option  (1/2/3/4/) : ";
            gets(correctOption);
            cout<<"Allotted Marks  :  ";
            gets(allottedMarks);
            char confirm;
            cout<<"Confirm (Y/N)   :  ";
            cin>>confirm;

            FILE* myfile;
            myfile=fopen("SQG-QTNBNK.txt","a");
            if(confirm=='Y')
            {
                fputs(categ,myfile);                        /// CATEGORY
                for(int i=0;i<9-strlen(categ);i++)
                    fputc(' ',myfile);
                fputs(id,myfile);                           /// ID
                for(int i=0;i<5-strlen(id);i++)
                    fputc(' ',myfile);
                fputs(que,myfile);                           /// QUESTION TEXT
                for(int i=0;i<50-strlen(que);i++)
                    fputc(' ',myfile);
                fputs(option1,myfile);                           /// OPTION 1
                for(int i=0;i<50-strlen(option1);i++)
                    fputc(' ',myfile);
                fputs(option2,myfile);                           /// OPTION 2
                for(int i=0;i<50-strlen(option2);i++)
                    fputc(' ',myfile);
                fputs(option3,myfile);                            /// OPTION 3
                for(int i=0;i<50-strlen(option3);i++)
                fputc(' ',myfile);
                fputs(option4,myfile);                            /// OPTION 4
                for(int i=0;i<50-strlen(option4);i++)
                    fputc(' ',myfile);
                fputs(correctOption,myfile);                            /// CORRECT OPTION
                for(int i=0;i<1-strlen(correctOption);i++)
                    fputc(' ',myfile);
                fputs(allottedMarks,myfile);                            /// ALLOTTED MARKS
                for(int i=0;i<3-strlen(allottedMarks);i++)
                    fputc(' ',myfile);
            }
            fclose(myfile);
        }

        void modifyExistingQuestions()                    /// FUNCTION TO MODIFY EXISTING QUESTION
        {
            int x;
            cout<<"\n\t\t\t\tModify Questions";
            cout<<"\n\t\t\t    =======================\n";
            char Id[6];
            bool flag=false;
            cout<<"Question Id   :  ";
            cin.sync();
            gets(id);                                         /// READING QUESTION ID TO CHECK THE SAME IN FILE
            {
                int i;
                for(i=strlen(id);i<5;i++)
                id[i]=' ';
                id[i]='\0';
            }
            FILE* myfile;
            myfile=fopen("SQG-QTNBNK.txt","r+");
            int questionBank[30];                                /// QUESTION BANK TO SELECT QUESTIONS
            for(int i=0;i<30;i++)
                questionBank[i]=i*268;
            for(int i=0;i<30;i++)                                /// READING AND FINDING THE CORRECT MATCH OF QUESTION ID IN FILE
            {
                fseek(myfile,questionBank[i]+9,SEEK_SET);
                {
                    int k=0;
                    while(k<5)
                        Id[k++]=fgetc(myfile);
                    Id[k]='\0';
                }
                if(!strcmp(Id,id))                               /// IF ID FOUND THEN DESPLAY THE CONTENT AND PROCEED FOR RESPECTIVE ACTION
                {
                    cout<<"\nField to modify";
                    cout<<"\n1. Question Text";
                    cout<<"\n2. 1st Option";
                    cout<<"\n3. 2nd Option";
                    cout<<"\n4. 3rd Option";
                    cout<<"\n5. 4th Option";
                    cout<<"\n6. Correct Option";
                    cout<<"\n7. Allotted Marks";
                    cout<<"\nEnter your choice (1/2/3/4/5/6/7) :  ";
                    cin>>x;
                    char c;
                    switch(x)
                    {
                    case 1:                                                                /// READING AND DISPLAYING QUESTION TEXT
                        {
                            cout<<"Question Text :  ";
                            fseek(myfile,questionBank[i]+14,SEEK_SET);
                            int m=0;
                            while(m<50)
                                {
                                    c=fgetc(myfile);
                                    cout<<c;
                                    m++;
                                }
                             cin.sync();
                             cout<<"\nEnter new text (skip if not to modify) : ";
                             gets(que);
                             break;
                         }
                    case 2:                                                                /// READING AND DISPLAYING OPTION 1
                        {
                            cout<<"Ist Option      :  ";
                            fseek(myfile,questionBank[i]+64,SEEK_SET);
                            int m=0;
                            while(m<50)
                            {
                                c=fgetc(myfile);
                                cout<<c;
                                m++;
                            }
                            cin.sync();
                            cout<<"\nEnter new text (skip if not to modify) : ";
                            gets(option1);
                            break;
                        }
                    case 3:                                                                    /// READING AND DISPLAYING OPTION 2
                        {
                            cout<<"2nd Option      :  ";
                            fseek(myfile,questionBank[i]+114,SEEK_SET);
                            int m=0;
                            while(m<50)
                            {
                                c=fgetc(myfile);
                                cout<<c;
                                m++;
                            }
                            cin.sync();
                            cout<<"\nEnter new text (skip if not to modify) : ";
                            gets(option2);
                            break;
                        }
                    case 4:                                                                    /// READING AND DISPLAYING OPTION 3
                        {
                            cout<<"3rd Option      :  ";
                            fseek(myfile,questionBank[i]+164,SEEK_SET);
                            int m=0;
                            while(m<50)
                            {
                                c=fgetc(myfile);
                                cout<<c;
                                m++;
                            }
                            cin.sync();
                            cout<<"\nEnter new text (skip if not to modify) : ";
                            gets(option3);
                            break;
                        }
                    case 5:                                                                    /// READING AND DISPLAYING OPTION 4
                        {
                            cout<<"4th Option      :  ";
                            fseek(myfile,questionBank[i]+214,SEEK_SET);
                            int m=0;
                            while(m<50)
                            {
                                c=fgetc(myfile);
                                cout<<c;
                                m++;
                            }
                            cin.sync();
                            cout<<"\nEnter new text (skip if not to modify) : ";
                            gets(option4);
                            break;
                        }
                    case 6:                                                                /// READING AND DISPLAYING CORRECT OPTION
                        {
                        cout<<"Correct  Option  (1/2/3/4/) : ";
                        fseek(myfile,questionBank[i]+264,SEEK_SET);
                        c=fgetc(myfile);
                        cout<<c;
                        cin.sync();
                        cout<<"\nEnter new text (skip if not to modify) : ";
                        gets(correctOption);
                        break;
                        }
                    case 7:                                                                /// READING AND DISPLAYIN ALLOTTED MARKS
                        {
                            cout<<"Allotted Marks  :  ";
                            fseek(myfile,questionBank[i]+265,SEEK_SET);
                            int m=0;
                            while(m<3)
                                {
                                    c=fgetc(myfile);
                                    cout<<c;
                                    m++;
                                }
                            cin.sync();
                            cout<<"\nEnter new text (skip if not to modify) : ";
                            gets(allottedMarks);
                            break;
                        }
                    }
                    char confirm;
                    cout<<"\nConfirm (Y/N)  :  ";
                    cin>>confirm;
                    if(confirm=='Y')
                    {
                        switch(x)
                        {
                        case 1:                                                     /// CORRECTING QUESTION TEXT
                            {
                                fseek(myfile,questionBank[i]+14,SEEK_SET);
                                fputs(que,myfile);
                                for(int i=0;i<50-strlen(que);i++)
                                fputc(' ',myfile);
                                break;
                            }
                        case 2:                                                     /// CORRECTING OPTION 1
                            {
                                fseek(myfile,questionBank[i]+64,SEEK_SET);
                                fputs(option1,myfile);
                                for(int i=0;i<50-strlen(option1);i++)
                                fputc(' ',myfile);
                                break;
                            }
                        case 3:                                                      /// CORRECTING OPTION 2
                            {
                                fseek(myfile,questionBank[i]+114,SEEK_SET);
                                fputs(option2,myfile);
                                for(int i=0;i<50-strlen(option2);i++)
                                    fputc(' ',myfile);
                                break;
                            }
                        case 4:                                                      /// CORRECTING OPTION 3
                            {
                                fseek(myfile,questionBank[i]+164,SEEK_SET);
                                fputs(option3,myfile);
                                for(int i=0;i<50-strlen(option3);i++)
                                    fputc(' ',myfile);
                                break;
                            }
                        case 5:                                                       /// CORRECTING OPTION 4
                            {
                                fseek(myfile,questionBank[i]+214,SEEK_SET);
                                fputs(option4,myfile);
                                for(int i=0;i<50-strlen(option4);i++)
                                fputc(' ',myfile);
                                break;
                            }
                        case 6:                                                        /// CORRECTING CORRECT OPTION
                            {
                                fseek(myfile,questionBank[i]+264,SEEK_SET);
                                fputs(correctOption,myfile);
                                break;
                            }
                        case 7:                                                        /// CORRECTING ALLOTTED MARKS
                            {
                                fseek(myfile,questionBank[i]+265,SEEK_SET);
                                fputs(allottedMarks,myfile);
                                for(int i=0;i<3-strlen(allottedMarks);i++)
                                    fputc(' ',myfile);
                                break;
                            }
                        }
                    }
                    flag=true;
                    break;
                }
            }
            if(!flag)
                cout<<"\nquestion id not found";
            fclose(myfile);
        }

        void deleteQuestions()                            /// FUNCTION TO DELETE ANY QUESTION
        {
            int x;
            cout<<"\n\t\t\t\tDelete Questions";
            cout<<"\n\t\t\t    =======================\n";
            char Id[6];
            bool flag=false;
            cin.sync();                                               /// GETTING QUESTION ID OF THE QUESTION TO BE DELETED
            cout<<"Question Id   :  ";
            gets(id);
            {
                int i;
                for(i=strlen(id);i<5;i++)
                    id[i]=' ';
                id[i]='\0';
            }
                FILE* myfile;
                myfile=fopen("SQG-QTNBNK.txt","r+");
                if(myfile==NULL)
            {
                printf("=========================\n\n");
                printf("Error Loading The Content\n\n");
                printf("=========================\n\n");
                return;
            }
                int questionBank[30];                                /// QUESTION BANK TO SELECT QUESTIONS
                for(int i=0;i<30;i++)                                /// STORING STARTING POINTER(CHARACTER NUMBER) OF EACH QUESTION
                    questionBank[i]=i*268;
                for(int i=0;i<30;i++)
                {
                    fseek(myfile,questionBank[i]+9,SEEK_SET);                       /// READING QUESTION ID FORM FILE
                    {
                        int k=0;
                        while(k<5)
                            Id[k++]=fgetc(myfile);
                        Id[k]='\0';
                    }
                    if(!strcmp(Id,id))                                              /// IF QUESTION ID MATCHES THEN DELETION PROCESS PROCEEDS
                    {
                        char c;
                        int m;
                    {
                        cout<<"Question Text :  ";                                  /// DISPLAYING THE QUESTION TEXT
                        fseek(myfile,questionBank[i]+14,SEEK_SET);
                        m=0;
                        while(m<50)
                        {
                            c=fgetc(myfile);
                            cout<<c;
                            m++;
                        }
                        cout<<"\nIst Option      :  ";                              /// DISPLAYING THE OPTION 1
                        fseek(myfile,questionBank[i]+64,SEEK_SET);
                        m=0;
                        while(m<50)
                        {
                            c=fgetc(myfile);
                            cout<<c;
                            m++;
                        }
                        cout<<"\n2nd Option      :  ";                               /// DISPLAYING THE OPTION 2
                        fseek(myfile,questionBank[i]+114,SEEK_SET);
                        m=0;
                        while(m<50)
                        {
                            c=fgetc(myfile);
                            cout<<c;
                            m++;
                        }
                        cout<<"\n3rd Option      :  ";                               /// DISPLAYING THE OPTION 3
                        fseek(myfile,questionBank[i]+164,SEEK_SET);
                        m=0;
                        while(m<50)
                        {
                            c=fgetc(myfile);
                            cout<<c;
                            m++;
                        }
                        cout<<"\n4th Option      :  ";                               /// DISPLAYING THE OPTION 4
                        fseek(myfile,questionBank[i]+214,SEEK_SET);
                        m=0;
                        while(m<50)
                        {
                            c=fgetc(myfile);
                            cout<<c;
                            m++;
                        }
                        cout<<"\nCorrect  Option  (1/2/3/4/) : ";                     /// DISPLAYING THE CORRECT OPTION
                        fseek(myfile,questionBank[i]+264,SEEK_SET);
                        c=fgetc(myfile);
                        cout<<c;
                        cout<<"\nAllotted Marks  :  ";                                /// DISPLAYING  THE ALLOTTED MARKS
                        fseek(myfile,questionBank[i]+265,SEEK_SET);
                        m=0;
                        while(m<3)
                        {
                            c=fgetc(myfile);
                            cout<<c;
                            m++;
                        } }
                        char confirm;
                        cout<<"\nConfirm (Y/N)  :  ";
                        cin>>confirm;
                        if(confirm=='Y')
                        {
                            int m=0;
                            char ch;
                            FILE* datafile;
                            datafile=fopen("read.txt","w");
                            if(datafile==NULL)
                                cout<<"error connecting the file";
                            fseek(myfile,0,SEEK_END);
                            int w=ftell(myfile);                                       /// READING TOTAL NUMBER OF CHARACTERS IN FILE
                            fseek(myfile,0,SEEK_SET);
                            while(m<w)                                                 /// COPYING CONTENT TO ANOTHER FILE WITHOUT DELETED FILE
                            {
                                ch=fgetc(myfile);
                                if(m<questionBank[i]||m>=questionBank[i]+268)
                                    fputc(ch,datafile);
                                m++;
                            }
                            fclose(datafile);
                            fclose(myfile);
                         }                                                            /// REMOVING THE PREVIOUS FILE AND RENAMING THE NEW FILE
                         remove("C:\\Users\\Chetan\\Documents\\CPP PROJECT\\SQG-QTNBNK.txt");
                         rename("read.txt","C:\\Users\\Chetan\\Documents\\CPP PROJECT\\SQG-QTNBNK.txt");
                         break;
                    }
                }
}

        void printQuestionList()                          /// FUNCTION TO PRINT QUESTION LIST
        {
            FILE* datafile;
            datafile = fopen("SQG-QTNBNK.txt","r");                /// OPENING THE FILE TO READ AND SAVE QUESTIONS
            if(datafile==NULL)
            {
                printf("=========================\n\n");
                printf("Error Loading The Content\n\n");
                printf("=========================\n\n");
                return;
            }
            char auxiliary[52];
            cout<<"\n\t\t\t\tQuestion List\n";
            while(!feof(datafile))
                {
                    fseek(datafile,-1,SEEK_CUR);
                    cout<<"\n\n=================================================================================================\n\n";
                    fgets(auxiliary,10,datafile);                       /// CATEGORY
                    cout<<"\nCategory  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,6,datafile);                        /// QUESTION ID
                    cout<<"\nQuestion Id  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,51,datafile);                       /// QUESTION TEXT
                    cout<<"\nQuestion Text  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,51,datafile);                       /// OPTION 1
                    cout<<"\nIst Option  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,51,datafile);                       /// OPTION 2
                    cout<<"\n2nd Option  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,51,datafile);                        /// OPTION 3
                    cout<<"\n3rd Option  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,51,datafile);                        /// OPTION 4
                    cout<<"\n4th Option  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,2,datafile);                         /// CORRECT ANSWER
                    cout<<"\nCorrect  Option  :  ";
                    cout<<auxiliary;
                    fgets(auxiliary,4,datafile);                         /// ALLOTTED MARKS
                    cout<<"\nAllotted Marks  :  ";
                    cout<<auxiliary;
                    fgetc(datafile);
                    }
                    fclose(datafile);
        }

        void manageMenu()                                  /// FUNCTION TO MANAGE THE MENU
        {
            int x;
            do
            {
            cout<<"\n\nManage Questions";
            cout<<"\n================";
            cout<<"\n1. Add New Questions";
            cout<<"\n2. Modify Existing Questions";
            cout<<"\n3. Delete Questions";
            cout<<"\n4. Print Question List";
            cout<<"\n5. Exit from this menu\n";
            cin>>x;
            switch(x)
            {
                case 1:
                    addNewQuestions();
                    break;
                case 2:
                    modifyExistingQuestions();
                    break;
                case 3:
                    deleteQuestions();
                    break;
                case 4:
                    printQuestionList();
                    break;
             } }
                while(x!=5);
        }
    };

int convertStrToInt(string p,int size)                  /// CONVERTING STRING TO INTEGER TYPE
{
    int x=p[0]-48;
    for(int i=1;i<size;i++)
    {
        x=x*10+p[i]-48;
    }
    return x;
}

int openScreen()                                   /// OPENING SCREEN -  MAIN MENU
{
    cout<<"\n=========================================================================================================\n\n";
    cout<<"Welcome to Simple Quiz Game ..\n";
    cout<<"Your Options\n";
    cout<<"============\n";
    cout<<"1. Administer Quiz\n";
    cout<<"2. Attend the Quiz\n";
    cout<<"3. Exit\n";
    int x;
    cin>>x;
    return x;
}

int attendQuiz()                                             /// ATTENDING QUIZ PORGRAMMED IN C AND LINKED IN THE HEADER
{
    char name[100];
    if(openingScreen()==2)
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
           quizEndScreen(name,&start);
           return 0;
        }
    }
}

int main()
{
X:  int y=openScreen();
    if(y==3)
        return 0;
    else if(y==1)
        {
            authentication admin;
            if(admin.administratorLogin()==0)
                goto X;
            else
            {
                manageQuestions manage;
                manage.manageMenu();
                goto X;
            }
        }
    else
        attendQuiz();
        goto X;
    return 0;
}
