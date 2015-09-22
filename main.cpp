//
//  main.cpp
//  ProjectZero_Final
//
//  Created by Sierra on 9/14/15.
//  Copyright (c) 2015 Sierra Adibi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class machine{
public:
    double average; //machine defined average
    double range; //machine defined range
    double total;
    int count;
    double calcAverage;
    double Q; // put this in q table
    vector<double> winnings;
    
    void initialize();
    void setstats();
    void calcs();
    void printvalues(double Qval);
};

void machine::initialize(){
    total = 0;
    count = 0;
    Q = 20;
}

void machine::setstats(){
    average = rand()%10;
    range = rand()%10;
}

void machine::printvalues(double Qval){
    cout << "\t\t\t" << total << "\t\t\t" << calcAverage;
    cout << "\t\t\t\t" << Qval << " \t\t\t\t" << count << endl << endl;
}

void machine::calcs(){
    total = 0;
    for (int i=0; i<winnings.size(); i++) {
        total = total + winnings.at(i);
    }
    calcAverage = total/winnings.size();
}

class casino{
public:
    int numofmachines;
    vector<machine>slots;
    
    void initialize();
};

void casino::initialize(){
    numofmachines = 3;
    for( int i=0;i<numofmachines;i++){
        machine m;
        m.initialize();
        m.setstats();
        slots.push_back(m);
    }
}

double pull(double median, double range){
    double r1 = ((double)rand()/RAND_MAX)*range;
    double r2 = ((double)rand()/RAND_MAX)*range;
    
    return median+r1-r2;
}

void printheader(int num, int casinocount, vector<casino> town, vector< vector<double> > Q){
    cout << "\n The results of rounds 1 through " << num << " are below: \n";
    cout << "Machine Number | Total Winnings | Average Pull Value | Q Value | Number of Pulls  \n";
    cout << "----------------------------------------------------------------------------------\n";
    
    for (int i=0; i<casinocount; i++){
        
        cout << "Casino Number " << i << ":" << endl;
        
        for (int j=0; j<town.at(i).slots.size();j++){
            
            town.at(i).slots.at(j).calcs();
            
            cout << "\t\t" << j;
            
            double Qval = Q.at(i).at(j);
            
            town.at(i).slots.at(j).printvalues(Qval);
        }
};
};


void casinoinitial(int casinocount, vector< vector<double> >& Q, vector<casino>& town){
    double Qvalue = 20;
    for (int i=0;i<casinocount;i++){
        casino c;
        c.initialize();
        town.push_back(c);
        vector <double> Qrow;
        for (int j=0;j<town.at(i).slots.size();j++){
            Qrow.push_back(Qvalue);
        }
        Q.push_back(Qrow);
    }
}

void play(int R, int casinocount, vector< vector<double> >& Q, vector<casino>& town){
    cout << "Welcome to the Multi-Armed Bandit Game!  Today we are playing with " << casinocount << " casinos." << endl;
    
    for(int r=0;r<R;r++){
        double alpha = 0.1;
        double epsilon = 0.1;
        int epsiloncount = 0;
        double test = (double)rand()/RAND_MAX;
        int state = abs(rand()%casinocount);
        double a, b, win;
        int aloc, bloc, nongreedy;
        
        if(test>epsilon){
            // make all this stuff a function called greedy,
            a = Q.at(state).at(0);
            aloc = 0;
            
            for(int i=0;i<Q.at(state).size()-1;i++){
                b = Q.at(state).at(i+1);
                bloc = i+1;
                
                if(a>=b){
                    continue;
                }else{
                    a = b;
                    aloc = bloc;
                }
            }
        }else{
            // make all this stuff a function called randomaction
            nongreedy = rand()%town.at(state).slots.size();
            aloc = abs(nongreedy);
        }
        // make this a function
        win = pull(town.at(state).slots.at(aloc).average, town.at(state).slots.at(aloc).range);
        town.at(state).slots.at(aloc).winnings.push_back(win);
        town.at(state).slots.at(aloc).count++;
        Q.at(state).at(aloc) = (1-alpha)*Q.at(state).at(aloc) + alpha*win;
        epsiloncount++;
    }
    
}




int main() {
    srand(time(NULL));
    
    int numofcasinos = 3;
    int rounds = 500;
    vector< vector<double> > Qtable;
    //const vector< vector<double> >* pQtable = &Qtable;
    vector<casino> southlake;
    //const vector<casino>* psouthlake = &southlake;
    
    casinoinitial(numofcasinos, Qtable, southlake);
    play(rounds, numofcasinos, Qtable, southlake);
    printheader(rounds, numofcasinos, southlake, Qtable);
    
    
    // function to initialize casinos xx
    // function to initialize Qtable xx
    // function to test epsilon values xx
    // function to test Q values xx
    // function to insert values xx
    // improve print function xx
    // function for counting pulls
    // function for printing pull counts
    
    return 0;
}
