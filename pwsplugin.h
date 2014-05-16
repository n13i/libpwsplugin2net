#ifndef PWSPluginH
#define PWSPluginH

#include <windows.h>
#include "pwsRTValue.h"

#define DLLSPEC extern "C" __declspec( dllexport )

//使用する型の宣言
#define MS_NORMAL 0
#define MS_CHECK 0
#define MS_GROUP 1
#define MS_SEPARATOR 2

#define TM_ONESHOT  0
#define TM_INTERVAL 1

//#define TArgTypeid      DWORD
#define TYPE_CHAR       0x01
#define TYPE_INT        0x02
#define TYPE_DOUBLE     0x03
#define TYPE_STRING     0x04
#define TYPE_BOOLEAN    0x05

//呼び出しスタイル
#define CS_ACTION 0x01
#define CS_WAITFORACTIONEND 0x02
#define CS_CRITICALACTION 0x03
#define CS_INVOKE 0x04
#define CS_INTERRUPT 0x05

//アプリケーションウィンドウ
#define WHT_APPLICATION 0x01
//ペルソナウインドウ
#define WHT_PERSONA     0x02
//吹き出しウインドウ
#define WHT_MESSAGEBOX  0x03

typedef enum {
    AYAF_NONE = 0x00,
    AYAF_SUCCEED,
    AYAF_CANCEL,
    AYAF_FATAL_ERROR
} exit_state_t;

#pragma pack(push, 1 )
struct TPWPInstance {
    void* pdata;        //プラグイン側データ格納ポインタ
    //システムデータ(プラグイン側で操作してはいけない)
    //TInstanceSet構造体のアドレスが入る
    void* sdata;
};

#pragma pack( pop )

typedef DWORD TPWPTimerHandle;

//コールバック関数のtypedef宣言
typedef void (__stdcall *TPWCMenuProc ) ( TPWPInstance* instance, const char *item );
typedef void (__stdcall *TPWCTimerProc ) ( TPWPInstance* instance, TPWPTimerHandle handle, DWORD param  );
typedef void (__stdcall *TPWCPluginProc )( TPWPInstance* instance, DWORD param );
typedef void (__stdcall *TPWCPluginProc2)( TPWPInstance* instance, const char* pcArgType, IRTValue** pArgs, int nArg, IRTValue* pRetval, DWORD param );
typedef int  (__stdcall *TPWCSynchronizeProc ) ( TPWPInstance *instance, DWORD param );

typedef void (*TPWPInvokeProc)(
    TPWPInstance* instance,
    exit_state_t state,
    DWORD style,
    char* pcType,
    char* pcFname,
    IRTValue* val,
    DWORD param );



//Pluginからexportされる関数のtypedef
typedef BOOL (__stdcall *TPWCInitialize)( int major, int minor, const char* substr , const struct TPWPFunctions* );
typedef void (__stdcall *TPWCDestroy)( );
typedef int  (__stdcall *TPWCNewInstance)( TPWPInstance* , const char* , const char* );
typedef void (__stdcall *TPWCDestroyInstance)( TPWPInstance* );
typedef void (__stdcall *TPWCMouseUpL) ( TPWPInstance* , int , int );
typedef void (__stdcall *TPWCMouseEnter) ( TPWPInstance* , const char* );
typedef void (__stdcall *TPWCDragAndDrop )( TPWPInstance* , DWORD );
typedef void (__stdcall *TPWCDefault)( TPWPInstance* );
typedef void (__stdcall *TPWCActivate)( TPWPInstance* instance , HWND );
typedef void (__stdcall *TPWCDeactivate)( TPWPInstance* instance , HWND );

// for Ver 3.10 or later
typedef void (__stdcall *TPWCMouseUpL2)( TPWPInstance* , const char*, int , int );
typedef void (__stdcall *TPWCMouseEnter2)( TPWPInstance* , const char*, const char* );
typedef void (__stdcall *TPWCDragged2)( TPWPInstance*, const char * );


//PWP関数群のtypedef宣言
typedef  int (__stdcall  *TPWPCall)( TPWPInstance* , DWORD, const char* , const char* , ... );
typedef  int (__stdcall  *TPWPInvoke)( TPWPInstance* , DWORD , char* , char* , TPWPInvokeProc , DWORD , ... );
typedef  BOOL (__stdcall *TPWPExportFunctionExists)( TPWPInstance*, const char* );
typedef  int (__stdcall *TPWPGetReturnType)( TPWPInstance* instance, DWORD*, int* );
typedef  int (__stdcall *TPWPGetReturn)( TPWPInstance*, void*, int );
typedef  int (__stdcall *TPWPRegisterAyaoriFunc)( TPWPInstance* , const char* funcname, TPWCPluginProc func, const char *typestring, DWORD param );
typedef  int (__stdcall *TPWPRegisterAyaoriFunc2)( TPWPInstance* , const char* funcname, TPWCPluginProc2 func, const char *type, DWORD param );
typedef  int (__stdcall *TPWPGetArgumentTypeAt)( TPWPInstance*, DWORD*, int* , int );
typedef  int (__stdcall *TPWPGetArgumentAt)( TPWPInstance*, void* , int , int );
typedef  int (__stdcall *TPWPPushResult)( TPWPInstance*, const void* , DWORD );
typedef  int (__stdcall *TPWPIsBasisState)( TPWPInstance* );
typedef  HWND (__stdcall *TPWPGetWindowHandle)( TPWPInstance* , DWORD );
typedef  int (__stdcall  *TPWPGetExecPersonaVendorSize)( TPWPInstance* );
typedef  void (__stdcall *TPWPGetExecPersonaVendor)( TPWPInstance* , char* );
typedef  int (__stdcall  *TPWPGetExecPersonaTypeSize)( TPWPInstance* );
typedef  void (__stdcall *TPWPGetExecPersonaType)( TPWPInstance* , char* );
typedef  void (__stdcall *TPWPGetPersonaDataFolder)( TPWPInstance* , char* );
typedef  int (__stdcall *TPWPIsOnLine)( void );
typedef  int (__stdcall *TPWPGetPropertySize)( TPWPInstance* , const char* );
typedef  int (__stdcall *TPWPGetProperty)( TPWPInstance* , const char* , char* , int );
typedef  int (__stdcall *TPWPPutProperty)( TPWPInstance* , const char* , const char* );
typedef  BOOL (__stdcall *TPWPPropertyExists)( TPWPInstance* , const char* );
typedef  int (__stdcall *TPWPMakePropertyTree)( TPWPInstance* , const char* , const char* );
typedef  int (__stdcall *TPWPDelPropertyTree)( TPWPInstance* , const char* );
typedef  BOOL (__stdcall *TPWPPropertyTreeExists)( TPWPInstance* , const char* );

typedef int (__stdcall *TPWPMenuItem_Add) ( TPWPInstance *instance, const char *item, int style, BYTE groupID, TPWCMenuProc menucallback );
typedef int (__stdcall *TPWPMenuItem_Insert) ( TPWPInstance *instance, const char *nextitem, const char *item, int style, BYTE groupID, TPWCMenuProc menucallback );
typedef int (__stdcall *TPWPMenuItem_Rename) ( TPWPInstance *instance, const char *item, const char *newname );
typedef int (__stdcall *TPWPMenuItem_Delete) ( TPWPInstance *instance, const char *item );
typedef int (__stdcall *TPWPMenuItem_SetState) ( TPWPInstance *instance, const char *item, BOOL check );
typedef int (__stdcall *TPWPMenuItem_GetState) ( TPWPInstance *instance, const char *item );
typedef int (__stdcall *TPWPMenuItem_SetEnable) ( TPWPInstance *instance, const char *item, BOOL enable );
typedef int (__stdcall *TPWPMenuItem_GetEnable) ( TPWPInstance *instance, const char *item );
typedef int (__stdcall *TPWPMenuItem_SetVisible) ( TPWPInstance *instance, const char *item, BOOL visible );
typedef int (__stdcall *TPWPMenuItem_GetVisible) ( TPWPInstance *instance, const char *item );
typedef const char* (__stdcall *TPWPMenuItem_GetSelect) ( TPWPInstance *instance, const char *item );
typedef const char* (__stdcall *TPWPMenuItem_GetSetupMenuName) ( TPWPInstance *instance );

typedef TPWPTimerHandle (__stdcall *TPWPTimer_Create) ( TPWPInstance *instance, int interval, int mode, TPWCTimerProc timeproc, DWORD param );
typedef int (__stdcall *TPWPTimer_Destroy) ( TPWPTimerHandle handle );
typedef int (__stdcall *TPWPTimer_Start) ( TPWPTimerHandle handle );
typedef int (__stdcall *TPWPTimer_Stop) ( TPWPTimerHandle handle );
typedef int (__stdcall *TPWPTimer_ResetInterval) ( TPWPTimerHandle handle, int interval );

typedef int (__stdcall *TPWPSynchronize) ( TPWPInstance *instance, TPWCSynchronizeProc func, DWORD param );

typedef void (__stdcall *TPWPNormalizeTopMosts) ( TPWPInstance *instance );
typedef void (__stdcall *TPWPRestoreTopMosts) ( TPWPInstance *instance );
typedef void (__stdcall *TPWPWait) ( TPWPInstance *instance, int );

typedef void (__stdcall *TPWPGetPluginFolder) ( TPWPInstance* instance , char* dest );

// for Ver 3.0 or later
typedef IRTValue* (__stdcall *TRTValue_CreateBool) ( BOOL b );
typedef IRTValue* (__stdcall *TRTValue_CreateChar) ( char c );
typedef IRTValue* (__stdcall *TRTValue_CreateInt)  ( int i );
typedef IRTValue* (__stdcall *TRTValue_CreateDouble) ( double d );
typedef IRTValue* (__stdcall *TRTValue_CreateString) ( const char *s );
typedef IRTValue* (__stdcall *TRTValue_CreateRTValue) ( IRTValue* rtv );
typedef IRTValue* (__stdcall *TRTValue_CreateRTArray) ( IRTArray* rta );
typedef IRTArray* (__stdcall *TRTArray_Create) ( const char* dsc );
typedef IRTArray* (__stdcall *TRTArray_Create2) ( const char* dsc, int n );
typedef IRTVarArray* (__stdcall *TRTVarArray_Create) ( const char* dsc );

#pragma pack(push, 1 )
struct TPWPFunctions{
    DWORD size;             //構造体全体のサイズ[Byte]

    //ペルソナ処理系に関する関数
    TPWPCall                        PWPCall;
    TPWPExportFunctionExists        PWPExportFunctionExists;
    TPWPRegisterAyaoriFunc          PWPRegisterAyaoriFunc;
    TPWPGetReturnType               PWPGetReturnType;
    TPWPGetReturn                   PWPGetReturn;
    TPWPGetArgumentTypeAt           PWPGetArgumentTypeAt;
    TPWPGetArgumentAt               PWPGetArgumentAt;
    TPWPPushResult                  PWPPushResult;
    TPWPIsBasisState                PWPIsBasisState;
    TPWPGetWindowHandle             PWPGetWindowHandle;

    //ペルソナに関する関数
    TPWPGetExecPersonaVendorSize    PWPGetExecPersonaVendorSize;
    TPWPGetExecPersonaVendor        PWPGetExecPersonaVendor;
    TPWPGetExecPersonaTypeSize      PWPGetExecPersonaTypeSize;
    TPWPGetExecPersonaType          PWPGetExecPersonaType;
    TPWPGetPersonaDataFolder        PWPGetPersonaDataFolder;

    //ネットワーク関連
    TPWPIsOnLine                    PWPIsOnLine;

    //プロパティ関連
    TPWPGetPropertySize             PWPGetPropertySize;
    TPWPGetProperty                 PWPGetProperty;
    TPWPPutProperty                 PWPPutProperty;
    TPWPPropertyExists              PWPPropertyExists;
    TPWPMakePropertyTree            PWPMakePropertyTree;
    TPWPDelPropertyTree             PWPDelPropertyTree;
    TPWPPropertyTreeExists          PWPPropertyTreeExists;

    //右クリックメニュー関連
    TPWPMenuItem_Add                PWPMenuItem_Add;
    TPWPMenuItem_Insert             PWPMenuItem_Insert;
    TPWPMenuItem_Rename             PWPMenuItem_Rename;
    TPWPMenuItem_Delete             PWPMenuItem_Delete;
    TPWPMenuItem_SetState           PWPMenuItem_SetState;
    TPWPMenuItem_GetState           PWPMenuItem_GetState;
    TPWPMenuItem_SetEnable          PWPMenuItem_SetEnable;
    TPWPMenuItem_GetEnable          PWPMenuItem_GetEnable;
    TPWPMenuItem_SetVisible         PWPMenuItem_SetVisible;
    TPWPMenuItem_GetVisible         PWPMenuItem_GetVisible;
    TPWPMenuItem_GetSelect          PWPMenuItem_GetSelect;
    TPWPMenuItem_GetSetupMenuName   PWPMenuItem_GetSetupMenuName;

    //タイマー関連
    TPWPTimer_Create                PWPTimer_Create;
    TPWPTimer_Destroy               PWPTimer_Destroy;
    TPWPTimer_Start                 PWPTimer_Start;
    TPWPTimer_Stop                  PWPTimer_Stop;
    TPWPTimer_ResetInterval         PWPTimer_ResetInterval;

    //その他
    TPWPSynchronize                 PWPSynchronize;

    //常に手前に表示設定の操作
    TPWPNormalizeTopMosts           PWPNormalizeTopMosts;
    TPWPRestoreTopMosts             PWPRestoreTopMosts;

    TPWPWait                        PWPWait;
    
    TPWPGetPluginFolder             PWPGetPluginFolder;

    // for Ver 3.0 or later
    TRTValue_CreateBool             PWPRTValue_CreateBool;
    TRTValue_CreateChar             PWPRTValue_CreateChar;
    TRTValue_CreateInt              PWPRTValue_CreateInt;
    TRTValue_CreateDouble           PWPRTValue_CreateDouble;
    TRTValue_CreateString           PWPRTValue_CreateString;
    TRTValue_CreateRTValue          PWPRTValue_CreateRTValue;
    TRTValue_CreateRTArray          PWPRTValue_CreateRTArray;
    TRTArray_Create                 PWPRTArray_Create;
    TRTArray_Create2                PWPRTArray_Create2;
    TRTVarArray_Create              PWPRTVarArray_Create;
    TPWPInvoke                      PWPInvoke;
    TPWPRegisterAyaoriFunc2         PWPRegisterAyaoriFunc2;
};
#pragma pack( pop )

#endif
