/*  參考: https://leetcode.com/problems/set-intersection-size-at-least-two/solutions/113089/c-concise-solution-onlogn-greedy-39-ms-b-7p5e/
 *  
 *  排序是重點 先把 最早結束的排前面, 結束時間一樣再把範圍大的排前面
 *  ex:
 *                   --[--]
 *                 ----[--]--------        case 1
 *           ----------[--]--------        case 1
 *                          ----[*-]       case 2
 *                                [-----]  case 3
 *
 *  Greedy point : 因為是根據intervals[i][1] 來排序, 所以取尾端兩個重複的機率最高
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
            if(a[1] < b[1]) return true;
            else if(a[1] == b[1]) return a[0] > b[0];
            else return false;
        });
        int ans = 0, left = -1, right = -1;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i][0] <= left) continue; // case 1
            else if (intervals[i][0] > right) {    // case 2 
                ans += 2;
                right = intervals[i][1];
                left = right - 1;
            }
            else {                                  // case 3   只有一個point重疊
                ans++;                              //          所以只取一個point        
                left = right;                       //          一個point被取走了 所以left等於下一個point
                right = intervals[i][1];            //          取最右邊
            }
        }
        return ans;
    }
};
/*  遇到interval的問題 排序是個重點, 應該要畫圖看看是要根據intervals[i][0] 或是 intervals[i][1]來排序
 *      
 */ 
