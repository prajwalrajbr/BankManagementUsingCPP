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

        void manager(fstream &file);
};

//The fastest way to check if the file exists.
inline bool bank::ifFileExist(const string& name){
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

//A simple multiplicative hash, even though the collision rate is high, it is enough for our simple program.
string bank::hash(string key){
	unsigned int x = 5674356;
	unsigned int hashVariable;
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

void bank::manager(fstream &file){
    class managers{
        private:
            int i;
            char mChoice, buf[1000], ch, pwd,pwd1[14], pwd2[14];
            string name,ID,email,pno,location,branchCode,ps;
            bank b;
            
        public:
            managers(){
                if(mData){
                    cout<<"WELCOME MANAGER"<<endl;
                    cout<<"1: VIEW PROFILE"<<endl;
                    cout<<"2: UPDATE PROFILE"<<endl;
                    cout<<"3: VIEW ALL EMPLOYEES"<<endl;
                    cout<<"4: ADD EMPLOYEE"<<endl;
                    cout<<"5: UPDATE EMPLOYEE DATA"<<endl;
                    cout<<"6: REMOVE EMPLOYEE"<<endl;
                    cout<<"7: LOG-OUT"<<endl;
                    cin>>mChoice;

                    switch(mChoice){

                    }
                }else{
                    mData = true;
                    managerDataInput();
                }
            }
            void managerDataInput(){
                strcpy(buf,"");
                cout<<"ENTER YOUR FULL NAME:"<<endl;
                getline(cin,name);
                strcat(buf,name.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE 8-DIGIT MANAGER ID:"<<endl;
                cin>>ID;
                cout<<b.is_digits(ID);
                strcat(buf,ID.c_str());
                strcat(buf,"|");

                cout<<"ENTER YOUR EMAIL-ID:"<<endl;
                cin>>email;
                strcat(buf,email.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE PASSWORD HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd1:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                    pwd = getch();
                    cout<<"*";
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                        goto startpwd1;
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd1;
                        }
                    }
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
                    cout<<"*";
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                        goto startpwd2;
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd2;
                        }
                    }
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

                cout<<"ENTER THE 10-DIGIT PHONE NUMBER:"<<endl;
                cin>>pno;
                strcat(buf,pno.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE LOCATION:"<<endl;
                cin>>location;
                strcat(buf,location.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE 6-DIGIT BRANCH CODE:"<<endl;
                cin>>branchCode;
                strcat(buf,branchCode.c_str());
                strcat(buf,"\n");

                cout<<buf;
                
            }
            void managerDataUpdate(fstream &file){
                return;
            }
            void managerDataDisplay(fstream &file){
                return;
            }
            
    };
    managers m;
    return;
}


//Exexcution starts from here.
int main(){
    bank b;
    fstream managerInfo;

    if(b.ifFileExist("minfo.txt")){
        //...file exist
        cout<<"exist"<<endl;
        mData = true;
        b.manager(managerInfo);
    }
    else{
        //...file does not exist
        cout<<"not exist"<<endl;
        managerInfo.open("minfo.txt",ios::out);
        cout<<"ENTER THE DETAILS FOR THE MANAGER ACCOUNT"<<endl;
        b.manager(managerInfo);

    }
    char choice;
    for(;;){

        cout<<"SELECT THE LOG-IN TYPE:"<<endl;
        cout<<"1: BANK MANAGER LOG-IN"<<endl;
        cout<<"2: EMPLOYEE LOG-IN"<<endl;
        cout<<"3: ACCOUNT HOLDER LOG-IN"<<endl;
        cout<<"4: EXIT"<<endl;       
        cin>>choice;
        
        switch (choice){
            case '1':
                cout<<"1"<<endl;
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
