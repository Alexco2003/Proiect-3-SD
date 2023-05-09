#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct Processor
{
    int index;
    int endTime;

    bool operator<(const Processor& other) const;

};

bool Processor::operator<(const Processor& other) const
{
    if (endTime == other.endTime)
        return index > other.index;
    return endTime > other.endTime;
}

int main()
{
    ifstream f1("proc2.in");
    ofstream f2("proc2.out");

    int N, M;
    f1 >> N >> M; /// Read the number of processors (N) and the number of tasks (M)

    vector<int> endTime(N + 1, 0); /// Stores the end time of the task on each processor
    map<int, int> taskProcessor; /// Stores the assigned processor for each task

    priority_queue<Processor> T; /// Heap to find the processor that finishes a task as soon as possible
    priority_queue<int, vector<int>, greater<int>> P; /// Heap to find the processor with the lowest available order number

    for (int i = 1; i <= N; i++)
    {
        P.push(i); /// Initialize P with all available processors
    }

    for (int i = 0; i < M; i++)
    {
        int startTime, processingTime;
        f1 >> startTime >> processingTime; /// Read the start time and processing time of the current task

        /// Remove processors from P that finish their task before the current task starts
        while (!T.empty() && T.top().endTime <= startTime)
        {
            P.push(T.top().index);
            T.pop();
        }

        int processorIndex;

        if (!P.empty())
        {
            processorIndex = P.top(); /// Choose the processor with the lowest available order number from P
            P.pop();
        }
        else
        {
            processorIndex = T.top().index; /// Choose the processor that finishes a task as soon as possible from T
            T.pop();
        }

        int endTime = startTime + processingTime; /// Calculate the end time of the task

        taskProcessor[i] = processorIndex; /// Assign the processor index to the current task

        T.push({ processorIndex, endTime }); /// Add the processor to T with its new end time
    }

    /// Write the assigned processor for each task to the output file
    for (int i = 0; i < M; i++)
    {
        f2 << taskProcessor[i] << "\n";
    }

    f1.close();
    f2.close();
    return 0;
}
