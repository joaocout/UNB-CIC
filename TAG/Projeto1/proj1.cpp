/*
ALUNO : JOAO PEDRO ASSUNCAO COUTINHO
MATRICULA : 18/0019813
github.com/joaocout
*/

/*
O programa pula todos os comentarios (linhas iniciadas com '%')
independentemente da linha em que estao escritos.
*/

/*
O primeiro input nao comentado deve ser composto por tres inteiros
responsaveis por descrever quantas arestas e vertices o grafo possui
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> simple_union(vector<int> a, vector<int> b){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int>::iterator eit, it;
    vector<int> temp(a.size()+b.size()), result;

    eit = set_union(a.begin(), a.end(), b.begin(), b.end(), temp.begin());
    for(it = temp.begin(); it!=eit; it++)
        result.push_back(*it);

    return result;
}
vector<int> simple_intersection(vector<int> a, vector<int> b){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int>::iterator eit, it;
    vector<int> temp(a.size()), result;

    eit = set_intersection(a.begin(), a.end(), b.begin(), b.end(), temp.begin());
    for(it = temp.begin(); it!=eit; it++)
        result.push_back(*it);

    return result;
}
vector<int> simple_difference(vector<int> a, vector<int> b){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int>::iterator eit, it;
    vector<int> temp(a.size()), result;

    eit = set_difference(a.begin(), a.end(), b.begin(), b.end(), temp.begin());
    for(it = temp.begin(); it!=eit; it++)
        result.push_back(*it);

    return result;
}


void Bron_Kerbosch(vector<int> r, vector<int> p, vector<int> x, vector<vector<int>> graph){

    //se P e X estao vazios
    if(p.empty() && x.empty()){
        cout << "Maximal Clique found: ";
        for(int i = 0; i < r.size(); i++)
            cout << r[i] << " ";
        cout << endl;
    }
    //para cada vertice em P
    for(int i = 0; i < p.size(); i++){
        
        vector<int> temp; // = {v} conjunto que soh possui um vertice
        temp.push_back(p[i]);

        Bron_Kerbosch(simple_union(r, temp), simple_intersection(p, graph[p[i]]), 
        simple_intersection(x, graph[p[i]]), graph);

        p = simple_difference(p, temp);
        x = simple_union(x, temp);
    
    }

}


int main () {

    string file_name;
    cout << "Enter the  input file name: ";
    cin >> file_name;

    ifstream input_file;
    input_file.open(file_name);

    if(input_file.fail()){
        cout << "Error opening the file / file doesn't exist" << endl;
    }
    else{

        string line;
        bool first_valid_input = false;
        int height, width, edges;

        //primeiro encontramos o primeiro input, para declarar o grafo corretamente
        while(!first_valid_input && getline(input_file, line)){

            if(line[0] != '%'){             //se a linha n for um comentario

                if(first_valid_input == false){ //se o primeiro input (que nao seja um comentario) nao tenha sido lido ainda
                    first_valid_input = true;
                    stringstream stream(line);   //transformando a string 'line' em um stream
                    stream >> height >> width >> edges;
                }

            }

            line.clear();

        }

        vector<vector<int>> dolphins(height + 1);

        //depois lemos as conexoes
        while(getline(input_file, line)){   //ate o fim do arquivo
            int a, b;
            stringstream stream(line);
            stream >> a >> b;
            
            //o grafo nao eh direcionado, entao ha conexao nas duas direcoes
            dolphins[a].push_back(b);
            dolphins[b].push_back(a);

            line.clear();
        
        }

        /*------------------------------------------*/
        /*grau de todos os vertices*/
        cout << "DEGREE OF EACH VERTEX" << endl;
        for(int i = 1; i < height+1; i++){  //golfinhos enumerados de 1 a 62
            cout << "degree(" << i << ") = " << dolphins[i].size() << endl;
        }
        cout << endl;

        /*------------------------------------------*/
        /*cliques maximais*/
        cout << "ALL MAXIMAL CLIQUES" << endl;
        vector<int> r;
        vector<int> p;
        vector<int> x;
        for(int i = 1; i<=height; i++){
            p.push_back(i);    //inicializando p com todos os vertices
        }
        Bron_Kerbosch(r, p, x, dolphins);
        cout << endl;

        /*--------------------------------------------*/
        input_file.close();

    }

    return 0;
}