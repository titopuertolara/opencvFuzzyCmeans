	#include "opencv2/highgui/highgui.hpp"
	  #include "opencv2/imgproc/imgproc.hpp"
	  #include <iostream>
	  #include <stdio.h>
	  #include <stdlib.h>
	  #include <string>
	  #include <fstream>
      #include <math.h>

	  
	  using namespace cv;
	  using namespace std;
    //--------------------------------------------------------------------------->


	 void fuzzyKmeansUnal(cv::Mat data,cv::Mat u,cv::Mat c,int k,float epsilon,int Iter,int m,float &J){
	 Mat d,totald;
	bool stop=false;
	int cont=0;
	
	d=Mat::zeros(data.rows,k,CV_32F);
	srand(time(0));

	 float e,f;
	 for(int i=0;i<u.rows;i++){
	 	for(int j=0;j<u.cols;j++){
	      e=rand();
	      f=e/RAND_MAX;
	      u.at<float>(i,j)=f;
	    }
	}

	float sumant=0;
	while(cont<Iter && stop==false){

    

   for (int j=0;j<data.cols;j++){
        for (int i=0;i<k;i++){
            float sumX=0;
            float sumu=0;
            for (int l=0;l<data.rows;l++){
             
              sumX=sumX+(pow(u.at<float>(l,i),m)*(data.at<float>(l,j)));
              sumu=sumu+pow(u.at<float>(l,i),m);
                          
              
            }
           c.at<float>(i,j)=sumX/sumu;
          
        }
      }
    for (int i=0;i<data.rows;i++){
        
        for (int j=0;j<k;j++){
            d.at<float>(i,j)=sqrt(pow((data.at<float>(i,0)-c.at<float>(j,0)),2)+pow((data.at<float>(i,1)-c.at<float>(j,1)),2));
           
        }
        
    }  

	
   totald=Mat::zeros(data.rows,1,CV_32F);
    for (int i=0;i<data.rows;i++){
        for (int j=0;j<k;j++){
            
           totald.at<float>(i,0)=totald.at<float>(i,0)+(pow(1/d.at<float>(i,j),(2/(m-1))));
           
        }
    }

 for (int i=0;i<data.rows;i++){
        for( int j=0;j<k;j++){
            
            
         u.at<float>(i,j)=pow(1/d.at<float>(i,j),(2/(m-1)))/totald.at<float>(i,0);
        	// u.at<float>(i,j)=1;
            
            
            
        }
    }

   float sumj=0;
    for (int i=0;i<data.rows;i++){
        float sumb=0;
        for (int j=0;j<k;j++){
            sumb=sumb+pow(u.at<float>(i,j),m)*(pow((data.at<float>(i,0)-c.at<float>(j,0)),2)+pow((data.at<float>(i,1)-c.at<float>(j,1)),2));
        }
            
        sumj=sumj+sumb;
    }
    
    if(abs(sumant-sumj)<epsilon){
        stop=true;
    J=sumj;
    }
    
    //cout<<abs(sumant-sumj)<<endl;
    
    sumant=sumj;
    J=sumj;
	cont++;
	}
	
    
	//cout<<endl;
	cout<<"El algoritmo se detuvo en "<<cont-1<<" iteraciones"<<endl;
	//cout<<"fcn: "<<J<<endl;
}



	  //--------------------------------------------------------------------------->
	   





	   int main( int argc, char** argv )
	  {

	  Mat data,u,c;
	 data=Mat::zeros(7,2,CV_32F);
	 	 
	 int Iter=100;
	 
	 int k=2;
	 int m=2;
	 float epsilon=0.00001;
	 float J;
	data.at<float>(0,0)=1;
	data.at<float>(1,0)=1.5;
	data.at<float>(2,0)=3;
	data.at<float>(3,0)=5;
	data.at<float>(4,0)=3.5;
	data.at<float>(5,0)=4.5;
	data.at<float>(6,0)=3.5;
	data.at<float>(0,1)=1;
	data.at<float>(1,1)=2;
	data.at<float>(2,1)=4;
	data.at<float>(3,1)=7;
	data.at<float>(4,1)=5;
	data.at<float>(5,1)=5;
	data.at<float>(6,1)=4.5;
    
    u=Mat::zeros(data.rows,k,CV_32F);
	c=Mat::zeros(k,2,CV_32F);
	fuzzyKmeansUnal( data,u,c, k,epsilon, Iter, m, J);
    cout<<"centroides"<<endl;
 	cout<<c<<endl;
	//cout<<d<<endl;
	//cout<<totald<<endl;
	cout<<endl;
	cout<<"Matriz de pertenencia"<<endl;
	cout<<u<<endl;
	cout<<endl;
	cout<<"fcn: "<<J<<endl;
	  	return 0;

	  }