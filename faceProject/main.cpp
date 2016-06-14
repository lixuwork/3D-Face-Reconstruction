#include "CDxUtil.h"
#include "CAsmUtil.h"
void helpInfo(){
	printf("2d picture to 3d model\n");
	printf("-i set the image\n");
	printf("-m set the model\n");
	printf("-h set the haarcascade\n");
	printf("example:faceProject -i img.jpg -m asm.amf -h haarcascade_frontalface_alt2.xml\n");
}

int main(int argc, char *argv[]){

	//ͼ��ģ�͡���harr�������Ŀ¼
	char* img_add=NULL;
	char* model_add=NULL;
	char* haar_add=NULL;
	if(argc==1){
		helpInfo();
		return 0;
	}
	for(int i=1;i<argc;++i){
		if(argv[i][0]!='-'&&argv[i][2]!='\0'&&i!=argc){
			helpInfo();
			return 0;
		}
		switch (argv[i][1])
		{
		case 'i':
			img_add=argv[i+1];
			++i;
			break;
		case 'm':
			model_add=argv[i+1];
			++i;
			break;
		case 'h':
			haar_add=argv[i+1];
			++i;
			break;
		default:
			break;
		}
	}
	if(img_add==NULL||model_add==NULL||haar_add==NULL){
		helpInfo();
		return 0;
	}
	
	//asm
	CASMUTIL asmUtil(model_add,haar_add);	//����ģ�ͺ�harr�����
	asmUtil.fit(img_add,true);	//���������������׼
	
	//dx
	CDXUTIL dxUtil;
	dxUtil.createFaceBuffer(asmUtil.getPointList(),
		asmUtil.getPointIndex(),
		asmUtil.getNumPrim(),
		asmUtil.getTextureWidth(),
		asmUtil.getTextureHeight(),
		img_add);
	dxUtil.go();
	return 0;
}