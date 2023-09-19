#include <iostream>
#include <string>
#include <vector>
using namespace std;

//a pokemon object represents a singular unique pokemon to be inserted into either a heap or a tree
struct Pokemon {
private:
    //pokemon of the same name will have the same pokedex number, so this value is not unique
    int pokedexNum;

    //the name and type of pokemon are stored as string values
    string name;
    string type1;
    string type2;

    //the following integers represent the stats of a particular pokemon
    //two pokemon of the same name will still have randomly generated stats
    int hp;
    int att;
    int def;
    int spcAtt;
    int spcDef;
    int speed;

    //searchedVal is used as an index when inserting into or searching within a tree or heap
    //it represents that pokemons index
    //for instance if you are sorting pokemon by health then searchedVal is equal to pokemon health
    int searchedVal;

public:

    //getters for each field
    int getSearchedValue()
    {
        return searchedVal;
    }
    int getPokedexNum() {
        return pokedexNum;
    }
    int getAtt() {
        return att;
    }
    int getDef() {
        return def;
    }
    int getSpcAtt() {
        return spcAtt;
    }
    int getSpcDef() {
        return spcDef;
    }
    int getSpeed() {
        return speed;
    }
    int getHealth() {
        return hp;
    }
    string getName() {
        return name;
    }
    string getType1() {
        return type1;
    }
    string getType2() {
        return type2;
    }

    //similar to a getter, this method essentially takes in a string input in order to 
    //decide what kind of value searchedVal holds
    void updateSearchedVal(string type)
    {
        if (type == "health")
            searchedVal = hp;
        if (type == "pokedexNum")
            searchedVal = pokedexNum;
        if (type == "attack")
            searchedVal = att;
        if (type == "defense")
            searchedVal = def;
        if (type == "specialAttack")
            searchedVal = spcAtt;
        if (type == "specialDefense")
            searchedVal = spcDef;
        if (type == "speed")
            searchedVal = speed;
    }

    //setters for each field
    void setPokedexNum(int in) {
        pokedexNum = in;

    }
    void setAtt(int in) {
        att = in;
    }
    void setDef(int in) {
        def = in;
    }
    void setSpcAtt(int in) {
        spcAtt = in;
    }
    void setSpcDef(int in) {
        spcDef = in;
    }
    void setSpeed(int in) {
        speed = in;
    }
    void setHealth(int in) {
        hp = in;
    }
    void setName(string in) {
        name = in;
    }
    void setType1(string in) {
        type1 = in;
    }
    void setType2(string in) {
        type2 = in;
    }
};
