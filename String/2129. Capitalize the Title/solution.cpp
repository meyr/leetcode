class Solution {
public:
    string capitalizeTitle(string title) {
        vector<int> space{{-1}};
        for(int i = 0; i < title.size(); ++i) {
            if(title[i] == ' ') space.push_back(i);
            else title[i] = tolower(title[i]);
        }
        space.push_back(title.size());
        for(int i = 1; i < space.size(); ++i) {
            int len = space[i] - space[i - 1] - 1;
            if(len > 2) 
                title[space[i - 1] + 1] = toupper(title[space[i - 1] + 1]);
        }
        return title;
    }
	// time  : O(N)
	// space : O(M) : M the number of space 
};
