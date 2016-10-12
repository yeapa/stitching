
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "CEventObserver.h"
#include "COutDataWkThreadPool.h"
#include "CReator.h"
#include "CEncoder.h"

// #include "CLog.h"
#include "CLocalThreadLog.h"
#include "CSimpleConfig.h"
#include "CMsgQueue.h"
#include "CImageTrans.h"

class CWkObserver: public CEventObserver
{
public:
	CWkObserver(unsigned int iEvent): CEventObserver(iEvent) {} ;
	~CWkObserver() {};
	int EventProcess(vector<vigra::BRGBImage*> *pInPara, char *pOutPara=NULL)
	{
//		string picName= "./hello.jpg";
//		exportImage(vigra::srcImageRange(*pInPara), vigra::ImageExportInfo(picName.c_str()).setCompression("80"));
		cout<<"threadid="<<pthread_self()<<"  vectorSize: "<<pInPara->size()<<endl;

        CImageTrans imageTrans(1920,1080);
        imageTrans.exportAImage(pInPara->front(),"./");
//
//        unsigned char* pYUV420P=new unsigned char[640*480*3/2];
//        imageTrans.BRGBImage2YUV420p(pInPara->front(),pYUV420P);
//        encoder->init();
//		encoder->encodeYuv(pYUV420P);


//        ofstream out("a.yuv");
//        out.write((const char*)pYUV420P,640*480*3/2);

//		printf(" is dealing with \"%s\"\n",pInPara );
		return 0;
	}
};


using namespace std;

int main(int argc, char** argv)
{
	//-------------------------------------------------------
	// CLog *pLog=new CLocalThreadLog("../log/testThreadLog");
	// pLog->Open();
	// pLog->WriteErrorLog("error log hello ");
	// //----------------------------------------------------------------
	// CConfig *pConfig = CSimpleConfig::GetFirstSingleton("../config/testconfig");
    // pConfig->ParseFile();
	// string a;
	// pConfig->GetParaValue("a", a);
	// cout << "string a = "+a;
	//-----------------------------------------------------------------

    int width = 1920;
    int height = 1080;

    CMsgQueue * msgQueue1=new CMsgQueue(1001);
    CMsgQueue * msgQueue2=new CMsgQueue(1002);
    CMsgQueue * msgQueue3=new CMsgQueue(1003);
    CMsgQueue * msgQueue4=new CMsgQueue(1004);

    CEncoder* encoder = new CEncoder(width,height,"ds.h264");
    encoder->init();

    CImageTrans* imageTrans=new CImageTrans(width,height,"./image/");

	int i=1;
	CReator *pReator = CReator::Instance();

	CEventObserver *pObserver = new CWkObserver(i);
	if( !(pReator->RegisterObserver(pObserver->GetEventHandle(), pObserver)) )
	{ cout<<pReator->GetError()<<endl; }


	CThreadPool *pThreadPool = new COutDataWkThreadPool(pReator);
	if( !pThreadPool->Init() )
		{ cout<<"fail in create COutDataWkThreadPool"<<endl; return -1;}


    Message tTest;
//    Message tTest2;
//            Message tTest3;
	while(1)
	{
		try
		{
			sleep(1);
            vector<vigra::BRGBImage*> images;
			// tTest.msg_type=1;
			// snprintf(tTest.pPara,10, "hello %d para from queue",i);

            msgQueue1->receiveMsg(&tTest,0);
            imageTrans->transform((const unsigned char *) tTest.pPara);
            imageTrans->exportAImage();
            images.push_back(imageTrans->getBRGBImage());

            msgQueue2->receiveMsg(&tTest,0);
            imageTrans->transform((const unsigned char *) tTest.pPara);
            imageTrans->exportAImage();
            images.push_back(imageTrans->getBRGBImage());

            msgQueue3->receiveMsg(&tTest,0);
            imageTrans->transform((const unsigned char *) tTest.pPara);
            imageTrans->exportAImage();
            images.push_back(imageTrans->getBRGBImage());

            msgQueue4->receiveMsg(&tTest,0);
            imageTrans->transform((const unsigned char *) tTest.pPara);
            imageTrans->exportAImage();
            images.push_back(imageTrans->getBRGBImage());


//			pThreadPool->DispatchEvent( (void *)imageTrans->getBRGBImage() );

//			pThreadPool->DispatchEvent( (void *)&tTest );
            pThreadPool->DispatchEvent( (void *)&images);
			i++;
		}
		catch(CException &ex)
		{ cout<<"======"<<ex.GetError()<<endl;}
	}
	return 0;
}
