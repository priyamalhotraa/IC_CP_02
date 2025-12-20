#include<iostream>
#include<ctime>
#include<vector>

using namespace std;

struct account{
    int accountnumber;
    int pin;
    float balance;
    float dailywithdrawn;
    vector<string> transactions;
};
int main(){
    account acc1={1001,1234,5000,0};
    account acc2={1002,4321,7000,0};

    account accounts[2]={acc1,acc2};

    int accno,pin;
    account* currentuser=nullptr;

    cout<<"Enter Account Number: ";
    cin>>accno;

    cout<<"Enter PIN: ";
    cin>>pin;

    for(int i=0;i<2;i++){
        if(accounts[i].accountnumber==accno && accounts[i].pin==pin){
            currentuser=&accounts[i];
            break;
        }
    }
    if(currentuser==nullptr){
        cout<<"INVALID LOGIN CREDENTIALS!\n";
        return 0;
    }
    cout<<"Login Successful!\n";

    int choice;

    do{
        cout<<"ATM MENU\n";
        cout<<"1.Check Balance\n";
        cout<<"2.Deposit\n";
        cout<<"3.Withdraw\n";
        cout<<"4.Mini Statement\n";
        cout<<"5.Transfer Money\n";
        cout<<"6.Change PIN\n";
        cout<<"7.Exit\n";

        cin>>choice;

        if(choice==1){
            cout<<"Your Current Balance is "<<currentuser->balance<<" rs"<<endl;
        }
        else if(choice==2){
            float amount;
            cout<<"Enter Deposit Amount: ";
            cin>>amount;

            currentuser->balance=currentuser->balance+amount;
            currentuser->transactions.push_back("You Deposited "+ to_string(amount)+" rs\n");
            cout<<"Succesfully Deposited!\n";
        }
        else if(choice==3){
            double amount;
            double todaysLimit=2000;

            cout<<"Enter Withdrawal Amount: ";
            cin>>amount;

            if(currentuser->dailywithdrawn+amount>todaysLimit){
                cout<<"Withdrawal limit Exceeded!\n";
            }
            else if(amount>currentuser->balance){
                cout<<"Not Enough Balance!\n";
            }
            else{
                currentuser->balance=currentuser->balance-amount;
                currentuser->dailywithdrawn=currentuser->dailywithdrawn+amount;
                currentuser->transactions.push_back("You Withdrew "+ to_string(amount)+" rs\n");
                cout<<"Succesfully Withdrawn! \n";
            }
        }
        else if(choice==4){
            cout<<"Mini Statement\n";
            int start=max(0,(int)currentuser->transactions.size()-5);

            for(int i=start;i<currentuser->transactions.size();i++){
                cout<<currentuser->transactions[i]<<endl;
            }
        }
        else if(choice==5){
            int otheracc;
            double amount;

            cout<<"Enter Receiver Account Number: \n";
            cin>>otheracc;

            cout<<"Enter Amount: \n";
            cin>>amount;

            account* receiver=nullptr;
            for(int i=0;i<2;i++){
                if(accounts[i].accountnumber==otheracc){
                    receiver=&accounts[i];
                    break;
                }
            }
            if(receiver==nullptr){
                cout<<"Invalid Account Number \n";
            }
            else if(amount>currentuser->balance){
                cout<<"Not Enough Balance!\n";
            }
            else{
                currentuser->balance=currentuser->balance-amount;
                receiver->balance=receiver->balance+amount;
                currentuser->transactions.push_back("You Transferred "+ to_string(amount)+" rs\n to "+to_string(otheracc));
                receiver->transactions.push_back("You received "+ to_string(amount)+" rs\n from "+to_string(currentuser->accountnumber));
                cout<<"Succesfully Transferred! \n";
            }
        }
        else if(choice==6){
            int oldpin;
            int newpin;

            cout<<"Enter Old Pin: \n";
            cin>>oldpin;

            if(oldpin==currentuser->pin){
                cout<<"Enter New Pin: ";
                cin>>newpin;

                currentuser->pin=newpin;
                cout<<"Successfully Changed Pin!\n";
            }
            else{
                    cout<<"You Entered Wrong Pin!\n";
            }
        }
    }
    while(choice!=7);{
        cout<<"Thank you for using the ATM!";
        return 0;
    }
}
