/*****************************************************************
 filename    :    DevEnumXML.cpp
 author      :    guandiqun
 created     :    2012/11/19
 description :    实现设备组;
 copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
 history     :    2012/11/19 初始版本
*****************************************************************/
#include "DevEnumXML.h"
#include "IVSCommon.h"
#include "wtypes.h"
#include "SDKDef.h"

#ifndef ELEMMAX
#define ELEMMAX 10
#endif

//视频制式的枚举型
const IVS_CHAR chVideoType[][ELEMMAX]  = {"NONE", "PAL", "NTSC"};
const IVS_CHAR chDevType[][ELEMMAX] = {"", "IPC", "DVS", "DVR", "eNVR"};
const IVS_CHAR chResolutionType[][ELEMMAX] = {"", "QCIF", "QVGA", "CIF", "2CIF", "DCIF", "VGA", "4CIF",  "HD1", "D1",
    "SVGA", "XGA", "720P", "XVGA", "SXGA", "USVGA", "UXGA", "1080P", "4096P" };
const IVS_CHAR chFormatType[][ELEMMAX] = {"NONE", "PAL","NTSC"};

const IVS_CHAR chH264ProfileType[][ELEMMAX] = {"", "BP", "EP", "HP", "MP"};
const IVS_CHAR chEnCodeModeCHType[][ELEMMAX] = {"", "H264", "MJPEG", "MPEG4", "MPEG2", "AVS"};
const IVS_CHAR chCommStatus[][ELEMMAX] = {"OFF", "ON"};
const IVS_CHAR chTransType[][ELEMMAX] = {"NONE", "FEC", "ARQ", "HARQ"};
const IVS_CHAR chDataFormat[][ELEMMAX] = {"", "G711A", "G711U", "G726", "AAC"};
const IVS_CHAR chIsOrNot[][ELEMMAX] = {"FALSE", "TRUE"};
const IVS_CHAR chCommMode[][ELEMMAX] = {"AUTO", "MANUAL"};
const IVS_CHAR chExposurePriority[][ELEMMAX] = {"LowNoise", "FrameRate"};
const IVS_CHAR chCommExImgMode[][ELEMMAX] = {"OFF", "ON", "AUTO", "EXTENDED"};

// edit by wanglei 00165153:2013.10.14 DTS2013101404169 【IVS_UINT32 - > IVS_CAMERA_RECORD_STREAM_CFG】
// CONFIG_CAMERA_RECORD_STREAM_CFG 通过SDK接口调用查询前端录像码流参数，会返回109100005操作内存失败
const IVS_UINT32 chSizeOfConfigType[] = {0, 
	sizeof(IVS_DEVICE_CFG),sizeof(IVS_DEVICE_NET_CFG),sizeof(IVS_DEVICE_TIME_CFG),
	sizeof(IVS_CAMERA_CFG),sizeof(IVS_CAMERA_STREAM_CFG),sizeof(IVS_CAMERA_DISPLAY_CFG),
	sizeof(IVS_CAMERA_IMAGING_CFG),sizeof(IVS_CAMERA_OSD_CFG),sizeof(IVS_MOTION_DETECTION),
	sizeof(IVS_VIDEO_HIDE_ALARM),sizeof(IVS_VIDEO_MASK),sizeof(IVS_AUDIO_CFG),
	sizeof(IVS_SERIAL_CHANNEL_CFG),sizeof(IVS_ALARM_IN_CFG),sizeof(IVS_ALARM_OUT_CFG),
	sizeof(IVS_PTZ_CFG),sizeof(IVS_CAMERA_EXTEND_CFG),sizeof(IVS_CAMERA_SNAPSHOT_CFG),
	sizeof(IVS_CAMERA_RECORD_STREAM_CFG),sizeof(IVS_CAMERA_FEC_CFG)
};


// 获取通道类型
IVS_VOID CDevEnumXML::GetChannelType( IVS_INT32 iNum ,IVS_CHAR *pchTemp)
{
	if (NULL == pchTemp)
	{
		BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "GetChannelType fail", "NA");
		return;
	}
   
    memset(pchTemp, 0, 2);
    if (iNum >= 10)
    {
        pchTemp[0] = iNum/10 + 48;//lint !e734
        pchTemp[1] = iNum%10 + 48;        
    }
    else
    {
        pchTemp[0] = '0';
        pchTemp[1] = iNum%10 + 48;
    }

}

// 获取通用状态
const IVS_CHAR* CDevEnumXML::GetCommStatusType( IVS_BOOL bEnable )
{
    if (bEnable)
    {
        return chCommStatus[1];
    }

    return chCommStatus[0];
}

// 获取通用状态
IVS_BOOL CDevEnumXML::GetCommStatusBool(const IVS_CHAR* pCommStatus)
{
    CHECK_POINTER(pCommStatus, IVS_OPERATE_MEMORY_ERROR);
    IVS_BOOL bRet = 1;

    if (0 == strcmp(chCommStatus[0], pCommStatus))
    {
        bRet = 0 ;
    }   

    return bRet;
}

// 获取编码格式
IVS_INT32 CDevEnumXML::GetEnCodeModeEnum(const IVS_CHAR* pCodeMode)
{
	CHECK_POINTER(pCodeMode, IVS_OPERATE_MEMORY_ERROR);

	IVS_INT32 iRet = 0;

	IVS_INT32 iLen = sizeof(chEnCodeModeCHType)/sizeof(chEnCodeModeCHType[0]);
	for (IVS_INT32 i = 0; i < iLen; i++ )
	{
		if (0 == strcmp(chEnCodeModeCHType[i], pCodeMode))
		{
			iRet = i;
		}
	}
	BP_RUN_LOG_INF("Get H264ProfileEnum fail", "VideoType=%d",iRet);

	return iRet;
}

// 获取编码格式
const IVS_CHAR *CDevEnumXML::GetEnCodeModeCH(IVS_INT32 iCodeMode)
{

    IVS_INT32 iMaxLen = sizeof(chEnCodeModeCHType)/sizeof(chEnCodeModeCHType[0]);

    if (iCodeMode > iMaxLen || iCodeMode < 0)
    {
		BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "iCodeMode fail", "NA");
        return "";
    }

    return chEnCodeModeCHType[iCodeMode];
}

// 获取编码格式为H264的Profile
const IVS_CHAR *CDevEnumXML::GetH264ProfileCH(IVS_INT32 iProfile)
{

    IVS_INT32 iMaxLen = sizeof(chH264ProfileType)/sizeof(chH264ProfileType[0]);

    if (iProfile > iMaxLen || iProfile < 0)
    {
		BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "iProfile fail", "NA");
        return "";
    }

    return chH264ProfileType[iProfile];
}

// 获取编码格式为H264的Profile
IVS_INT32 CDevEnumXML::GetH264ProfileEnum(const IVS_CHAR* pH264Profile)
{
    CHECK_POINTER(pH264Profile, IVS_OPERATE_MEMORY_ERROR);

    IVS_INT32 iRet = 0;

    IVS_INT32 iLen = sizeof(chH264ProfileType)/sizeof(chH264ProfileType[0]);
    for (IVS_INT32 i = 0; i < iLen; i++ )
    {
        if (0 == strcmp(chH264ProfileType[i], pH264Profile))
        {
            iRet = i;
        }
    }
    BP_RUN_LOG_INF("Get VideoFormatEnum fail", "VideoType=%d",iRet);

    return iRet;
}

// 获取视频制式的枚举型
IVS_INT32 CDevEnumXML::GetVideoFormatEnum(const IVS_CHAR* pVideoType )
{
    CHECK_POINTER(pVideoType, IVS_OPERATE_MEMORY_ERROR);

    IVS_INT32 iRet = 0;
    IVS_INT32 iLen = sizeof(chVideoType)/sizeof(chVideoType[0]);
    for (IVS_INT32 i = 0; i < iLen; i++ )
    {
        if (0 == strcmp(chVideoType[i], pVideoType))
        {
            iRet = i;
        }
    }
    BP_RUN_LOG_INF("Get VideoFormatEnum fail", "VideoType=%d",iRet);

    return iRet;
}

// 获取视频制式的枚举型
const IVS_CHAR* CDevEnumXML::GetVideoFormatType( const IVS_INT32 iFormatType )
{

    IVS_INT32 iMaxLen = sizeof(chFormatType)/sizeof(chFormatType[0]);

    if (iFormatType > iMaxLen || iFormatType < 0)
    {
		BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "iFormatType fail", "NA");
		return "";
	}

    return chFormatType[iFormatType];
}

// 获取镜头码流分辨率
const IVS_CHAR *CDevEnumXML::GetResolutionCH(IVS_INT32 iResolution)
{
    IVS_INT32 iMaxLen = sizeof(chResolutionType)/sizeof(chResolutionType[0]);

    if (iResolution > iMaxLen || iResolution < 0)
    {
		BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "iResolution fail", "NA");
        return "";
    }

    return chResolutionType[iResolution];
}

// 获取镜头码流分辨率
IVS_INT32 CDevEnumXML::GetResolutionEnum(const IVS_CHAR*pResolution)
{
	CHECK_POINTER(pResolution, IVS_OPERATE_MEMORY_ERROR);

    IVS_INT32 iRet = 0;

    IVS_INT32 iLen = sizeof(chResolutionType)/sizeof(chResolutionType[0]);
    for (IVS_INT32 i = 0; i < iLen ; i ++)
    {
        if (0 == strcmp(chResolutionType[i], pResolution))
        {
            iRet = i;
        }
    }  

    BP_RUN_LOG_INF("Get ResolutionEnum", "resolution=%d",iRet);

    return iRet;
}

// 根据类型获取
const IVS_CHAR* CDevEnumXML::GetDevType(IVS_INT32 iDeviceType)
{

    IVS_INT32 iMaxLen = sizeof(chDevType)/sizeof(chDevType[0]);

    if (iDeviceType > iMaxLen || iDeviceType < 0)
    {
		BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "iDeviceType fail", "NA");
        return "";
    }

    return chDevType[iDeviceType];
}

// 根据类型获取
IVS_INT32 CDevEnumXML::GetDevTypeEnum( const IVS_CHAR* pDeviceType )
{
	CHECK_POINTER(pDeviceType, IVS_OPERATE_MEMORY_ERROR);

    IVS_INT32 iRet = 0;
    IVS_INT32 iLen = sizeof(chDevType)/sizeof(chDevType[0]);
    for (IVS_INT32 i = 0; i < iLen ; i ++)
    {
        if (0 == strcmp(chDevType[i], pDeviceType))
        {
            iRet = i;
        }
    }  
    BP_RUN_LOG_INF("Get ResolutionEnum fail", "resolution=%d",iRet);

    return iRet;
}

//获取排序的枚举型
IVS_BOOL CDevEnumXML::GetOrderTypeBool( const IVS_CHAR* pLoginType )
{

    CHECK_POINTER(pLoginType, IVS_OPERATE_MEMORY_ERROR);

    if (0 == strcmp(pLoginType, "DOWN"))
    {
        return 0;
    }

    return  1;
}
// 获取Field的枚举型
IVS_BOOL CDevEnumXML::GetFieldEnum(const IVS_CHAR* pFieldType)
{
    CHECK_POINTER(pFieldType, IVS_OPERATE_MEMORY_ERROR);

    if (0 == strcmp(pFieldType, "EXACT"))
    {
        return 0;
    }

    return  1;
}

// 获取告警类型
const IVS_BOOL CDevEnumXML::GetAlamTypeEnum(const IVS_CHAR*  cAlam )
{

    if (0 == strcmp("1",cAlam))
    {
        return 1;
    }

    return 0;   
}

// 获取告警类型
const IVS_CHAR* CDevEnumXML::GetAlamTypeCH(  IVS_BOOL bAlam )
{

	if (bAlam)
	{
		return "1";
	}

	return "0";   
}

// 获取正反向控制
const IVS_CHAR *CDevEnumXML::GetPosNegDirCtlCH(bool bPosNegDirCtl)
{
    if (bPosNegDirCtl)
    {
        return "FORWARD";
    }
    else
    {
		return "BACK";
    }
}

// 获取码率类型
const IVS_CHAR *CDevEnumXML::GetBitRateTypeCH(IVS_INT32 bitRateType)
{
    const IVS_CHAR *result = "";
    switch (bitRateType)
    {
    case BITRATE_CBR:
        result = "CBR";
        break;
    case BITRATE_VBR:
        result = "VBR";
        break;
    default:;
    }

    return result;
}

// 获取编码格式为MJPEG的Profile
const IVS_CHAR *CDevEnumXML::GetMjpegProfileCH(IVS_INT32 profile)
{

    const IVS_CHAR* result = "";
    switch (profile)
    {
    case MJPEG_PROFILE_SP:
        result ="SP";
        break;
    case MJPEG_PROFILE_ASP:
        result ="ASP";
        break;
    default:;
    }

    return result;
}

// 获取正反向控制
IVS_INT32 CDevEnumXML::GetPosNegDirCtlEnum(const IVS_CHAR* posNegDirectControl)
{

    IVS_INT32 iRet = 1;
    CHECK_POINTER(posNegDirectControl, iRet);
    //const std::string strPosNegDirectControl[] = {"BACK", "FORWARD"};
    if (0 == strcmp("BACK", posNegDirectControl))
    {
        iRet = 0;
    }

    return iRet;

}

// 获取码率类型
IVS_INT32 CDevEnumXML::GetBitRateTypeEnum(const IVS_CHAR* bitRateType)
{
	CHECK_POINTER(bitRateType, IVS_OPERATE_MEMORY_ERROR);

    IVS_INT32 iRet = -1;

    if (0 == strcmp("CBR", bitRateType))
    {
        iRet = BITRATE_CBR;
    }
    else if (0 == strcmp("VBR", bitRateType))
    {
        iRet = BITRATE_VBR; 
    }

    return iRet;
}

// 获取编码格式为MJPEG的Profile
IVS_INT32 CDevEnumXML::GetMjpegProfileEnum(const IVS_CHAR* profile)
{
	CHECK_POINTER(profile, IVS_OPERATE_MEMORY_ERROR);

    IVS_INT32  iRet = -1;

    if (0 == strcmp("SP", profile))
    {
        iRet = MJPEG_PROFILE_SP;
    }
    else if (0 == strcmp("ASP", profile))
    {
        iRet =  MJPEG_PROFILE_ASP; 
    } 

    return  iRet;
}

// 获取主设备协议类型
const IVS_CHAR *CDevEnumXML::GetDevProtocolTypeCH(IVS_INT32 typeCode)
{

	const IVS_CHAR* result = "";
	switch (typeCode)
	{
	case DEVICE_PRO_TEYES:
		result ="TEYES";
		break;
	case DEVICE_PRO_ONVIF:
		result ="ONVIF";
		break;
	case DEVICE_PRO_HUAWEI:
		result ="HWSDK";
		break;
	case DEVICE_PRO_HIK:
		result ="HIKSDK";
		break;
	default:
		result = "-1";
		break;
	}

	return result;
}

// 获取主设备协议类型
IVS_INT32 CDevEnumXML::GetDevProtocolTypeEnum( const IVS_CHAR* typeCode )
{
	CHECK_POINTER(typeCode, IVS_OPERATE_MEMORY_ERROR);

	IVS_INT32  iRet = -1;

	if (0 == strcmp("TEYES", typeCode))
	{
		iRet = DEVICE_PRO_TEYES;
	}
	else if (0 == strcmp("ONVIF", typeCode))
	{
		iRet =  DEVICE_PRO_ONVIF; 
	} 
	else if (0 == strcmp("HWSDK", typeCode))
	{
		iRet =  DEVICE_PRO_HUAWEI; 
	}
	else if (0 == strcmp("HIKSDK", typeCode))
	{
		iRet =  DEVICE_PRO_HIK; 
	}

	return  iRet;
}

// 获取主设备提供商类型
const IVS_CHAR *CDevEnumXML::GetDevVendorTypeCH(IVS_INT32 typeCode)
{
	const IVS_CHAR* result = "";
	switch (typeCode)
	{
	case VENDOR_HUAWEI:
		result ="HUAWEI";
		break;
	case VENDOR_HIKVISION:
		result ="HIK";
		break;
	case VENDOR_DAHUA:
		result ="DAHUA";
		break;
// 	case DEVICE_PRO_HIK:
// 		result ="HIKSDK";
// 		break;
	default:
		result = "-1";
		break;
	}

	return result;
}

// 获取主设备提供商类型
IVS_INT32 CDevEnumXML::GetDevVendorTypeEnum( const IVS_CHAR* typeCode )
{
	CHECK_POINTER(typeCode, IVS_OPERATE_MEMORY_ERROR);

	IVS_INT32  iRet = -1;

	if (0 == strcmp("HUAWEI", typeCode))
	{
		iRet = VENDOR_HUAWEI;
	}
	else if (0 == strcmp("HIK", typeCode))
	{
		iRet =  VENDOR_HIKVISION; 
	} 
	else if (0 == strcmp("DAHUA", typeCode))
	{
		iRet =  VENDOR_DAHUA; 
	}

	return  iRet;
}

//获取串口类型
IVS_INT32 CDevEnumXML::GetSerialTypeEnum( const IVS_CHAR* typeCode )
{
	CHECK_POINTER(typeCode, IVS_OPERATE_MEMORY_ERROR);

	IVS_INT32  iRet = -1;

	if (0 == strcmp("RS232", typeCode))
	{
		iRet = SERIAL_RS232;
	}
	else if (0 == strcmp("RS485", typeCode))
	{
		iRet =  SERIAL_RS485; 
	} 
	else if (0 == strcmp("RS422", typeCode))
	{
		iRet =  SERIAL_RS422; 
	}

	return  iRet;
}

//获取串口类型对应的字符串
const IVS_CHAR *CDevEnumXML::GetSerialTypeCH(IVS_INT32 typeCode)
{
	const IVS_CHAR* result = "";
	switch (typeCode)
	{
	case SERIAL_RS232:
		result ="RS232";
		break;
	case SERIAL_RS485:
		result ="RS485";
		break;
	case SERIAL_RS422:
		result ="RS422";
		break;
	default:
		result = "-1";
		break;
	}

	return result;
}

// 获取可靠传输类型从字符串到整形
IVS_INT32 CDevEnumXML::GetReliableTransTypeINT(const IVS_CHAR* pTransType)
{
	CHECK_POINTER(pTransType, IVS_OPERATE_MEMORY_ERROR);

	IVS_INT32 iRet = -1;
	IVS_INT32 iLen = sizeof(chTransType) / sizeof(chTransType[0]);
	for (int i = 0;i < iLen;i++)
	{
		if (0 == strcmp(chTransType[i], pTransType))
		{
			iRet = i;
			break;
		}
	}
	
	BP_RUN_LOG_INF("Get ReliableTransType", "resolution=%d",iRet);	
	
	return iRet;
}

// 获取可靠传输类型从整形到字符串
const IVS_CHAR* CDevEnumXML::GetReliableTransTypeCHAR(IVS_INT32 iTransType)
{
	const IVS_CHAR* result = "";
	switch(iTransType)
	{
	case RELIABLE_TRANSMISSION_NONE:
		result = "NONE";
		break;
	case RELIABLE_TRANSMISSION_FEC:
		result = "FEC";
		break;
	case RELIABLE_TRANSMISSION_ARQ:
		result = "ARQ";
		break;
	case RELIABLE_TRANSMISSION_HARQ:
		result = "HARQ";
		break;
	default:
		{
			BP_RUN_LOG_ERR(IVS_OPERATE_MEMORY_ERROR, "iTransType fail", "NA");
			result = NULL;
		}	
		break;
	}

	return result;
}

// 获取数据格式类型从字符串到整形
IVS_INT32 CDevEnumXML::GetDataFormatINT(const IVS_CHAR* pDataFormat)
{
	CHECK_POINTER(pDataFormat, IVS_OPERATE_MEMORY_ERROR);
	IVS_INT32 iRet = -1;
	IVS_INT32 iLen = sizeof(chDataFormat)/sizeof(chDataFormat[0]);
	for (int i = 1; i < iLen; i++)
	{
		if (0 == strcmp(chDataFormat[i], pDataFormat))
		{
			iRet = i;
			break;
		}
	}
	BP_RUN_LOG_INF("Get DataFormat", "resolution=%d",iRet);
	return iRet;
}

// 获取数据格式类型从整形到字符串
const IVS_CHAR* CDevEnumXML::GetDataFormatCHAR(IVS_INT32 iDataFormat)
{
	const IVS_CHAR* result = "";
	switch(iDataFormat)
	{
	case PAY_AUDIO_LOAD_TYPE_PCMA:
		result = "G711A";
		break;
	case PAY_AUDIO_LOAD_TYPE_PCMU:
		result = "G711U";
		break;
	case PAY_AUDIO_LOAD_TYPE_G726:
		result = "G726";
		break;
	case PAY_AUDIO_LOAD_TYPE_AAC:
		result = "AAC";
		break;
	default:
		{
			BP_RUN_LOG_ERR(IVS_XML_INVALID, "iDataFormat fail", "NA");
			result = NULL;
		}
		break;
	}
	return result;
}

// 获取摄像机类型
const IVS_CHAR* CDevEnumXML::GetCameraTypeEnum(IVS_INT32 iCameraType)
{
	const IVS_CHAR* result = "";
	switch(iCameraType)
	{
	case CAMERA_FIX:
		result = "FIX";
		break;
	case CAMERA_PTZ:
		result = "PTZ";
		break;
	case CAMERA_DOME:
		result = "DOME";
		break;
	case CAMERA_FIX_DOME:
		result = "FIX_DOME";
		break;
	default:
		{
			BP_RUN_LOG_ERR(IVS_FAIL, "iCameraType fail", "NA");
			result = NULL;
		}
		break;
	}
	return result;
}

// 获取通用是否存在
const IVS_CHAR* CDevEnumXML::GetCommIsOrNotType(IVS_INT32 iType)
{
	if (iType)
	{
		return chIsOrNot[1];
	}

	return chIsOrNot[0];
}

// 获取网络类型
const IVS_CHAR* CDevEnumXML::GetNetType(IVS_INT32 iNetType)
{
	const IVS_CHAR* result = "";
	switch(iNetType)
	{
	case NET_TYPE_LAN:
		result = "LAN";
		break;
	case NET_TYPE_WAN:
		result = "WLAN";
		break;
	default:
		{
			BP_RUN_LOG_ERR(IVS_FAIL, "iNetType fail", "NA");
			result = NULL;
		}
		break;
	}
	return result;
}

// 获取随路音频
const IVS_CHAR* CDevEnumXML::GetVoiceInEnable(IVS_INT32 iVoiceInEnable)
{
	const IVS_CHAR* result = "";
	switch(iVoiceInEnable)
	{
	case 0:
		result = "0";
		break;
	case 1:
		result = "1";
		break;
	default:
		{
			BP_RUN_LOG_ERR(IVS_FAIL, "iVoiceInEnable fail", "NA");
			result = NULL;
		}
		break;
	}
	return result;
}

// 获取设备配置大小
IVS_UINT32 CDevEnumXML::GetSizeOfConfigType(IVS_UINT32 uiConfigType)
{
	IVS_UINT32 iSize = sizeof(chSizeOfConfigType)/sizeof(chSizeOfConfigType[0]);
	if (uiConfigType >= iSize)
	{
		return 0;
	}
	return chSizeOfConfigType[uiConfigType]; 
}

// 获取通用模式
IVS_INT32 CDevEnumXML::GetCommMode(const IVS_CHAR* pCommMode)
{
	IVS_INT32 iRet = 0;
	IVS_INT32 iLen = sizeof(chCommMode)/sizeof(chCommMode[0]);
	for (IVS_INT32 i = 0; i != iLen ; i ++)
	{
		if (0 == strcmp(chCommMode[i], pCommMode))
		{
			iRet = i;
		}
	}

	return iRet;
}

// 获取曝光优先
IVS_INT32 CDevEnumXML::GetExposurePriority(const IVS_CHAR* pExposurePriority)
{
	IVS_INT32 iRet = 0;
	IVS_INT32 iLen = sizeof(chExposurePriority)/sizeof(chExposurePriority[0]);
	for (IVS_INT32 i = 0; i != iLen ; i ++)
	{
		if (0 == strcmp(chExposurePriority[i], pExposurePriority))
		{
			iRet = i;
		}
	}

	return iRet;
}

// 获取通用过滤模式
IVS_INT32 CDevEnumXML::GetCommExImgMode(const IVS_CHAR* pCommExImgMode)
{
	IVS_INT32 iRet = 0;
	IVS_INT32 iLen = sizeof(chCommExImgMode)/sizeof(chCommExImgMode[0]);
	for (IVS_INT32 i = 0; i != iLen ; i ++)
	{
		if (0 == strcmp(chCommExImgMode[i], pCommExImgMode))
		{
			iRet = i;
		}
	}

	return iRet;
}

// 获取曝光优先
const IVS_CHAR* CDevEnumXML::GetExposurePriorityStr(IVS_INT32 iExposurePriority)
{
	IVS_INT32 iLen = sizeof(chExposurePriority)/sizeof(chExposurePriority[0]);
	for (IVS_INT32 i = 0; i != iLen; i++)
	{
		if (iExposurePriority == i)
		{
			return chExposurePriority[i];
		}
	}

	return chExposurePriority[0];
}

// 获取通用模式
const IVS_CHAR* CDevEnumXML::GetCommModeStr(IVS_INT32 iCommMode)
{
	IVS_INT32 iLen = sizeof(chCommMode)/sizeof(chCommMode[0]);
	for (IVS_INT32 i = 0; i != iLen; i++)
	{
		if (iCommMode == i)
		{
			return chCommMode[i];
		}
	}
	return chCommMode[0];
}

// 获取通用过滤模式
const IVS_CHAR* CDevEnumXML::GetCommExImgModeStr(IVS_INT32 iCommExImgMode)
{
	IVS_INT32 iLen = sizeof(chCommExImgMode)/sizeof(chCommExImgMode[0]);
	for (IVS_INT32 i = 0; i != iLen; i++)
	{
		if (i == iCommExImgMode)
		{
			return chCommExImgMode[i];
		}
	}
	return chCommExImgMode[0];
}
