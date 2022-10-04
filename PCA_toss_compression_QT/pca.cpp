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
float eigenVlaueArray[26];
int index_eigen[26];

pca::pca()
{
    PCAResult= Eigen::MatrixXf(26,1370*3);
}

void pca::calculateMeans()
{

    qDebug()<<"CALCULATE MEANS";

    int m=0;

    MA_each = Eigen::MatrixXf(26,1370*3);
    float mx=0,my=0,mz=0;
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370;j++)
        {
            int k=j*3;
            mx+=M(i,k);
            my+=M(i,k+1);
            mz+=M(i,k+2);
        }
        mx/=1370; my/=1370; mz/=1370;

        for(int j=0;j<1370;j++)
        {
            int k=j*3;
            MA_each(i,k)=M(i,k)-mx;
            MA_each(i,k+1)=M(i,k+1)-my;
            MA_each(i,k+2)=M(i,k+2)-mz;

        }
    }

    for(int i=0;i<1370*3;i++)
    {
        for(int j=0;j<26;j++)
        {
            mean(0,i)+=MA_each(j,i);
        }
        mean(0,i)/=26;
    }



    //original-mean MA 26*(1370*3)
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
        {

            MA(i,j)=MA_each(i,j)-mean(j,0);

        }
    }

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
    double MA_total1=1;
    float MA_total2=0;
    float covariance =0;

    Eigen::MatrixXf centered = MA_each.rowwise() - MA_each.colwise().mean();
   // qDebug()<<MA_each.rows()<<MA_each.cols()<<centered.rows()<<centered.cols();
   qDebug()<<"centered row col" <<centered.rows()<<centered.cols();
   Eigen::MatrixXf CV2 = (centered * centered.transpose())/26;
    qDebug()<<"CV2 row col" <<CV2.rows()<<CV2.cols();
   CV=CV2;
    /*
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
       {
            MA_total1*=MA(i,j);
          //  qDebug()<<i<<j<<"MA_total"<<MA_total1 <<"MA"<<MA(i,j);

        }

        MA_total2+=MA_total1;
        MA_total1=1;

        qDebug()<<MA_total1;
    }


    qDebug()<<"Ma_total1"<<MA_total1;
    covariance= MA_total2/25;
    qDebug()<<"MA_total2"<<MA_total2;
    //if(covariance==-INFINITE || covariance == INFINITE || covariance == nan)
    covariance=50;

    qDebug()<<"cov"<<covariance;

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
    */
    qDebug()<<"CALCULATE covariance";

}

bool compare(int a, int b){
    return a > b;
}
void pca::calculateEigen()
{
     qDebug()<<CV.rows()<<CV.cols();
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> es;
    es.compute(CV);
    qDebug()<<es.eigenvalues().size();
    for(int i=0;i<26;i++)
    {

        //eigenValues(i,0)= es.eigenvalues().col(0)[i].real();
        //qDebug()<<i<<" "<<eigenValues(i,0);
        eigenVlaueArray[i]=es.eigenvalues()[i];
        qDebug()<<"eigenValue "<<i<<eigenVlaueArray[i];
    }

    //sort(eigenVlaueArray,eigenVlaueArray+26,compare);
    qDebug()<<"CALCULATE eigenVlaueArray";
    /*
    for(int i=0;i<26;i++)
        qDebug()<<"eigenValue" <<i<<eigenVlaueArray[i];
        */


    for(int i=25;i>=0;i--)
    {
        for(int j=0;j<26;j++)
            eigenVectors(25-i,j)=es.eigenvectors().col(i)[j];

    }
/*
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<26;j++)
            qDebug()<<eigenVectors(i,j);
        qDebug()<<"-----------------------------------------";

    }
    */


    qDebug()<<"ev 개수 : " << es.eigenvalues().size();
    qDebug()<<"ev2 col, row : " << es.eigenvectors().cols()<<es.eigenvectors().rows();
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
        }
    }

    for(int i=0;i<useEigen.rows();i++)
        qDebug()<<useEigen(i,0);
    //useEigen M*26 original-means 26*(1370*3) ->M차원의 데이터들
    //useEigen.transpose 26*M (useEigen x original-means)*(1370*3)

    //고정되지 않음.?
    PCAResult = useEigen.transpose()*(useEigen*MA);

    qDebug()<<" PCAResult : " << PCAResult(2,0)<<"original"<<MA(2,0);
    qDebug()<<" PCAResult : " << PCAResult(0,0)<<"original"<<MA(0,0);

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<1370*3;j++)
        {
            PCAResult(i,j)+=mean(0,j);
        }
    }

    qDebug()<<" PCAResult+mean : " << PCAResult(2,0)<<"original"<<MA(2,0);
    qDebug()<<" PCAResult+mean : " << PCAResult(0,0)<<"original"<<MA(0,0);
    qDebug()<<"CALCULATE PCA";
//PCAResult=MA;
}
