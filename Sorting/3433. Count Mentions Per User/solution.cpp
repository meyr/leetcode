/*
 *  必須先處理 每個user的status 所以先對timestamp排序 再對message排序 相同時間下OFFLINE要在MESSAGE之前
 *  每處理一個event都先把online的user放回去
 *  最後 ALL 使用一個all_cnt來記錄最後再加回去即可
 *
 *  time  : O(ElogE + N + N + E) = O(ElogE + N)
 *  space : O(N + N + N + logE) = O(N + logE)
 */
class Solution {
    enum properties{
        msg,
        ts,
        ms
    };
    vector<int> status; // online by default
    vector<int> mentions;
    deque<vector<int>> offline; // record offline user
    int all_cnt{}, numberOfUsers{};
    void processMetionMessage(string& message) {
        if(message[0] == 'A') all_cnt++;
        else if(message[0] == 'H') {
            for(int i = 0; i < numberOfUsers; ++i)
                mentions[i] += status[i];
        } else {
            istringstream iss(message);
            string str;
            while(iss >> str) {
                int id = stoi(str.substr(2));
                mentions[id]++;
            }
        }
    }
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        sort(begin(events), end(events), [](vector<string>& a, vector<string>& b){  //O(ElogE), E : size of events
            int tsa = stoi(a[ts]), tsb = stoi(b[ts]);
            if(tsa < tsb) return true;
            else if(tsa == tsb) return a[msg][0] > b[msg][0];
            else return false;
        });
        status.resize(numberOfUsers, 1);                                            // O(N),  N : numberOfUsers
        mentions.resize(numberOfUsers);                                             // O(N)
        this->numberOfUsers = numberOfUsers;
        for(auto& event : events) {                                                 // O(E)
            int time = stoi(event[ts]);
            while(!offline.empty() && time >= offline.front()[0]) {
                status[offline.front()[1]] = 1;
                offline.pop_front();
            }
            if(event[msg] == "MESSAGE") {
                processMetionMessage(event[ms]);
            } else {
                int id = stoi(event[ms]);
                offline.push_back({time + 60, id});
                status[id] = 0;
            }
        }
        for(int i = 0; i < numberOfUsers; ++i)
            mentions[i] += all_cnt;
        return mentions;
    }
};
