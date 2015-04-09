#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

class dataCLASS {
      // ---------- VARIABLES ----------  
      public:
      int no_columns, no_rows;
      vector< vector <int> > data;
      vector< vector <int> > temp;
      char fileName[30];
      // ----------- METHODS -----------
      
      // --------- importData ----------
      int importData(){
         printf("Give the name of input file: ");
         std::cin.getline(fileName, 30);
         ifstream inputFile(fileName); 
         if (inputFile.is_open()) {
            int num;
            vector <int> numbers_in_line;
            while (inputFile >> num) {
               numbers_in_line.push_back(num);
               if (numbers_in_line.size() == no_columns) {
                  data.push_back(numbers_in_line);
                  numbers_in_line.clear();
               }
            }
         }
         else {
            cerr << "There was an error opening the input file!\n";
            exit(1);
            }
         inputFile.close();
         return 0;
      }
      
      // --------- exportData ----------
      int exportData(){
         int value;
         printf("Give the name of output file: ");
         std::cin.getline(fileName, 30);         
         fstream outputFile(fileName); 
         if (outputFile.is_open()) {
            for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    value = data[row][col];
                    outputFile << value << "\t";
                }
            outputFile << endl;
            }
         }
         else {
            cerr << "There was an error opening the input file!\n";
            exit(1);
            }
         outputFile.close();          
         return 0;
      }
      
      // ---------- showData -----------
      int showData(){
         for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    cout << data[row][col] << "\t";
                }
            cout << endl;
            }
         return 0;        
      }
                 
      // ------- addValueToData --------
      int addValueToData(int addValue){
         for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    data[row][col] = data[row][col] + addValue;
                    }
                }
         return 0;
      }
      
      // ------- increaseNegativeToZero --------
      int increaseNegativeToZero(){
         for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    if (data[row][col] < 0 ) { data[row][col] = 0; }
                    }
                }
         return 0;
         }
       
       // ---- fillBelowLimitWithZero
       int fillBelowLimitWithZero(int limit){  
          for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    if (data[row][col] < limit ) { data[row][col] = 0; }
                    }
                }
          return 0;
          }
       
       // ----- smoothData --------
       int smoothData(){
           int TempValue = 0;
           int TempR, TempC;
           temp.assign(data.begin(),data.end());
           for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    TempR = row;
                    TempC = col;
                    TempValue = 0;
                    if (row == 0 || row == no_rows-1 || col == 0 || col == no_columns-1){
                          /*  if (row == 0 && col == 0) {}
                            if (row == 0 && col == no_columns) {}
                            if (row == no_rows && col == 0) {}
                            if (row == no_rows && col == no_columns) {}
                            if (row == 0 && (col != 0 || col != no_columns)) {}
                            if (row == no_rows && (col != 0 || col != no_columns)) {}
                            if (col == 0 && (row != 0 || row != no_rows)) {}
                            if (col == no_columns && (row != 0 || row != no_rows)) {}
                          */}
                    else{        
                            for(int R1 = TempR - 1; R1 <= TempR + 1; R1++){
                                for(int C1 = TempC - 1; C1 <= TempC + 1; C1++){
                                    TempValue = TempValue + data[R1][C1];
                                    }
                                }
                            temp[row][col] = floor(0.5 + TempValue/9);
                            }        
                    }
                }
           data.assign(temp.begin(), temp.end());
           return 0;
           }
       
       
       // ----- reduceIfNearIsZero     
       int reduceIfNearIsZero(){
       int NoOfZeros = 0, TempR, TempC;
       temp.assign(data.begin(),data.end());
           for (int row = 0; row < no_rows; ++row) {
                for (int col = 0; col < no_columns; ++col){
                    NoOfZeros = 0;
                    TempR = row;
                    TempC = col;
                    if (row == 0 || row == no_rows-1 || col == 0 || col == no_columns-1){
                          /*  if (row == 0 && col == 0) {}
                            if (row == 0 && col == no_columns) {}
                            if (row == no_rows && col == 0) {}
                            if (row == no_rows && col == no_columns) {}
                            if (row == 0 && (col != 0 || col != no_columns)) {}
                            if (row == no_rows && (col != 0 || col != no_columns)) {}
                            if (col == 0 && (row != 0 || row != no_rows)) {}
                            if (col == no_columns && (row != 0 || row != no_rows)) {}
                          */}
                    else{        
                            for(int R1 = TempR - 1; R1 <= TempR + 1; R1++){
                                for(int C1 = TempC - 1; C1 <= TempC + 1; C1++){
                                    if (data[R1][C1] < 1) {NoOfZeros++;}
                                    }
                                }
                            if (NoOfZeros >= 4) {temp[row][col] = 0;}
                            }
                    }
                }
           data.assign(temp.begin(), temp.end());
           return 0;
           }
           
      
      };
      
int main(){
int temp;
dataCLASS Experimental;
printf("\nspecify number of columns: " );
scanf("%i", &Experimental.no_columns);
printf("\nspecify number of rows: " );
scanf("%i", &Experimental.no_rows);
printf("\nno_columns, no_rows assigned \nSpecify input filename: ");
cin.getline(Experimental.fileName, 30);         
Experimental.importData();
Experimental.showData();
//printf("\nSet limit value: ");
//cin >> temp;
Experimental.smoothData();
Experimental.smoothData();
Experimental.smoothData();
Experimental.fillBelowLimitWithZero(700);
//printf("\nData after substraction \n" );
//Experimental.showData();
Experimental.reduceIfNearIsZero();
Experimental.reduceIfNearIsZero();
Experimental.showData();
cin.getline(Experimental.fileName, 30);         
Experimental.exportData();
printf("Write something: ");
cin.getline(Experimental.fileName, 30);         
return 0;
}
