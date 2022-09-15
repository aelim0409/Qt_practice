#include "pca.h"
#include <iostream>

using namespace std;

obj_loader *loader = new obj_loader();


Eigen::MatrixXf mean(1,1370*3);
Eigen::MatrixXf v_total(26,1);
Eigen::MatrixXf cv_total;
Eigen::MatrixXf variance(26,1);
Eigen::MatrixXf eigenValues(26,1);
Eigen::MatrixXf eigenVectors(26,26);
Eigen::MatrixXf useEigen;


pca::pca()
{
    PCAResult= Eigen::MatrixXf(26,1370*3);
}

void pca::calculateMeans()
{
    //M 26*(1370*3)
    qDebug()<<"CALCULATE MEANS";
   // qDebug()<<mean.rows();
  //  float m=0;
    int m=0;
    /*
    for(int i=0;i<26;i++)
    {

        for(int j=0;j<1370*3;j++)
        {
           // qDebug()<<"CALCULATE MEANS"<<j;

            mean(0,j)+=M(i,j);

            //qDebug()<<mean(i,0);
        }

        //qDebug()<<mean(i,0);
       // m=0;
    }
    */
    for(int i=0;i<1370*3;i++)
    {
        for(int j=0;j<26;j++)
        {
            mean(0,i)+=M(j,i);
        }
        mean(0,i)/=26;
    }



    //original-mean MA 26*(1370*3)
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
        {

            MA(i,j)=M(i,j)-mean(0,j);

        }
    }

    //qDebug()<<"means"<<means.x() << means.y()<<means.z();
}

void pca::calculateVariances()
{

     for(int j=0;j<1370*3;j++)
    {
       for(int i=0;i<26;i++)
            v_total(i,0)+=pow(MA(i,j),2);
    }

     for(int i=0;i<26;i++)
        variance(i,0) = v_total(i,0)/25;
 qDebug()<<"CALCULATE variance";

}

void pca::calculateCovariance()
{
    float MA_total1=1;
    float MA_total2=0;
    float covariance =0;

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
            MA_total1*=MA(i,j);

        MA_total2+=MA_total1;
    }

    covariance= MA_total2/25;
//cv 26*26
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<26;j++)
        {
            if(i==j)
                CV(i,j)=variance(i,0);
            else
                CV(i,j)=covariance;
        }
    }
    qDebug()<<"CALCULATE covariance";

}

void pca::calculateEigen()
{
    Eigen::EigenSolver<Eigen::MatrixXf> es(CV);
    for(int i=0;i<26;i++)
    {

        eigenValues(i,0)= es.eigenvalues().col(0)[i].real();
        qDebug()<<i<<" "<<eigenValues(i,0);
    }

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<26;j++)
            eigenVectors(i,j)=es.eigenvectors().col(i)[j].real();

    }

    qDebug()<<"ev 개수 : " << es.eigenvalues().size();
    qDebug()<<"CALCULATE eigenvectors";
}

void pca::pcaOutput(int N)
{
    //useEigen  M*26
    useEigen=Eigen::MatrixXf(N,26);
    qDebug()<<"PC 개수 : " << N;

    int m=0;
    for(int i=0;i<N;i++)
    {

        for(int j=0;j<26;j++)
         {

            useEigen(i,j)=eigenVectors(i,j);
            //useEigen(i,j)=0;

        }
    }
    //useEigen M*26 original-means 26*(1370*3) ->M차원의 데이터들
    //useEigen.transpose 26*M (useEigen x original-means)*(1370*3)
    PCAResult = useEigen.transpose()*(useEigen*MA);
    qDebug()<<" PCAResult : " << PCAResult(2,0)<<"original"<<M(2,0);
    qDebug()<<" PCAResult : " << PCAResult(0,0)<<"original"<<M(0,0);
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
        {

            PCAResult(i,j)+=mean(0,j);

        }

    }
    qDebug()<<" PCAResult+mean : " << PCAResult(2,0)<<"original"<<M(2,0);
    qDebug()<<" PCAResult+mean : " << PCAResult(0,0)<<"original"<<M(0,0);
qDebug()<<"CALCULATE PCA";
//PCAResult=MA;
}
