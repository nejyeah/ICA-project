//Filename:dataset.cpp
#include"../include/dataset.h"

dataset::dataset(){
    pixel=NULL;
    label=NULL;
    number=0;
    nrow_pixel=0;
    ncol_pixel=0;
}

void dataset::malloc(int symbol){
    if(symbol==0){
        label=new unsigned char[number];
    }
    else if(symbol==1){
        pixel=new double*[number];
        for(int i=0;i<number;i++){
            pixel[i]=new double[nrow_pixel*ncol_pixel];
        }
    }
    else{
        cerr<<"malloc cannot go on for the wrong file!"<<endl;
    }
}

void dataset::free() {
    if(pixel!=NULL){
        for(int i=0;i<number;i++){
            delete[] pixel[i];
            pixel[i]=NULL;
        }
        delete[] pixel;
        pixel=NULL;
    }
    if(label!=NULL){
        delete[] label;
        label=NULL;
    }
}

void dataset::loaddata(string filename){
    ifstream fp;
    char *magicnumber=new char[4];
    char *totalnumber=new char[4];
    unsigned char *totalnumber1=new unsigned char[4];
    char buffer;
    unsigned char unsignedbuffer;
    fp.open(filename.c_str(),ifstream::in|ifstream::binary);
    if(!fp){
        cerr<<"error:cannot open the file!"<<endl;
    }
    else{
        //based on the data-loading 
        cout<<"successfully open "<<filename<<endl;
        fp.read(magicnumber,4);
        fp.read(totalnumber,4);
        for(int i=0;i<4;i++){
            totalnumber1[i]=totalnumber[i];
        }
        number=(int)totalnumber1[0]*pow(256,3)+(int)totalnumber1[1]*pow(256,2)+(int)totalnumber1[2]*pow(256,1)+(int)totalnumber1[3]*pow(256,0);
        if((int)magicnumber[3]==3){
            char *nrow=new char[4];
            char *ncol=new char[4];
            fp.read(nrow,4);
            fp.read(ncol,4);

            nrow_pixel=(int)nrow[3];
            ncol_pixel=(int)ncol[3];
            //cout<<"number:"<<number<<" nrow_pixel:"<<nrow_pixel<<" ncol_pixel:"<<ncol_pixel<<endl;
            malloc(1);
            for(int i=0;i<number;i++){
                for(int j=0;j<nrow_pixel*ncol_pixel;j++){
                    fp.read(&buffer,1);
                    unsignedbuffer=buffer;
                    pixel[i][j]=unsignedbuffer/255.0;
                    //cout<<pixel[i][j]<<" ";
                }
                //cout<<endl;

            }
            cout<<number<<" images in"<<filename<<" loading successfully"<<endl;
            delete[] nrow;
            delete[] ncol;
        }
        else if((int)magicnumber[3]==1){
            malloc(0);
            for(int i=0;i<number;i++){
                fp.read(&buffer,1);
                label[i]=buffer;
            }
            cout<<number<<" labels in"<<filename<<" loading successfully"<<endl;
        }
        else{
            cerr<<"loaddata error!"<<endl;
        }
        fp.close();

    }
    delete[] magicnumber;
    delete[] totalnumber;
    delete[] totalnumber1;
}
