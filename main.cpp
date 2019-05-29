#include <iostream>
#include <fstream>
#include <list>
#include <string.h>

using namespace std;

class LexicalAnalysis{

private:
    ifstream inputStream, palabrasReservadas;
    ofstream outputStream;
    char* output_file;
    list<string> listaPalabras;
    void(cAnalisisLexico)
public:
    LexicalAnalysis(){}

    LexicalAnalysis(char* s){}

    LexicalAnalysis(char* input_file, char* result_file){
        inputStream.open(input_file);
        try{
            if(inputStream.fail())
                throw 1;
            cout<<"Open file successful"<<endl;
            outputStream.open(result_file);
            string cad;
            while(!palabrasReservadas.eof()){
                palabrasReservadas >> cad;
                listaPalabras.push_back(cad);
            }
            /*for(list<string>::iterator it = listaPalabras.begin(); it!=listaPalabras.end(); it++){
                cout << *it <<endl;
            }*/

        }catch (int i){
           cout << ((i==1)?"File cant be opened":"Unknow error");
        }
    }

    bool esReservada(const char* id){
        bool encontrada = false;
        for(list<string>::iterator it = listaPalabras.begin(); it!=listaPalabras.end(); it++){
            if(strcmp(id, (*it).c_str())){
                encontrada = true;
                break;
            }
        }
        return encontrada;
    }

    void createTokens(){
        string id;
        char c;
        while(!inputStream.eof()){
            c = inputStream.get();
            if(c=='(')
                outputStream<<"TokPI"<<endl;
            else if(c==';')
                outputStream<<"TokPyK"<<endl;
            else if(c=='>')
                outputStream<<"TokMayor"<<endl;
            else if(c=='<')
                outputStream<<"TokMenor"<<endl;
            else if(c=='/'){
                c = inputStream.get();
                if(c=='/')
                    while(inputStream.get()!='\n')
                        c = inputStream.get();
                outputStream << "COMMENT" <<endl;
            }
            else if(isalpha(c) || c=='_'){
                c = inputStream.get();
                while(isalnum(c) || c=='_'){
                    id += c;
                    c=inputStream.get();
                }
                if(!esReservada(id.c_str()))
                    outputStream<<"(TokID,"<<id<<")";
                else
                    outputStream<<"(TokPR,"<<id<<")";
                inputStream.unget();
            }
            else if(isdigit(c)){ // Constante
                outputStream << "(TokCTE, "<<id<<")";
            }
            else if(c=='+' || c=='-'){ // Función exponencial
    
            }
            else
                outputStream<<c;
        }
    }
};

int main(int nArgs, char** args)
{
    char* outputFile = "TokenizedCode.txt";
    if(nArgs == 3)
        outputFile = args[2];
    LexicalAnalysis LEXICAL(args[1], outputFile);
    LEXICAL.createTokens();
    return 0;
}
