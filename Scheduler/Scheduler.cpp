#include<bits/stdc++.h>
#define pb push_back
using namespace std;

class taskInfo{
    public:
        taskInfo(string name,int aT,int bT,int dL):taskName(name),arrivalTime(aT),burstTime(bT),deadline(dL){
            burstTimeConst = bT;
        }
        string taskName;
        int arrivalTime,burstTime,deadline,startTime=-1,endTime,burstTimeConst;
};

class dLCompare{
    public:
    bool operator() (const taskInfo* t1,const taskInfo* t2) const{
        return t1->deadline > t2->deadline;
    }
};

class bTCompare{
    public:
    bool operator() (const taskInfo* t1,const taskInfo* t2) const{
        return t1->burstTime > t2->burstTime;
    }
};

void FCFS(vector<taskInfo*> allTasks){
    int time = allTasks[0]->arrivalTime,waitingTime=0,responseTime=0,turnAroundTime=0;
    double s=allTasks.size();
    printf("---FCFS---\nTask StartT EndT Duration\n");
    for(auto t : allTasks){
        waitingTime += time - (t->arrivalTime);
        responseTime += waitingTime;
        turnAroundTime += waitingTime+t->burstTime;
        time+=t->burstTime;
        printf("%s %d %d %d\n",(t->taskName).c_str(),(time - t->burstTime),time,t->burstTime);
    }
    double AWT = (waitingTime/s),ATT = (turnAroundTime/s);
    printf("AWT: %.2f  ART: %.2f  ATT:  %.2f\n\n",AWT,AWT,ATT);
}

void RR(vector<taskInfo*> arrT,int quantum){
    vector<taskInfo*> allTasks;
    for(auto it : arrT){
        taskInfo *task = new taskInfo(it->taskName,it->arrivalTime,it->burstTime,it->deadline);
        allTasks.pb(task);
    }
    int time = allTasks[0]->arrivalTime,waitingTime=0,responseTime=0,turnAroundTime=0,counter=0,currQ=0;
    double s=allTasks.size();
    int i=0;
    queue<taskInfo*> waitingQ;
    printf("---RR---\nTask StartT EndT Duration\n");
    while(true){
        for(int idx=i;(idx<allTasks.size() && allTasks[idx]->arrivalTime==time);idx++){
            waitingQ.push(allTasks[idx]);
            i++;
        }

        if(waitingQ.empty() && i>=s && counter==s) break;

        auto t = waitingQ.front();


        (t->burstTime)--;

        if(currQ == quantum-1){
            waitingQ.pop();
            if(t->burstTime>0)waitingQ.push(t);
        }


        currQ = (currQ+1)%quantum;

        if(t->startTime==-1){
            t->startTime = time;
        }
        time++;
        if(t->burstTime <=0){
            t->endTime = time;
            responseTime+=(t->startTime - t->arrivalTime);
            waitingTime+=(time - t->arrivalTime - t->burstTimeConst);
            turnAroundTime+=(time-t->startTime);
            counter++;
            printf("%s %d %d\n",(t->taskName).c_str(),(t->startTime),time);
        }

    }
    double AWT = (waitingTime/s),ATT = (turnAroundTime/s),ART = (responseTime/s);
    printf("AWT: %.2f  ART: %.2f  ATT:  %.2f\n\n",AWT,ART,ATT);
    for(auto it : allTasks) delete it;
}

void SJF(vector<taskInfo*> allTasks){
    priority_queue<taskInfo*,vector<taskInfo*>> readyQ;
    int time = allTasks[0]->arrivalTime,waitingTime=0,responseTime=0,turnAroundTime=0;
    double s=allTasks.size();
    int i=0;
    printf("---SJF---\nTask StartT EndT Duration\n");
    while(true){
        for(int idx=0;idx<allTasks.size();idx++){
            if(allTasks[idx]->arrivalTime <=time && idx>=i){
                readyQ.push(allTasks[idx]);
                i++;
            }
        }
        if(readyQ.empty() && i>=s) break;
        else if(readyQ.empty() && i<s){
            time = allTasks[i]->arrivalTime;
        }

        auto t = readyQ.top();
        readyQ.pop();
        waitingTime += time - (t->arrivalTime);
        responseTime += waitingTime;
        turnAroundTime += waitingTime+t->burstTime;
        time+=t->burstTime;
        printf("%s %d %d %d\n",(t->taskName).c_str(),(time - t->burstTime),time,t->burstTime);
    }
    double AWT = (waitingTime/s),ATT = (turnAroundTime/s);
    printf("AWT: %.2f  ART: %.2f  ATT:  %.2f\n\n",AWT,AWT,ATT);
}

void SRTF(vector<taskInfo*> arrT){
    vector<taskInfo*> allTasks;
    for(auto it : arrT){
        taskInfo *task = new taskInfo(it->taskName,it->arrivalTime,it->burstTime,it->deadline);
        allTasks.pb(task);
    }
    priority_queue<taskInfo*,vector<taskInfo*>,bTCompare> readyQ;
    int time = allTasks[0]->arrivalTime,waitingTime=0,responseTime=0,turnAroundTime=0,counter=0;
    double s=allTasks.size();
    int i=0;
    printf("---SRTF---\nTask StartT EndT Duration\n");
    while(true){
        for(int idx=i;(idx<allTasks.size() && allTasks[idx]->arrivalTime==time);idx++){
            readyQ.push(allTasks[idx]);
            i++;
        }

        if(readyQ.empty() && i>=s && counter==s) break;

        auto t = readyQ.top();
        readyQ.pop();

        if(t->startTime==-1){
            t->startTime = time;
        }

        time++;

        (t->burstTime)--;
        if(t->burstTime>0)readyQ.push(t);
        else{
            printf("%s %d %d\n",(t->taskName).c_str(),(t->startTime),time);
            t->endTime = time;
            responseTime+=(t->startTime - t->arrivalTime);
            waitingTime+=(time - t->arrivalTime - t->burstTimeConst);
            turnAroundTime+=(time-t->startTime);
            counter++;
        }
    }
    double AWT = (waitingTime/s),ATT = (turnAroundTime/s),ART = (responseTime/s);
    printf("AWT: %.2f  ART: %.2f  ATT:  %.2f\n\n",AWT,ART,ATT);
    for(auto it : allTasks) delete it;
}

void RTEDF(vector<taskInfo*> arrT){
    vector<taskInfo*> allTasks;
    for(auto it : arrT){
        taskInfo *task = new taskInfo(it->taskName,it->arrivalTime,it->burstTime,it->deadline);
        allTasks.pb(task);
    }
    priority_queue<taskInfo*,vector<taskInfo*>,dLCompare> readyQ;
    int time = allTasks[0]->arrivalTime,waitingTime=0,responseTime=0,turnAroundTime=0,counter=0;
    double s=allTasks.size();
    int i=0;
    printf("---RTEDF---\nTask StartT EndT Duration\n");
    while(true){
        for(int idx=i;(idx<allTasks.size() && allTasks[idx]->arrivalTime==time);idx++){
            readyQ.push(allTasks[idx]);
            i++;
        }

        if(readyQ.empty() && i>=s && counter==s) break;

        auto t = readyQ.top();
        readyQ.pop();

        if(t->startTime==-1){
            t->startTime = time;
        }
        time++;
        (t->burstTime)--;
        if(t->burstTime>0)readyQ.push(t);
        else{
            printf("%s %d %d\n",(t->taskName).c_str(),(t->startTime),time);
            t->endTime = time;
            responseTime+=(t->startTime - t->arrivalTime);
            waitingTime+=(time - t->arrivalTime - t->burstTimeConst);
            turnAroundTime+=(time-t->startTime);
            counter++;
        }
    }
    double AWT = (waitingTime/s),ATT = (turnAroundTime/s),ART = (responseTime/s);
    printf("AWT: %.2f  ART: %.2f  ATT:  %.2f\n\n",AWT,ART,ATT);
    for(auto it : allTasks) delete it;
}


int main(int argc, char** argv){
    string fileName = argv[1];
    ifstream inFile(fileName);
    string line,taskName;
    int arrivalTime,burstTime,deadline;
    getline(inFile,line);
    vector<taskInfo*> allTasks;
    while(getline(inFile,line)){
        stringstream lineStream(line);
        lineStream>>taskName>>arrivalTime>>burstTime>>deadline;
        taskInfo *task = new taskInfo(taskName,arrivalTime,burstTime,deadline);
        allTasks.pb(task);
    }
    freopen("out.txt","w",stdout);
    FCFS(allTasks);
    RR(allTasks,atoi(argv[2]));
    SJF(allTasks);
    SRTF(allTasks);
    RTEDF(allTasks);
    for(auto it : allTasks) delete it;
}
