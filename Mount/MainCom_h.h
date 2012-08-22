

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Aug 22 17:58:28 2012
 */
/* Compiler settings for .\MainCom.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MainCom_h_h__
#define __MainCom_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITrueCryptMainCom_FWD_DEFINED__
#define __ITrueCryptMainCom_FWD_DEFINED__
typedef interface ITrueCryptMainCom ITrueCryptMainCom;
#endif 	/* __ITrueCryptMainCom_FWD_DEFINED__ */


#ifndef __TrueCryptMainCom_FWD_DEFINED__
#define __TrueCryptMainCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrueCryptMainCom TrueCryptMainCom;
#else
typedef struct TrueCryptMainCom TrueCryptMainCom;
#endif /* __cplusplus */

#endif 	/* __TrueCryptMainCom_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "Password.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TrueCryptMainCom_LIBRARY_DEFINED__
#define __TrueCryptMainCom_LIBRARY_DEFINED__

/* library TrueCryptMainCom */
/* [version][helpstring][uuid] */ 


EXTERN_C const IID LIBID_TrueCryptMainCom;

#ifndef __ITrueCryptMainCom_INTERFACE_DEFINED__
#define __ITrueCryptMainCom_INTERFACE_DEFINED__

/* interface ITrueCryptMainCom */
/* [helpstring][oleautomation][object][uuid] */ 


EXTERN_C const IID IID_ITrueCryptMainCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("252C9DE6-D4B9-4A59-8A10-9CA73217B3D0")
    ITrueCryptMainCom : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE AnalyzeKernelMiniDump( 
            LONG_PTR hwndDlg) = 0;
        
        virtual int STDMETHODCALLTYPE BackupVolumeHeader( 
            LONG_PTR hwndDlg,
            BOOL bRequireConfirmation,
            BSTR lpszVolume) = 0;
        
        virtual DWORD STDMETHODCALLTYPE CallDriver( 
            DWORD ioctl,
            BSTR input,
            BSTR *output) = 0;
        
        virtual int STDMETHODCALLTYPE ChangePassword( 
            BSTR volumePath,
            Password *oldPassword,
            Password *newPassword,
            int pkcs5,
            LONG_PTR hWnd) = 0;
        
        virtual DWORD STDMETHODCALLTYPE CopyFile( 
            BSTR sourceFile,
            BSTR destinationFile) = 0;
        
        virtual DWORD STDMETHODCALLTYPE DeleteFile( 
            BSTR file) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsPagingFileActive( 
            BOOL checkNonWindowsPartitionsOnly) = 0;
        
        virtual DWORD STDMETHODCALLTYPE ReadWriteFile( 
            BOOL write,
            BOOL device,
            BSTR filePath,
            BSTR *bufferBstr,
            unsigned __int64 offset,
            unsigned __int32 size,
            DWORD *sizeDone) = 0;
        
        virtual DWORD STDMETHODCALLTYPE RegisterFilterDriver( 
            BOOL registerDriver,
            int filterType) = 0;
        
        virtual DWORD STDMETHODCALLTYPE RegisterSystemFavoritesService( 
            BOOL registerService) = 0;
        
        virtual int STDMETHODCALLTYPE RestoreVolumeHeader( 
            LONG_PTR hwndDlg,
            BSTR lpszVolume) = 0;
        
        virtual DWORD STDMETHODCALLTYPE SetDriverServiceStartType( 
            DWORD startType) = 0;
        
        virtual DWORD STDMETHODCALLTYPE WriteLocalMachineRegistryDwordValue( 
            BSTR keyPath,
            BSTR valueName,
            DWORD value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrueCryptMainComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrueCryptMainCom * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrueCryptMainCom * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrueCryptMainCom * This);
        
        void ( STDMETHODCALLTYPE *AnalyzeKernelMiniDump )( 
            ITrueCryptMainCom * This,
            LONG_PTR hwndDlg);
        
        int ( STDMETHODCALLTYPE *BackupVolumeHeader )( 
            ITrueCryptMainCom * This,
            LONG_PTR hwndDlg,
            BOOL bRequireConfirmation,
            BSTR lpszVolume);
        
        DWORD ( STDMETHODCALLTYPE *CallDriver )( 
            ITrueCryptMainCom * This,
            DWORD ioctl,
            BSTR input,
            BSTR *output);
        
        int ( STDMETHODCALLTYPE *ChangePassword )( 
            ITrueCryptMainCom * This,
            BSTR volumePath,
            Password *oldPassword,
            Password *newPassword,
            int pkcs5,
            LONG_PTR hWnd);
        
        DWORD ( STDMETHODCALLTYPE *CopyFile )( 
            ITrueCryptMainCom * This,
            BSTR sourceFile,
            BSTR destinationFile);
        
        DWORD ( STDMETHODCALLTYPE *DeleteFile )( 
            ITrueCryptMainCom * This,
            BSTR file);
        
        BOOL ( STDMETHODCALLTYPE *IsPagingFileActive )( 
            ITrueCryptMainCom * This,
            BOOL checkNonWindowsPartitionsOnly);
        
        DWORD ( STDMETHODCALLTYPE *ReadWriteFile )( 
            ITrueCryptMainCom * This,
            BOOL write,
            BOOL device,
            BSTR filePath,
            BSTR *bufferBstr,
            unsigned __int64 offset,
            unsigned __int32 size,
            DWORD *sizeDone);
        
        DWORD ( STDMETHODCALLTYPE *RegisterFilterDriver )( 
            ITrueCryptMainCom * This,
            BOOL registerDriver,
            int filterType);
        
        DWORD ( STDMETHODCALLTYPE *RegisterSystemFavoritesService )( 
            ITrueCryptMainCom * This,
            BOOL registerService);
        
        int ( STDMETHODCALLTYPE *RestoreVolumeHeader )( 
            ITrueCryptMainCom * This,
            LONG_PTR hwndDlg,
            BSTR lpszVolume);
        
        DWORD ( STDMETHODCALLTYPE *SetDriverServiceStartType )( 
            ITrueCryptMainCom * This,
            DWORD startType);
        
        DWORD ( STDMETHODCALLTYPE *WriteLocalMachineRegistryDwordValue )( 
            ITrueCryptMainCom * This,
            BSTR keyPath,
            BSTR valueName,
            DWORD value);
        
        END_INTERFACE
    } ITrueCryptMainComVtbl;

    interface ITrueCryptMainCom
    {
        CONST_VTBL struct ITrueCryptMainComVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrueCryptMainCom_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrueCryptMainCom_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrueCryptMainCom_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrueCryptMainCom_AnalyzeKernelMiniDump(This,hwndDlg)	\
    ( (This)->lpVtbl -> AnalyzeKernelMiniDump(This,hwndDlg) ) 

#define ITrueCryptMainCom_BackupVolumeHeader(This,hwndDlg,bRequireConfirmation,lpszVolume)	\
    ( (This)->lpVtbl -> BackupVolumeHeader(This,hwndDlg,bRequireConfirmation,lpszVolume) ) 

#define ITrueCryptMainCom_CallDriver(This,ioctl,input,output)	\
    ( (This)->lpVtbl -> CallDriver(This,ioctl,input,output) ) 

#define ITrueCryptMainCom_ChangePassword(This,volumePath,oldPassword,newPassword,pkcs5,hWnd)	\
    ( (This)->lpVtbl -> ChangePassword(This,volumePath,oldPassword,newPassword,pkcs5,hWnd) ) 

#define ITrueCryptMainCom_CopyFile(This,sourceFile,destinationFile)	\
    ( (This)->lpVtbl -> CopyFile(This,sourceFile,destinationFile) ) 

#define ITrueCryptMainCom_DeleteFile(This,file)	\
    ( (This)->lpVtbl -> DeleteFile(This,file) ) 

#define ITrueCryptMainCom_IsPagingFileActive(This,checkNonWindowsPartitionsOnly)	\
    ( (This)->lpVtbl -> IsPagingFileActive(This,checkNonWindowsPartitionsOnly) ) 

#define ITrueCryptMainCom_ReadWriteFile(This,write,device,filePath,bufferBstr,offset,size,sizeDone)	\
    ( (This)->lpVtbl -> ReadWriteFile(This,write,device,filePath,bufferBstr,offset,size,sizeDone) ) 

#define ITrueCryptMainCom_RegisterFilterDriver(This,registerDriver,filterType)	\
    ( (This)->lpVtbl -> RegisterFilterDriver(This,registerDriver,filterType) ) 

#define ITrueCryptMainCom_RegisterSystemFavoritesService(This,registerService)	\
    ( (This)->lpVtbl -> RegisterSystemFavoritesService(This,registerService) ) 

#define ITrueCryptMainCom_RestoreVolumeHeader(This,hwndDlg,lpszVolume)	\
    ( (This)->lpVtbl -> RestoreVolumeHeader(This,hwndDlg,lpszVolume) ) 

#define ITrueCryptMainCom_SetDriverServiceStartType(This,startType)	\
    ( (This)->lpVtbl -> SetDriverServiceStartType(This,startType) ) 

#define ITrueCryptMainCom_WriteLocalMachineRegistryDwordValue(This,keyPath,valueName,value)	\
    ( (This)->lpVtbl -> WriteLocalMachineRegistryDwordValue(This,keyPath,valueName,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrueCryptMainCom_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TrueCryptMainCom;

#ifdef __cplusplus

class DECLSPEC_UUID("CECBC0EE-78D9-41E6-BCF1-BC222BB224BA")
TrueCryptMainCom;
#endif
#endif /* __TrueCryptMainCom_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


