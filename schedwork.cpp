

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleSolver(std::map<Worker_T, int>& workload, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, size_t worker, size_t day);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    vector<Worker_T> g(dailyNeed, INVALID_ID); //create starter sched
    for(unsigned int i = 0; i<avail.size();i++){
      sched.push_back(g);
    }
    map<Worker_T, int> workload; //create map for workers and their maximum shifts
    for(unsigned int i = 0; i < avail[0].size(); i++){
      workload.insert(make_pair(i, maxShifts));
    }

    bool result = scheduleSolver(workload, avail, dailyNeed, sched, 0, 0);
    return result;
}

bool scheduleSolver(std::map<Worker_T, int>& workload, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, size_t worker, size_t day)
{
    if(day == sched.size()) return true; //you have reached the end of the matrix
    
    else
    { 
        for(unsigned int i = 0; i < avail[day].size(); ++i)
        {
            //if the worker is already working that day then continue
            if(find(sched[day].begin(), sched[day].end(), i) != sched[day].end())
            {
                continue;
            }
            if(avail[day][i] == true && workload[i] > 0)
            {
                bool done = false;
                workload[i] -= 1;
                sched[day][worker] = i;
                //if there are not enough workers for that shfit recurse to add another
                if(worker != sched[day].size() -1)
                {
                    done = scheduleSolver(workload, avail, dailyNeed, sched, worker+1, day);
                }
                //recurse to the next day and start with worker 0 again
                else
                {
                    done = scheduleSolver(workload, avail, dailyNeed, sched, 0, day+1);
                }
                if(done == true) return done; //if true then return solution
                workload[i] +=1; //add back workers' availability
                sched[day][worker] = INVALID_ID; //set that job shift to have no one
            }
        }
    }
    return false; //reached end so no viable solution
}
