#include<iostream>
using namespace std;
int acumulacion(int **A,int **B,int &b,int f,int c,int k){//devuelve un valor  de la multiplicacion de matrices
  return A[f][k]*B[k][c];
}
int calculo(int **A,int **B,int **C,int &a,int &b,int f,int c,int k=0){//ya en la posicion saca su valor recorriendo una fila y una columna a la vez
  if(k==b){return 0;}
  C[f][c]+=acumulacion(A,B,b,f,c,k);//acumula el valor de la multiplicacion de la fila
  return calculo(A,B,C,a,b,f,c,++k);//aumenta la posicion de la columna
}
int columna(int **A,int **B,int **C,int &a,int &b,int f,int c=0){//recorre las columnas
  if(c==a){return 0;}
  calculo(A,B,C,a,b,f,c);
  return columna(A,B,C,a,b,f,++c);// el c es un contador para parar el cual inicia con un valor de 0
}
int fila(int **A,int **B,int **C,int &a,int &b,int f=0){//recorre las filas
  if(f==a){return 0;}
  columna(A,B,C,a,b,f);
  return fila(A,B,C,a,b,++f);// el f es un contador para parar el cual inicia con un valor de 0
}
int matrix(int **A,int &a,int &b,int i=0){//separa memoria para una matriz
    if(i==a)return 0;// caso para parar
    *(A+i)=new int[b];//crea nuevos punteros para la matriz
    return matrix(A,a,b,++i);
}
int datos(int **A,int &a,int &b,int i=0,int j=0){//ingresa valores para una matriz
  cin>>*(*(A+i)+j);
  if(i!=a-1 or j!=b-1){
    if(j==b-1){i++;j=0;}// como estamos usando posiciones tipo array la posicion tambien empieza en 0 y termina en len-1(len es el numero de elementos que se tiene)
    else j++;
    datos(A,a,b,i,j);
  }
}
int rellenar(int **A,int &a,int &b,int i=0,int j=0){//rellena de ceros una matriz
  *(*(A+i)+j)=0;
  if(i!=a-1 or j!=b-1){
    if(j==b-1){i++;j=0;}
    else j++;
    rellenar(A,a,b,i,j);
  }
}
int printo(int **A,int &a,int &b,int i=0,int j=0){//imprime una matriz
  if(i==0 and j==0)cout<<'\n';
  cout<<*(*(A+i)+j);
  if(i!=a-1 or j!=b-1){
    if(j==b-1){
      cout<<'\n';
      i++;j=0;
    }
    else {
      cout<<' ';
      j++;
    }
    printo(A,a,b,i,j);
  }
  else cout<<'\n';
}
int borrar(int **A,int &a,int i=0){//libera la memoria separada
  if(i==a)return 0;
  delete []*(A+i);
  return borrar(A,a,++i);
}
int main(){
  int a,b;
  cin>>a>>b;
  int **A =new int*[a],**B =new int*[b],**C =new int*[a];
  matrix(A,a,b);// aqui creamos la matriz M con los valores que el usuario inserto
  matrix(B,b,a);// aqui creamos otra invirtiendo los valores para que se pueda multiplicar
  matrix(C,a,a);
  datos(A,a,b);
  datos(B,b,a);
  rellenar(C,a,a);
  fila(A,B,C,a,b);//multiplicamos las matrices
    cout<<"matrizA"<<endl;printo(A,a,b);
    cout<<"matrizB"<<endl;printo(B,b,a);
    cout<<"matrizC"<<endl;printo(C,a,a);//muestra el resultado de la multuplicacion
  borrar(A,a);// borra las matrices para recuperar toda la memoria
  borrar(B,b);
  borrar(C,a);
  return 0;
}

