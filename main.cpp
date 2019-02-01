#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>

using namespace std;

class Compiler {
private:
    char* filename_in;
    char* filename_out;
    ifstream inputFile, reservedWordsFile;
    ofstream outputFile;
    string fileContent;
    list<string> reservedWords;
public:
    /* +-----------------------------------------------------------------
       |    VALIDAR LOS PARAMETROS
       +----------------------------------------------------------------- */
    bool checkParameters(char** args){
        // Obligatoriamente se debe especificar un archivo de entrada
        if(args[1] == NULL){
            cout << "No se ha especificado archivo de entrada.\n" << endl;
            return false;
        } else {
            // Si no se especifica un archivo de salida, asignar valor por default
            char default_OutputFilename[] = "a.out";
            filename_in = args[1];
            filename_out = (args[2]!=NULL)?args[2]:default_OutputFilename;
            return true;
        }
    }

    /* +-----------------------------------------------------------------
       |    CARGAR EL CONTENIDO DEL ARCHIVO
       +----------------------------------------------------------------- */
    bool loadFile(){
        // Validar que el archivo existe
        bool file_exists = false;
        try{
            inputFile.open(filename_in);
            file_exists = inputFile.is_open();
            // Cargar el contenido del archivo en la cadena
            fileContent.assign((istreambuf_iterator<char>(inputFile)),
                                     (istreambuf_iterator<char>()));
            inputFile.close();
        }catch(int Exception){
            file_exists = false;
            cout << "El archivo especificado no existe" << endl;
        }
        return file_exists;
    }

    /* +-----------------------------------------------------------------
       |    CONSTRUCTOR POR DEFAULT
       +----------------------------------------------------------------- */
    Compiler(){}

    /* +-----------------------------------------------------------------
       |    CONSTRUCTOR QUE RECIBE ARGUMENTOS
       +----------------------------------------------------------------- */
    Compiler(char** args){
        if(checkParameters(args))
            loadFile();
    }

    /* +-----------------------------------------------------------------
       |    CARGAR LA LISTA DE PALABRAS RESERVADAS
       +----------------------------------------------------------------- */
    void loadReservedWords(){
        try{
            reservedWordsFile.open("ReservedWords.txt");
            if(reservedWordsFile.fail())
                throw -1;
            string readedWord;
            while(!reservedWordsFile.eof()){
                reservedWordsFile >> readedWord;
                reservedWords.push_back(readedWord);
            }
        }catch(int Exception){
            cout<< "No se pudo abrir el archivo de palabras reservadas" <<endl;
        }
    }

    /* +-----------------------------------------------------------------
       |    VERIFICAR SI UNA PALABRA ES RESERVADA
       +----------------------------------------------------------------- */
    bool isReservedWord(string word){
        list<string>::iterator itemFinder = find(reservedWords.begin(), reservedWords.end(), word);
        return (itemFinder!=reservedWords.end());
    }

    /* +-----------------------------------------------------------------
       |    REGRESAR EL CONTENIDO LEIDO DEL ARCHIVO
       +----------------------------------------------------------------- */
    string getFileContent(){
        return fileContent;
    }
};

int main(int nargs, char** args)
{
    Compiler COMPILER(args);
    COMPILER.loadReservedWords();
    cout << COMPILER.getFileContent() << endl;

    string someTestWord = "include";
    cout << COMPILER.isReservedWord(someTestWord);
    return 0;
}
