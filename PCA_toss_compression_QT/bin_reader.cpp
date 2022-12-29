#include "bin_reader.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include <QDebug>
#include <QChar>
#include <stdio.h>

using namespace std;

bin_reader::bin_reader()
{

}


void bin_reader::loadModel(char* s)
{

    ifstream f(s,ios_base::in|ios_base::binary);

    for(int i=0;i<12;i++)
    {
        char c;
         f.read(&c,sizeof(char));
         st_info.header[i]=c;
    }


    f.read((char *) &st_info.version,sizeof(int));
    f.read((char *) &st_info.num_points,sizeof(int));

    f.read((char *) &st_info.startFrame,sizeof(float));
    f.read((char *) &st_info.sampleRate,sizeof(float));

     f.read((char *) &st_info.num_samples,sizeof(int));
     qDebug()<<st_info.header<<st_info.version<<st_info.num_points<<st_info.startFrame<<st_info.sampleRate<<st_info.num_samples;

     int cnt=0;
     int idx=0;
     int idx_sample=0;
     pos_xyz p;
     samples sam;
     while(idx_sample!=st_info.num_samples)
     {
         float pos;
          f.read((char *) &pos,sizeof(float));


          if(cnt%3==0)  p.x=pos;
          else if(cnt%3==1)  p.y=pos;
          else if(cnt%3==2)
          {
              p.z=pos;
              sam.positions.push_back(p);
             // qDebug()<<sample[idx_sample].positions[idx].x<<sample[idx_sample].positions[idx].y<<sample[idx_sample].positions[idx].z;
              idx++;
          }
        if( idx==st_info.num_points)
        {
            sample.push_back(sam);
            sam.positions.clear();
            idx=0;
            idx_sample++;
        }
          cnt++;



     }

/*
     for(int i=0;i<idx_sample;i++)
     {
         for(int j=0;j<sample[i].positions.size();j++)
         {
             qDebug()<<i<<sample[i].positions[j].x<<sample[i].positions[j].y<<sample[i].positions[j].z;

         }
     }

*/
/*
     qDebug()<<sample.size();
     for(int i=0;i<sample.size();i++)
     {
         qDebug()<<i<<sample[i].positions.size();
     }
     */
}
