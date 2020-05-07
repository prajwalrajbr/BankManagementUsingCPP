#include<bits/stdc++.h>//It's the header file that includes every header files, i.e., links every header file to our program.
#include <sys/stat.h>//This is required to check if the file exist or not.
#include <termios.h>//This is required to change settings of the terminal.

using namespace std;

//The input password must not show on terminal, so the code implemented is
//From here...............................................................
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo){
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if(echo){
      current.c_lflag |= ECHO; /* set echo mode */
  }else{
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void){
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo){
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(){
  return getch_(0);
}

//To here.................................................................

bool mData=false;

class bank{
    private:
        char username[20], password[16];
    public:
        inline bool ifFileExist(const string& name);
        string hash(string key);
        bool is_digits(const string &str);

        void manager();
};

//The fastest way to check if the file exists.
inline bool bank::ifFileExist(const string& name){
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}
//A simple multiplicative hash, even though the collision rate is high, it is enough for our simple program.
string bank::hash(string key){
	unsigned int x = 5674356;
	unsigned int hashVariable = 0;
	for(int i = 0;i < key.length();i++){
		hashVariable = hashVariable ^ ( key[i] );
		hashVariable = hashVariable * x;
	}
    stringstream hexHash;
    hexHash << hex << hashVariable;
    key = hexHash.str();
    transform(key.begin(), key.end(), key.begin(), ::toupper);
	return key;
}

bool bank::is_digits(const string &str){
    return str.find_first_not_of("0123456789")==string::npos;
}

void bank::manager(){
    class managers{
        private:
            fstream file;
            int i, j;
            char mChoice, buf[1000], ch, pwd,pwd1[14], pwd2[14],id[100],pwde[100],mname[100];
            string name,ID,email,pno,location,branchCode,ps;
            bank b;
            
        public:
            void managersDashBoard(){
                if(mData){
                    file.open("minfo.txt",ios::in);
                    file.getline(mname,99,'|');
                    file.getline(id,99,'|');
                    for(i=0;i<2;i++){
                        file.getline(pwde,99,'|');
                    }
                    file.close();
                    j=0;
                    while(true){
                        cout<<"ENTER THE MANAGER ID : ";
                        cin>>ID;
                        cout<<"ENTER THE PASSWORD : ";
                        getch();
                        strcpy(pwd1,"");
                        i = 0;
                        while(true){
                            pwd = getch();
                            if (pwd=='\n'){
                                break;
                            }
                            cout<<"*";
                            ps=pwd;
                            strcat(pwd1,ps.c_str());
                            i++;
                        }
                        
                        ps="";
                        for(i=0;i<strlen(pwd1);i++){
                            ps = ps+pwd1[i];
                        }
                        ps=b.hash(ps);
                        if ((strcmp(ps.c_str(),pwde)==0)&&(strcmp(ID.c_str(),id)==0)){
                            cout<<"\nSUCCESSFULLY LOGGED-IN"<<endl;
                            break;
                        }else{
                            cout<<"\nTHE ENTERED USERNAME OR PASSWORD IS INCORRECT"<<endl;
                            if(j==2){
                                cout<<"TOO MANY ATTEMPTS";
                                exit(1);
                            }
                        }
                        j++;
                    }
                    cout<<"WELCOME "<<mname<<endl;
                    
                    while(true){
                        cout<<"\n1: VIEW PROFILE"<<endl;
                        cout<<"2: UPDATE PROFILE"<<endl;
                        cout<<"3: ADD EMPLOYEE"<<endl;
                        cout<<"4: UPDATE EMPLOYEE DATA"<<endl;
                        cout<<"5: VIEW ALL EMPLOYEES"<<endl;
                        cout<<"6: SEARCH EMPLOYEE"<<endl;
                        cout<<"7: REMOVE EMPLOYEE"<<endl;
                        cout<<"8: LOG-OUT"<<endl;
                        mChoice = getch();

                        switch(mChoice){
                            case '1':
                                managerDataDisplay();
                                break;
                            case '2':
                                managerDataUpdate();
                                break;
                            case '3':
                                cout<<"3";
                                break;
                            case '4':
                                cout<<"4";
                                break;
                            case '5':
                                cout<<"5";
                                break;
                            case '6':
                                cout<<"6";
                                break;
                            case '7':
                                cout<<"7";
                                break;
                            default :
                                cout<<"SUCCESSFULLY LOGGED-OUT"<<endl; 
                                return;
                        }
                    }
                }else{
                    managerDataInput();
                    mData = true;
                    managersDashBoard();
                }
            }
            void managerDataInput(){
                strcpy(buf,"");                
                cout<<"ENTER YOUR FULL NAME:"<<endl;
                getline(cin,name);
                strcat(buf,name.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE 8-DIGIT MANAGER-ID:"<<endl;
                for(;;){
                    cin>>ID;
                    if(b.is_digits(ID)){
                        if(strlen(ID.c_str())==8){
                            break;
                        }else{
                            cout<<"THE ID MUST BE 8 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE ID MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,ID.c_str());
                strcat(buf,"|");

                cout<<"ENTER YOUR EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }
                strcat(buf,email.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE PASSWORD HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd1:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd1;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd1;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd1,ps.c_str());
                    i++;
                }
                cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                startpwd2:
                strcpy(pwd2,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd2;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd2;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd2,ps.c_str());
                    i++;
                }
                if ((strcmp(pwd1,pwd2))!=0){
                    cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                    goto startpwd1;
                }
                ps="";
                for(i=0;i<strlen(pwd1);i++){
                    ps = ps+pwd1[i];
                }
                ps = b.hash(ps);
                strcat(buf,ps.c_str());
                strcat(buf,"|");

                cout<<"\nENTER THE 10-DIGIT PHONE NUMBER:"<<endl;
                for(;;){
                    cin>>pno;
                    if(b.is_digits(pno)){
                        if(strlen(pno.c_str())==10){
                            break;
                        }else{
                            cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,pno.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE LOCATION OF THE BANK:"<<endl;
                cin>>location;
                strcat(buf,location.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE 6-DIGIT BRANCH CODE:"<<endl;
                for(;;){
                    cin>>branchCode;
                    if(b.is_digits(branchCode)){
                        if(strlen(branchCode.c_str())==6){
                            break;
                        }else{
                            cout<<"THE BRANCH CODE MUST BE 6 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE BRANCH CODE MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,branchCode.c_str());
                strcat(buf,"\n");
                
                file.open("minfo.txt",ios::out);
                file.write(buf,strlen(buf));
                file.close();
                cout<<"MANAGER ACCOUNT SUCCESSFULLY CREATED..."<<endl;
                
                return;
            }
            void managerDataUpdate(){
                file.open("minfo.txt",ios::in);
                
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                location="";
                for(i=0;i<strlen(mname);i++){
                    location = location+mname[i];
                }
                file.getline(mname,99,'\n');
                branchCode="";
                for(i=0;i<strlen(mname);i++){
                    branchCode = location+mname[i];
                }
                file.close();

                strcpy(buf,"");                
                cout<<"ENTER THE NEW NAME OF THE MANAGER:"<<endl;
                getch();
                getline(cin,name);
                strcat(buf,name.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE  NEW 8-DIGIT MANAGER-ID:"<<endl;
                for(;;){
                    cin>>ID;
                    if(b.is_digits(ID)){
                        if(strlen(ID.c_str())==8){
                            break;
                        }else{
                            cout<<"THE ID MUST BE 8 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE ID MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,ID.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE NEW EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }
                strcat(buf,email.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE NEW PASSWORD HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd3:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd3;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd3;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd1,ps.c_str());
                    i++;
                }
                cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                startpwd4:
                strcpy(pwd2,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{                        
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd4;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd4;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd2,ps.c_str());
                    i++;
                }
                if ((strcmp(pwd1,pwd2))!=0){
                    cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                    goto startpwd3;
                }
                ps="";
                for(i=0;i<strlen(pwd1);i++){
                    ps = ps+pwd1[i];
                }
                ps = b.hash(ps);
                strcat(buf,ps.c_str());
                strcat(buf,"|");

                cout<<"\nENTER THE NEW 10-DIGIT PHONE NUMBER:"<<endl;
                for(;;){
                    cin>>pno;
                    if(b.is_digits(pno)){
                        if(strlen(pno.c_str())==10){
                            break;
                        }else{
                            cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,pno.c_str());
                strcat(buf,"|");

                strcat(buf,location.c_str());
                strcat(buf,"|");

                strcat(buf,branchCode.c_str());
                strcat(buf,"\n");
            
                file.open("minfo.txt",ios::out);
                file.write(buf,strlen(buf));
                file.close();
                cout<<"MANAGER ACCOUNT SUCCESSFULLY UPDATED..."<<endl;
                return;
            }
            void managerDataDisplay(){        
                file.open("minfo.txt",ios::in);
                cout<<"\nMANAGER's DEAILS :"<<endl;
                file.getline(mname,99,'|');
                cout<<"FULL NAME : "<<mname<<endl;
                file.getline(mname,99,'|');
                cout<<"MANAGER-ID : "<<mname<<endl;
                file.getline(mname,99,'|');
                cout<<"EMAIL ADDRESS : "<<mname<<endl;
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                cout<<"PHONE NO. : "<<mname<<endl;
                file.getline(mname,99,'|');
                cout<<"LOCATION OF THE BANK : "<<mname<<endl;
                file.getline(mname,99,'\n');
                cout<<"BRANCH CODE : "<<mname<<endl;
                file.close();
                return;
            }
            
    };
    managers m;
    m.managersDashBoard();
    return;
}


//Exexcution starts from here.
int main(){
    bank b;
    fstream managerInfo;

    cout<<"WELCOME TO \'BANK OF MIT\'"<<endl;

    if(b.ifFileExist("minfo.txt")){
        //...file exist
        mData = true;
    }
    else{
        //...file does not exist
        managerInfo.open("minfo.txt",ios::out);
        managerInfo.close();
        cout<<"ENTER THE DETAILS FOR THE MANAGER ACCOUNT"<<endl;
        b.manager();
    }
    char choice;
    for(;;){

        cout<<"\nSELECT THE LOG-IN TYPE:"<<endl;
        cout<<"1: BANK MANAGER LOG-IN"<<endl;
        cout<<"2: EMPLOYEE LOG-IN"<<endl;
        cout<<"3: ACCOUNT HOLDER LOG-IN"<<endl;
        cout<<"4: EXIT"<<endl;       
        choice = getch();
        
        switch (choice){
            case '1':
                b.manager();
                break;
            
            case '2':
                cout<<"1"<<endl;
                break;
            
            case '3':
                cout<<"1"<<endl;
                break;
        
            default:
                exit(0);
            
        }

    }
    return 0;
}
