#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Compiler {
private:
    char* filename_in;
    char* filename_out;
    ifstream inputFile;
    ofstream outputFile;
    string fileContent;
public:
    /* +-----------------------------------------------------------------
       |    VALIDAR LOS PARÁMETROS
       +----------------------------------------------------------------- */
    bool checkParameters(char** args){
        if(args[1] == NULL){
            cout << "No se ha especificado archivo de entrada.\n" << endl;
            return false;
        } else {
            char default_OutputFilename[] = "a.out";
            this->filename_in = args[1];
            this->filename_out = (args[2]!=NULL)?args[2]:default_OutputFilename;
            return true;
        }
    }

    /* +-----------------------------------------------------------------
       |    CARGAR EL CONTENIDO DEL ARCHIVO
       +----------------------------------------------------------------- */
    void loadFile(){
        inputFile.open(filename_in);
            fileContent.assign((istreambuf_iterator<char>(inputFile)),
                        (istreambuf_iterator<char>()) );
        inputFile.close();
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
       |    CONSTRUCTOR QUE RECIBE ARGUMENTOS
       +----------------------------------------------------------------- */
    string printFileContent(){
        return this->fileContent;
    }
};

int main(int nargs, char** args)
{
    Compiler COMPILER(args);
    cout << COMPILER.printFileContent() << endl;
    return 0;
}
