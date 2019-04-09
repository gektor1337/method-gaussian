//
//  main.cpp
//  gauss
//
//  Created by Руднев Павел Сергеевич on 02/04/2019.
//  Copyright © 2019 Руднев Павел Сергеевич. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <locale>
#include <cstdlib>
#include <ctime>
using namespace std;

void eq (double *a, double *y, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            //cout << a[i*n+j] << "*x" << j;
            if (j < n - 1) {
                //cout <<" + ";
            }
        }
        //cout <<" = " << y[i] << '\n';
    }
    return;
}

double *Gss (double *a, double *y, int n) {
    double *x, max;
    int k, index;
    const double eps = 0.00001;
    x = new double[n];
    k = 0;
    while (k < n) {
        max = fabs(a[k*n+k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(a[i*n+k]) > max) {
                max = fabs(a[i*n+k]);
                index = i;
            }
        }
        if (max < eps) {
            cout << "Решений нет тк есть нулевой столбец " ;
            cout << index << " матрицы A" << '\n';
            return 0;
        }
        for (int j = 0; j < n; j++) { //пр€мой ход
            double array = a[k*n+j];
            a[k*n+j] = a[index*n+j];
            a[index*n+j] = array;
        }
        double array = y[k];
        y[k] = y[index];
        y[index] = array;
        
        for (int i = k; i < n; i++) {
            double array = a[i*n+k];
            if (fabs(array) < eps) continue;
            for (int j = 0; j < n; j++) {
                a[i*n+j] = a[i*n+j] / array;
            }
            y[i] = y[i] / array;
            if (i == k) continue;
            for (int j = 0; j < n; j++)
                a[i*n+j] = a[i*n+j] - a[k*n+j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; k--) { //обратный ход
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i*n+k] * x[k];
    }
    return x;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    double *a, *y, *x, *a2;
    int n;
    cout << " какой размер матрицы?: ";
    cin >> n;
    a = new double[n*n];
    a2 = new double[n*n];
    y = new double[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //cout << "a[" << i << "][" << j << "]= ";
            a[i*n+j] = rand()%100 ;
            //cin>>a[i*n+j];
        }
    }
    if(n>10){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout<<a[i*n+j]<<"\t";
            }
            cout<<". . .\t"<<a[i*n+(n-1)]<<"\t";
            cout<<"\n";
        }
        cout<<"\n";
        
        for(int i=0;i<3;i++){for (int j = 0; j < 10; j++){cout<<'.'<<'\t';} cout<<'\t'<<'.'<<'\n';} cout<<'\n';
        
        
        for (int j = 0; j < 10; j++) {
            cout<<a[(n-1)*n+j]<<"\t";
        }
        cout<<". . .\t"<<a[(n-1)*n+(n-1)]<<"\t";
    }else{
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout<<a[i*n+j]<<"\t";
            }
            cout<<"\n";
        }
    }
    cout<<"\n";cout<<"\n";
    
    for (int i = 0; i < n; i++) {
        //cout << "y[" << i << "]= ";
        y[i]= rand()%100;
        
        //cout<<y[i]<<endl;
    }
    cout<<endl;
    eq(a, y, n);
    
    x = Gss(a, y, n);
    for (int i = 0; i < 10; i++){
        cout << "x[" << i << "]=" << x[i] << '\n'; //ответ
    }
    cout <<".\n.\n.\n"<< "x[" << n-1 << "]=" << x[n-1] << '\n';
    
    cout<<"\nѕроверка :"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //cout << "a[" << i << "][" << j << "]= ";
            a2[i*n+j]=x[i]-y[i];
            //cout<<a2[i*n+j]<<'\t';
        }
        //cout<<'\n';
    }
    
    if(n>10){
        for (int i = 0; i < 10; i++) {
            
            cout<<a2[i]<<"\n";
            
        }
        cout<<".\n.\n.\n"<<a2[(n-1)];
        cout<<"\n";
        
        //for(int i=0;i<3;i++){cout<<'.'<<'\t'; cout<<'\t'<<'.'<<'\n';} cout<<'\n';
        
        //for (int j = 0; j < 10; j++) {
        //     cout<<a2[(n-1)*n+j]<<"\t";
        //     }
        //  cout<<". . .\t"<<a2[(n-1)*n+(n-1)]<<"\t";
    }else{
        for (int i = 0; i < n; i++) {
            
            cout<<a2[i]<<"\n";
            
        }
    }
    
    cin.get();cin.get();
    return 0;
}
