#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <memory>



/*C Function calls must be declared as extern and should  have prototype forward declararion 
 implementation  is done not within the class implementation but after main method 
 This is the linux work  around  the header #include <filesystem> */ 

extern "C" {
    void readfilesNames();
} ;

using namespace std ;

class ReadData{

public :
    /* class vatriable  that holds file name */
    
     /* the public  constructor */ 
    ReadData() ;
    /*Detsructor */
    ~ReadData() ; 


    /*class methods */
    uint countFileLines(string f ) ; // counts the number of lines in a given file
    
    /* setter and getter methods */
    void setFileName() ; //sets the private instance variable filename from stdin 
    string getFileName() ; // gets instance private  variable  filename 


   
    
 private :   
    
    string _filename ;
    uint _numfilelines ; 

} ;  // end Cpp template definitions 


/* class  implimentations   for methods start here  */

ReadData::ReadData(){
 cout << "Constructor called " << endl <<  "List of file names " << endl ;
 readfilesNames() ;
} ;


// destructor 

ReadData::~ReadData(){
 cout <<  "Destructor called " << endl ; 

};

/* gets the file name that we want to process */

void ReadData::setFileName()
{
  
   cout<<"Please enter name of  file to process : "  ; 

   cin >> _filename ; // read from std in until eol 
   cout << endl << "filename entered was : " << _filename  << endl;
}

string ReadData::getFileName()
{
   return this->_filename;
}

/* counts the number of lines in file to be processed  */
uint ReadData::countFileLines(string f)
{
     string line;  
     uint count = 0 ; // make sure this is set to zero  using  the this pointer to instannce variable 

     
         ifstream file(f); // create input file stream object 

         while (getline(file, line)){
          count ++;
        
         }

           cout << "Numbers of lines in the file : " <<  count << endl << endl ;


       

   return count ;
};

int main(int argc, char *argv[]){

 cout<< "Program to validate data" << endl ;
 // create instance of class 
 unique_ptr<ReadData> ptr(new ReadData()) ;
 // call method for reading file 
 ptr->setFileName() ;

 // count number of lines in that file 

 ptr->countFileLines(ptr->getFileName()) ; 


 return 0 ;
}

/* definition of  external c functions for  reading  current
 directory and filnames within that directory  work around header <filesystem> on linux */


void readfilesNames(){

char cwd[PATH_MAX]; // C MACRO define 4092  as size 

DIR *d;
    struct dirent *dir;
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working dir: %s\n\n", cwd);
   } else {
       perror("getcwd() error");
   }


    d = opendir(cwd);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n\n", dir->d_name);
        }
        closedir(d);
    }

};