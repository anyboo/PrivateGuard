// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _I_CLEANPROC_H_
#define  _I_CLEANPROC_H_

//ע���ɨ�������ص���������
typedef BOOL (WINAPI *ScanRegCallBack)  (void* pMain,int iType,LPCTSTR lpcszKeyFullPath,LPCTSTR lpcszValueName,LPCTSTR lpcszValueData);
typedef BOOL (WINAPI *ScanRegCallBackError)  (void* pMainError,int iType,LPCTSTR lpcszKeyFullPathError,LPCTSTR lpcszValueNameError);

//�ļ�ɨ�������ص���������
typedef BOOL (WINAPI *ScanFileCallBack) (void* pMainError,int iType,LPCTSTR lpcszFileFullPath,DWORD dwFileLowPart,LONG dwFileHighPart);
typedef BOOL (WINAPI *ScanFileCallBackError) (void* pMainError,int iType,LPCTSTR lpcszFileFullPath,DWORD dwFileLowPart,LONG dwFileHighPart);


/************************************************************************/
//ע�������ṹ
/************************************************************************/
//����ע���ṹ��׼C�ӿ�

typedef struct _RegInfo
{	
	int			iType;
	TCHAR		szKeyFullPath[MAX_PATH*4];
	TCHAR		szValueName[MAX_PATH*4];

}RegInfo;

//����ע���ṹ�Ǳ�׼C�ӿ�(�ڲ�ʹ��)
typedef struct _RegInfo_in
{	
	int			iType;
	CString		strKeyFullPath;
	CString		strValueName;

}RegInfo_in;

typedef CSimpleArray<RegInfo_in>		VEC_REGINFO;


/************************************************************************/
//�ļ�����ṹ
/************************************************************************/
//�����ļ��ṹ��׼C�ӿ�
typedef struct _FileInfo
{	
	int			iType;
	TCHAR		szFileFullPath[MAX_PATH*4];

}FileInfo;

//�����ļ��ṹ�Ǳ�׼C�ӿ�(�ڲ�ʹ��)
typedef struct _FileInfo_in
{	
	int			iType;
	CString		strFileFullPath;

}FileInfo_in;

typedef CSimpleArray<FileInfo_in>		VEC_FILEINFO;



/************************************************************************/
//�����ļ�ͨ����ṹ
/************************************************************************/

//��׼C�ӿ�
typedef struct  _FILEEXTS
{
	int			iType;						//����
	TCHAR		szFileExts[MAX_PATH*4];		//�ļ�ͨ���

}FILEEXTS,*PFILEEXTS;

typedef struct  _SCANPATH
{	
	int			iType;						//����ɨ��·��
	TCHAR		szScanFile[MAX_PATH*4];		//�ļ�·��

}SCANPATH,*PSCANPATH;


typedef struct  _GARBAINFO
{
	PFILEEXTS	pFileExts;
	int			iExitsCount;

	PSCANPATH   pScanPath;
	int			iPathCount;

}GARBAINFO;


//�Ǳ�׼C�ӿ��ڲ�ʹ��
typedef struct  _FILEEXTS_IN					
{
	int			iType;				//����
	CString		strFileExts;		//�ļ�ͨ���

}FILEEXTS_IN;


typedef struct  _SCANPATH_IN
{	
	int			iType;				//����ɨ��·��
	CString		strScanFile;		//�ļ�·��

}SCANPATH_IN;

typedef struct  _GARBAINFO_IN
{
	CSimpleArray<FILEEXTS_IN>		vec_fileExtsInfo;
	CSimpleArray<SCANPATH_IN>		vec_scanPathInfo;

}GARBAINFO_IN;


//����ӿ�
class __declspec(uuid("0E2D6083-2A33-4c8e-9940-ECF0657880FF")) IKClearProc
{
public:
	virtual void DZ_SetCleanCallBack(ScanRegCallBack fnRegCallBack,ScanFileCallBack fnFileCallBack,void* pMain) = 0;
	virtual void DZ_SetCleanCallBackError(ScanRegCallBackError fnRegCallBackError,ScanFileCallBackError fnFileCallBackError,void* pMainError) = 0;

	virtual BOOL DZ_StartScan(int* iType,int iCount) = 0;
	virtual BOOL DZ_StopScan() = 0;

	virtual BOOL DZ_StartScanBage(GARBAINFO* garbInfo) =0;
	virtual BOOL DZ_StopScanBage()=0;

	virtual BOOL DZ_CleanReg(RegInfo* pRegInfo,int iCount) =0;
	virtual BOOL DZ_CleanFile(FileInfo* pFileInfo,int iCount)=0;

	virtual void DZ_IsScanClean(BOOL bClean=FALSE) = 0;

	virtual BOOL DZ_ResetRegsiter(LPCTSTR strRegFilePath=NULL)=0;
	virtual BOOL DZ_GetNoinstallApp(int n) = 0;
};


/************************************************************************/
//�������Ͷ���
/************************************************************************/
#define	CLEAN_COMPATE						0000			//ɨ�����

#define BEGINPROC(x)						(x+100)
#define ENDPROC(x)							(x+200)
#define SCANING(x)							(x+300)

#define IECLEAN								1000
#define	IECLEAN_TEMPFOLDER					1001			//ie��ʱ�ļ���
#define	IECLEAN_VISITHOST					1002			//������ַ��¼
#define IECLEAN_COOKIE						1003			//cookie�ļ���
#define IECLEAN_ADDRBSR						1004			//��ַ��
#define IECLEAN_INDEXDATA					1005			//���index.data	
#define IECLEAN_HISTORY                     1006
#define MAXTHON_COOKIES                     1007             //maxthon cooies
#define THEWORLD_COOKIES                    1008

#define WINSHISTORY							2000
#define WINSHISTORY_RUNDLG					2001			//���жԻ���
#define WINSHISTORY_RUNHISTORY				2002			//������ʹ���Ŀ¼
#define WINSHISTORY_OPENSAVE				2003			//���뱣���¼
#define WINSHISTORY_WINSIZE					2004			//�������С
#define WINSHISTORY_RECENTDOCREG			2005			//���ʹ�õ��ĵ���¼(ע���)
#define WINSHISTORY_RECENTDOCFILE			2005			//���ʹ�õ��ĵ���¼(�ļ�)
#define WINSHISTORY_FILEEXTS				2007			//�ļ���չ����ʷ��¼
#define WINSHISTORY_USERASSIST				2008			//����򿪳�����ʷ��¼
#define WINSHISTORY_TRAYNOTIFY				2009			//֪ͨ����ͼ����ʷ��¼
#define WINSHISTORY_NETERIVE				2010			//����������ӳ�� 
#define WINSHISTORY_FINDCMP					2011			//���Ҽ����
#define WINSHISTORY_FINDDOC					2012			//�����ĵ�
#define WINSHISTORY_PRTPORT					2013			//��ӡ�˿�
#define WINSHISTORY_WINLOG					2014			//windows��־�ļ�
#define WINSHISTORY_WINTEMP					2015			//windows��ʱ�ļ���
#define WINSHISTORY_REGEDIT					2016			//ע��������ʵ�λ��
#define	WINSHISTORY_STREAM					2017			//�����ע�����

//����
#define GOOGL_TOOLBAR						2018			//google������
#define BAIDU_TOOLBAR						2019            //�ٶȹ�����������¼
#define QQ_TOOLBAR                          2034            //QQ������������¼
#define WINLIVE_TOOLBAR                     2035            //Windows Live������������¼

#define WINSHISTORY_PRGHISTORY				2020			//������ʼ�¼
#define MEMORY_DMP							2021			//�ڴ�ת��
#define	WINSHISTORY_CLIPBOARD				2029			//������
#define WINDOWS_RECYCLE                     2030            //����վ
#define WINDOWS_SEARCH                      2031            //Windows ������¼
#define WINDOWS_NETHOOD                     2032            //Windows �����ھ�
#define WINDOWS_JUMPLIST                    2033            //Windows 7 ��ת�б�
#define WINDOWS_SUOLIETU                    2036            //����ͼ����
//����ʵ��
//���� 2022-2029



#define REGCLEAN							3000
#define REGCLEAN_INVALIDDLL					3001			//��Ч��̬���ӿ�
#define REGCLEAN_INVALIDMENU				3002			//��Ч�Ҽ��˵�
#define REGCLEAN_INVALIDAPPPATH				3003			//��Ч��Ӧ�ó���·��
#define REGCLEAN_INVALIDFIRE				3004			//��Ч�ķ���ǽ
#define REGCLEAN_INVALIDMUI					3005			//��ЧMUI����
#define REGCLEAN_INVALIDHELP				3006			//��Ч�İ����˵�
#define REGCLEAN_INVALIDFONT				3007			//��Ч����Ϊʵ��
#define REGCLEAN_INVALIDINSTALL				3008			//��Ч�İ�װ����
#define REGCLEAN_INVALIDUNINSTALL			3009			//��Ч�ķ���װ����
#define REGCLEAN_INVALIDSTARTMENU			3010			//��Ч�Ŀ�ʼ�˵�
#define REGCLEAN_INVALIDSTARTSRUN			3011			//��Ч��������Ŀ
#define REGCLEAN_FAILACTIVEX				3012			//�����ActiveX��Ϣ
#define REGCLEAN_FAILAFILEASS				3013			//������ļ�����
#define REGCLEAN_FAILCLASS					3014			//���������Ϣ
#define REGCLEAN_REDUNDANCY					3015			//������Ϣ


#define FILEGARBAGE							4000
#define	FILEGARBAGE_RECYCLED				4001			//����վ����
#define FILEGARBAGE_STARTMENULINK			4002			//��Ч�Ŀ�ʼ�˵���ݷ�ʽ
#define FILEGARBAGE_DESKTOPLINK				4003			//��Ч�������ݷ�ʽ
#define FILEGARBAGE_INVALIDDIR				4004			//���õ�Ŀ¼	<δʵ��,δ����>
#define FILEGARBAGE_EXTS					4005			//������չ������ɨ��


#define BROWSERSCLEAN						5000			
#define BROWSERSCLEAN_CHROME				5001			//�ȸ����������
#define	BROWSERSCLEAN_FIREFOX				5002			//��������
#define BROWSERSCLEAN_MAXTHON				5003			//���������
#define	BROWSERSCLEAN_TT					5004			//��ѶTT�����
#define BROWSERSCLEAN_360					5005			//360�����
#define BROWSERSCLEAN_WORDWIN				5006			//����֮��
#define BROWSERSCLEAN_MYIE2					5007			//MYIE2
#define BROWSERSCLEAN_SOGO                  5008            //SOGO�ѹ��������ʷ��¼
#define SOGO_COOKIES                        5009            //�ѹ��������ʷ��¼
#define SOGO_FORM                           5010            //�ѹ�������Զ�����ı�
#define SOGO_PASS                           5011            //�ѹ�������Զ����������
#define SOGO_ADVFORM                        5012            //�ѹ����������������ѱ���ı�

#define BROWSERSCLEAN_OPERA                  5013            //Opera�������ʷ��¼
#define OPERA_COOKIES                       5014            //Opera�����Cookies
#define OPERA_FORM                          5015            //Opera������Զ����������

#define IECLEAN_PASSWORD					6001			//ie����
#define IECLEAN_SAVEFROM					6002			//ie�����

#define CHROME_PASSWORD						6003			//chrome����
#define CHROME_SAVEFROM						6004			//chrome��

#define FIREFOX_PASSWORD					6005			//firefox����
#define FIREFOX_SAVEFROM					6006			//firefox��

#define PASSANDFROM_360						6007			//360������û�����

#define	WORDWIN_USER						6008			//����֮���û�����
#define FIREFOX_COOKIES                     6009            //firefox cookies
#define CHROME_COOKIES                      6010            //chrome cookies
#define TECENT_PASSANDFORM                  6011             //TT��������
#define THEWORLD_PASS                       6012              // THE WORLD pass
#define THEWORLD_FORM                       6013             //THE WORLD   from
#define MAXTHON_FORM                        6014             //�����Զ���
#define MAXTHON_PASS                        6015             //��������
#define PASSANDFROM_TT                      6016              //TT


//����IM��Ϣ����
//���� 7001~7005

// ���ع���
#define THUNDERDOWNLOADER                   9037			//Ѹ������
#define FLASHGETDOWNLOADER                  9038			//FlashGet����
#define BITCOMETDOWNLOADER                  9039			//BitComet����
#define QQDOWNLOADER                        9044            //QQ����

#define PPS_PLAYER                          9041            //PPS ������
#define PPTV_PLAYER                         9042            //PPTV ������
#define QVOD_PLAYER                         9043            //QVOD ������
#define FENGXING_PLAYER                     9045            // fengxing
#define SHESHOU_PLAYER                      9046            //sheshou
#define KUWOMUSIC_PLAYER                    9047             //�������ֺ�
#define FUXINPDF_READER                     9048             //���PDF�Ķ�����ʷ��¼

#define ALIIM_IM                            9049             //����������¼��Ϣ
#define WINLIVE_MSG                         9050             //WINDOWS LIVES MESSAGER
#define XUNLEI7_DOWNLOADER                  9051             //Ѹ��7

#endif