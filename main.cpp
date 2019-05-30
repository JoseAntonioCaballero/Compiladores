#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <string.h>

using namespace std;

/*-----------------------------------------------------------------------
 *      REPORTAR UN ERROR AL USUARIO
 *----------------------------------------------------------------------- */
void reportError(const char* description){
    cout << "   ---[ ERROR ]---"<<endl<<" "<<description<<endl;
    exit(-1);
}

class LexicalAnalysis{
private:
    ifstream inputStream;
    ofstream outputStream;
    ifstream reservedWords_file;
    list<string> reserved_words;
    char* archivoSalida;

public:
    

    /*-----------------------------------------------------------------------
     *      CONSTRUCTORES DE LA CLASE
     *----------------------------------------------------------------------- */
    LexicalAnalysis(){}

    LexicalAnalysis(char* s){}

    LexicalAnalysis(char* input_filename, char* output_filename)
    {
        try {
            inputStream.open(input_filename);
            if(inputStream.fail()) throw 1;
            reservedWords_file.open("PalabrasReservadas.txt");
            if(reservedWords_file.fail()) throw 2;

            string temp_reader;
            while(!reservedWords_file.eof()){
                reservedWords_file>>temp_reader;
                reserved_words.push_back(temp_reader);
            }

            outputStream.open(output_filename);
        } catch (int Exception) {
            switch(Exception){
                case 1: reportError("No se pudo abrir el archivo fuente"); break;
                case 2: reportError("No se pudo abrir el archivo de palabras reservadas"); break;
            }
        }
    }

    /*-----------------------------------------------------------------------
     *      VERIFICAR SI LA PALABRA DADA, ES RESERVADA
     *----------------------------------------------------------------------- */
    bool isReservedWord(char* word)
    {
        for(list<string>::iterator i=reserved_words.begin();i!=reserved_words.end();i++){
            if(strcmp(word,(*i).c_str())==0)
                return true;
        }
        return false;
    }

    /*-----------------------------------------------------------------------
     *      IDENTIFICACIÓN DE TOKENS
     *----------------------------------------------------------------------- */
    void generateTokens(){
        string id;
        char c;

        while(!inputStream.eof()){
            c=inputStream.get();
            if(c=='(')
                outputStream<<"TokPI"<<endl;
            else if(c==';')
                outputStream<<"TokPyK"<<endl;
            else if(c=='>')
                outputStream<<"TokMayor"<<endl;
            else if(c=='<')
                outputStream<<"TokMenor"<<endl;

            else if(isalpha(c)|| c== '_'){  // Nombres de variables
                id=c;
                c=inputStream.get();
                while(isalnum(c) || c== '_'){
                    id+=c;
                    c=inputStream.get();
                }
                if(!isReservedWord((char*)id.c_str()))  // Palabras reservadas
                    outputStream<<"(TokID,"<<id<<")";
                else
                     outputStream<<"(TokPR,"<<id<<")";
                outputStream<<"(TokenID,"<<id<<")";
                inputStream.unget();
            } else if(c=='/'){  // Comentarios de una sola linea
                c=inputStream.get();
                if(c=='/'){
                    c= inputStream.get();
                    while(c!='\n')
                        c=inputStream.get();
                    inputStream.unget();
                    outputStream<<"TokComentario Corto";
                } else if(isalpha(c)){
                    outputStream<<"TokDiv";
                    inputStream.unget();
                }else if(c=='*'){   // Comentarios multilínea
                    char d;
                    do{
                        while(inputStream.get()!='*');
                            inputStream.unget();
                        while(inputStream.get()=='*');
                            inputStream.unget();
                            if((d=inputStream.get())=='/'){
                                outputStream<<"TokComentario largo";
                                inputStream.unget();
                                break;
                            }
                    }while(d!='/');
                }
            } else {
                outputStream<<c;
            }
        }
    }
};


int main(int nArgs, char** args)
{
    // Obligatoriamente, necesitamos un archivo de entrada
    if(args[1] == NULL)
        reportError("No se ha especificado un archivo a procesar");

    // Especificamos el nombre del archivo de salida. En GCC, por defecto se genera "a.out"
    char default_name[] = {"a.txt"};
    char* output_filename = (args[2] != NULL)?args[2]:default_name;

    // Proceso de análisis léxico
    LexicalAnalysis LEXER(args[1], output_filename);
    LEXER.generateTokens();

    return 0;
}
