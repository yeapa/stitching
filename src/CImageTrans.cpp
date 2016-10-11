//
// Created by ye on 16-9-19.
//

#include "CImageTrans.h"
#include <time.h>
void CImageTrans::exportAImage(int i){
    char * name=new char[100];
    sprintf(name,"%d.jpg",i);
    string picName(name);
    picName=m_path+picName;
    exportImage(srcImageRange(*m_pCurImage), vigra::ImageExportInfo(picName.c_str()).setCompression("80"));
}

void CImageTrans::exportAImage(){
    time_t  rawtime;
    time(&rawtime);
    char name[100];
    sprintf(name,"%ld.jpg",rawtime);
    string picName(name);
    picName=m_path+picName;
    exportImage(srcImageRange(*m_pCurImage), vigra::ImageExportInfo(picName.c_str()).setCompression("80"));
}

void CImageTrans::exportAImage( vigra::BRGBImage* image,string path){
    time_t  rawtime;
    time(&rawtime);
    char name[100];
    sprintf(name,"%ld.jpg",rawtime);
    string picName(name);
    picName=path+picName;
    exportImage(srcImageRange(*image), vigra::ImageExportInfo(picName.c_str()).setCompression("80"));
}

bool CImageTrans::BRGBImage2YUV420p(vigra::BRGBImage* image, unsigned char* pYUV420P){
    unsigned char* pRGB24 = new unsigned char[m_width*m_height*3];
    struct SwsContext* pImgCtx = sws_getContext(m_width,m_height,AV_PIX_FMT_RGB24,m_width,m_height,AV_PIX_FMT_YUV420P,SWS_BILINEAR,0,0,0);

    for(int j=0;j<m_height;j++){
        for(int i=0;i<m_width;i++){
//            cout<<image->width()<<endl;
            pRGB24[(j*m_width+i)*3]=(*image)[j][i].red();
            pRGB24[(j*m_width+i)*3+1]=(*image)[j][i].green();
            pRGB24[(j*m_width+i)*3+2]=(*image)[j][i].blue();
        }
    }

    AVPicture pFrameYUV,pFrameRGB;
    avpicture_fill(&pFrameYUV,pYUV420P,AV_PIX_FMT_YUV420P,m_width,m_height);
    avpicture_fill(&pFrameRGB,pRGB24,AV_PIX_FMT_RGB24,m_width,m_height);
    if (m_pImgCtx != NULL) {
        sws_scale(pImgCtx, (const uint8_t *const *) pFrameRGB.data, pFrameRGB.linesize, 0, m_height, pFrameYUV.data,
                  pFrameYUV.linesize);
    }
}

bool CImageTrans::transform(const unsigned char * pYUV)
{
    if (m_width < 1 || m_height < 1 || pYUV == NULL || m_pRGB24 == NULL)
        return false;

    vigra::BRGBImage* image=new vigra::BRGBImage(m_width,m_height);
    m_pCurImage=image;
    AVPicture pFrameYUV,pFrameRGB;
    avpicture_fill(&pFrameYUV,pYUV,AV_PIX_FMT_YUYV422,m_width,m_height);
    avpicture_fill(&pFrameRGB,m_pRGB24,AV_PIX_FMT_RGB24,m_width,m_height);
    if (m_pImgCtx != NULL){
        sws_scale(m_pImgCtx,(const uint8_t* const*)pFrameYUV.data,pFrameYUV.linesize,0,m_height,pFrameRGB.data,pFrameRGB.linesize);
//            FILE *output=fopen("out.rgb","wb");
//            fwrite(pFrameRGB.data[0],(m_width)*(height)*3,1,output);

        int x=0;
        int y=0;
        for(int i = 0; i<m_width*m_height*3;i+=3){
            vigra::RGBValue<vigra::UInt8>  rgbPoint;
            rgbPoint.setRed(pFrameRGB.data[0][i]);
            rgbPoint.setGreen(pFrameRGB.data[0][i+1]);
            rgbPoint.setBlue(pFrameRGB.data[0][i+2]);
            (*m_pCurImage)[x][y]=rgbPoint;
            y++;
            if (y>=m_width){
                y=0;
                x++;
            }
        }
//          cout<<endl<<"linesize:"<<pFrameRGB.linesize[0]<<endl;
        return true;
    }else{
        return false;
    }
}
