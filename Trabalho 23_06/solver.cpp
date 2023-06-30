#include <iostream>
#include <fn.hpp>
#include <algorithm>

using namespace fn;
using namespace std;

class Contato
{
    string id;
    std::map<string, int> phones;
    int qntLigacoes;

public:
    Contato(string id)
    {
        this->id = id;
        this->qntLigacoes = 0;
    }

    string getName()
    {
        return id;
    }

    int getQntLig()
    {
        return this->qntLigacoes;
    }

    void setQntLig(int n)
    {
        this->qntLigacoes += n;
    }

    void addTelefone(string name, int number)
    {
        this->phones[name] = number;
    }

    void rmTelefone(string name)
    {
        phones.erase(name);
    }

    string toStr()
    {
        stringstream ss;

        ss << getName() << "[";

        for (auto &it : phones)
        {
            ss << it.first << ":" << it.second << (it != *phones.rbegin() ? ", " : "");
        }

        ss << "]";
    }
};

class SpeedList
{
    vector<Contato> contatos;

public:
    void addContato(Contato &c)
    {
        if (c.getQntLig() == 0)
        {
            return;
        }

        contatos.push_back(c);

        sort(contatos.begin(), contatos.end(), [](auto a, auto b) {
            if(a.getQntLig() == b.getQntLig()) {
                return a.getName() < b.getName();
            }else{
                return a.getQntLig() > b.getQntLig();
            }
            ; });
    }

    void rmContato(Contato &c)
    {
        contatos.erase(find(contatos.begin(), contatos.end(), c));
    }

    string toStr(){
        stringstream ss;

        for(int i = 0; i < (int) contatos.size(); i++){
            ss << "{" << to_string(contatos[i].getQntLig()) << "call}"<< contatos[i].toStr() << "\n";
        }

        return ss.str();
    }
};

class Historico
{
};

class Agenda
{
    vector<Contato> contatos;
    SpeedList speedList;
    Historico historico;

public:

    void addContato(Contato &c){
        contatos.push_back(c);
        speedList.addContato(c);
    }

    string toStr(){
        stringstream ss;

        for(int i = 0; i < (int) contatos.size(); i++){
            ss << contatos[i].toStr() << "\n";
        }

        return ss.str();
    }
};

int main()
{
    Agenda a;
    while (true)
    {
        std::string line = input();
        auto args = split(line, ' ');
        write('$' + line);

        if (args[0] == "add")
        {
            Contato c(args[1]);

            for(int i = 2; i < args.size(); i++){
                auto p = split(args[i], ':');
                c.addTelefone(p[0], stoi(p[1]));
            }
            a.addContato(c);
        }
        else if (args[0] == "agenda")
        {
            write(a.toStr());
        }
        else if (args[0] == "call")
        {
        }
        else if (args[0] == "speedlist")
        {
        }
        else if (args[0] == "history")
        {
        }
        else if (args[0] == "rmFone")
        {
        }
        else if (args[0] == "rm")
        {
        }
        else if (args[0] == "end")
        {
            break;
        }
    }
}