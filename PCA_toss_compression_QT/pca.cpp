#include "pca.h"
#include <iostream>

using namespace std;

obj_loader *loader = new obj_loader();


Eigen::MatrixXf mean;
Eigen::MatrixXf v_total;
Eigen::MatrixXf cv_total;
Eigen::MatrixXf variance;
Eigen::MatrixXf eigenValues;
Eigen::MatrixXf eigenVectors;
Eigen::MatrixXf useEigen;
Eigen::MatrixXf PCAResult;

pca::pca()
{

}

void pca::calculateMeans()
{
    //M 26*(1370*3)
    qDebug()<<"CALCULATE MEANS";

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
            mean(i,0)+=M(i,j);
    }

    for(int i=0;i<26;i++)
        mean(i,0)/=26;
    //original-mean MA 26*(1370*3)
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
            MA(i,j)=M(i,j)-mean(i,0);
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
}

void pca::pcaOutput(int M)
{
    //useEigen  M*26
    for(int i=M-1;i<=0;i--)
    {
        for(int j=0;j<26;j++)
             useEigen(M-1-i,j)=eigenVectors(i,j);
    }
    //M*26 26*(1370*3) ->M차원의 데이터들
    //26*M M*(1370*3)
    PCAResult = useEigen.transpose()*(useEigen*MA);

}
