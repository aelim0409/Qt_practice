#ifndef PCA_H
#define PCA_H

#include <QVector>
#include <QVector3D>
#include "eigen/Eigen/Dense"
#include <vector>
#include <obj_loader.h>

class pca
{
private:

public:
    pca();
    pca(int num_sample, int num_dim);

    int m_numSample;
    int m_numDim;

    Eigen::MatrixXf M ;
    Eigen::MatrixXf MA ;
    Eigen::MatrixXf centered ;
    Eigen::MatrixXf CV ;
    Eigen::MatrixXf EV ;
    Eigen::MatrixXf PCAResult;
    Eigen::MatrixXf PcaToOriginal;


    Eigen::MatrixXf mean;
    Eigen::MatrixXf v_total;
    Eigen::MatrixXf cv_total;
    Eigen::MatrixXf variance;
    Eigen::MatrixXf eigenValues;
    Eigen::MatrixXf eigenVectors;
    Eigen::MatrixXf useEigen;
    //float *eigenValueArray;
    //int *index_eigen;
    Eigen::MatrixXf useEigen2;
 Eigen::MatrixXf M_check;
    QVector3D means;
    QVector<QVector3D> data;
    bool pcaPCClick;
    void calculateMeans();
    void calculateVariances();
    void calculateCovariance();
    void calculateTotalVariance();
    void calculateEigen();
    void pcaOutput(int M);
    void pcaPC(int eigenIndex,int weight);
};

#endif // PCA_H
