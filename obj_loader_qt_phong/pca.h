#ifndef PCA_H
#define PCA_H

#include <QVector>
#include <QVector3D>
#include "eigen/Eigen/Dense"
#include <vector>

class pca
{
private:

public:
    pca();

    struct Data
    {

        QVector3D v = QVector3D(0, 0, 0);
        QVector3D vn = QVector3D(0, 0, 0);
        QVector3D f = QVector3D(0, 0, 0);

    };







    QVector<Data> data;
    void calculateMeans(QVector<Data>);
    void calculateVariances();
    void calculateCovariance();
    void calculateTotalVariance();
    void calculateEigen(int M);
    void pcaOutput();
};

#endif // PCA_H
