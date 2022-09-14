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

    Eigen::MatrixXf M ;
    Eigen::MatrixXf MA ;
    Eigen::MatrixXf CV ;
    Eigen::MatrixXf EV ;


    QVector3D means;

    QVector<QVector3D> data;
    void calculateMeans();
    void calculateVariances();
    void calculateCovariance();
    void calculateTotalVariance();
    void calculateEigen();
    void pcaOutput(int M);
};

#endif // PCA_H
