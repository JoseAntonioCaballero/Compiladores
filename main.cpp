#include <iostream>
#include <fstream>

using namespace std;

class LexicalAnalysis{
    
private:
    ifstream inputStream;
    ofstream outputStream;
    char* output_file;

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
        }catch (int i){
           cout << ((i==1)?"File cant be opened":"Unknow error");
        }
    }

    void tokenParsing(){
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
            else if(isalpha(c) || c=='_'){
                c = inputStream.get();
                while(isalpha(c) || c=='_')
                    c=inputStream.get();
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
    LEXICAL.tokenParsing();
    return 0;
}
