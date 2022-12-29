#include "pca.h"
#include <iostream>
#include <stdio.h>

using namespace std;

obj_loader *loader = new obj_loader();
float eigenValueArray[2754*3] ={0.0f,};
int index_eigen[2754*3]={0};

pca::pca()
{

    m_numSample=26;
    m_numDim=1370;

    pcaPCClick=false;
    M = Eigen::MatrixXf (m_numSample,m_numDim*3);
    MA = Eigen::MatrixXf (m_numSample,m_numDim*3);
    CV = Eigen::MatrixXf (m_numDim*3,m_numDim*3);
    centered = Eigen::MatrixXf(m_numSample,m_numDim*3);
    PCAResult= Eigen::MatrixXf(m_numSample,m_numDim*3);
     PcaToOriginal= Eigen::MatrixXf(m_numSample,m_numDim*3);
    mean=Eigen::MatrixXf (1,m_numDim*3);
    M_check = Eigen::MatrixXf (m_numSample,m_numDim*3);

    eigenValues=Eigen::MatrixXf (m_numDim*3,1);
    eigenVectors=Eigen::MatrixXf (m_numDim*3,m_numDim*3);
   // Eigen::MatrixXf useEigen;

    //Eigen::MatrixXf useEigen2;


}

pca::pca(int num_sample, int num_dim)
{

    m_numSample=num_sample;
    m_numDim=num_dim;

    pcaPCClick=false;
    M = Eigen::MatrixXf (m_numSample,m_numDim*3);
    MA = Eigen::MatrixXf (m_numSample,m_numDim*3);
    CV = Eigen::MatrixXf (m_numDim*3,m_numDim*3);
    centered = Eigen::MatrixXf(m_numSample,m_numDim*3);
    PCAResult= Eigen::MatrixXf(m_numSample,m_numDim*3);
     PcaToOriginal= Eigen::MatrixXf(m_numSample,m_numDim*3);
    mean=Eigen::MatrixXf (1,m_numDim*3);
    M_check = Eigen::MatrixXf (m_numSample,m_numDim*3);

    eigenValues=Eigen::MatrixXf (m_numDim*3,1);
    eigenVectors=Eigen::MatrixXf (m_numDim*3,m_numDim*3);
   // Eigen::MatrixXf useEigen;

    //Eigen::MatrixXf useEigen2;


}




void pca::calculateMeans()
{

    qDebug()<<"CALCULATE MEANS";


    for(int i=0;i<m_numDim;i++)
    {
        float mx=0,my=0,mz=0;
        for(int j=0;j<m_numSample;j++)
        {
            int k=i*3;
            mx+=M(j,k+0);
            my+=M(j,k+1);
            mz+=M(j,k+2);
        }

        mx/=m_numSample; my/=m_numSample; mz/=m_numSample;

         for(int j=0;j<m_numSample;j++)
        {
            int k=i*3;
            centered(j,k+0)=M(j,k+0)-mx;
            centered(j,k+1)=M(j,k+1)-my;
            centered(j,k+2)=M(j,k+2)-mz;

        }
    }

qDebug()<<"CALCULATE MEANS1";
/*
    for(int i=0;i<m_numDim*3;i++)
    {

        mean(0,i) = 0.0f;
       // qDebug()<<mean(0,i-1);
        for(int j=0;j<m_numSample;j++)
        {

            mean(0,i)+=centered(j,i);
        }
        mean(0,i)/=m_numSample;
    }
    */

for(int i=0;i<m_numDim*3;i++)
{

    mean(0,i) = 0.0f;
   // qDebug()<<mean(0,i-1);
    for(int j=0;j<m_numSample;j++)
    {

        mean(0,i)+=M(j,i);
    }
    mean(0,i)/=m_numSample;
}

qDebug()<<"CALCULATE MEANS2";

    //original-mean MA 26*(1370*3)
    for(int i=0;i<m_numSample;i++)
    {
        for(int j=0;j<m_numDim*3;j++)
        {
            MA(i,j)=M(i,j)-mean(0,j);
        }
    }

/*
    for(int i=0;i<m_numSample;i++)
    {
        float mx=0,my=0,mz=0;
        for(int j=0;j<m_numDim;j++)
        {
            int k=j*3;
            mx+=MA(i,k+0);
            my+=MA(i,k+1);
            mz+=MA(i,k+2);
        }
        mx/=m_numDim; my/=m_numDim; mz/=m_numDim;

        for(int j=0;j<m_numDim;j++)
        {
            int k=j*3;
            MA(i,k+0)=MA(i,k+0)-mx;
            MA(i,k+1)=MA(i,k+1)-my;
            MA(i,k+2)=MA(i,k+2)-mz;

        }
    }
*/
    qDebug()<<"success MEANS";

}


void pca::calculateCovariance()
{


   // Eigen::MatrixXf centered = MA_each.rowwise() - MA_each.colwise().mean();
   // qDebug()<<MA_each.rows()<<MA_each.cols()<<centered.rows()<<centered.cols();
   qDebug()<<"centered row col" <<centered.rows()<<centered.cols();
   CV = (centered.transpose() * centered)/(m_numSample);        //4110 * 26  26*4110
    //CV = (MA_each*MA_each.transpose())/m_numSample;
    qDebug()<<"CV row col" <<CV.rows()<<CV.cols();

    qDebug()<<"CALCULATE covariance";

}


void pca::calculateEigen()
{

    qDebug()<<"Start CalculateEigen";
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> es;
    es.compute(CV);

    qDebug()<<"eigen Size"<<es.eigenvalues().size();


    for(int i = 0; i<m_numSample; i++)
    {
        int index = es.eigenvalues().size()-1 - i;
        eigenValueArray[i]=es.eigenvalues()[index];
        //qDebug()<<"eigenvalues"<<i<<eigenValueArray[i];
    }

    for(int i = 0; i<m_numSample; i++)
    {
        int index = es.eigenvectors().cols()-1 - i;
        for(int j=0;j<es.eigenvectors().cols();j++)
        {
            eigenVectors(i,j)=es.eigenvectors().col(index)[j];

            //qDebug()<<"eigenVectors"<<i<<j<<es.eigenvectors().col(i)[j];
        }

    }




    qDebug()<<"CALCULATE eigenVlaueArray";

//normalize check?-> 이미 ㄷㅚ어있음
/*
    Eigen::MatrixXf eigenVecNormalized = es.eigenvectors().normalized();
    qDebug()<<"normeigenVec"<<es.eigenvectors().normalized().size();
    for(int i=es.eigenvalues().size()-1;i>=es.eigenvalues().size()-1-m_numSample;i--)
    {
        for(int j=0;j<es.eigenvalues().size();j++)
        {

            eigenVectors(es.eigenvalues().size()-1-i,j)=eigenVecNormalized(i,j);
            //qDebug()<<"eigenVectors"<<i<<j<<es.eigenvectors().col(i)[j];
        }

      // qDebug()<<"eigeVector index 0 "<<25-i<<eigenVectors(25-i,0);
    }
*/






    qDebug()<<"eval 개수 : " << es.eigenvalues().size();
    qDebug()<<"evec col, row : " << es.eigenvectors().cols()<<es.eigenvectors().rows();
    qDebug()<<"CALCULATE eigenvectors";

}

void pca::pcaOutput(int N)
{
    //useEigen  M*26
    //useEigen=Eigen::MatrixXf(N,m_numSample);
    useEigen2=Eigen::MatrixXf(N,m_numDim*3);
    qDebug()<<"PC 개수 : " << N;
    pcaPCClick=false;
    int m=0;



    for(int i=0;i<N;i++)
    {
        for(int j=0;j<m_numDim*3;j++)
         {
          useEigen2(i,j)=eigenVectors(i,j);

        }
    }


    //qDebug()<<useEigen2(0,0)<<eigenVectors(0,0);

    //m_numSample*N{(N*m_numSample)*(m_numSample*m_numSample)}
    PcaToOriginal = useEigen2*(useEigen2.transpose()*MA);

    qDebug()<<"PcaToOriginal"<<PcaToOriginal(0,0);

    for(int i=0;i<m_numSample;i++)
    {
        for(int j=0;j<m_numDim*3;j++)
        {
            PCAResult(i,j)=PcaToOriginal(i,j)+mean(0,j);
        }
         qDebug()<<"PCAResult"<<i<<PCAResult(i,0);
    }

    qDebug()<<" PCAResult+mean1 : " << PCAResult(2,0)<<"original"<<MA(2,0);
    qDebug()<<" PCAResult+mean1 : " << PCAResult(0,0)<<"original"<<MA(0,0);


    Eigen::MatrixXf checkPCA(N,N);
    qDebug()<<"PCAResult_mean.row(0) rows cols"<<PcaToOriginal.row(0).rows()<<PcaToOriginal.row(0).cols();
     qDebug()<<"eigenVectors row col"<<eigenVectors.rows()<<eigenVectors.cols();
     qDebug()<<"useEigen2*MA_each.row(i).transpose() row col"<<(useEigen2*centered.row(0).transpose()).rows()<<(useEigen2*centered.row(0).transpose()).cols();
/*
    for(int i=0;i<m_numSample;i++)
    {
     checkPCA.col(i)=useEigen2*(MA.row(i).transpose());
    }
*/
   // checkPCA=useEigen2*(MA.transpose());
    checkPCA=useEigen2*MA.transpose();
    /*
    for(int i=0;i<N;i++)
    {
         for(int j=0;j<N;j++)
            qDebug()<<checkPCA(j,i);
       qDebug()<<"-----------"<<i<<"-----------";
    }

*/
    for(int i=0;i<m_numSample;i++)
    {
        float mx=0,my=0,mz=0;
        for(int j=0;j<m_numDim;j++)
        {
            int k=j*3;
            mx+=PCAResult(i,k+0);
            my+=PCAResult(i,k+1);
            mz+=PCAResult(i,k+2);
        }
        mx/=m_numDim; my/=m_numDim; mz/=m_numDim;

        for(int j=0;j<m_numDim;j++)
        {
            int k=j*3;
            PCAResult(i,k+0)=PCAResult(i,k+0)-mx;
            PCAResult(i,k+1)=PCAResult(i,k+1)-my;
            PCAResult(i,k+2)=PCAResult(i,k+2)-mz;

        }
    }
}

void pca::pcaPC(int eigenIndex,int weight)
{


    for(int j=0;j<m_numDim*3;j++)
    {
        PcaToOriginal(0,j)=mean(0,j);
    }

    qDebug()<<"w:"<<weight;

     Eigen::MatrixXf EigenVec(1,m_numDim*3);

     for(int i=0;i<m_numDim*3;i++)
     {
         EigenVec(0,i)=eigenVectors(eigenIndex,i);
     }

    qDebug()<<"eigenVlaueArray"<<sqrt(eigenValueArray[eigenIndex]);
    float w=sqrt(eigenValueArray[eigenIndex])*weight;
    EigenVec*=w;
    PcaToOriginal=PcaToOriginal+EigenVec;

    for(int i=0;i<m_numSample;i++)
    {
        for(int j=0;j<m_numDim*3;j++)
        {
            PCAResult(i,j)=PcaToOriginal(0,j);
        }
    }

    for(int i=0;i<m_numSample;i++)
    {
        float mx=0,my=0,mz=0;
        for(int j=0;j<m_numDim;j++)
        {
            int k=j*3;
            mx+=PCAResult(i,k+0);
            my+=PCAResult(i,k+1);
            mz+=PCAResult(i,k+2);
        }
        mx/=m_numDim; my/=m_numDim; mz/=m_numDim;

        for(int j=0;j<m_numDim;j++)
        {
            int k=j*3;
            PCAResult(i,k+0)=PCAResult(i,k+0)-mx;
            PCAResult(i,k+1)=PCAResult(i,k+1)-my;
            PCAResult(i,k+2)=PCAResult(i,k+2)-mz;

        }
    }


    //qDebug()<<" PCAResult_PC : " << PCAResult(2,0);
    qDebug()<<" PCAResult_PC : " << PCAResult(0,0);


}

