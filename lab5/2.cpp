#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Visitor {
    int time;
    string ticket;
};

struct Window {
    int index;
    int total_time = 0;
    vector<string> tickets;

    // оператор для приоритета в очереди (наименьшее время — выше приоритет)
    bool operator>(const Window& other) const {
        return total_time > other.total_time;
    }
};

int main() {
    int num_windows;
    cout << "Введите кол-во окон: ";
    cin >> num_windows;
    cin.ignore();

    vector<Visitor> queue;
    vector<Window> windows(num_windows);
    for (int i = 0; i < num_windows; ++i) {
        windows[i].index = i + 1;
    }

    int ticket_number = 764;
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "ENQUEUE") {
            int time;
            ss >> time;
            string ticket = "T" + to_string(ticket_number++);
            queue.push_back({ time, ticket });
            cout << ticket << endl;
        }
        else if (command == "DISTRIBUTE") {
            // приоритетная очередь по total_time (минимум — первый)
            priority_queue<Window, vector<Window>, greater<Window>> pq(windows.begin(), windows.end());

            for (auto& visitor : queue) {
                Window w = pq.top(); pq.pop();
                w.total_time += visitor.time;
                w.tickets.push_back(visitor.ticket);
                pq.push(w);
            }

            // переносим обратно в вектор для сортировки по номеру окна
            vector<Window> result;
            while (!pq.empty()) {
                result.push_back(pq.top());
                pq.pop();
            }
            sort(result.begin(), result.end(), [](const Window& a, const Window& b) {
                return a.index < b.index;
            });

            for (const auto& w : result) {
                cout << "Окно " << w.index << " (" << w.total_time << " минут): ";
                for (size_t i = 0; i < w.tickets.size(); ++i) {
                    if (i > 0) cout << ", ";
                    cout << w.tickets[i];
                }
                cout << endl;
            }
            break; 
        }
    }

    return 0;
}