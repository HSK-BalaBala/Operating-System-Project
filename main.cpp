#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int waiting;
    int turnaround;
};

// 读取文件
vector<Process> readProcesses(const string &filename) {
    ifstream file(filename);
    vector<Process> processes;
    string header;
    getline(file, header); // 跳过第一行标题

    Process p;
    while (file >> p.pid >> p.arrival >> p.burst >> p.priority) {
        processes.push_back(p);
    }
    return processes;
}

// FCFS 调度
void fcfs(vector<Process> &p) {
    sort(p.begin(), p.end(), [](auto &a, auto &b) { return a.arrival < b.arrival; });

    int currentTime = 0;
    for (auto &proc : p) {
        if (currentTime < proc.arrival) currentTime = proc.arrival;
        proc.waiting = currentTime - proc.arrival;
        currentTime += proc.burst;
        proc.turnaround = proc.waiting + proc.burst;
    }

    cout << "\n--- FCFS Scheduling ---\n";
    cout << "PID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (auto &proc : p) {
        cout << proc.pid << "\t" << proc.arrival << "\t" << proc.burst
             << "\t" << proc.waiting << "\t" << proc.turnaround << endl;
    }

    double avgWT = 0, avgTAT = 0;
    for (auto &proc : p) {
        avgWT += proc.waiting;
        avgTAT += proc.turnaround;
    }
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << avgWT / p.size() << endl;
    cout << "Average Turnaround Time: " << avgTAT / p.size() << endl;
}

int main() {
    vector<Process> processes = readProcesses("processes.txt");
    if (processes.empty()) {
        cout << "No process data found!" << endl;
        return 0;
    }
    fcfs(processes);
    return 0;
}
