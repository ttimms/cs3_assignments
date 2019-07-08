// 
// process.cpp
// Tyler Timms
// 11/18/2018
//

#include <iostream>
#include <string>
#include <queue>
#include <ctime>

using std::string;
using std::cout;
using std::endl;
using std::queue;

class State;
static int processNumber = 0;

class Process{
public:
    Process();

    void admit();
    void interrupt();
    void exit();
    void schedulerDispatch();
    void IOEventWait();
    void IOEventCompletion();

    const int getId(){return id_;}

    string report();
    void changeState(State* s){state_=s;}

private:
    State* state_;
    int id_;
};

class State{
public:

    virtual void admit(Process*){}
    virtual void interrupt(Process*){}
    virtual void exit(Process*){}
    virtual void schedulerDispatch(Process*){}
    virtual void IOEventWait(Process*){}
    virtual void IOEventCompletion(Process*){}

    virtual ~State(){delete this;}

    virtual string report() = 0;
    void changeState(Process* p, State* s){
       p->changeState(s);
    }
};

class New : public State{
public:
    static State* instance(){
        static State* onlyInstance = new New;
        return onlyInstance;
    }
    void admit(Process *p) override;

    string report() override {return "new";}

};

class Ready : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }
    void schedulerDispatch(Process *p) override; 

    string report() override {return "ready";}
    
};

class Running : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Running;
        return onlyInstance;
    }
    void exit(Process *p) override;
    void interrupt(Process *p) override;
    void IOEventWait(Process *p) override;

    string report() override {return "running";}
    
};

class Waiting : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Waiting;
        return onlyInstance;
    }
    void IOEventCompletion(Process *p) override;

    string report() override {return "waiting";}
    
};

class Terminated : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Terminated;
        return onlyInstance;
    }
    ~Terminated(){delete this;}
    string report() override {return "terminated";}
    
};

// Process member functions ---------------------------------------------------
Process::Process(){
    ++processNumber;
    id_ = processNumber;
    state_ = New::instance();
}

void Process::admit(){state_->admit(this);}

void Process::interrupt(){state_->interrupt(this);}

void Process::exit(){state_->exit(this);}

void Process::schedulerDispatch(){state_->schedulerDispatch(this);}

void Process::IOEventWait(){state_->IOEventWait(this);}

void Process::IOEventCompletion(){state_->IOEventCompletion(this);}

string Process::report(){return state_->report();}


// State Transition member functions ------------------------------------------
void New::admit(Process *p){changeState(p, Ready::instance());}

void Ready::schedulerDispatch(Process *p){changeState(p, Running::instance());}

void Running::exit(Process *p){changeState(p, Terminated::instance());}

void Running::interrupt(Process *p){changeState(p, Ready::instance());}

void Running::IOEventWait(Process *p){changeState(p, Waiting::instance());}

void Waiting::IOEventCompletion(Process *p){changeState(p, Ready::instance());}

int main(){

    srand(time(0));

    queue<Process*> readyQueue;
    queue<Process*> waitingQueue;

    for(int i=0; i<5; ++i){
        Process *p = new Process;
        p->admit();
        readyQueue.push(p);
    }

    while(!readyQueue.empty() || !waitingQueue.empty()){

        if(!readyQueue.empty()){
            readyQueue.front()->schedulerDispatch();

            cout << "process " << readyQueue.front()->getId() << " is "
                << readyQueue.front()->report() << endl;

            int probability = rand() % 3;

            switch(probability){
                case 0:
                    readyQueue.front()->exit();
                    cout << "process " << readyQueue.front()->getId() << " is "
                        << readyQueue.front()->report() << endl;

                    readyQueue.pop();
                    break;

                case 1:
                    readyQueue.front()->interrupt();
                    cout << "process " << readyQueue.front()->getId() << " is "
                        << readyQueue.front()->report() << endl;
                    readyQueue.push(readyQueue.front());
                    readyQueue.pop();
                    break;

                case 2:
                    readyQueue.front()->IOEventWait();
                    cout << "process " << readyQueue.front()->getId() << " is "
                        << readyQueue.front()->report() << endl;
                    waitingQueue.push(readyQueue.front());
                    readyQueue.pop();
                    break;
            }
        }

        if(!waitingQueue.empty()){
            int probability2 = rand() % 2;

            if(probability2 == 0){
                waitingQueue.front()->IOEventCompletion();
                cout << "process " << waitingQueue.front()->getId() << " is "
                     << waitingQueue.front()->report() << endl;
                readyQueue.push(waitingQueue.front());
                waitingQueue.pop();
            }
        }
    }
}
