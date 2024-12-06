#include <bits/stdc++.h>
#include "SkipList.cpp"
using namespace std;
class Player{
private:
    string name;
    int score;
public:
    Player(string name="", int score= 0){
        this->name = name;
        this->score = score;
    }
    string getName(){
        return name;
    }
    int getScore(){
        return score;
    }
    void setScore(int score){
        this->score = score;
    }
    bool operator<(const Player& other) const {
        if (score == other.score) {
            return name < other.name;
        }
        return score < other.score;
    }
    bool operator>(const Player& other) const {
        if (score == other.score) {
            return name > other.name;
        }
        return score > other.score;
    }
    bool operator==(const Player& other) const {
        return score == other.score && name == other.name;
    }
    bool operator!=(const Player& other) const {
        return !(*this == other);
    }
    bool operator<=(const Player& other) const {
        return *this < other || *this == other;
    }
    friend ostream& operator<<(ostream& os, const Player& player) {
        os << "(Name: " << player.name << ", Score: " << player.score <<")";
        return os;
    }
};
class GameEngine{
private:
    SkipList<Player> skipList;
public:
    GameEngine(SkipList<Player> skipList) : skipList(skipList) {}

    void addPlayer(string name, int score){
        skipList.insert(Player(name, score));
    }
    void removePlayer(Player player){
        skipList.remove(player);
    }
    void printLeaderBoard(){
        skipList.print();
    }
    bool searchPlayer(Player player){
        return skipList.search(player);
    }
    void updatePlayerScore(Player player, int newScore){
        Player newPlayer = Player(player.getName(), newScore);
        skipList.remove(player);
        skipList.insert(newPlayer);
    }
    void updatePlayerName(Player player, string newName){
        Player newPlayer = Player(newName, player.getScore());
        skipList.remove(player);
        skipList.insert(newPlayer);
    }
    void updatePlayer(Player player, string newName, int newScore){
        Player newPlayer = Player(newName, newScore);
        skipList.remove(player);
        skipList.insert(newPlayer);
    }
    void printTopPlayers(int n){
        auto curr = skipList.getRoot();
        int height = skipList.getHeight();
        int count = n;
        while (curr->next[height]){
            curr = curr->next[height];
        }
        while (curr->next[0]){
            curr = curr->next[0];
        }
        while (count && curr->prev){
            cout<<curr->data<<endl;
            curr = curr->prev;
            --count;
        }
    }
    int getPlayerScoreByName(string name){
        auto curr= skipList.getRoot();
        int h = skipList.getHeight();
        while (curr->next[0] && curr->data.getName() != name){
            curr = curr->next[0];
        }
        if (curr && curr->data.getName() == name){
            return curr->data.getScore();
        }
//        for (int i = h; i >= 0; --i) {
//            while (curr->next[i] && curr->data.getName() < name){
//                curr = curr->next[i];
//            }
//            if (curr && curr->data.getName() == name){
//                return curr->data.getScore();
//            }
//        }

        return -1;
    }
    string getPlayerNameByScore(int score){
        auto curr= skipList.getRoot();
        int h = skipList.getHeight();
        for (int i = h; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->data.getScore() <= score){
                curr = curr->next[i];
            }
            if (curr && curr->data.getScore() == score){
                return curr->data.getName();
            }
        }
        return "Not Found";
    }
};
int main(){
    GameEngine gameEngine(SkipList<Player>(3));
    gameEngine.addPlayer("A", 100);
    gameEngine.addPlayer("B", 100);
    gameEngine.addPlayer("C", 300);
    gameEngine.addPlayer("D", 400);
    gameEngine.addPlayer("E", 25);
    gameEngine.printLeaderBoard();
    cout<<"-------------------\n";
    cout<<"Top 3:\n";
    gameEngine.printTopPlayers(3);
    cout<<"-------------------\n";
    Player p("A", 100);
    gameEngine.updatePlayer(p, "A", 200);
    gameEngine.printLeaderBoard();
    cout<<"Top 4:\n";
    gameEngine.printTopPlayers(4);
    cout<<"-------------------\n";
    gameEngine.removePlayer(Player("E", 25));
    gameEngine.printLeaderBoard();
    cout<<"The player B: "<<gameEngine.getPlayerScoreByName("B")<<endl;
    cout<<"The player with score 200: "<<gameEngine.getPlayerNameByScore(200)<<endl;
    cout<<"The player with score 400: "<<gameEngine.getPlayerNameByScore(400)<<endl;
    cout<<"The player with score 10:"<<gameEngine.getPlayerNameByScore(10)<<endl;
}