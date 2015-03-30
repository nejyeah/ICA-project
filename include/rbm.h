//Filename:rbm.h
#ifndef CAT_R
#define CAT_R
#include"dataset.h"
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<time.h>

using namespace std;

class RBM{
    public:i
        RBM(dataset &data,const int n_hidden,const int batch_size);
        void initialization();
    private:
        const int n_hidden;
        const int n_visible;
        const int batch_size;
        const float lr;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
        vector<double> vbias;
        vector< vector<double> > w;

        
};

#endif
