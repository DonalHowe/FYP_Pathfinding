#include <queue>
#include <iostream>

using namespace std;

int main() {
    // Create a priority queue of integers
    priority_queue<int> pq;

    // Insert some elements into the priority queue
    pq.push(10);
    pq.push(20);
    pq.push(30);
    pq.push(40);
    pq.push(50);

    // Remove the element with value 30
    int target = 30;
    priority_queue<int> new_pq;
    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();
        if (current != target) {
            new_pq.push(current);
        }
    }
  

    // Print the remaining elements in the priority queue
    while (!pq.empty()) {
        cout << pq.top() << " ";
        
        pq.pop();
    }
    cout << endl;

    return 0;
}
