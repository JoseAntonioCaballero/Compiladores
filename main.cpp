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
            this->filename_in = args[1];
            this->filename_out = (args[2]!=NULL)?args[2]:default_OutputFilename;
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
            this->inputFile.open(filename_in);
            file_exists = this->inputFile.is_open();
            // Cargar el contenido del archivo en la cadena
            this->fileContent.assign((istreambuf_iterator<char>(inputFile)),
                                     (istreambuf_iterator<char>()));
            this->inputFile.close();
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
       |    REGRESAR EL CONTENIDO LEIDO DEL ARCHIVO
       +----------------------------------------------------------------- */
    string getFileContent(){
        return this->fileContent;
    }
};

int main(int nargs, char** args)
{
    Compiler COMPILER(args);
    cout << COMPILER.getFileContent() << endl;
    return 0;
}
